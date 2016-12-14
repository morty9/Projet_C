//
//  functions.h
//  dictionary_part2
//
//  Created by Bérangère La Touche on 14/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>

struct LinkedList{
    char* value;
    struct LinkedList* next;
};

typedef struct LinkedList LinkedList;

void menu(LinkedList*);

LinkedList* newElement(char*);

void printLinkedList(LinkedList*);

int checkName(char*);

void dictionaryList(LinkedList*);

void createDictionary(LinkedList*);

void chooseDictionary(LinkedList*);

void displayDictionary(char*);

void deleteDictionary(char*, LinkedList*);

int my_strcmp(char*, char*);

void replaceCapital(char*);

#endif /* functions_h */
