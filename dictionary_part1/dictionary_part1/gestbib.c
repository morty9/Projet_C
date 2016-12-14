//
//  gestbib.c
//  dictionary_part1
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#include "gestbib.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <regex.h>


//menu2() second menu linked to a dictionary (created or choosen)
void menu2(char* dictionary , LinkedList* dictionaryList) {
    
    char* action = malloc(sizeof(char));
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 6)\n\n");
    printf("1. Search for a word in the dictionary\n");
    printf("2. Display words in the dictionary\n");
    printf("3. Add a word in the dictionary\n");
    printf("4. Make a dictionary with an import file\n");
    printf("5. Destroy the dictionary\n");
    printf("6. Go back to the main menu\n");
    
    do {
        scanf("%s",action);
        
        switch (*action) {
            case 49:
                searchWord(dictionary,dictionaryList);
                menu2(dictionary,dictionaryList);
                break;
            case 50:
                displayDictionary(dictionary);
                menu2(dictionary, dictionaryList);
                break;
            case 51:
                addWords(dictionary, dictionaryList);
                menu2(dictionary,dictionaryList);
                break;
            case 52:
                chooseTextFile(dictionary, dictionaryList);
                menu2(dictionary, dictionaryList);
            case 53:
                deleteDictionary(dictionary,dictionaryList);
                break;
            case 54:
                menu(dictionaryList);
                break;
            default:
                printf("Wrong entry ! Please retry\n");
                break;
        }
    }while(*action != 49 && *action != 50 && *action != 51 && *action != 52 && *action != 53 && *action != 54);
    
}

//searchWord() allows to search a word in a dictionary (created or choosen)
void searchWord(char* name, LinkedList* dictionarys){
    
    char *wordToFind = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    int lineNumber = 0;
    int count = 0;
    int result = 0;
    int returnScanf = 0;
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
        
        do {
            printf("\nPlease enter the word you would like to find\n");
            getchar();
            returnScanf = scanf("%[\ea-zA-ZÀÁÂÆÇÈÉÊËÌÍÎÏÑÒÓÔŒÙÚÛÜÝŸàáâæçèéêëìíîïñòóôœùúûüýÿ'-]s",wordToFind);
            
            if(strcmp(wordToFind, "\e") == 0) {
                menu2(name, dictionarys);
            }
            
            scanf ("%*[^\n]");
            
            
            if(returnScanf != 0) {
                count = 1;
                while(fgets(answer, 255, dictionary)){
                    lineCounter++;
                    answer[strcspn(answer, "\n")] = '\0';
                    if(!strcmp(answer, wordToFind)){
                        result = 1;
                        lineNumber = lineCounter;
                    }
                }
                
                if(result){
                    printf("\n%s has been found at line number %d\n",wordToFind,lineNumber);
                }
                else{
                    printf("\nThe word you've entered doesn't exist in this dictionary\n");
                }
                
            }else {
                printf("\nYour input can contain letters only ! Please retry\n");
            }
            
        }while(!count);
        
        
    }else {
        
        printf("\n\Error while opening the dictionary\n\n");
        
    }
    
    fclose(dictionary);
    free(answer);
    free(wordToFind);
}

//addWords() allows to add words to a dictionary (created or choosen)
void addWords(char* name, LinkedList* dictionaryList){
    
    char* numberOfWords = malloc(sizeof(char));
    char* newWord = malloc(sizeof(char)*255);
    int nb = 0;
    int count = 0;
    int cpt = 0;
    int returnScanf;
    
    do {
        printf("How many words would you like to add to the dictionary\n");
        getchar();
        returnScanf = scanf("%[\e0-9]s",numberOfWords);
        
        if(strcmp(numberOfWords, "\e") == 0) {
            menu2(name, dictionaryList);
        }
        
        scanf ("%*[^\n]");
        
        if(returnScanf != 0) {
            cpt = 1;
            FILE* dictionary = fopen(name,"a+");
            
            if(dictionary){
                printf("\nPlease enter the new word you would like to add to the dictionary\n");
                
                nb = atoi(numberOfWords);
                while(count < nb){
                    getchar();
                    returnScanf = scanf("%[\ea-zÀÁÂÆÇÈÉÊËÌÍÎÏÑÒÓÔŒÙÚÛÜÝŸàáâæçèéêëìíîïñòóôœùúûüýÿ'-]s",newWord);
                    
                    if(strcmp(newWord, "\e") == 0){
                        addWords(name, dictionaryList);
                    }
                    
                    if(strcmp(newWord, "\e\e") == 0) {
                        menu2(name, dictionaryList);
                    }
                    
                    scanf ("%*[^\n]");
                    if(returnScanf != 0) {
                        fputs(newWord,dictionary);
                        fputs("\n",dictionary);
                        count++;
                    }else {
                        printf("Your input can contain letters only and 2 minimum ! Please retry\n");
                    }
                }
                printf("\nYour words have been added succesfully\n");
            }
            else{
                printf("\nError while oppening the dictionary \n\n");
            }
            fclose(dictionary);
        }else {
            printf("Your input can contain numbers only ! Please retry\n");
        }
    }while(!cpt);
    
    free(newWord);
    free(numberOfWords);
    
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
    menu2(fileName, dictionarys);
    
    free(wordsToPut);
    free(importName);
    
    return importName;
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
