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

int d = 0, e = 0;

void check_and_write(char *line, FILE *pass_o) {
  if(!strcmp(line, "\n"))
    return;

  char *base = NULL, *token, *sub, *comp, *guigui, *nomp;
  base = malloc(sizeof(line));
  size_t len = 100;
  __ssize_t read = 0;
  long long int z, begin, end, check, l, r, x, o = 1, zzz;
  pos_actual *soka;
  pos_actual_line *looo;

  strcpy(base, line);
  token = strtok(base, " ");

  while (!strcmp(token, " ")) {
      token = strtok(NULL, " ");
  }

  mntline *hui = s_mnt->head;
  formal_pos_line *paracheck;
  mdtline *bui = s_mdt->head;

  //trim token
  comp = (char *)malloc(sizeof(token));
  if(token[(strlen(token) - 1)] == '\n')
      strncpy(comp, token, (strlen(token) - 1));
  else
      strcpy(comp, token);

  for(z = 0; z < s_mnt->count; z++) {
      sub = hui->name;
      if(!strcmp(comp, sub)) {  //comp has macro name, token too if not with \n
        //if token matches a mnt def name
        r = 0;
        begin = hui->start;
        end = hui->end;
        check = hui->param;
        paracheck = hui->muhaha->head;
        //first check
        //build_pa(soka);
        soka = malloc(sizeof(pos_actual));
        soka->head = NULL;
        soka->count = 0;

        token = strtok(NULL, " ");
        while(token != NULL) {
            if (!strcmp(token, " ") || !strcmp(token, "\n")) {  //maybe the arguments
                token = strtok(NULL, " ");
                continue;
            }
            nomp = (char *)malloc(sizeof(token));
            if(token[(strlen(token) - 1)] == '\n')
                strncpy(nomp, token, (strlen(token) - 1));
            else
                strcpy(nomp, token);
            add_to_pa(soka, nomp);
            token = strtok(NULL, " ");
        }
        if(soka->count != check) {
            fprintf(pass_o, "< incufficent parameters, cannot expand macro %s >\n", sub);
            return;
        }
        //convert and check, later
        for(l = 0; l < (begin - 1); l++) {
          bui = bui->next;
        }
        for(l = begin; l <= end; l++) {
          //fprintf(pass_o, "%s", bui->def);
          //tokenwise expansion
          guigui = malloc(sizeof(bui->def));  //def 1st line
          strcpy(guigui, bui->def);
          token = strtok(guigui, " ");  //a word in that line from def
          while(token != NULL) {
              o = 1;
              if (!strcmp(token, " ") || !strcmp(token, "\n")) {
                  token = strtok(NULL, " ");
                  continue;
              }
              paracheck = hui->muhaha->head;  //the pf table
              looo = soka->head;              //the af table
              for(zzz = 0; zzz < check; zzz++) {    //(l + 1)th match from fp parameter
                  nomp = (char *)malloc(sizeof(token));
                  if(token[(strlen(token) - 1)] == '\n')
                      strncpy(nomp, token, (strlen(token) - 1));
                  else
                      strcpy(nomp, token);
                  //printf("token %s against fp %s\n", nomp, paracheck->formal);
                  if(!strcmp(nomp, paracheck->formal)) { //if word in def, matches a fp parameter
                    //we replace it with actual parameter
                    while(looo->position != paracheck->position)
                      looo = looo->next;
                    o = 0;
                    //printf("replacing fromal %s with actual %s\n", paracheck->formal, looo->actual);
                    //fprintf(pass_o, "%s ", looo->actual); //print actual instead
                    if(token[(strlen(token) - 1)] == '\n')
                      fprintf(pass_o, "%s\n", looo->actual);
                    else
                      fprintf(pass_o, "%s ", looo->actual);  //not a parameter, just print the word
                    //break;
                  }
                  paracheck = paracheck->next;
              }
              if(o) {
                if(token[(strlen(token) - 1)] == '\n')
                  fprintf(pass_o, "%s", token);
                else
                  fprintf(pass_o, "%s ", token);  //not a parameter, just print the word
              }
              token = strtok(NULL, " ");        //try for next word
          }
          printf("crash\n");
          bui = bui->next;
          //l++;
          printf("here?\n");
          if(bui == NULL) {
            break;
          }
          printf("here l is %lld!\n", l);
        }
        printf("naaah\n");
        return;
      }
      hui = hui->next;
  }
  //nothing to expand
  fprintf(pass_o, "%s", line);
  return;
}
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
        if(e == 1) {  //expansion flag;
          //check_and_write(line, pass_o);
          hase = malloc(sizeof(line));
          strcpy(hase, line);
          goto kurwa;
        }
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
                if(s_mnt->count == k)
                  d = 0;
                continue;
            }
            //nested macro
            else if (!strcmp(token, "MACRO") || !strcmp(token, "macro") || !strcmp(token, "Macro") || !strcmp(token, "MACRO\n") || !strcmp(token, "macro\n") || !strcmp(token, "Macro\n")) {
                d = 1;
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
        d = 0;
        e = 1;
        //fprintf(pass_o, "%s", hase);
        kurwa:
        check_and_write(hase, pass_o);
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
