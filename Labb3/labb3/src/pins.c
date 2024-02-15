// Inkluderar nödvändiga bibliotek och filen "pins.h".
#include "pins.h"
#include <driver/gpio.h>

/* Funktion för att initialisera en LED-pinne */
void initLEDPin(uint8_t pinN) {
    gpio_config_t io_confD1;
    io_confD1.mode = GPIO_MODE_OUTPUT; // Ange att pinnen används som en utgång.
    io_confD1.pin_bit_mask = (u_int64_t)1 << pinN; // Ange vilken pinne som ska konfigureras.
    gpio_config(&io_confD1); // Utför konfigurationen för pinnen.
}

/* Funktion för att initialisera en knapp-pinne */
void initButtonPin(uint8_t pinN) {
    gpio_config_t io_confB1;
    io_confB1.mode = GPIO_MODE_INPUT; // Ange att pinnen används som en ingång.
    io_confB1.pin_bit_mask = (u_int64_t)1 << pinN; // Ange vilken pinne som ska konfigureras.
    io_confB1.pull_up_en = 1; // Aktivera pull-up resistor.
    io_confB1.pull_down_en = 0; // Inaktivera pull-down resistor.
    io_confB1.intr_type = GPIO_INTR_NEGEDGE; // Ange typ av avbrott vid negativ flank.
    gpio_config(&io_confB1); // Utför konfigurationen för pinnen.
}

/* Funktion för att slå på eller av en LED baserat på nivån (level) */
void setLED(uint8_t pinN, uint8_t level) {
    if (level) {
        gpio_set_level(pinN, 1); // Slå på lampan genom att sätta pinnen till hög (1).
    } else {
        gpio_set_level(pinN, 0); // Slå av lampan genom att sätta pinnen till låg (0).
    }
}
