//
//  gestrech.h
//  dictionary_part2
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#ifndef gestrech_h
#define gestrech_h

#include <stdio.h>

struct LinkedList{
    char* value;
    struct LinkedList* next;
    
};

typedef struct LinkedList LinkedList;

//main menu
void menu(LinkedList*);

//second menu
void menu2(char*,LinkedList*);

//creation of a dictionary
void createDictionary(LinkedList*);

//displaying a dictionary
void displayDictionary(char*);

//taking the dictionary list in the directory
void dictionaryList(LinkedList*);

//create new element for LinkedList
LinkedList* newElement(char*);

//print LinkedList with all dictionary
void printLinkedList(LinkedList*);

//allow to choose a dictionary among a list
void chooseDictionary(LinkedList*);

//check if the file have .txt extension
int checkName(char*);

//allows to delete a dictionary
void deleteDictionary(char*, LinkedList*);

//ask to user for a threshold
char* getThreshold(char*, LinkedList*);

//init threshold research
void initTresholdResearch(char*, LinkedList*);

//display words of dictionary choosen
void displayWords(int,char*,LinkedList*);

//ask to user for a word to search
char* getTheWordToSearch(char*,LinkedList*);

//compare word of user and word of dictionary with the thresold
int my_strcmp(char*, char*);

//allow to replace capital letter in lower case letter
void replaceCapital(char *);

#endif /* gestrech_h */
