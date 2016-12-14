//
//  gestorth.c
//  dictionary_part3
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#include "gestorth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


//menu2() second menu linked to a dictionary (created or choosen)
void menu2(char * import, char* dictionary , LinkedList* dictionaryList) {
    
    char* action = malloc(sizeof(char));
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 5)\n\n");
    printf("1. Display words of your dictionary\n");
    printf("2. Display missing words\n");
    printf("3. Display missing words and list of close words\n");
    printf("4. Destroy the dictionary\n");
    printf("5. Go back to the main menu\n");
    
    do {
        scanf("%s",action);
        
        switch (*action) {
            case 49:
                displayDictionary(dictionary);
                menu2(import, dictionary, dictionaryList);
                break;
            case 50:
                searchMissingWords(import, dictionary, dictionaryList);
                menu2(import, dictionary, dictionaryList);
                break;
            case 51:
                searchMissingWordsAndTreshold(import, dictionary, dictionaryList);
                menu2(import, dictionary, dictionaryList);
                break;
            case 52:
                deleteDictionary(dictionary, import, dictionaryList);
                break;
            case 53:
                menu(dictionaryList);
                break;
            default:
                printf("Wrong entry ! Please retry\n");
                break;
        }
    }while(*action != 49 && *action != 50 && *action != 51 && *action != 52 && *action != 53);
    
}

//users choose a text file who want to import
char* chooseTextFile(char* dictionary, LinkedList* dictionarys) {
    
    dictionaryListDir(dictionarys);
    
    char* name = malloc(sizeof(char)*255);
    char* newImportName = malloc(sizeof(char)*255);
    
    if(dictionarys->value == NULL) {
        dictionarys = dictionarys->next;
    }
    
    int found = 0;
    do {
        LinkedList* head = dictionarys;
        printf("\nEnter the name of the file you want to import\n");
        scanf("%s",name);
        
        if(strcmp(name,"\e") == 0) {
            menu(dictionarys);
        }
        
        strcat(name, ".txt");
        
        while(head != NULL && head->value != NULL){
            if(strcmp(name, head->value) == 0){
                found = 1;
                newImportName = formattingFile(name, dictionary, dictionarys);
                break;
            }
            head = head->next;
        }
        
        if(head == NULL) {
            printf("This file doesn't exist, please retry\n");
        }
        
    }while(!found);
    
    free(name);
    return newImportName;
}

//allow to formatting a file to transform him in dictionary
char* formattingFile(char* name, char* dictionary, LinkedList* dictionarys) {
    
    FILE* import = fopen(name, "r+");
    FILE* importNew;
    char* importName = malloc(sizeof(char)*255);
    char words;
    int i = 0;
    int create = 0;
    char * wordsToPut = malloc(sizeof(char)*255);
    char*  fileName = malloc(sizeof(char)*255);
    
    do {
        printf("Enter a name for your new file\n");
        scanf("%s",importName);
        
        if(strcmp(importName, "\e") == 0) {
            chooseTextFile(dictionary, dictionarys);
        }
        
        strcat(importName, ".txt");
        
        if(importName != NULL){
            
            importNew = fopen(importName,"r+");
            
            if(importNew == NULL){
                importNew = fopen(importName, "a+");
                create = 1;
                while ((words = fgetc(import)) != EOF) {
                    wordsToPut[i] = words;
                    if((words == 32 || words == 13) && importNew != NULL) {
                        wordsToPut[i] = '\n';
                        if (wordsToPut[i-1] >= 33 && wordsToPut[i-1] <= 64 ) {
                            wordsToPut[i-1] = wordsToPut[i];
                            wordsToPut[strlen(wordsToPut) - 1] = 0;
                        }
                        replaceCapital(wordsToPut);
                        fputs(wordsToPut, importNew);
                        char* next = malloc(sizeof(char)*255);
                        wordsToPut = next;
                        i = 0;
                    }else {
                        i++;
                    }
                }
                printf("You're file have been imported correctly\n");
                fclose(importNew);
                fclose(import);
            }else {
                fclose(importNew);
                fclose(import);
            }
            
        }else{
            printf("Empty names are not allowed\n");
        }
        
        if(!create) {
            printf("This file already exist, please retry\n");
        }
        
    }while(!create);
    
    fileName = removeOccurances(importName);
    menu2(fileName, dictionary, dictionarys);
    
    free(wordsToPut);
    free(importName);
    
    return importName;
}

//allow to construct array of the file before the getMissingWords function
char** searchMissingWords(char* name, char* dictionary, LinkedList* dictionaryList) {
    
    int dicoSize = fileLength(dictionary);
    int fileSize = fileLength(name);
    char** arrayText = fillArray(name,fileSize);
    char** arrayDictio = fillArray(dictionary,dicoSize);
    char** result = malloc(sizeof(char*));
    
    result = getMissingWords(arrayText, fileSize, arrayDictio, dicoSize);
    
    return result;
}

//allow to construct array of the file before the getMissingWordsWithThreshold function
void searchMissingWordsAndTreshold(char* import, char* dictionary, LinkedList* dictionaryList) {
    
    int dicoSize = fileLength(dictionary);
    int fileSize = fileLength(import);
    char** arrayDictio = fillArray(dictionary,dicoSize);
    char** arrayText = fillArray(import,fileSize);
    
    missingWordsWithThreshold(arrayText, fileSize, arrayDictio, dicoSize, import, dictionary);
    
    free(arrayText);
    free(arrayDictio);
    
}

