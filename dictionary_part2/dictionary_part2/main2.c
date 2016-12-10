//
//  main.c
//  dictionary_part2
//
//  Created by Bérangère La Touche on 10/12/2016.
//  Copyright © 2016 Bérangère La Touche. All rights reserved.
//

#include <stdio.h>
#include "gestrech.h"

int main(int argc, const char * argv[]) {
    
    LinkedList* dictionarys = newElement(NULL);
    
    menu(dictionarys);
    
    return 0;
}
