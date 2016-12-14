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
#include "functions.h"

void menu2(char*,LinkedList*);

void addWords(char*, LinkedList*);

char* chooseTextFile(char*, LinkedList*);

char* formattingFile(char*, char*, LinkedList*);

void searchWord(char*, LinkedList*);

char* removeOccurances(char*);

int howManyOccurances(char**, int , char*);

#endif /* gestbib_h */
