//
// Created by shantanu on 11/4/17.
//
#include "para_tables.h"
#ifndef MACRO_PRO_MNT_H
#define MACRO_PRO_MNT_H
typedef struct mntline {
    char *name;
    long long int param;
    long long int start;
    long long int end;
    struct formal_pos *muhaha;
    struct mntline *next;
}mntline;

typedef struct mnt {
    mntline *head;
    long long int count;
}mnt;

void mnt_up(mnt *s_mdt);
void mnt_disp(mnt *s_mdt);
int add_to_mnt(mnt *s_mdt, char *line);

#endif //MACRO_PRO_MNT_H
