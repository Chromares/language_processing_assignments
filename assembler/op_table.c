//
// Created by shantanu on 3/9/16.
//

#include "op_table.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#define ASSEMBLY "assembly.txt"
#define RESTRICTIONS "restrictions.txt"
#define REG_NUMBER 12

char *reg_names[] = {"ah", "bh", "ch", "dh", "al", "bl", "cl", "dl", "areg", "breg", "creg", "dreg"};

//start writing file here, cant pass so much data without another data structure;

int find_nmemonic(char *line, op_table *op_check, restrictions *res_head, location_counter *LC,
                  struct symbol_table *symtable) {
    char *token, *main, *copy;
    int pre = 0, post = 0, *point, g = 0, i;
    int k = 0;
    op *temp;
    symbol_item *total_temp;
    copy = malloc(sizeof(line));
    strcpy(copy, line);
    token = strtok(line, " ");
    point = &pre;

    int p = 0;
    while(token != NULL) {
        if(!strcmp(token, " ")) {
            token = strtok(NULL, " ");
            continue;
        }
        p = 0;
        temp = op_check->head;
        for (i = 0; i < op_check->length; i++) {
            if (!strcmp(temp->op_name, token)) {
                if(g) {
                    printf("More than one ops in one line!\n");
                    exit(EXIT_FAILURE);
                }
                g++;
                step_update_LC(LC, temp->length);
                point = &post;
                main = malloc(sizeof(token));
                strcpy(main, token);
                p++;
            }   //leave behind a key, use +ve numbers for all;
            temp = temp->next;
        }
        if(!p) {
            total_temp = symtable->head;
            for (k = 0; k < REG_NUMBER; k++) {
                if(!strcmp(token, reg_names[k])) {
                    p++;
                }
            }
            if(!p) {
                    add_symbol(symtable, token, LC);
            }
        }
        *point += 1;
        token = strtok(NULL, " ");
    }
    if(g)
        post--;
    restrictions *tempr;
    tempr = res_head;
    while((tempr->next != NULL) && g) {
        if(!strcmp(main, tempr->opname)) {
            if((pre != tempr->lbound) || (post != tempr->ubound)) {
                printf("Operands dude! Operands.\n"); //use LC next time
                exit(EXIT_FAILURE);
            }
        }
        tempr = tempr->next;
    }


    //if no match, we assume no restrictions!
    //x equ y -we know whats up but how do we pass info to pass 2? too much work re checking all operands
    //if no g, its a directive
    //directives need to be hard coded, so we leave it here for now
    //return 1 if okay, 0 if soft error, exit if hard error, 3 if directive, 4 if directive executed

    if(!g) {
        token = strtok(copy, " ");
        while(token != NULL) {
            if (!strcmp(token, " ")) {
                token = strtok(NULL, " ");
                continue;
            }
            if((!strcmp(token, "start")) || (!strcmp(token, "Start"))) {
                token = strtok(NULL, " ");
                step_update_LC(LC, (atoi(token) - LC->previous_line->count));
                return 4;
            }
            token = strtok(NULL, " ");
        }
        step_update_LC(LC, 1); //assume length of assembler directives to be 1
        return 3;
    }
    else
        return 1;
}

void build_op_table(op_table *opcheck_table) {
    FILE *opcheck = fopen(ASSEMBLY, "r");
    if(opcheck == NULL)
        exit(EXIT_FAILURE);
    op *temp;
    temp = opcheck_table->head;
    char *line = NULL, *token;
    size_t len = 0;
    __ssize_t read = 0;
    while((read = getline(&line, &len, opcheck)) != -1) {
        token = strtok(line, " ");
        temp->op_name = malloc(sizeof(token));
        strcpy(temp->op_name, token);
        token = strtok(NULL, " ");
        temp->op_code = (long)atoi(token);
        token = strtok(NULL, " ");
        temp->length = (long)atoi(token);
        temp->next = (op *)(malloc(sizeof(op)));
        temp = temp->next;
        opcheck_table->length++;
        temp->next = NULL;
    }
}

void build_res_table(restrictions *res_head) {
    FILE *rescheck = fopen(RESTRICTIONS, "r");
    if(rescheck == NULL)
        exit(EXIT_FAILURE);
    restrictions *temp;
    temp = res_head;
    char *line = NULL, *token;
    size_t len = 0;
    __ssize_t read = 0;
    while((read = getline(&line, &len, rescheck)) != -1) {
        token = strtok(line, " ");
        temp->opname = malloc(sizeof(token));
        strcpy(temp->opname, token);
        token = strtok(NULL, " ");
        temp->ubound = (int) (long)atoi(token);
        token = strtok(NULL, " ");
        temp->lbound = (int) (long)atoi(token);
        temp->next = (restrictions *)(malloc(sizeof(restrictions)));
        temp = temp->next;
        temp->next = NULL;
    }
    return;
}

void display_optable(op_table *opTable) {
    op *temp;
    temp = opTable->head;
    printf("\n\n------------------OP TABLE------------------\n\n");
    for (int i = 0; i < opTable->length; i++) {
        printf("%s\t%lld\t%lld", temp->op_name, temp->op_code, temp->length);
        temp = temp->next;
        printf("\n");
    }
    return;
}

void display_restable(restrictions *resTable) {
    restrictions *temp;
    temp = resTable;
    printf("\n\n------------------RES TABLE------------------\n\n");
    while (temp->next != NULL) {
        printf("%s\t%d\t%d", temp->opname, temp->lbound, temp->ubound);
        temp = temp->next;
        printf("\n");
    }
    return;
}