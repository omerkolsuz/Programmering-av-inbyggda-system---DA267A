//Author Ömer Kolsuz, Oscar Svantesson
#include "random.h"
#include <esp_random.h>
//Generates random number
int getRandomsecs(int min, int max){
    return esp_random() %(max-min +1) + min;
}
