//
//  functions.h
//  dictionary_part1
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

void dictionaryListDir(LinkedList*);

void createDictionary(LinkedList*);

void chooseDictionary(LinkedList*);

void displayDictionary(char*);

void deleteDictionary(char*, LinkedList*);

char** fillArray(char*, int);

int fileLength(char*);

void replaceCapital(char *);

int my_strcmp(char*, char*);

int my_strlen(char*);

#endif /* functions_h */
