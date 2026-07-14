<<<<<<< HEAD
#ifndef LIST_H
#define LIST_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "typesenum.h"

typedef struct node {
    void* data;
    enum types type;
    struct node* next;
} node;

typedef struct list {
    int size;
    struct node* head;
} list;


void list_init(list* l);

void display_list(list* l);
void insertAt(list* l,int index,enum types t,...);
void* at( list* l, int index);
void removeAt(list* l, int index);
void removeBack(list* l);
void removeFront(list* l);
enum types typeAt(list* l, int index);
list tolist(int size,...);



#endif 
=======
#ifndef LIST_H
#define LIST_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "typesenum.h"

typedef struct node {
    void* data;
    enum types type;
    struct node* next;
} node;

typedef struct list {
    int size;
    struct node* head;
} list;


void list_init(list* l);

void display_list(list* l);
void insertAt(list* l,int index,enum types t,...);
void* at( list* l, int index);
void removeAt(list* l, int index);
void removeBack(list* l);
void removeFront(list* l);
enum types typeAt(list* l, int index);
list tolist(int size,...);



#endif 
>>>>>>> 4ef01f8 (fixing bugs)
