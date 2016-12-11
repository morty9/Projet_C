//
//  gestbib.h
//  dictionary_part1
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#ifndef gestbib_h
#define gestbib_h

#include <stdio.h>

struct LinkedList{
    char* value;
    struct LinkedList* next;
    
};

typedef struct LinkedList LinkedList;

void menu(LinkedList*);
void menu2(char*,LinkedList*);
void createDictionary(LinkedList*);
void searchWord(char*, LinkedList*);
void displayDictionary(char*);
void dictionaryList(LinkedList*);
LinkedList* newElement(char*);
void printLinkedList(LinkedList*);
void chooseDictionary(LinkedList*);
void addWords(char*, LinkedList*);
int checkName(char*);
void deleteDictionary(char*, LinkedList*);
void deleteWord(char*);
void chooseTextFile(char*, LinkedList*);
void formattingFile(char*, char* , LinkedList* );
void replaceCapital(char *);

#endif /* gestbib_h */
