//
// Created by shantanu on 3/9/16.
//

#ifndef ASSEMBLER_2PASS_SYM_TABLE_H
#define ASSEMBLER_2PASS_SYM_TABLE_H

#include "location_counter.h"

typedef struct symbol_item {
    long long int address;
    char *symbol_name;
    struct symbol_item *next;
}symbol_item;

typedef struct symbol_table {
    struct symbol_item *head;
    long long int length;
}symbol_table;

void add_symbol(symbol_table *symtable, char *token, location_counter *LC);
void display_symtable(symbol_table *symTable);

#endif //ASSEMBLER_2PASS_SYM_TABLE_H
