#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdlib.h>
#include <string.h>
#include "typesenum.h"
typedef struct dict_entry
{
    char *key;
    void *value;
    enum types type;
    struct dict_entry *next;
}dict_entry; 
typedef struct dict
{ 
    dict_entry **table;
    int size;
    int key_count;
}dict;
dict Dictionary(int size, ...);
void insert(dict *d,char *key,enum types t,...);
void* dict_get(dict *d,char *key);
void dict_remove(dict *d,char *key);
enum types typeOffEntry(dict * d,char* key);
#endif  

