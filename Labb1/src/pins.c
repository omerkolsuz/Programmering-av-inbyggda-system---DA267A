//Author Ömer Kolsuz, Oscar Svantesson

#include "pins.h"
#include "driver/gpio.h"
/* initialises the 4 pins */

// here we gonna initialises the 4 pins which we are gonna use one the board /Oscar & Ömer

#define ledA 33    // yellow led
#define ledB 25    // white led
#define buttonA 26 // green button
#define buttonB 27 // blue button

void initPins()
{

    // init the 2 LEDs pins as output and the 2 buttons' pins as input
    // you will need to use gpio_config()
    gpio_config_t config; // here we creating config structe

    // ledA pin33
    config.pin_bit_mask = (u_int64_t)1 << ledA;
    config.mode = GPIO_MODE_OUTPUT; // here we setting ledA to output
    config.pull_down_en = 0;
    config.pull_up_en = 0;

    gpio_config(&config);

    // ledB pin25
    config.pin_bit_mask = (u_int64_t)1 << ledB;
    config.mode = GPIO_MODE_OUTPUT;
    //config.pull_down_en = 0;
    //config.pull_up_en = 0;
    gpio_config(&config);

    // ButtonA
    config.pin_bit_mask = (u_int64_t)1 << buttonA;
    config.mode = GPIO_MODE_INPUT; // here we setting buttonA to input
    config.pull_down_en = 0;
    config.pull_up_en = 1;
    gpio_config(&config);

    // ButtonB
    config.pin_bit_mask = (u_int64_t)1 << buttonB;
    config.mode = GPIO_MODE_INPUT; // here we setting buttonA to input
   // config.pull_down_en = 0;
   // config.pull_up_en = 1;
    gpio_config(&config);
}
/* switches LED A on if level!=0 or off if level==0*/
void setLEDA(uint8_t level)
{
    gpio_set_level(ledA, level);
  //Used in earlier steps, not used in last step
   // if (level)
   // {
        // set the pin of LED A to ON
        // you probably need to use gpio_set_level()
  
   // }
   // else
   // {
     //   gpio_set_level(ledB, level);
        // set the pin of LED A to OFF
    //}
}
/* switches LED B on if level!=0 or off if level==0*/
void setLEDB(uint8_t level)
{
      gpio_set_level(ledB, level);
    //not used in last step
   // if (level)
 //   {
        // set the pin of LED A to ON
        // you probably need to use gpio_set_level()
     
   // }
  //  else
   // {
    //    gpio_set_level(ledA, level);
        // set the pin of LED A to OFF
  //  }
}
// same as setLEDA()

/* tells if button A is currently being pressed /
uint8_t isButtonAPressed()
{
// read the value of button A
// if using a pull-up, the button is pressed when the pin is LOW
return 0; // return 1 if A is pressed, 0 otherwise
}
/ tells if button A is currently being pressed */

uint8_t isButtonAPressed()
{
    return !gpio_get_level(buttonA);
}

uint8_t isButtonBPressed()
{
    // same as with button A, but another pin
    return !gpio_get_level(buttonB);
}