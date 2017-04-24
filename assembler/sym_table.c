//
// Created by shantanu on 3/9/16.
//

#include "sym_table.h"
#include "location_counter.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

char *p;

void add_symbol(symbol_table *symtable, char *token, location_counter *LC) {
    if(!strcmp(token, " "))
        return;
    //assembler directives
    if(!strcmp(token, "start") || !strcmp(token, "Start"))
        return;
    char *l;
    if(token[strlen(token) - 1] == '\n') {
        l = strtok(token, "\n");
        token = l;
    }
    symbol_item *tempr;
    tempr = symtable->head;
    int i = 0;
    if(!strcmp(token, "dc") || !strcmp(token, "ds")) {
        //search for p, use lc + 1;
        for (i = 0; i < symtable->length; i++) {
            if(!strcmp(tempr->symbol_name, p)) {
                tempr->address = (LC->previous_line->count);
                return;
            }
            tempr = tempr->next;
        }
        if(i == symtable->length) {
            tempr->symbol_name = malloc(sizeof(p));
            strcpy(tempr->symbol_name, p);
            tempr->next = malloc(sizeof(symbol_item));
            tempr = tempr->next;
            tempr->next = NULL;
            tempr->address = 0;
            symtable->length += 1;
        }
        return;
    }

    p = malloc(sizeof(token));
    if(token[(strlen(token) - 1)] == '\n')
        strncpy(p, token, (strlen(token) - 1));
    else
        strcpy(p, token);
    if((p[0] >= '0') && (p[0] <= '9'))
        return;
    for (i = 0; i < symtable->length; i++) {
        if(!(strcmp(token, tempr->symbol_name))) {
            return;
        }
        tempr = tempr->next;
    }
    symbol_item *temp;
    temp = symtable->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->symbol_name = malloc(sizeof(token));
    strcpy(temp->symbol_name, p);
    temp->next = malloc(sizeof(symbol_item));
    temp = temp->next;
    temp->next = NULL;
    temp->address = 0;
    symtable->length += 1;
    return;
}

void display_symtable(symbol_table *symTable) {
    symbol_item *temp;
    temp = symTable->head;
    printf("\n\n------------------SYM TABLE------------------\n\n");
    for (int i = 0; i < symTable->length; i++) {
        printf("%s\t%lld", temp->symbol_name, temp->address);
        temp = temp->next;
        printf("\n");
    }
    return;
}