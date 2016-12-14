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
#include "functions.h"

void menu2(char*,LinkedList*);

char* getThreshold(char*, LinkedList*);

void initTresholdResearch(char*, LinkedList*);

void displayWords(int,char*,LinkedList*);

char* getTheWordToSearch(char*,LinkedList*);

int my_strcmp(char*, char*);

void replaceCapital(char *);

#endif /* gestrech_h */
