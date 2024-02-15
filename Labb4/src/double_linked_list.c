//Author: Oscar Svantesson, Ömer Kolsuz
#include<stdlib.h>
#include<limits.h>
#include"double_linked_list.h"
#include<esp32/rom/ets_sys.h>
#include<stdio.h>




int addElementDoubleLinkedList(struct doubleLinkedList* list, int value) {
    // Create a new element
    struct doubleLinkedListElement* newElement = (struct doubleLinkedListElement*)malloc(sizeof(struct doubleLinkedListElement));
    
    if (newElement == NULL) {
        // Memory allocation failed
        return INT_MIN;
    }
    
    newElement->data = value;
    newElement->next = NULL;
    newElement->previous = NULL;

    // Special case: Empty list
    if (list->first == NULL) {
        list->first = newElement;
        list->last = newElement;
        return value;
    }

    // Find the correct position to insert the new element
    struct doubleLinkedListElement* current = list->first;
    while (current != NULL) {
        if (current->data >= value) {
            // Insert before the current element
            if (current->previous != NULL) {
                current->previous->next = newElement;
            }
            else {
                list->first = newElement;
            }
            newElement->previous = current->previous;
            newElement->next = current;
            current->previous = newElement;
            return value;
        }
        current = current->next;
    }

    // Insert at the end
    list->last->next = newElement;
    newElement->previous = list->last;
    list->last = newElement;
    return value;
}



void initDoubleLinkedList(struct doubleLinkedList* list) {
  list->first = NULL;
  list->last = NULL;
}


int removeFirstElementDoubleLinkedList(struct doubleLinkedList* list) {
    if (list->first == NULL) {
        // List is empty
        return INT_MIN;
    }
    
    struct doubleLinkedListElement* removedElement = list->first;
    int removedValue = removedElement->data;

    if (list->first == list->last) {
        // Only one element in the list
        list->first = NULL;
        list->last = NULL;
    }
    else {
        list->first = list->first->next;
        list->first->previous = NULL;
    }

    free(removedElement);
    return removedValue;
}


int removeLastElementDoubleLinkedList(struct doubleLinkedList* list) {
    if (list->last == NULL) {
        // List is empty
        return INT_MIN;
    }

    struct doubleLinkedListElement* removedElement = list->last;
    int removedValue = removedElement->data;

    if (list->first == list->last) {
        // Only one element in the list
        list->first = NULL;
        list->last = NULL;
    }
    else {
        list->last = list->last->previous;
        list->last->next = NULL;
    }

    free(removedElement);
    return removedValue;
}

// Function to search for a value in the double linked list
int searchValueInDoubleLinkedList(struct doubleLinkedList* list, int value) {
    struct doubleLinkedListElement* current = list->first;

    while (current != NULL) {
        if (current->data == value) {
            // Value found in the list
            return 1; // 1 = success
        }
        current = current->next;
    }

    // Value not found in the list
    return 0; // 0 = fail
}

void sortDoubleLinkedList(struct doubleLinkedList* list) {
    struct doubleLinkedListElement*current;
    struct doubleLinkedListElement*index;
    int temp;

    if (list->first == NULL) {
        // List is empty
        return;
    }

    for (current = list->first; current->next != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
        }
    }
}



