// Inkludera nödvändiga bibliotek och filen "sampler.h".
#include "sampler.h"
#include <driver/adc.h>
#include "esp_timer.h"
#include <esp_log.h>

// Variabler för att konfigurera ADC-sampling.
static esp_timer_handle_t timer_handle;
static const adc_channel_t channel = ADC_CHANNEL_6;
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static int DEFAULT_VREF = 1100;
static int sample = 1100;
static int previous = 0;
static int counter = 0;

// Hanterar avbrott från ADC-sampling.
void IRAM_ATTR isr_handler(void* arg) {
    previous = sample;
    sample = adc1_get_raw(channel);

    // Räkna antal övergångar över/under referensspänningen för att beräkna frekvens.
    if ((sample < DEFAULT_VREF && previous > DEFAULT_VREF) ||
        (sample > DEFAULT_VREF && previous < DEFAULT_VREF)) {
        counter++;
    }
}

/**
* Startar samplande på en given pinne (GPIO34) med en given frekvens.
* Parameter freq: samplingsfrekvensen
*/
void startSampling(int freq) {
    // Konfigurera ADC-inställningar.
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);

    // Konfigurera timer-avbrott.
    esp_timer_create_args_t timer_config = {
        .callback = isr_handler,
        .name = "sample_timer"
    };

    esp_timer_create(&timer_config, &timer_handle);
    esp_timer_start_periodic(timer_handle, 1000000 / freq); // Konvertera frekvens till mikrosekunder.
}

/**
* Stoppar samplande processen.
*/
void stopSampling() {
    esp_timer_stop(timer_handle);
}

/**
* Återställer frekvensdetektering utan att stoppa samplingsprocessen.
*/
void resetSampling() {
    counter = 0;
}

/**
* Beräknar den genomsnittliga frekvensen av signalen som samplats (eller samplas).
*/
float getFrequency() {
    // Frekvensen är hälften av antalet övergångar över/under referensspänningen per sekund.
    float freq = counter / 2.0;
    return freq;
}
