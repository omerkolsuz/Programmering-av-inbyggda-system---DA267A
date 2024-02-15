// @author Ömer Kolsuz & Oscar Svantesson

#include <stdio.h>
#include <esp_task_wdt.h>
#include <esp_timer.h>
#include "Sampler.h"
#include "Notes.h"
#include "Pins.h"
#include <driver/gpio.h>

#define ESP_INTR_FLAG_DEFAULT 0
#define PUSH_TIME_US 250000 // == 250ms
static volatile uint64_t lastPush = -PUSH_TIME_US;
static volatile float fr;
int currentNote = 0;

// Funktion som hanterar knapptryckningar
static void buttonPress_handler(void *arg) {
    uint64_t now = esp_timer_get_time();
    if ((now - lastPush) > PUSH_TIME_US) {
        lastPush = now;
        currentNote = (currentNote + 1) % 6; // Modulo 6 för att cykla mellan 0 och 5
    }
}

// Funktion för att sätta LED-lampor baserat på frekvensområde
void setLeds(float freq, float min, float max) {
    switch (true) {
        case (freq >= min && freq <= max):
            setLED(12, 1);
            setLED(14, 1);
            break;
        case (freq < min):
            setLED(12, 1);
            break;
        case (freq > max):
            setLED(14, 1);
            break;
    }
}

// Huvudfunktionen för programmet
void app_main(){
    // Initialisera pinnar och knapptryckningshanterare
    initLEDPin(12);
    initLEDPin(14);
    initButtonPin(18);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(18, buttonPress_handler, NULL);
    vTaskDelay(pdMS_TO_TICKS(5000));

    // Visa meddelanden på seriell terminal och styr LED-lampor
    printf("Blue led = noten är för låg \n");
    setLED(12, 1);
    setLED(14, 0);
    vTaskDelay(pdMS_TO_TICKS(4000));

    printf("Red led = noten är för hög \n");
    setLED(12, 0);
    setLED(14, 1);
    vTaskDelay(pdMS_TO_TICKS(4000));

    // Blinka LED-lampor för att indikera inledningen av avläsning
    for (int i = 0; i < 5; i++) {
        setLED(12, 1);
        setLED(14, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        setLED(12, 0);
        setLED(14, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    // Huvudloop
    while (1) {
        // Stäng av LED-lampor och vänta 2 sekunder
        setLED(12, 0);
        setLED(14, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Starta sampling och vänta 1 sekund
        startSampling(6000);
        vTaskDelay(pdMS_TO_TICKS(1000));
        stopSampling();
        fr = getFrequency(); // Hämta frekvens från sensorn

        // Beroende på nuvarande not, ställ in LED-lampor och skriv ut meddelanden
    if (currentNote == 0) {
        //Not: E4, Frekvens : 329.63 Hz
        printf("Blinkande blå LED = Tonen är för låg\n");
        printf("Blinkande röd LED = Tonen är för hög\n");
        printf("\n--------------\n");
        printf("Aktuell ton: E4\n");
        setLeds(fr, 326.63, 332.63); // Ställer in LED-lamporna baserat på den uppmätta frekvensen.
        printf("Frekvens: %.2f Hz\n", fr); // Skriver ut den uppmätta frekvensen med två decimaler.
        printf("--------------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Väntar i 2 sekunder innan nästa åtgärd.
        resetSampling(); // Återställer sensorn för nästa mätning.
    }
    else if (currentNote == 1) {
        // Not: B3, Frekvens: 246.94 Hz
        printf("Blinkande blå LED = Tonen är för låg\n");
        printf("Blinkande röd LED = Tonen är för hög\n");
        printf("\n--------------\n");
        printf("Aktuell ton: B3\n");
        setLeds(fr, 243.94, 249.94); // Anpassar LED-lamporna baserat på den uppmätta frekvensen.
        printf("Frekvens: %.2f Hz\n", fr); // Skriver ut den uppmätta frekvensen med två decimaler.
        printf("--------------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Väntar i 2 sekunder innan nästa åtgärd.
        resetSampling(); // Återställer sensorn för nästa mätning.
    }
    else if (currentNote == 2) {
        // Not: G3, Frekvens: 196.00 Hz
        printf("Blinkande blå LED = Tonen är för låg\n");
        printf("Blinkande röd LED = Tonen är för hög\n");
        printf("\n--------------\n");
        printf("Aktuell ton: G3\n");
        setLeds(fr, 193.00, 199.00); // Anpassar LED-lamporna baserat på den uppmätta frekvensen.
        printf("Frekvens: %.2f Hz\n", fr); // Skriver ut den uppmätta frekvensen med två decimaler.
        printf("--------------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Väntar i 2 sekunder innan nästa åtgärd.
        resetSampling(); // Återställer sensorn för nästa mätning.

    }
    else if (currentNote == 3) {
        // Not: D3, Frekvens: 146.83 Hz
        printf("Blinkande blå LED = Tonen är för låg\n");
        printf("Blinkande röd LED = Tonen är för hög\n");
        printf("\n--------------\n");
        printf("Aktuell ton: D3\n");
        setLeds(fr, 143.83, 149.83); // Anpassar LED-lamporna baserat på den uppmätta frekvensen.
        printf("Frekvens: %.2f Hz\n", fr); // Skriver ut den uppmätta frekvensen med två decimaler.
        printf("--------------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Väntar i 2 sekunder innan nästa åtgärd.
        resetSampling(); // Återställer sensorn för nästa mätning.

    }
    else if (currentNote == 4) {
       // Not: A2, Frekvens: 110.00 Hz
        printf("Blinkande blå LED = Tonen är för låg\n");
        printf("Blinkande röd LED = Tonen är för hög\n");
        printf("\n--------------\n");
        printf("Aktuell ton: A2\n");
        setLeds(fr, 107.00, 113.00); // Anpassar LED-lamporna baserat på den uppmätta frekvensen.
        printf("Frekvens: %.2f Hz\n", fr); // Skriver ut den uppmätta frekvensen med två decimaler.
        printf("--------------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Väntar i 2 sekunder innan nästa åtgärd.
        resetSampling(); // Återställer sensorn för nästa mätning.

    }
    else if (currentNote == 5) {
        // Not: E2, Frekvens: 82.41 Hz
        printf("Blinkande blå LED = Tonen är för låg\n");
        printf("Blinkande röd LED = Tonen är för hög\n");
        printf("\n--------------\n");
        printf("Aktuell ton: E2\n");
        setLeds(fr, 79.41, 85.41); // Anpassar LED-lamporna baserat på den uppmätta frekvensen.
        printf("Frekvens: %.2f Hz\n", fr); // Skriver ut den uppmätta frekvensen med två decimaler.
        printf("--------------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Väntar i 2 sekunder innan nästa åtgärd.
        resetSampling(); // Återställer sensorn för nästa mätning.

    }
}
}