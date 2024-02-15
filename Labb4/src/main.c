//Author: Oscar Svantesson, Ömer Kolsuz
#include <stdio.h>
#include <stdlib.h>
#include <esp_task_wdt.h>
#include<esp32/rom/ets_sys.h>

#include "single_linked_list.h"
#include "double_linked_list.h"


void testDoubleLinkedList1() {
    printf("Double linked list test 1\n");
    printf("-----------------------\n");
    // Create a double linked list
    struct doubleLinkedList doubleList;
    initDoubleLinkedList(&doubleList);

    // Add two elements
    addElementDoubleLinkedList(&doubleList, 5);
    addElementDoubleLinkedList(&doubleList, 3);

    // Print the double linked list
    struct doubleLinkedListElement* current = doubleList.first;
    printf("Double Linked List: \n");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Remove head
    removeFirstElementDoubleLinkedList(&doubleList);
 current = doubleList.first;
    printf("Double Linked List after head removed: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Add two elements
    addElementDoubleLinkedList(&doubleList, 7);
    addElementDoubleLinkedList(&doubleList, 2);
 current = doubleList.first;
    printf("Double Linked List after 2 elements added: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Remove two heads
    removeFirstElementDoubleLinkedList(&doubleList);
    removeFirstElementDoubleLinkedList(&doubleList);
 current = doubleList.first;
    printf("Double Linked List after 2 heads removed: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Print the double linked list again
    current = doubleList.first;
    printf("Double Linked List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Check if the list has one element left
    int isOneElementLeft = (doubleList.first != NULL && doubleList.first == doubleList.last);

    printf("Double Linked List has one element left: %s\n", isOneElementLeft ? "true" : "false");
        printf("\n");
        printf("-----------------------\n");
}
void testDoubleLinkedList2() {
    printf("Double linked list test 2\n");
    printf("-----------------------\n");
    struct doubleLinkedList dList;
    initDoubleLinkedList(&dList);

    printf("Double Linked List Test:\n");

    // Add two elements
    addElementDoubleLinkedList(&dList, 5);
    addElementDoubleLinkedList(&dList, 3);

    // Print elements
    struct doubleLinkedListElement* current = dList.first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Remove head (first) and then last
    removeFirstElementDoubleLinkedList(&dList);
    removeLastElementDoubleLinkedList(&dList);
printf("List after first and then last head removed:\n");
    // Print elements after removal
    current = dList.first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Add another element
    addElementDoubleLinkedList(&dList, 7);
printf("List after element added:\n");
    // Print elements after adding
    current = dList.first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
      printf("-----------------------\n");
}
void testDoubleLinkedList3() {
    printf("Double linked list test 3\n");
    printf("-----------------------\n");
    struct doubleLinkedList dList;
    initDoubleLinkedList(&dList);
    addElementDoubleLinkedList(&dList, 5);
    addElementDoubleLinkedList(&dList, 3);
    addElementDoubleLinkedList(&dList, 8);
    printf("Double linked list:\n");
     struct doubleLinkedListElement* current = dList.first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    int valueToSearch = 3;
    int searchResult = searchValueInDoubleLinkedList(&dList, valueToSearch);
    printf("Value to search: %d", valueToSearch);
    printf("\n");
    if (searchResult) {
        printf("Value %d found in the double linked list.\n", valueToSearch);
    } else {
        printf("Value %d not found in the double linked list.\n", valueToSearch);
    }
        printf("-----------------------\n");
}


void testDoubleLinkedList4(){
    printf("Double linked list test 4\n");
    printf("-----------------------\n");
      struct doubleLinkedList dList;
    initDoubleLinkedList(&dList);
    addElementDoubleLinkedList(&dList, 8);
    addElementDoubleLinkedList(&dList, 4);
    addElementDoubleLinkedList(&dList, 9);
    printf("Double linked list before sorting:\n");
struct doubleLinkedListElement* current = dList.first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

         sortDoubleLinkedList(&dList);
         current = dList.first;
         printf("Double linked list after sorting:\n");
           while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
        printf("\n");
    }
     printf("\n");
         printf("-----------------------\n");
}


void testSingleLinkedList1() {
     printf("Single linked list test 1\n");
    printf("-----------------------\n");
    struct singleLinkedList sList;
    initSingleLinkedList(&sList);

    // Add three elements to the single-linked list
    addElementSingleLinkedList(&sList, 5);
    addElementSingleLinkedList(&sList, 3);
    addElementSingleLinkedList(&sList, 8);

    // Print the elements in the list
    struct singleLinkedListElement* current = sList.first;
    printf("Elements in the single-linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Remove two elements from the list
    int removedValue1 = removeFirstElementSingleLinkedList(&sList);
    int removedValue2 = removeLastElementSingleLinkedList(&sList);

    printf("Removed elements: %d, %d\n", removedValue1, removedValue2);

    // Print the elements in the modified list
    current = sList.first;
    printf("Elements in the modified single-linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    printf("-----------------------\n");
}


void  testSingleLinkedList2() {
     printf("Single linked list test 2\n");
    printf("-----------------------\n");
    struct singleLinkedList sList;
    initSingleLinkedList(&sList);

    // Add three elements to the single-linked list
    addElementSingleLinkedList(&sList, 5);
    addElementSingleLinkedList(&sList, 3);
    addElementSingleLinkedList(&sList, 8);

    // Print the elements in the list
    struct singleLinkedListElement* current = sList.first;
    printf("Elements in the single-linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Remove two elements from the list
    int removedValue1 = removeFirstElementSingleLinkedList(&sList);
    int removedValue2 = removeLastElementSingleLinkedList(&sList);

    printf("Removed elements: %d, %d\n", removedValue1, removedValue2);

    // Print the elements in the modified list
    current = sList.first;
    printf("Elements in the modified single-linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Add two more elements to the single-linked list
    addElementSingleLinkedList(&sList, 12);
    addElementSingleLinkedList(&sList, 7);

    // Print the elements after adding two more
    current = sList.first;
    printf("Elements after adding two more: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
      printf("-----------------------\n");
}

void testSingleLinkedList3(){
    printf("Single linked list test 3\n");
    printf("-----------------------\n");
    struct singleLinkedList sList;
    initSingleLinkedList(&sList);

    // Add three elements to the single-linked list
    addElementSingleLinkedList(&sList, 5);
    addElementSingleLinkedList(&sList, 3);
    addElementSingleLinkedList(&sList, 8);

    // Print the elements in the list
    struct singleLinkedListElement* current = sList.first;
    printf("Elements in the single-linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    // Add elements to the list

    // Search for a value (e.g., 3) in the single-linked list
    int searchResult = searchValueInSingleLinkedList(&sList, 3);

    if (searchResult) {
        printf("\nValue found in the single-linked list.\n");
    } else {
        printf("Value not found in the single-linked list.\n");
    }
      printf("\n");
        printf("-----------------------\n");
}

void testSingleLinkedList4(){
printf("Single linked list test 4\n");
    printf("-----------------------\n");
    struct singleLinkedList sList;
    initSingleLinkedList(&sList);

    // Add three elements to the single-linked list
    addElementSingleLinkedList(&sList, 5);
    addElementSingleLinkedList(&sList, 3);
    addElementSingleLinkedList(&sList, 8);

    // Print the elements in the list
    struct singleLinkedListElement* current = sList.first;
    printf("Elements in the single-linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
sortSingleLinkedList(&sList);
current = sList.first;
 printf("\nElements in the single-linked list after sorting:\n ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n-----------------------\n");

}

void app_main() {

testDoubleLinkedList1();
testDoubleLinkedList2();
testDoubleLinkedList3();
testDoubleLinkedList4();
testSingleLinkedList1();
testSingleLinkedList2();
testSingleLinkedList3();
testSingleLinkedList4();

}
