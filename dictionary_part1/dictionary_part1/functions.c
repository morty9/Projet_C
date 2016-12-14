//
//  functions.c
//  dictionary_part1
//
//  Created by Bérangère La Touche on 14/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#include "functions.h"
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "gestbib.h"
#include <dirent.h>

//menu() Main menu to choose for create a new dictionary or choose an existing dictionary
void menu(LinkedList* dictionary) {
    
    
    dictionaryListDir(dictionary);
    
    char* choice = malloc(sizeof(char));
    
    printf("-----------------------\nTHE DICTIONARY - PART 1\n-----------------------\nChoose an option (1 to 2)\n\n");
    printf("1. Create new dictionary\n");
    printf("2. Use an existing dictionary\n");
    
    do{
        scanf("%s",choice);
        
        switch(*choice) {
            case 49:
                createDictionary(dictionary);
                break;
            case 50:
                printLinkedList(dictionary);
                chooseDictionary(dictionary);
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
void createDictionary(LinkedList* dictionarys){
    
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
            menu(dictionarys);
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
                menu2(dictionaryName, dictionarys);
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
void chooseDictionary(LinkedList* dictionary) {
    
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
            menu(dictionary);
        }
        
        strcat(name, ".txt");
        
        while(head != NULL && head->value != NULL){
            if(strcmp(name, head->value) == 0){
                menu2(name,head);
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
                    createDictionary(dictionary);
                    break;
                    
                case 110:
                    continue;
                    break;
                    
                case 27:
                    menu(dictionary);
                    break;
                    
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
        }while (*choice != 121 && *choice != 110 && *choice != 27);
        
    }while(!found);
    
    free(name);
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
void deleteDictionary(char* name, LinkedList* dictionaryList) {
    
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
                    menu2(name, dictionaryList);
                    break;
                    
                case 27:
                    menu2(name, dictionaryList);
                    break;
                    
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
        }while(*choice != 121 && *choice != 110 && *choice != 27);
        
        printf("\nThe dictionary %s has been deleted succesfully\n\n",name);
        
        menu(dictionaryList);
        
        fclose(dictionary);
    }else {
        printf("Error !");
        menu(dictionaryList);
        fclose(dictionary);
    }
}

//calculate number of words in a file
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

//make an array with the words file
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

//convert capital letters in tiny letters
void replaceCapital(char *string)
{
    int i = 0;
    
    for (i = 0; string[i] != '\0' ; i ++) {
        if (string[i] >= 'A' && string[i] <= 'Z') {
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

//calculate size of a string
int my_strlen(char* aString){
    int res = 0;
    
    do {
        res++;
    } while (aString[res] != '\0');
    
    return res;
}
