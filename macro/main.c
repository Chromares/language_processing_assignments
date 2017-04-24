#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "mnt.h"
#include "mdt.h"
#include "para_tables.h"

#define INPUT "input.txt"
#define OUTPUT "output.txt"

mnt *s_mnt;
mdt *s_mdt;

void collect() {
    FILE *pass;
    pass = fopen("inp.txt", "r");
    if(pass == NULL)
        exit(EXIT_FAILURE);

    FILE *pass_o;
    pass_o = fopen("outp.txt", "w+");
    char *line = NULL, *token, *sub;
    line = malloc((100 * sizeof(char)));
    size_t len = 100;
    __ssize_t read = 0;
    mntline *temp;
    char c = 'y', *hase;
    int qw, switcher = 0;
    long long int ds;   //dhobaless16.comp@coep.ac.in
    //printf("huhu");
    while ((read = getline(&line, &len, pass)) != -1) {

        if(switcher) {
            hase = malloc(sizeof(line));
            strcpy(hase, line);
            token = strtok(hase, " ");
            while (!strcmp(token, " ")) {
                token = strtok(NULL, " ");
            }
            if (!strcmp(token, "MEND") || !strcmp(token, "mend") || !strcmp(token, "Mend") || !strcmp(token, "MEND\n") || !strcmp(token, "mend\n") || !strcmp(token, "Mend\n")) {
                temp = s_mnt->head;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->end = s_mdt->count;
                switcher = 0;
                continue;
            }
            else {
                add_to_mdt(s_mdt, line);
            }
        }

        hase = malloc(sizeof(line));
        strcpy(hase, line);

        qw = add_to_mnt(s_mnt, line);

        if (!qw) {
            temp = s_mnt->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->start = s_mdt->count;
            switcher = 1;
            continue;
        }
        //just consume right now, we will expand later// also consume with pos
        fprintf(pass_o, "%s ", hase);
    }
    return;
}

int main() {
    mdt_up(s_mdt);
    mnt_up(s_mnt);

    collect();

    mdt_disp(s_mdt);
    mnt_disp(s_mnt);
    mntline *kat;
    kat = s_mnt->head;
    printf("hello\n");
    while(kat->next != NULL) {
        display_fp(kat->muhaha);
        kat = kat->next;
    }
    return 0;
}
