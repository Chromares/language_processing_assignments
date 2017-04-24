//
// Created by shantanu on 11/4/17.
//

#include "mdt.h"
#include "mnt.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "para_tables.h"

void mdt_up(mdt *s_mdt) {
    s_mdt = malloc(sizeof(mdt));
    s_mdt->count = 0;
    s_mdt->head = NULL;
    return;
}
void mdt_disp(mdt *s_mdt) {
    mdtline *temp = s_mdt->head;
    long long int i = 0;
    printf("COUNT\tDEFINITION\n");
    for (i = 0; i < s_mdt->count; i++) {
        printf("%lld\t%s", temp->line_count, temp->def);
        temp = temp->next;
    }
    return;
}
void add_to_mdt(mdt *s_mdt, char *line) {

    mdtline *temp;
    if(s_mdt->head == NULL) {
        temp = malloc(sizeof(mdtline));
        s_mdt->head = temp;
        temp->next = NULL;
    }
    else {
      temp = s_mdt->head;
      while(temp->next != NULL) {
          temp = temp->next;
      }
      temp->next = malloc(sizeof(mdtline));
      temp->next->next = NULL;
      temp = temp->next;
    }

    s_mdt->count += 1;
    temp->line_count = s_mdt->count;
    temp->def = malloc(sizeof(line));
    strcpy(temp->def, line);
    return;
}
