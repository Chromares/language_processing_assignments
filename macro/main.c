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
    pass_o = fopen("output.txt", "w+");
    if(pass_o == NULL)
        exit(EXIT_FAILURE);
    char *line = NULL, *token, *sub;
    line = malloc((100 * sizeof(char)));
    size_t len = 100;
    __ssize_t read = 0;
    mntline *temp;
    char c = 'y', *hase;
    int qw, switcher = 0, qww;
    long long int ds, i, k;
    while ((read = getline(&line, &len, pass)) != -1) {
        //printf("%s\n", line);
        if(switcher) {
            hase = malloc(sizeof(line));
            strcpy(hase, line);
            token = strtok(hase, " ");
            while (!strcmp(token, " ")) {
                token = strtok(NULL, " ");
            }
            if(!strcmp(token, "MEND") || !strcmp(token, "mend") || !strcmp(token, "Mend") || !strcmp(token, "MEND\n") || !strcmp(token, "mend\n") || !strcmp(token, "Mend\n")) {
                temp = s_mnt->head;
                //while(temp->next != NULL) {
                //    temp = temp->next;
                //}
                //k = switcher - 1;
                for(i = 1; i < (s_mnt->count - k); i++) {
                  temp = temp->next;
                }
                temp->end = s_mdt->count;
                switcher--;
                k++;
                continue;
            }
            //nested macro
            else if (!strcmp(token, "MACRO") || !strcmp(token, "macro") || !strcmp(token, "Macro") || !strcmp(token, "MACRO\n") || !strcmp(token, "macro\n") || !strcmp(token, "Macro\n")) {
                qww = add_to_mnt(s_mnt, line);
                temp = s_mnt->head;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->start = s_mdt->count + 1;
                switcher++;
                continue;
            }
            else {
                add_to_mdt(s_mdt, line);
                continue;
            }
        }
        k = 0;
        hase = malloc(sizeof(line));
        strcpy(hase, line);
        qw = add_to_mnt(s_mnt, line);

        if (!qw) {
            temp = s_mnt->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->start = (s_mdt->count + 1);
            switcher = 1;
            continue;
        }
        //just consume right now, we will expand later// also consume with pos
        fprintf(pass_o, "%s", hase);
    }
    return;
}

int main() {
    //mdt_up(s_mdt);
    //mnt_up(s_mnt);
    s_mdt = malloc(sizeof(mdt));
    s_mdt->count = 0;
    s_mdt->head = NULL;


    s_mnt = malloc(sizeof(mnt));
    s_mnt->count = 0;
    s_mnt->head = NULL;

    collect();

    printf("MDT Table\n\n");
    mdt_disp(s_mdt);
    printf("\n\nMNT Table\n\n");
    mnt_disp(s_mnt);
    printf("\n\nFormal vs Positional Tables\n\n");
    mntline *kat;
    kat = s_mnt->head;
    long long int i;
    printf("-----------------\n");
    for(i = 0; i < s_mnt->count; i++) {
        printf("   %s\n", kat->name);
        display_fp(kat->muhaha);
        kat = kat->next;
    }
    return 0;
}
