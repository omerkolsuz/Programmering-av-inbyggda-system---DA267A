//@author Ömer Kolsuz & Oscar Svantesson

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <esp32/rom/ets_sys.h>
#include "circular_buffer.h"
#include <limits.h>
#define BUFFER_SIZE 4

void blackboxTest1()
{
    printf("Running Blackbox Test 1\n");

    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    // Add an element to the circular buffer
    int addedElement = addElement(&buffer, 1);

    // Print the buffer content
    printf("Buffer after adding an element:\n");
    printBuffer(&buffer);

    // Remove one element from the circular buffer
    int removedElement = removeHead(&buffer);

    // Print the buffer content after removal
    printf("\nBuffer after removing an element:\n");
    printBuffer(&buffer);

    // Check if the added and removed elements are the same
    if (addedElement == removedElement)
    {
        printf("\nAdded and removed elements are the same: %d\n", addedElement);
    }
    else
    {
        printf("\nAdded and removed elements are different.\n");
    }
    // Free allocated memory
    free(buffer_data);
}

void blackboxTest2()
{

    printf("Running Blackbox Test 2\n");

    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    // Add an element to the circular buffer
    int addedElement = addElement(&buffer, 1);
    int addedElement2 = addElement(&buffer, 2);

    // Print the buffer content
    ets_delay_us(2000000ul);
    printf("Buffer after adding an element:\n ");
    printBuffer(&buffer);

    // Remove one element from the circular buffer
    int removedElement = removeHead(&buffer);
    int removedElement2 = removeHead(&buffer);

    // Print the buffer content after removal
    ets_delay_us(2000000ul);
    printf("\nBuffer after removing an element:\n");
    printBuffer(&buffer);

    // Check if added and removed elements are in the same order
    if (addedElement == removedElement && addedElement2 == removedElement2)
    {
        printf("\nAdded and removed elements are in the same order.\n");
    }
    else
    {
        printf("\nAdded and removed elements are NOT in the same order.\n");
    }

    // Free allocated memory
    free(buffer_data);
}

void blackboxTest3()
{
    printf("Running Blackbox Test 3\n");

    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    int addedElement = addElement(&buffer, 15);
    int addedElement2 = addElement(&buffer, 36);

    // Print the buffer content
    ets_delay_us(2000000ul);
    printf("Buffer after adding an element:\n ");
    printBuffer(&buffer);

    int removedElement = removeHead(&buffer);
    int removedElement2 = removeHead(&buffer);

    // Print the buffer content
    printf("Buffer after removing an element:\n ");
    printBuffer(&buffer);

    // Free allocated memory
    free(buffer_data);
}

