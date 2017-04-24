//
// Created by shantanu on 1/9/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "op_table.h"
#define REG_NUMBER 12


char *regs[] = {"ah", "bh", "ch", "dh", "al", "bl", "cl", "dl", "areg", "breg", "creg", "dreg"};

void init_my_tables(symbol_table *symbols, location_counter *LC, op_table *op_check) {
    symbols->head = (symbol_item *)malloc(sizeof(symbol_item));
    LC->head = (location_count *)malloc(sizeof(location_count));
    LC->previous_line = malloc(sizeof(location_count));
    LC->previous_line = LC->head;
    LC->previous_line->next = NULL;
    symbols->head->next = NULL;
    op_check->head = (op *)(malloc(sizeof(op)));
    LC->length = 0;
    symbols->length = 0;
    op_check->length = 0;
    LC->head->count = 0;
    LC->previous_line->count = 0;
    return;
}

void pass_two (op_table *opcheck_table, symbol_table *symbols, int **literal_table_and_pool, int **forward_references,
               FILE *passone, location_counter *LC, restrictions *res) {
    FILE *passone_o = fopen("pass_one_out.txt", "r");
    char *line = NULL, *token, *sub;
    line = malloc((100* sizeof(char)));
    size_t len = 100;
    __ssize_t read = 0;
    op *temp_op;
    symbol_item *temp_si;
    char c = 'y';
    FILE *passtwo = fopen("pass_two_out.txt", "w+");
    while((read = getline(&line, &len, passone_o)) != -1) {
        token = strtok(line, " ");
        while (token != NULL) {
            sub = malloc(sizeof(token));
            strcpy(sub, token);
            //just find here all, we will later give op the right to print and give out keys instead
            if(sub[0] == '[') {
                fprintf(passtwo, "%s ", sub);
                token = strtok(NULL, " ");
                sub = malloc(sizeof(token));
                if(token[strlen(token) - 1] == '\n') {
                    strncpy(sub, token, strlen(token) - 1);
                }
                else
                    strcpy(sub, token);
            }
            if((sub[0] >= '0') && (sub[0] <= '9')) {
                fprintf(passtwo, "%s", sub);
                goto end;
            }
            for (int i = 0; i < REG_NUMBER; i++) {
                if(!strcmp(sub, regs[i])) {
                    fprintf(passtwo, "%d ", i);
                    i = REG_NUMBER;
                }
            }
            char *hase = NULL;
            temp_si = symbols->head;
            if(sub[strlen(sub) - 1] == '\n') {
                hase = strtok(sub, "\n");
            }
            if(hase != NULL) {
                sub = hase;
            }
            for (long long int i = 0; i < symbols->length; i++) {
                if(!strcmp(sub, temp_si->symbol_name)) {
                    if(temp_si->address == 0) {
                        c = 'n';
                        if(sub[strlen(sub) - 1] == '\n')
                            fprintf(passtwo, "%s", temp_si->symbol_name);
                        else
                            fprintf(passtwo, "%s ", temp_si->symbol_name);
                    }
                    else
                        fprintf(passtwo, "%lld ", temp_si->address);
                    i = symbols->length;
                }
                temp_si = temp_si->next;
            }
            temp_op = opcheck_table->head;
            for (long long int i = 0; i < opcheck_table->length; i++) {
                if(!strcmp(sub, temp_op->op_name)) {
                    fprintf(passtwo, "%lld ", temp_op->op_code);
                    i = opcheck_table->length;
                }
                if(!strcmp(sub, "dc") || !strcmp(sub, "ds")) {
                    fprintf(passtwo, "<DECLARATION DIRECTIVE> ");
                    i = opcheck_table->length;
                }
                temp_op = temp_op->next;
            }
            end:
            token = strtok(NULL, " ");
            if((token == NULL) && (c == 'n')) {
                c = 'y';
                fprintf(passtwo, "\n\t<UNDEFINED SYMBOL ERROR>");
            }
            if((token == NULL) && ((sub[0] >= '0') && (sub[0] <= '9')));
            else if(token == NULL)
                fprintf(passtwo, "\n");
        }
    }
    return;
}

void pass_one(op_table *opcheck_table, symbol_table *symbols, int **literal_table_and_pool, int **forward_references,
              FILE *as, location_counter *LC) {
    restrictions *res = malloc(sizeof(restrictions));
    res->next = NULL;
    res->lbound = 0;
    res->ubound = 0;
    res->opname = NULL;
    build_res_table(res);

    build_op_table(opcheck_table);

    char *line = NULL, *token;
    size_t len = 100;
    __ssize_t read = 0;
    int check;
    char *space, *base, *hase;

    //now go through assembly input
    //linear search, every time? :/ need something awesome
    //so many linked lists dont look good either;
    //lets go parallel with an optional hash map based on memory analysis
    //lets just finish the single thread part first;

    as = fopen("inp.txt", "r");
    space = malloc(sizeof(char));
    space[0] = ' ';
    location_count *temp;
    temp = LC->head;

    FILE *passone = fopen("pass_one_out.txt", "w+");
    while((read = getline(&line, &len, as)) != -1) {
        base = malloc(sizeof(line));
        strcpy(base, line);
        check = find_nmemonic(line, opcheck_table, res, LC, symbols);
        if(check == 3) {
            fprintf(passone, "[%lld] ", temp->count);
            token = strtok(base, " ");
            while(token != NULL) {
                if(!strcmp(token, space)) {
                    token = strtok(NULL, " ");
                    continue;
                }
                hase = malloc(sizeof(token));
                strcpy(hase, token);
                if((hase != NULL) && (*hase != '\n'))
                    fprintf(passone, "%s", hase); //should contain \n
                token = strtok(NULL, " ");
                if(token != NULL)
                    fprintf(passone, " ");
            }
            temp = temp->next;
            continue;
        }
        else if(check == 1) {
            token = strtok(base, " ");
            fprintf(passone, "[%lld] ", temp->count);
            while(token != NULL) {
                if(!strcmp(token, space)) {
                    token = strtok(NULL, " ");
                    continue;
                }
                hase = malloc(sizeof(token));
                strcpy(hase, token);
                if((hase != NULL) && (*hase != '\n'))
                    fprintf(passone, "%s", hase); //should contain \n
                token = strtok(NULL, " ");
                if(token != NULL)
                    fprintf(passone, " ");
            }
            temp = temp->next;
            continue;
        }
        else if(check == 4) {
            temp = temp->next;
            continue;
        }
    }
    display_optable(opcheck_table);
    display_restable(res);
    display_symtable(symbols);
    fclose(passone);
    fclose(as);
    pass_two(opcheck_table, symbols, literal_table_and_pool, forward_references, passone, LC, res);
    return;
}

//void init_everything_else(int **pInt, int **pInt1) {
//
//}

int main (int argc, char *argv[]) {
    FILE *file = fopen(argv[0], "r");
    location_counter LC;
    symbol_table symbols;
    op_table opcheck_table;
    int **literal_table_and_pool, **forward_references;
    init_my_tables(&symbols, &LC, &opcheck_table);
    //init_everything_else(literal_table_and_pool, forward_references);
    pass_one(&opcheck_table, &symbols, literal_table_and_pool, forward_references, file, &LC);
    return 0;
}
