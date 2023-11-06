#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flight.h"


Node * makeNode(flight* n, Node * nextItem) {
  Node * ret = (Node * ) malloc(sizeof(Node));
  ret->fly = n;
  ret->next = nextItem;
  return ret;
}//I got this method from the CS305 moodle page

flight* makeFlight(char* p, int n, int a, int d) {
  if(strlen(p) != 2 || n < 10 || n > 9999 || a < 0 || a > 2400 || d < 0 ||
     d > 2400) {
    printf("an attempt to make a flight had invalid information :( \n");
    return NULL;
  }
  flight* ret = (flight*) malloc(sizeof(flight));
  char* c = (char *) malloc(sizeof(char)*2);
  *c = *p;
  c[1] = p[1];
  ret->place = c;
  ret->num = n;
  ret->arrive = a;
  ret->depart = d;
  return ret;
}

Node* addNode(Node* flights, char* c, int n, int a, int d) {
  if(flights == NULL) {
    printf("Inserting flight: %s %d %d %d\n", c, n, a, d);
    return makeNode(makeFlight(c, n, a, d), NULL);
  }
  if(n == flights->fly->num){
    printf("flight with that code exists");
    return flights;
  }
  
  if(n < flights->fly->num) {
    Node* interm = makeNode(makeFlight(c, n, a, d), flights);
    printf("Inserting flight: %s %d %d %d\n", c, n, a, d);
    return interm;
  }
  flights->next = addNode(flights->next, c, n, a, d);
  return flights;
}


Node* makeList(Node* flights, FILE *fp) {
  rewind(fp);
  char* c;
  int n, a, d;
  
  if(fp == NULL) printf("null file :(");
  flights = NULL;

  int count = 0;
  *c = getc(fp);
  while(*c != EOF) {
    if(*c == '\n') count++;
    *c = getc(fp);
  }//gets line count from input file
  rewind(fp);
  
  for(int i = 0; i < count; i++) {
    if(fscanf(fp, "%s %d %d %d", c, &n, &a, &d) != 4) {
      printf("an attempt to make a flight had invalid information :( \n");
      continue;
    }
    if(strlen(c) != 2 || !isupper(c[0]) || !isupper(c[1]) || n < 10 || n > 9999 || a < 0 || a > 2400 || d < 0 ||
       d > 2400) {
      printf("an attempt to make a flight had invalid information :( \n");
      continue;
    }
    flights = addNode(flights, c, n, a, d);
  }
  
  return flights;
}


void printFlights(Node* flights) {
  if(flights == NULL) {
    printf("No flights currently listed\n");
    return;
  }
  printf("%s %d %d %d \n",
	 flights->fly->place, flights->fly->num,
	 flights->fly->arrive, flights->fly->depart);
  if(flights->next == NULL) return;
  printFlights(flights->next);
}

struct LLNode* insert(Node * flights, flight * f) {
  return makeNode(f, flights);
}

Node* delete(Node * flights, int num) {
  if(flights == NULL) return NULL;
  if(flights->fly->num == num) {
    printf("found it\n");
    Node* next = flights->next;
    freeNode(flights);
    return next;
  }
  flights->next = delete(flights->next, num);
  return flights;
}

void save(Node * flights, char * name) {
  FILE * fp = fopen(name, "w");
  if(fp == NULL) printf("file could not be opened. input valid filename");
  while(flights != NULL) {
    fprintf(fp, "%s %d %d %d \n", flights->fly->place, flights->fly->num,
	    flights->fly->arrive, flights->fly->depart);
    flights = flights->next;
  }
}

void freeNode(Node * out){
  free(out->fly->place);
  free(out->fly);
  free(out);
}

