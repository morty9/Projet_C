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
#include "functions.h"

void menu2(char*, char*,LinkedList*);

char* chooseTextFile(char*, LinkedList*);

char* formattingFile(char*,char*,LinkedList*);

char** searchMissingWords(char*,char*,LinkedList*);

void searchMissingWordsAndTreshold(char*, char*, LinkedList*);

char** getMissingWords(char**, int, char**, int);

void missingWordsWithThreshold(char** , int , char** , int, char*, char*);

void displayCLosedWordsForEach(char**, int, char*, char*);

char* correctFile(char**, char*, char*, int);

void newFileCorrected(char*, char**, int);

char** getCLosedWords(char*, char*, int, int*);

int getClosedLength(char*, char*);

int howManyOccurances(char**, int,char*);

char* removeOccurances(char*);

#endif /* gestorth_h */
