//
// Created by shantanu on 11/4/17.
//

#ifndef MACRO_PRO_PARA_TABLES_H
#define MACRO_PRO_PARA_TABLES_H
typedef struct pos_actual_line {
    char *actual;
    long long int position;
    struct pos_actual_line *next;
}pos_actual_line;

typedef struct pos_actual {
    struct pos_actual_line *head;
    long long int count;
}pos_actual;

typedef struct formal_pos_line {
    char *formal;
    long long int position;
    struct formal_pos_line *next;
}formal_pos_line;

typedef struct formal_pos {
    struct formal_pos_line *head;
    long long int count;
}formal_pos;

void build_pa(pos_actual *pa);
void build_fp(formal_pos *fp);
void add_to_fp(formal_pos *fp, char *item);
void display_pa(pos_actual *pa);
void display_fp(formal_pos *pa);
void add_to_pa(pos_actual *pa, char *item);
#endif //MACRO_PRO_PARA_TABLES_H