void blackboxTest4()
{
    printf("Running Blackbox Test 4\n");

    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    int addedElement = addElement(&buffer, 7);
    int addedElement2 = addElement(&buffer, 9);
    int addedElement3 = addElement(&buffer, 29);
    int addedElement4 = addElement(&buffer, 50);

    // Print the buffer content
    printf("Buffer after adding an element:\n ");
    printBuffer(&buffer);

    // Check if the last added element overwrote the first added element
    if (addedElement == addedElement4)
    {
        printf("\nThe last added element overwrote the first added element.\n");
    }
    else
    {
        printf("\nThe last added element did not overwrite the first added element.\n");
    }

    // Free allocated memory
    free(buffer_data);
}
void blackboxTest5()
{
    printf("Running Blackbox Test 5\n");

    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    int addedElement = addElement(&buffer, 7);
    int addedElement2 = addElement(&buffer, 9);
    int addedElement3 = addElement(&buffer, 29);
    int addedElement4 = addElement(&buffer, 50);

    printf("Buffer after adding an element:\n ");
    printBuffer(&buffer);
    printf("\n ");

    int removedElement = removeHead(&buffer);
    printf("\nAfter removing 1 element \n");
    printBuffer(&buffer);
    printf("\n ");

    int removedElement2 = removeHead(&buffer);
    printf("\nAfter removing 2 element\n");
    printBuffer(&buffer);
    printf("\n ");

    int removedElement3 = removeHead(&buffer);
    printf("\nAfter removing 3 element\n");
    printBuffer(&buffer);
    printf("\n ");

    int removedElement4 = removeHead(&buffer);
    printf("\nAfter removing 4 element\n");
    printBuffer(&buffer);
    printf("\n ");

    printf("\nBuffer after removing an element:\n ");
    printBuffer(&buffer);
    printf("\n ");

    // Check if added and removed elements are in the same order
    if (addedElement == removedElement && addedElement2 == removedElement2 && addedElement3 == removedElement3 && addedElement4 == removedElement4)
    {
        printf("\nAdded and removed elements are in the same order.\n");
    }
    else
    {
        printf("\nAdded and removed elements are NOT in the same order.\n");
    }

    // Free allocated memory
    free(buffer_data);
}
void blackboxTest6()
{

    printf("Running Blackbox Test 6\n");

    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    int addedElement = addElement(&buffer, 7);
    int val = contains(&buffer, 7);
    printf("Nbr of elements in buffer: %d \n", val);
    printf("\n\n\n");
}
// Den här metoden lägger en element till bufferten och sedan kollar om bufferten innehåller en element med samma värde.
void blackboxTest7()
{
    struct circularBuffer buffer;
    int buffer_data = (int)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    int addElements1 = addElement(&buffer, 20);
    printf("\n I bufferten lades till: \n");
    printBuffer(&buffer);

    int containsmetod = contains(&buffer, 20);
    if (containsmetod == INT_MIN)
    {
        printf("\n Bufferten innehåller inte det värdet du vill hitta \n");
    }
    else
    {
        printf("\n Buffert innehåller: %d \n" + containsmetod);
    }
    free(buffer_data);
}
// Den här metoden lägger till två element. Sedan kollar man ifall bufferten innehåller värdet på den andra elementen som du la till.
void blackboxTest8()
{
    struct circularBuffer buffer;
    int buffer_data = (int)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    int addElements1 = addElement(&buffer, 1);
    int addElements2 = addElement(&buffer, 2);
    printf("\n I bufferten lades till: \n");
    printBuffer(&buffer);

    int containsmetod = contains(&buffer, 2);
    if (containsmetod == INT_MIN)
    {
        printf("\n Bufferten innehåller inte det värdet \n");
    }
    else
    {
        printf("\n Buffert innehåller: %d \n" + containsmetod);
    }
    free(buffer_data);
}
void blackboxTest9()
{
    struct circularBuffer buffer;
    int buffer_data = (int)malloc(BUFFER_SIZE * sizeof(int)); // memory allocation (malloc)
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    // adding some random number to buffer
    int addElements1 = addElement(&buffer, 35);
    int addElements2 = addElement(&buffer, 77);
    int addElements3 = addElement(&buffer, 3);

    printf("\n I bufferten lades till: \n");
    printBuffer(&buffer);

    int containsmetod = contains(&buffer, 3);
    if (containsmetod == INT_MIN)
    {
        printf("\n Bufferten innehåller inte det värdet \n");
    }
    else
    {
        printf("\n Buffert innehåller: %d \n" + containsmetod);
    }

    free(buffer_data);
}
void whiteboxTest()
{
    struct circularBuffer buffer;
    int buffer_data = (int)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\nWhite Box Testing\n");
    if (buffer.maxLength == BUFFER_SIZE)
    {
        printf("maxLength == bufferSize\nSucess\n");
    }
    if (buffer.head == 0)
    {
        printf("head == 0\nSucess\n");
    }
    if (buffer.tail == 0)
    {
        printf("tail == 0\nSucess\n");
    }
    printf("White box test is done :)\n");

    // Free allocated memory
    free(buffer_data);
}

void app_main()
{
    printf("\n\n\n");
    printf("\n\n\n");

     blackboxTest1();
     blackboxTest2();
     blackboxTest3();
      blackboxTest4();
     blackboxTest5();
     blackboxTest6();
     blackboxTest7();
      blackboxTest8();
     blackboxTest9();
    whiteboxTest();

    printf("\n\n\n");
}
