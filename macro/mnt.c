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
    printf("NAME\t#\tSTART\tEND\n");
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

    token = strtok(line, " ");
    while(!strcmp(token, " ")) {
        token = strtok(NULL, " ");
    }
    if(!strcmp(token, "MACRO") || !strcmp(token, "macro") || !strcmp(token, "Macro")) {
        token = strtok(NULL, " ");
    }
    else
        return 1;

    if(s_mdt->head == NULL) {
      temp = malloc(sizeof(mntline));
      s_mdt->head = temp;
      temp->next = NULL;
    }
    else {
      temp = s_mdt->head;
      while(temp->next != NULL) {
        temp = temp->next;
      }
      temp->next = (mntline *)malloc(sizeof(mntline));
      temp->next->next = NULL;
      temp = temp->next;
    }
    temp->param = 0;


    //name
    while (!strcmp(token, " ")) {
        token = strtok(NULL, " ");
    }
    //printf("name is %s\n", token);
    temp->name = (char *)malloc(sizeof(token));
    if(token[(strlen(token) - 1)] == '\n')
        strncpy(temp->name, token, (strlen(token) - 1));
    else
        strcpy(temp->name, token);

    //dig up params
    formal_pos *huehue = malloc(sizeof(formal_pos));
    build_fp(huehue);
    char *para;
    token = strtok(NULL, " ");
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
    s_mdt->count += 1;

    return 0;
}
