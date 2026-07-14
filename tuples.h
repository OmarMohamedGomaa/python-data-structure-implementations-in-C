<<<<<<< HEAD
#ifndef TUPLE_H
#define TUPLE_H
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "typesenum.h"
typedef struct tupleNode {
    void * data;
    enum types type;
    
} tupleNode;

typedef struct tuple {
    int size;
    tupleNode ** nodes;
} tuple;
tuple makeTuple(int size, ...);
void * tupleAt(int index,tuple *t);
void displayTuple(tuple *t);
enum types tupleTypeAt(int index,tuple *t);
=======
#ifndef TUPLE_H
#define TUPLE_H
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "typesenum.h"
typedef struct tupleNode {
    void * data;
    enum types type;
    
} tupleNode;

typedef struct tuple {
    int size;
    tupleNode ** nodes;
} tuple;
tuple makeTuple(int size, ...);
void * tupleAt(int index,tuple *t);
void displayTuple(tuple *t);
enum types tupleTypeAt(int index,tuple *t);
>>>>>>> 4ef01f8 (fixing bugs)
#endif   