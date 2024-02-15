// Author Oscar Svantesson, Ömer Kolcuz
#include <esp_pm.h>
#include <esp_task_wdt.h>
#include <math.h>
#include <stdio.h>
#include "i2C.h"
#include "circular_buffer.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include <esp_sleep.h>
#include <driver/i2c.h>

#define SAMPLING_PERIOD 100
#define BUFF_SIZE 50
#define ALGO_PERIOD 3000
#define MIN_SD 500
#define K 1.1
#define MIN_INTRA_STEP_TIME 300
#define STEPS_GOAL 15
#define LED_PIN 26
#define BUTTON_PIN 14

SemaphoreHandle_t xSemaphore = NULL;
SemaphoreHandle_t buttonPressedSemaphore = NULL;
struct circularBuffer buffer;
int step_count = 0;

// Constants for LED blinking
#define LED_BLINK_DELAY pdMS_TO_TICKS(200)
#define LED_BLINK_COUNT 3

// Task to sample accelerometer data and add it to a circular buffer
static void sampling_task(void *arg) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        u_int32_t acc = getMagnitude();
        addElement(&buffer, acc);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SAMPLING_PERIOD));
    }
}

// Task to process the accelerometer data and count steps
static void algo_task(void *arg) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        u_int32_t size = getsize(&buffer);
        u_int32_t tail = buffer.tail;
        double sd = 0;
        double mean = 0;
        if (size > 0) {
            for (int i = buffer.head; i != tail; i = modulus_inc(buffer.maxLength, i)) {
                mean += buffer.data[i];
            }
            mean = (mean / (double)size);
            for (int i = buffer.head; i != tail; i = modulus_inc(buffer.maxLength, i)) {
                sd += pow((buffer.data[i] - mean), 2);
            }
            sd = sqrt((sd / (double)size));
            if (sd < MIN_SD) sd = MIN_SD;
            u_int32_t sample;
            u_int32_t lastStepTS = -MIN_INTRA_STEP_TIME;
            for (int i = 0; i < size; i++) {
                sample = removeHead(&buffer);
                if (sample > mean + K * sd) {
                    if (i * SAMPLING_PERIOD - lastStepTS > MIN_INTRA_STEP_TIME) {
                        step_count++;
                        lastStepTS = i * SAMPLING_PERIOD;
                    }
                }
            }
        }
        printf("Steps: %d\n", step_count);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(ALGO_PERIOD));
    }
}

void led_task(void *arg) {
    while (1) {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            if (step_count >= STEPS_GOAL) {
                for (int i = 0; i < LED_BLINK_COUNT; i++) {
                    gpio_set_level(LED_PIN, 1);
                    vTaskDelay(LED_BLINK_DELAY);
                    gpio_set_level(LED_PIN, 0);
                    vTaskDelay(LED_BLINK_DELAY);
                }
            }
        }
    }
}

// Interrupt handler for the button press event
void button_handler(void *arg) {
    xSemaphoreGiveFromISR(xSemaphore, NULL);
}

void app_main() {
    esp_pm_config_t light_sleep_config = {
        .max_freq_mhz = 80,
        .min_freq_mhz = 15,
        .light_sleep_enable = 1,
    };

    esp_err_t err = esp_pm_configure(&light_sleep_config);

    buttonPressedSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(led_task, "led_task", 2048, NULL, 10, NULL);

    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);

    gpio_isr_handler_add(BUTTON_PIN, button_handler, NULL);

    int *data = (int *)malloc(BUFF_SIZE * sizeof(int));

    initCircularBuffer(&buffer, data, BUFF_SIZE);
    init();

    xTaskCreate(sampling_task, "sampling", 2048, NULL, 1, NULL);
    xTaskCreate(algo_task, "algo", 2048, NULL, 0, NULL);
}
