//
// Created by shantanu on 11/4/17.
//

#ifndef MACRO_PRO_MDT_H
#define MACRO_PRO_MDT_H
typedef struct mdtline {
    long long int line_count;
    char *def;
    struct mdtline *next;
}mdtline;

typedef struct mdt {
    mdtline *head;
    long long int count;
}mdt;

void mdt_up(mdt *s_mdt);
void mdt_disp(mdt *s_mdt);
void add_to_mdt(mdt *s_mdt, char *line);

#endif //MACRO_PRO_MDT_H
