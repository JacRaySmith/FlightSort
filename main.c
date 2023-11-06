#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

void main(int argv, char* argc[]) {
  FILE *fp;
  Node* flights = NULL;
  if(argv == 2) {
    fp = fopen(argc[1], "r");
    if(fp == NULL) {
      printf("no file input. Try again :(");
      return;
    }
    flights = makeList(flights, fp);
  }
  else if(argv > 2) {
    printf("please call with only the filename after flight \n");
    return;
  }

  printf("Would you like to add a flight(type a)\n"
"delete a flight(type d)\n"
"save the current contents of flights(type s)\n"
"print current list of flights(type p)\n"
"or quit(type q)\n\n");

  while(true) {
    char call;
    scanf("%s", &call);
    if(call == 'a') {
       char* c;
       int n, a, d;
       printf("print flight tag, number, arrival time, and departure time\n");
       scanf("%s %d %d %d", c, &n, &a, &d);
       flights = addNode(flights, c, n, a, d);
    }
    else if(call == 'd') {
      int num;
      printf("what flight number would you like to delete?\n");
      scanf("%d", &num);
      flights = delete(flights, num);
    }
    else if(call == 's') {
      printf("what is the file name you want to save to\n");
      scanf("%s", &call);
      save(flights, &call);
    }
    else if(call == 'p') printFlights(flights);
    else if(call == 'q') break;
    else printf("please input a valid call \n");
  }

  while(flights != NULL) {
    Node* free = flights;
    flights = flights->next;
    freeNode(free);
  }
  if(argv == 2)
    fclose(fp);
}
