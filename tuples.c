#include "tuples.h"
#include <string.h>
#include <stdio.h>
tuple makeTuple(int size, ...){
    va_list args;
    va_start(args, size);
    tuple t;
    t.size = size;
    t.nodes = malloc(sizeof(tupleNode*)*size);
    tupleNode ** head = t.nodes;
    for (int i = 0; i < size; i++)
    {
        (t.nodes[i]) = malloc(sizeof(tupleNode));
        enum types ty = va_arg(args, enum types);
        switch (ty)
        {
        case string:
            (t.nodes[i])->type = string;
            char * str = va_arg(args, char*);
            char *strdata = malloc(strlen(str)+1);
            strcpy(strdata ,str);
            (t.nodes[i])->data = strdata;
            break;
        case integer:
            (t.nodes[i])->type = integer;
            int *intdata = malloc(sizeof(int));
            *intdata = va_arg(args, int);
            (t.nodes[i])->data = intdata;
            break;
        case floating:
            (t.nodes[i])->type = floating;
            double *data = malloc(sizeof(double));
            *data = va_arg(args, double);
            (t.nodes[i])->data = data;
            break;
        default:
            (t.nodes[i])->type = pointer;
            (t.nodes[i])->data = va_arg(args, void*);
            break;
        }
    }
    va_end(args);
    t.nodes = head;
    return t;
}
void * tupleAt(int index,tuple *t){
    if (index < t->size)
        return t->nodes[index]->data;
    else 
        return NULL;
}
enum types tupleTypeAt(int index,tuple *t){
    if (index < t->size)
        return t->nodes[index]->type;
    else 
        return -1;
}
void displayTuple(tuple *t)
{
    tupleNode* current ;
    printf("(");
    for (int i =0; i < t->size ; i++) {
        current = t->nodes[i];
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

        if ( i < t->size - 1)
            printf(",");
        
    }
    printf(") \n");
}
