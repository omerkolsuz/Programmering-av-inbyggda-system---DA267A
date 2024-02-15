// Author Ömer Kolsuz & Oscar Svantesson
// Date 6/9/2023
#include <esp_task_wdt.h>

#include "pins.h"
#include "random.h"
int i;
/*
Waits for "millis" milliseconds without upsetting the watchdog timer
*/
void waitMs(unsigned int millis)
{
    TickType_t delay = millis / portTICK_PERIOD_MS;
    vTaskDelay(delay);
}

/*
Starts the game by making the leds shift in random speed. In the end both the leds are on.
*/
void startGame()
{
    for (i = 0; i < 10; i++)
    {

        setLEDA(1);
        setLEDB(1);
        waitMs(100);
        setLEDA(0);
        setLEDB(0);
        waitMs(100);
    }
    int randomly = getRandomsecs(1000, 10000);
    waitMs(randomly);
    setLEDA(1);
    setLEDB(1);
}
//Reads from the 2 buttons and the winners led is on and the losers is off. 
void app_main()
{
    initPins();
    while (1)
    {
        // signal that the game is about to start
        startGame();
        uint8_t winner = 0;
        if (isButtonAPressed())
        {
            winner = 2;
        }
        else if (isButtonBPressed())
        {
            winner = 1;
        }
        while (!winner)
        {
            // check if either button A or B are pressed
            if (isButtonAPressed())
            {
                printf("Winner player A");
                winner = 2;
            }
            else if (isButtonBPressed())
            {
                winner = 1;
                printf("Winner player B");
            }
        }
        if (winner == 1)
        {
            setLEDB(1);
            setLEDA(0);
        }
        else if (winner == 2)
        {
            setLEDA(1);
            setLEDB(0);
        }

        waitMs(3000);
        setLEDA(0);
        setLEDB(0);
    }
}