//get missing words of file
char** getMissingWords(char** arrayText, int textFileSize, char** arrayDictio, int dictioSize){
    
    int line = 0;
    int lineCounter = 0;
    int i = 0;
    char** result= malloc(sizeof(char*) * textFileSize);
    
    printf("\n\nHere's a missing word:\n");
    
    while(i < textFileSize && i < dictioSize){
        lineCounter++;
        if(strcmp(arrayText[i], arrayDictio[i]) != 0 ) {
            line = lineCounter;
            result[i] = arrayText[i];
            printf("%d: %s\n",line,arrayText[i]);
        }
        i++;
    }
    
    return result;
}

//get missing words of file with a threshold
void missingWordsWithThreshold(char** arrayText, int textFileSize, char** arrayDictio, int dictioSize, char* import, char* dictionary){

    int size = 0;
    int i;
    char** arrayMissing = malloc(sizeof(char*) * textFileSize);

    arrayMissing = getMissingWords(arrayText, textFileSize, arrayDictio, dictioSize);
    
    for (i = 0; arrayMissing[i] ; i++) {
        size++;
    }

    displayCLosedWordsForEach(arrayMissing, size, import, dictionary);
    
}

//display closed words between each string and dictionary
void displayCLosedWordsForEach(char**array, int size, char* fileName, char* dictionary){
    
    int nbrOfClosedWords = 0;
    char* words = malloc(sizeof(char)*255);
    
    printf("\n\nList of closed words for each missing word\n\n");
    
    for(int i = 0; i < size; i++){
        int sizeRes = 0;
        nbrOfClosedWords = getClosedLength(array[i], dictionary);
        if(nbrOfClosedWords){
            char** res = getCLosedWords(dictionary,array[i], nbrOfClosedWords, &sizeRes);
            printf("\n\nThe closed words for '%s' are : \n", array[i]);
            printArray(res, nbrOfClosedWords);
            char * thresholdArray = correctFile(res, array[i], fileName, sizeRes);
            if(thresholdArray != NULL) {
                array[i] = thresholdArray;
            }
        }else {
            printf("No closed words for %s\n",array[i]);
        }

    }
    
    newFileCorrected(fileName, array, size);
    
    free(words);
}

//take closed words array, the more closed words of a string
char* correctFile(char** res, char* array, char* fileName, int sizeRes) {
    
    int j;
    char* thresholdArray = malloc(sizeof(char));
    
    for(j = 0; j < sizeRes ; j++) {
        if(res[j] == NULL || res[j] == '\0') {
            continue;
        }
        if(array != '\0' && res[j] != '\0' && array != NULL && res[j] != NULL && my_strcmp(array, res[j]) <= 1) {
            thresholdArray = res[j];
            printf("\n\n%s\n",thresholdArray);
            return thresholdArray;
        }
    }

    thresholdArray = res[0];
    return thresholdArray;
}

//create a file with the corrected words
void newFileCorrected(char* filename, char** array, int size) {
    
    FILE* correctFile = fopen(filename,"w+");
    int i;
    
    if(correctFile) {
        for(i = 0; i < size ; i++) {
            array[i][strcspn(array[i], "\n")] = '\0';
            fputs(array[i], correctFile);
            fputs("\n", correctFile);
        }
        fclose(correctFile);
    }else {
        fclose(correctFile);
    }
    
}

//get closed words between a string and a dictionary
char** getCLosedWords(char* fileName, char* string, int nbrOfClosedWords, int* sizeRes){
    
    char** result = malloc(sizeof(char*) * nbrOfClosedWords);
    
    FILE* file = fopen(fileName,"r");
    
    if(file){
        int i = 0;
        char* wordFromFile = malloc(sizeof(char)*255);
        
        while (fgets(wordFromFile, 255, file)) {
            if(my_strcmp(wordFromFile, string) <= 2) {
                result[i] = malloc(sizeof(char)*255);
                strcpy(result[i], wordFromFile);
                (*sizeRes)++;
                i++;
            }
        }
        fclose(file);
    }else {
        fclose(file);
    }
    return result;
}

//get number of closed words between a string and a dictionary
int getClosedLength(char* aString, char* fileName){
    
    int closedWords = 0;
    
    FILE* file = fopen(fileName,"r");
    
    if(file){
        
        char* wordFromFile = malloc(sizeof(char)*255);
        
        while (fgets(wordFromFile, 255, file)) {
            if(my_strcmp(wordFromFile, aString) <= 2){
                closedWords++;
            }
        }
        fclose(file);
    }else {
        fclose(file);
    }
    return closedWords;
}

//calculate occurences in array
int howManyOccurances(char** array, int size,char* string){
    int ocurance = 0;
    int i;
    
    int wordToBeCompared = my_strlen(string);
    
    int wordFromArraySize = 0;
    
    char* temp = malloc(sizeof(char)*255);
    
    for(i = 0; i < size; i++){
        
        strcpy(temp,array[i]);
        
        wordFromArraySize =  my_strlen(temp);
        
        if(wordFromArraySize > wordToBeCompared){
            if(!strncmp(string, array[i], wordFromArraySize)){
                ocurance++;
            }
        }
        else{
            if(!strncmp(string, array[i], wordToBeCompared)){
                ocurance++;
            }
        }
    }
    return ocurance;
}


//removes occurences in array
char* removeOccurances(char* filename){
    
    int fileSize = fileLength(filename);
    
    char** array = fillArray(filename,fileSize);
    
    int i = 0;
    while (i < fileSize) {
        while(howManyOccurances(array, fileSize, array[i]) >= 2){
            int j;
            for(j = i; j < fileSize; j++){
                array[j] = array[j+1];
            }
            fileSize--;
        }
        i++;
    }
    
    FILE* file = fopen(filename, "w+");
    if(file){
        for(int j = 0; j < fileSize; j++){
            fputs(array[j], file);
            fputs("\n", file);
        }
        fclose(file);
    }else {
        fclose(file);
    }
    
    return filename;
}

