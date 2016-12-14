//
//  gestrech.c
//  dictionary_part2
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#include "gestrech.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <dirent.h>

//menu2() second menu linked to a dictionary (created or choosen)
void menu2(char* dictionary , LinkedList* dictionaryList) {
    
    char* action = malloc(sizeof(char));
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 4)\n\n");
    printf("1. Display words in the dictionary\n");
    printf("2. Advanced research with near list of words\n");
    printf("3. Destroy the dictionary\n");
    printf("4. Go back to the main menu\n");
    
    do {
        scanf("%s",action);
        
        switch (*action) {
            case 49:
                displayDictionary(dictionary);
                menu2(dictionary, dictionaryList);
                break;
            case 50:
                initTresholdResearch(dictionary, dictionaryList);
                menu2(dictionary, dictionaryList);
                break;
            case 51:
                deleteDictionary(dictionary,dictionaryList);
                break;
            case 52:
                menu(dictionaryList);
                break;
            default:
                printf("Wrong entry ! Please retry\n");
                break;
        }
    }while(*action != 49 && *action != 50 && *action != 51 && *action != 52);
    
}

// init the treshold research
void initTresholdResearch(char* name, LinkedList* dictionarys){
    
    char* retry = malloc(sizeof(char));
    char* thresholdStr = malloc(sizeof(char));
    int checked = 0;
    int threshold = 0;
    
    thresholdStr = getThreshold(name, dictionarys);
    
    threshold = atoi(thresholdStr);
    
    if(threshold){
        displayWords(threshold, name, dictionarys);
        checked = 1;
    }
    
    while(!checked){
        
        do{
            printf("Wrong entry! Would you like to try again? y/n\n");
            scanf("%s",retry);
            switch (*retry) {
                case 121:
                    initTresholdResearch(name,dictionarys);
                    break;
                case 110:
                    menu2(name,dictionarys);
                default:
                    printf("Wrong entry! Please retry\n");
                    break;
            }
        }while(*retry != 121 && *retry != 110);
    }
    
}

// returns the threshold entered by user as
char* getThreshold(char* name, LinkedList* dictionarys){
    
    char* threshold = malloc(sizeof(char)*255);
    int returnScanf = 0;
    
    do{
        printf("\nEnter the treshold you'd like to apply to your research\n");
        getchar();
        returnScanf = scanf("%[\e0-9]s",threshold);
        
        if(strcmp(threshold, "\e") == 0) {
            menu2(name, dictionarys);
        }
        
        scanf("%*[^\n]");
        
        if(returnScanf == 0) {
            printf("You're input can contains numbers only ! Please retry\n");
        }
        
    } while(returnScanf == 0);
    
    return threshold;
    
}

// open dictionary and display words that fit given threshold
void displayWords(int threshold, char* name, LinkedList* dictionarys){
    
    FILE* dictionary = fopen(name,"r+");
    char* choice = malloc(sizeof(char) *255);
    char* wordFromFile = malloc(sizeof(char)*255);
    char* wordToFind = malloc(sizeof(char) * 255);
    int displayed = 0;
    
    if(!dictionary){
        printf("Error while opening dictionary\n");
    }
    else{
        
        //executes only if entered word is a real string
        wordToFind = getTheWordToSearch(name,dictionarys);
        
        
        while (fgets(wordFromFile, 255, dictionary)) {
            
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';
            
            if(my_strcmp(wordToFind, wordFromFile) <= threshold){
                printf("%s\n",wordFromFile);
                displayed = 1;
            }
        }
        
        
        free(wordToFind);
        free(wordFromFile);
        
        
        //launch a second try if word to search wasn't found
        if(!displayed){
            
            printf("The word you've entered isn't close to any other in this dictionary would you like to try with an other word? y/n\n");
            do{
                scanf("%s", choice);
                
                switch (choice[0]){
                    case 121:
                        displayWords(threshold, name, dictionarys);
                        break;
                    case 110 :
                        menu2(name, dictionarys);
                        break;
                    default:
                        printf("Wrong entry ! Please retry\n");
                        break;
                }
                
            }while(choice[0] != 121 && choice[0] != 110);
            
        }
        
    }
    fclose(dictionary);
}

char* getTheWordToSearch(char* name, LinkedList* dictionarys){
    
    char* word = malloc(sizeof(char)*255);
    char* choice = malloc(sizeof(char)*255);
    int returnScanf = 0;
    
    printf("Enter the word you would like to work with\n");
    getchar();
    returnScanf = scanf("%[\ea-zA-ZÀÁÂÆÇÈÉÊËÌÍÎÏÑÒÓÔŒÙÚÛÜÝŸàáâæçèéêëìíîïñòóôœùúûüýÿ'-]s",word);
    
    if(strcmp(word, "\e") == 0) {
        getTheWordToSearch(name,dictionarys);
    }
    
    if(strcmp(word, "\e\e") == 0) {
        initTresholdResearch(name,dictionarys);
    }
    
    scanf("%*[^\n]");
    
    if(returnScanf == 0){
        printf("Please make sure you have entered a correct word\n");
        printf("Would you like to try again? y/n\n");
        
        do{
            scanf("%s",choice);
            switch (*choice) {
                case 121:
                    getTheWordToSearch(name,dictionarys);
                    break;
                case 110:
                    menu2(name, dictionarys);
                    break;
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
            
        }while(*choice != 121 && *choice != 110);
        
    }
    
    return word;
    
}
