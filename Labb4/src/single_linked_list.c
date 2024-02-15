//Author: Oscar Svantesson, Ömer Kolsuz
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include"single_linked_list.h"

// Function to search for a value in the single linked list
int searchValueInSingleLinkedList(struct singleLinkedList* list, int value) {
    struct singleLinkedListElement* current = list->first;

    while (current != NULL) {
        if (current->data == value) {
            // Value found in the list
            return 1; // You can return 1 to indicate success or any other value/logic as needed
        }
        current = current->next;
    }

    // Value not found in the list
    return 0; // You can return 0 to indicate failure or any other value/logic as needed
}


int addElementSingleLinkedList(struct singleLinkedList* list, int value) {
    // Create a new element
    struct singleLinkedListElement* newElement = (struct singleLinkedListElement*)malloc(sizeof(struct singleLinkedListElement));
    
    if (newElement == NULL) {
        // Memory allocation failed
        return INT_MIN;
    }
    
    newElement->data = value;
    newElement->next = NULL;

    // Special case: Empty list or new element should be the first
    if (list->first == NULL || value <= list->first->data) {
        newElement->next = list->first;
        list->first = newElement;
        return value;
    }

    // Find the correct position to insert the new element
    struct singleLinkedListElement* current = list->first;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    newElement->next = current->next;
    current->next = newElement;

    return value;
}


void initSingleLinkedList(struct singleLinkedList* list) {
  list->first = NULL;
}

int removeFirstElementSingleLinkedList(struct singleLinkedList* list) {
    if (list->first == NULL) {
        // List is empty
        return INT_MIN;
    }
    
    struct singleLinkedListElement* removedElement = list->first;
    int removedValue = removedElement->data;

    list->first = list->first->next;
    free(removedElement);
    
    return removedValue;
}
void sortSingleLinkedList(struct singleLinkedList* list) {
    int swapped;
    struct singleLinkedListElement* ptr1;
    struct singleLinkedListElement* lptr = NULL;

    // Check if the list is empty
    if (list->first == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = list->first;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap the data of the two nodes
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}



int removeLastElementSingleLinkedList(struct singleLinkedList* list) {
    if (list->first == NULL) {
        // List is empty
        return INT_MIN;
    }
    
    // If there is only one element in the list, treat it as a special case
    if (list->first->next == NULL) {
        int removedValue = list->first->data;
        free(list->first);
        list->first = NULL;
        return removedValue;
    }
    
    // Traverse the list to find the element before the last one
    struct singleLinkedListElement* current = list->first;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    // Now, 'current' points to the element before the last one
    struct singleLinkedListElement* removedElement = current->next;
    int removedValue = removedElement->data;
    
    // Remove the last element
    free(removedElement);
    current->next = NULL;
    
    return removedValue;
}
