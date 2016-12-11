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

//menu() Main menu to choose for create a new dictionary or choose an existing dictionary
void menu(LinkedList* dictionary, LinkedList* importFile) {
    
    
    dictionaryListDir(dictionary);
    dictionaryListDir(importFile);
    
    char* choice = malloc(sizeof(char));
    
    printf("-----------------------\nTHE DICTIONARY - PART 2\n-----------------------\nChoose an option (1 to 2)\n\n");
    printf("1. Create new dictionary\n");
    printf("2. Use an existing dictionary\n");
    
    do{
        scanf("%s",choice);
        
        switch(*choice) {
            case 49:
                createDictionary(dictionary, importFile);
                break;
            case 50:
                printLinkedList(dictionary);
                chooseDictionary(dictionary, importFile);
                break;
            default:
                printf("Invalid choice ! Please try again\n");
                break;
        }
    }while(*choice != 49 && *choice != 50);
    
    free(choice);
}


//newElement() allows to create a new element in a linked list
LinkedList* newElement(char* v){
    LinkedList* ll = malloc(sizeof(LinkedList));
    ll->value = v;
    ll->next = NULL;
    
    return ll;
}

//printLinkedList() allows to display all the existing dictionary's
void printLinkedList(LinkedList* ll){
    
    printf("\nHere are the dictionarys you can use\n");
    
    while(ll != NULL){
        if(ll->value != NULL){
            if(checkName(ll->value)){
                printf("%s\n", ll->value);
            }
        }
        ll = ll->next;
    }
}

//checkName() allows to check if the needed file have ".txt" extension
int checkName(char* astring){
    
    char dot = '.';
    char* extension = ".txt";
    
    char* ret = strchr(astring, dot);
    
    if(ret != NULL && !strcmp(ret, extension)){
        return 1;
    }
    else
        return 0;
}


//dictionaList() put all dictionary's of the directory in a linked list
void dictionaryListDir(LinkedList* dictionarys) {
    
    DIR* directory = opendir("./");
    
    if(directory != NULL) {
        
        struct dirent * content;
        
        while ((content = readdir(directory)) != NULL)
        {
            if(checkName(content->d_name)){
                dictionarys->next = newElement(content->d_name);
                dictionarys = dictionarys->next;
            }
        }
        closedir(directory);
    }else {
        printf("Failed to open dictionary");
    }
}


//createDictionary() allows to create a new dictionary
void createDictionary(LinkedList* dictionarys, LinkedList* importFile){
    
    char* dictionaryName = malloc(sizeof(char)*255);
    int create = 0;
    //dictionaryList(dictionarys);
    FILE* newDictionary = NULL;
    
    if(dictionarys->value == NULL) {
        dictionarys = dictionarys->next;
    }
    
    do {
        printf("Enter a name for your new dictionary\n");
        scanf("%s",dictionaryName);
        
        if(strcmp(dictionaryName, "\e") == 0) {
            menu(dictionarys, importFile);
        }
        
        strcat(dictionaryName, ".txt");
        
        if(dictionaryName != NULL){
            
            newDictionary = fopen(dictionaryName,"r+");
            
            if(newDictionary == NULL){
                newDictionary = fopen(dictionaryName, "w");
                dictionaryListDir(dictionarys);
                create = 1;
                printf("\nYour new dictionary has been succesfully created\n\n");
                fclose(newDictionary);
                //menu2(dictionaryName, dictionarys, importFile);
            }else {
                fclose(newDictionary);
            }
            
        }else{
            printf("Empty names are not allowed\n");
        }
        printf("This dictionary already exist, please retry\n");
    }while(!create);
    
    free(dictionaryName);
}


