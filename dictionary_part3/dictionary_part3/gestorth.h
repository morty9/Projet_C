//
//  gestorth.h
//  dictionary_part3
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#ifndef gestorth_h
#define gestorth_h

#include <stdio.h>

struct LinkedList{
    char* value;
    struct LinkedList* next;
};
typedef struct LinkedList LinkedList;


void menu(LinkedList*, LinkedList*);
void menu2(char*, char*,LinkedList*, LinkedList*);
void createDictionary(LinkedList*, LinkedList*);
void displayDictionary(char*);
void dictionaryListDir(LinkedList*);
LinkedList* newElement(char*);
void printLinkedList(LinkedList*);
void chooseDictionary(LinkedList*, LinkedList*);
int checkName(char*);
void deleteDictionary(char*, char*, LinkedList*, LinkedList*);
int my_strcmp(char*, char*);
void replaceCapital(char *);


char* chooseTextFile(char*, LinkedList*, LinkedList*);
int fileLength(char*);
char** fillArray(char*,int);
char** getMissingWords(char**, int, char**, int);
char* formattingFile(char*,char*,LinkedList*, LinkedList*);
char** searchMissingWords(char*,char*,LinkedList*,LinkedList*);
void searchMissingWordsAndTreshold(char*, char*, LinkedList*, LinkedList*);
void missingWordsWithThreshold(char** , int , char** , int, char*, char*);
void printArray(char**array, int);
int getMissingWordsLength(char* textFileName, char* dictioFile);
int getClosedLength(char* aString, char* fileName);
char** getCLosedWords(char* fileName, char* string, int);
void displayCLosedWordsForEach(char**array, int size, char* fileName, char* dictionary);
int howManyOccurances(char**, int,char*);
void removeOccurances(char**, int, char*);
int my_strlen(char*);

LinkedList* newElement(char*);
void printLinkedList(LinkedList*);
LinkedList* fillList(char*, LinkedList*);

#endif /* gestorth_h */
