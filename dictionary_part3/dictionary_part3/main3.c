//
//  main.c
//  dictionary_part3
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#include <stdio.h>
#include "gestorth.h"

int main(int argc, const char * argv[]) {
    
    LinkedList* dictionarys = newElement(NULL);
    LinkedList* importFiles = newElement(NULL);
    
    menu(dictionarys, importFiles);
    
    //mainMenu();
    
    return 0;
}