//chooseDictionary() allows to choose an existing dictionary
void chooseDictionary(LinkedList* dictionary, LinkedList* importFile) {
    
    char* name = malloc(sizeof(char)*255);
    char* choice = malloc(sizeof(char));
    
    if(dictionary->value == NULL) {
        dictionary = dictionary->next;
    }
    
    int found = 0;
    do {
        LinkedList* head = dictionary;
        printf("\nEnter the name of the dictionary you want to work on\n");
        scanf("%s",name);
        
        if(strcmp(name,"\e") == 0) {
            menu(dictionary, importFile);
        }
        
        strcat(name, ".txt");
        
        while(head != NULL && head->value != NULL){
            if(strcmp(name, head->value) == 0){
                //menu2(name,head,importFile);
                chooseTextFile(name, importFile, dictionary);
                found = 1;
                break;
            }
            head = head->next;
        }
        
        do {
            printf("This dictionary doesn't exist, would you like to create one ? y/n\n");
            scanf("%s",choice);
            switch (*choice) {
                case 121:
                    createDictionary(dictionary, importFile);
                    break;
                    
                case 110:
                    continue;
                    break;
                    
                case 27:
                    menu(dictionary,importFile);
                    break;
                    
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
        }while (*choice != 121 && *choice != 110 && *choice != 27);
        
    }while(!found);
    
    free(name);
}


//menu2() second menu linked to a dictionary (created or choosen)
void menu2(char * import, char* dictionary , LinkedList* dictionaryList, LinkedList* importFile) {
    
    char* action = malloc(sizeof(char));
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 7)\n\n");
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
                menu2(import, dictionary, dictionaryList, importFile);
                break;
            case 50:
                searchMissingWords(import, dictionary, dictionaryList, importFile);
                menu2(import, dictionary, dictionaryList, importFile);
                break;
            case 51:
                searchMissingWordsAndTreshold(import, dictionary, dictionaryList, importFile);
                menu2(import, dictionary, dictionaryList, importFile);
                break;
            case 52:
                deleteDictionary(dictionary, import, dictionaryList, importFile);
                break;
            case 53:
                menu(dictionaryList, importFile);
                break;
            default:
                printf("Wrong entry ! Please retry\n");
                break;
        }
    }while(*action != 49 && *action != 50 && *action != 51 && *action != 52 && *action != 53);
    
}

//displayDictionary() allows to display words of a dictionary (created or choosen)
void displayDictionary(char* dictionaryName){
    
    printf("Dictionary name that you're working on is %s\n",dictionaryName);
    
    FILE* dictionary = fopen(dictionaryName,"r");
    
    char* current = malloc(sizeof(char)*255);
    
    if(dictionary){
        
        while(fgets(current, sizeof(current), dictionary)){
            printf("%s",current);
        }
    }
    else{
        printf("The dictionary is not available\n");
    }
    
    fclose(dictionary);
    free(current);
}

//deleteDictionary() allows to delete a dictionary
void deleteDictionary(char* name, char* import, LinkedList* dictionaryList, LinkedList* importFile) {
    
    char* choice = malloc(sizeof(char));
    
    FILE* dictionary = fopen(name,"w+");
    
    if(dictionary != NULL) {
        
        printf("\nAre you sure you want to delete %s y/n\n",name);
        
        do {
            scanf("%s",choice);
            
            switch (*choice) {
                case 121:
                    remove(name);
                    break;
                    
                case 110:
                    menu2(name, import, dictionaryList, importFile);
                    break;
                    
                case 27:
                    menu2(name, import, dictionaryList, importFile);
                    break;
                    
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
        }while(*choice != 121 && *choice != 110 && *choice != 27);
        
        printf("\nThe dictionary %s has been deleted succesfully\n\n",name);
        
        menu(dictionaryList, importFile);
        
        fclose(dictionary);
    }else {
        printf("Error !");
        menu(dictionaryList, importFile);
        fclose(dictionary);
    }
}

//convert capital letters in tiny letters
void replaceCapital(char *string)
{
    int i = 0;
    
    for (i = 0; string[i] != '\0'; i ++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            string[i] += 'a' - 'A';
        }
    }
}

