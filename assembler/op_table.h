//
// Created by shantanu on 3/9/16.
//

#ifndef ASSEMBLER_2PASS_OP_TABLE_H
#define ASSEMBLER_2PASS_OP_TABLE_H

#include "location_counter.h"
#include "sym_table.h"

typedef struct op {
    long long int length;
    char *op_name;
    long long int op_code;
    struct op *next;
}op;

typedef struct op_table {
    struct op *head;
    long long int length;
}op_table;

typedef struct restrictions {
    int ubound;
    int lbound;
    char *opname;
    struct restrictions *next;
}restrictions;

int find_nmemonic(char *line, op_table *op_check, restrictions *res, location_counter *LC, symbol_table *symable);
void build_op_table(op_table *op_check);
void build_res_table(restrictions *head);
void display_optable(op_table *opTable);
void display_restable(restrictions *resTable);

#endif //ASSEMBLER_2PASS_OP_TABLE_H
