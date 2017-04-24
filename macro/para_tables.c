//
// Created by shantanu on 11/4/17.
//
#include "para_tables.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

void build_pa(pos_actual *pa)  {
    pa = malloc(sizeof(pos_actual));
    pa->head = NULL;
    pa->count = 0;
    return;
}
void build_fp(formal_pos *fp) {
    fp = malloc(sizeof(formal_pos));
    fp->head = NULL;
    fp->count = 0;
    return;
}
void add_to_fp(formal_pos *fp, char *item) {
    formal_pos_line *temp;
    if(fp->head == NULL) {
      temp = malloc(sizeof(formal_pos_line));
      fp->head = temp;
      temp->next = NULL;
    }
    else {
      temp = fp->head;
      while(temp->next != NULL) {
          temp = temp->next;
        }
        temp->next = malloc(sizeof(formal_pos_line));
        temp = temp->next;
        temp->next = NULL;
    }

    temp->formal = malloc(sizeof(item));
    strcpy(temp->formal, item);
    fp->count += 1;
    temp->position = fp->count;
    temp->next = NULL;
    return;
}
void add_to_pa(pos_actual *pa, char *item) {
    pos_actual_line *temp;
    temp = pa->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->actual = malloc(sizeof(item));
    strcpy(temp->actual, item);
    pa->count += 1;
    temp->position = pa->count;
    temp->next = NULL;
    return;
}

void display_pa(pos_actual *pa) {
    pos_actual_line *temp;
    temp = pa->head;
    long long int i;
    for(i = 0; i < pa->count; i++) {
        printf("%lld\t %s\n", temp->position, temp->actual);
        temp = temp->next;
    }
    printf("-----------------\n");
    return;
}

void display_fp(formal_pos *pa) {
    formal_pos_line *temp;
    temp = pa->head;
    long long int i;
    for(i = 0; i < pa->count; i++) {
        printf("%lld\t %s\n", temp->position, temp->formal);
        temp = temp->next;
    }
    if(!pa->count)
        printf("\t<NO ARGUMENTS>\n");
    printf("-----------------\n");
    return;
}
