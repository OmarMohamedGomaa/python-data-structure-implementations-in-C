#include "list.h"
#include <stdarg.h>
#include <string.h>
void display_list(list *l){
    node* current = l->head;
    printf("[");
    while (current != NULL)
        {
        switch (current->type)
        {
        case integer:
            printf("%d ",*(int*)current->data);
            break;
        case string:
            printf("%s ",(char*)current->data);
            break;
        case floating:
            printf("%f ",*(double*)current->data);
            break;
        default:
            printf("%p ",current->data);
            break;
        }
        current = current->next;
        if (current != NULL)
        {
            printf(",");
        }
    }
    printf("] \n");
}
void insertAt(list* l,int index,enum types t,...){
    if (index < 0 || index > l->size) 
    {
        printf("Index out of bounds\n");
        return;
    }
    node* newNode = malloc(sizeof(node));
    va_list args;
    va_start(args, t);
    switch (t)
        {
        case string:
            newNode->type = string;
            char *strdata = va_arg(args, char*);
            newNode->data = malloc(strlen(strdata)+1);
            strcpy((char*)newNode->data, strdata);
            break;
        case integer:
            newNode->type = integer;
            int *intdata = malloc(sizeof(int));
            *intdata = va_arg(args, int);
            newNode->data = intdata;
            break;
        case floating:
            newNode->type = floating;
            double *data = malloc(sizeof(double));
            *data = va_arg(args, double);
            newNode->data = data;
            break;
        default:
            newNode->type = pointer;
            newNode->data = va_arg(args, void*);
            break;
        }
    va_end(args);
    if (index == 0) {
        newNode->next = l->head;
        l->head = newNode;
    } else {
        node* current = l->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    l->size++;
    va_end(args);   
}
enum types typeAt(list * l,int index){
    if (index < 0 || index >= l->size) 
    {
        printf("Index out of bounds\n");
        return -1 ;
    }
    node* current = l->head;
    for (int i = 0; i < index; i++) 
        current = current->next;
    
    return current->type;
}   
void* at(list * l,int index){
    if (index < 0 || index >= l->size) {
        printf("Index out of bounds\n");
        return NULL ;
    }
    node* current = l->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}
void removeAt(list * l,int index){
    if (index < 0 || index >= l->size) {
        printf("Index out of bounds\n");
        return;
    }
    node* toDelete;
    if (index == 0) {
        toDelete = l->head;
        l->head = l->head->next;
    }
    else {
        node* current = l->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }
    free(toDelete->data);
    free(toDelete);
    l->size--;
}
void removeBack(list * l){
    removeAt(l, l->size - 1);
}
void removeFront(list * l){
    removeAt(l, 0);
}
list tolist(int size,...){
    list l;
    list_init(&l);
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; i++) {
        enum types t = va_arg(args, enum types);
        switch (t)
        {
        case integer:
            insertAt(&l,i,t,va_arg(args,int));
            break;
        case string:
            insertAt(&l,i,t,va_arg(args,char*));
            break;
        case floating:
            insertAt(&l,i,t,va_arg(args,double));
            break;
        default:
            insertAt(&l,i,t,va_arg(args,void*));
            break;
        }
    }
    return l;
}
void list_init(list * l){
    l->head = NULL;
    l->size = 0;
}
