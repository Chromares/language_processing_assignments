//
// Created by shantanu on 11/4/17.
//
#include "mnt.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "para_tables.h"

void mnt_up(mnt *s_mdt) {
    s_mdt = (mnt *)malloc(sizeof(mnt));
    s_mdt->count = 0;
    s_mdt->head = NULL;
    return;
};
void mnt_disp(mnt *s_mdt) {
    mntline *temp = (mntline *)malloc(sizeof(mntline));
    temp = s_mdt->head;
    long long int i = 0;
    printf("NAME\tPARAMETER COUNT\tSTART\tEND\n");
    for (i = 0; i < s_mdt->count; i++) {
        printf("%s\t%lld\t%lld\t%lld\n", temp->name, temp->param, temp->start, temp->end);
        temp = temp->next;
    }
    return;
}
int add_to_mnt(mnt *s_mdt, char *line) {
    // 0 if cool, 1 if not a line for mdt, 2 if mend found;
    char *lined = NULL, *token = NULL;
    size_t len = 0;
    __ssize_t read = 0;
    long long int param_count = 0, start, end;
    mntline *temp;
    temp = s_mdt->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = (mntline *)malloc(sizeof(mntline));
    temp->next->next = NULL;
    token = strtok(line, " ");
    temp->param = 0;
    while (!strcmp(token, " ")) {
        token = strtok(NULL, " ");
    }
    if (!strcmp(token, "MACRO") || !strcmp(token, "macro") || !strcmp(token, "Macro")) {
        token = strtok(NULL, " ");
    }
    else
        return 1;
    //name
    while (!strcmp(token, " ")) {
        token = strtok(NULL, " ");
    }
    //if(!strcmp(token + ((sizeof(token) - 1)), "\n")) {
    //    token = strtok(NULL, "\n");
    //}
    //char *t = malloc(sizeof(token));
    temp->name = (char *)malloc(sizeof(token));
    if(token[(strlen(token) - 1)] == '\n')
        strncpy(temp->name, token, (strlen(token) - 1));
    else
        strcpy(temp->name, token);
    //strcpy(temp->name, token);

    //dig up params
    formal_pos *huehue = malloc(sizeof(formal_pos));
    build_fp(huehue);
    char *para;
    while(token != NULL) {
        if (!strcmp(token, " ") || !strcmp(token, "\n")) {
            token = strtok(NULL, " ");
            continue;
        }
        para = (char *)malloc(sizeof(token));
        if(token[(strlen(token) - 1)] == '\n')
            strncpy(para, token, (strlen(token) - 1));
        else
            strcpy(para, token);

        add_to_fp(huehue, para);
        temp->param += 1;
        token = strtok(NULL, " ");
    }
    temp->muhaha = huehue;
    return 0;
}