//compare strings to find different caracter
int my_strcmp(char* str1, char* str2) {
    
    int count = 0;
    int i;
    char* str = malloc(sizeof(char)*255);
    
    replaceCapital(str1);
    replaceCapital(str2);
    
    if(strlen(str1) < strlen(str2)) {
        str = str2;
    }else {
        str = str1;
    }
    
    for (i = 0 ; str[i] != '\0' ; i ++) {
        if(str1[i] != str2[i]) {
            count++;
        }
    }
    
    return count;
    
}


char* chooseTextFile(char* dictionary, LinkedList* importFile, LinkedList* dictionarys) {
    
    dictionaryListDir(importFile);
    
    char* name = malloc(sizeof(char)*255);
    char* newImportName = malloc(sizeof(char)*255);
    
    if(importFile->value == NULL) {
        importFile = importFile->next;
    }
    
    int found = 0;
    do {
        LinkedList* head = importFile;
        printf("\nEnter the name of the file you want to import\n");
        scanf("%s",name);
        
        if(strcmp(name,"\e") == 0) {
            menu(importFile, dictionarys);
        }
        
        strcat(name, ".txt");
        
        while(head != NULL && head->value != NULL){
            if(strcmp(name, head->value) == 0){
                found = 1;
                newImportName = formattingFile(name, dictionary, importFile, dictionarys);
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

int fileLength(char* filename){
    int result = 0;
    FILE* file = fopen(filename,"r");
    
    char* word = malloc(sizeof(char)*255);
    
    if(file != NULL){
        
        while(fgets(word,255,file)){
            result ++;
        }
        
    }
    
    printf("Nombre de mots dans votre fichier: %d\n", result);
    
    free(word);
    
    return result;
}

char* formattingFile(char* name, char* dictionary,LinkedList* importFile, LinkedList* dictionarys) {
    
    FILE* import = fopen(name, "r+");
    FILE* importNew;
    char* importName = malloc(sizeof(char)*255);
    char words;
    int i = 0;
    int create = 0;
    char * wordsToPut = malloc(sizeof(char)*255);
    char** array;
    int size = 0;
    
    do {
        printf("Enter a name for your new file\n");
        scanf("%s",importName);
        
        if(strcmp(importName, "\e") == 0) {
            chooseTextFile(dictionary, importFile, dictionarys);
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
    
    fclose(import);
    
    size = fileLength(importName);
    array = fillArray(importName, size);
    
    removeOccurances(array, size, importName);
    
    menu2(importName, dictionary, dictionarys, importFile);
    free(wordsToPut);
    free(importName);
    
    return importName;
}


char** searchMissingWords(char* name, char* dictionary, LinkedList* dictionaryList, LinkedList* importFile) {
    
    int dicoSize = fileLength(dictionary);
    int fileSize = fileLength(name);
    char** arrayText = fillArray(name,fileSize);
    char** arrayDictio = fillArray(dictionary,dicoSize);
    char** result = malloc(sizeof(char*));
    
    result = getMissingWords(arrayText, fileSize, arrayDictio, dicoSize);
    
    return result;
}

void searchMissingWordsAndTreshold(char* import, char* dictionary, LinkedList* dictionaryList, LinkedList*importFile) {
    
    int dicoSize = fileLength(dictionary);
    int fileSize = fileLength(import);
    char** arrayDictio = fillArray(dictionary,dicoSize);
    char** arrayText = fillArray(import,fileSize);
    
    missingWordsWithThreshold(arrayText, fileSize, arrayDictio, dicoSize, import, dictionary);
    
    free(arrayText);
    free(arrayDictio);
    
}

char** fillArray(char* filename,int size){
    
    char** array = malloc(sizeof(char*)*size);
    
    FILE* file = fopen(filename,"r");
    
    if(file != NULL){
        char* wordFromFile = malloc(sizeof(char)*255);
        int i = 0;
        while (fgets(wordFromFile,255,file)) {
            
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';
            
            
            if(i < size){
                array[i] = malloc(sizeof(char)*255);
                strcpy(array[i],wordFromFile);
            }
            i++;
        }
        free(wordFromFile);
        fclose(file);
    }else {
        printf("Erreur file\n");
        fclose(file);
    }
    
    return array;
}


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
    
    for(int i = 0; result[i]; i++) {
        printf("%s\n",result[i]);
    }
    
    return result;
}


void printArray(char**array, int size){
    
    int i = 0;
    
    for(i = 0; i < size; i++){
        printf("%s\n",array[i]);
    }
    
}

void missingWordsWithThreshold(char** arrayText, int textFileSize, char** arrayDictio, int dictioSize, char* import, char* dictionary){

    int size = 0;
    int i;
    char** arrayMissing = malloc(sizeof(char*) * textFileSize);

    arrayMissing = getMissingWords(arrayText, textFileSize, arrayDictio, dictioSize);
    
    for (i = 0; arrayMissing[i] ; i++) {
        printf("%s\n",arrayMissing[i]);
        
    }
    
    for (i = 0; arrayMissing[i] ; i++) {
        size++;
    }

    displayCLosedWordsForEach(arrayMissing, size, import, dictionary);
    
}


void displayCLosedWordsForEach(char**array, int size, char* fileName, char* dictionary){
    
    FILE* file = fopen(fileName,"r+");
    FILE* correction = fopen("correction.txt", "a+");
    
    int j = 0;
    int nbrOfClosedWords = 0;
    char* words = malloc(sizeof(char)*255);
    int s = 0;
    
    printf("\n\nList of closed words for each missing word\n\n");
    
    for(int i = 0; i < size; i++){
        
        nbrOfClosedWords = getClosedLength(array[i], dictionary);
        if(nbrOfClosedWords){
            char** res = getCLosedWords(dictionary,array[i], nbrOfClosedWords);
            printf("\n\nThe closed words for %s are : \n", array[i]);
            printArray(res, nbrOfClosedWords);
            if(file && correction) {
                while(fgets(words, 255, file) != '\0') {
                    s += strlen(words);
                    words[strcspn(words, "\n")] = '\0';
                    if(strcmp(words, array[i]) == 0) {
                        file = fopen(fileName, "a+");
                        fseek(file, s, SEEK_SET);
                        for (int j = 0; res[j] ; j++) {
                            if(my_strcmp(words, res[j]) == 1) {
                                fputs(res[j], file);
                            }
                        }
                    }
                    fseek(file, 0, SEEK_SET);
                }
            }
            //fputs(res[j],correction);
        }else {
            printf("No closed words for %s\n",array[i]);
        }

    }
    
    free(words);
}



char** getCLosedWords(char* fileName, char* string, int nbrOfClosedWords){
    
    char** result = malloc(sizeof(char*) * nbrOfClosedWords);
    
    FILE* file = fopen(fileName,"r");
    
    if(file){
        int i = 0;
        char* wordFromFile = malloc(sizeof(char)*255);
        
        while (fgets(wordFromFile, 255, file)) {
            if(my_strcmp(wordFromFile, string) <= 2) {
                result[i] = malloc(sizeof(char)*255);
                strcpy(result[i], wordFromFile);
                i++;
            }
        }
        fclose(file);
    }
    return result;
}


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
    }
    return closedWords;
}

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


void removeOccurances(char** array, int size, char* name){
    int i = 0;
    int k = 0;
    int count = 0;

    while (i < size) {
        while(howManyOccurances(array, size, array[i]) >= 2){
            int j;
            for(j = i; j < size; j++){
                array[j] = array[j+1];
            }
            size--;
        }
        i++;
    }
    
    printf("Here's the new array with occurances removed\n");
    printArray(array, size);
}

int my_strlen(char* aString){
    int res = 0;
    
    do {
        res++;
    } while (aString[res] != '\0');
    
    return res;
}

