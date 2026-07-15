#include "dictionaries.h"
#include <stdio.h>
#include <stdarg.h>
// Forward declaration
void dict_insert(dict *dic, char *key,enum types t, va_list args);


// Simple hash function
unsigned int hash(char *key) 
{
    unsigned int  hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash;
}


// Initialize dictionary
dict Dict_innit(int size)
{
    dict dic;
    dic.table = malloc(sizeof(dict_entry*)*size);
    dic.size = size;
    dic.key_count = 0;
    // Initialize all entries to NULL
 
    for(int i=0;i<size;i++) 
        dic.table[i] = NULL;
    
    return dic;
}

// Create dictionary
dict Dictionary(int size, ...){
    dict dic = Dict_innit(size);

    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; i++)
    { 
        char* key = va_arg(args, char*);
        enum types t = va_arg(args,enum types);
        dict_insert(&dic,key,t,args);
        // Advance the args pointer based on type
        switch (t)
        {
        case string:
            va_arg(args, char*);
            break;
        case integer:
            va_arg(args, int);
            break;
        case floating:
            va_arg(args, double);
            break;
        default:
            va_arg(args, void*);
            break;
        }
        
    }
    va_end(args);
    return dic;
}
//resize dictionary
dict resize_dict(dict *dic, int new_size)
{
    dict new_dic = Dict_innit(new_size);
    dict_entry *entry;
    for(int i = 0; i < dic->size; i++)
    {
        
        entry = dic->table[i];
        while (entry != NULL)
        {
            
            switch (entry->type)
            {
            case string:
                insert(&new_dic,entry->key,string,(char*)entry->value);
                break;
            case integer:
                insert(&new_dic,entry->key,integer,*(int*)entry->value);
                break;
            case floating:
                insert(&new_dic,entry->key,floating,*(double*)entry->value);
                break;
            default:
                insert(&new_dic,entry->key,pointer,entry->value);
                break;
            }
            free(entry->value);
            entry->value = NULL;
            if (entry->key != NULL)
                {
                    free(entry->key);
                    entry->key = NULL;
                }
            dict_entry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(dic->table);
    return new_dic;
}

enum types typeOffEntry(dict * d,char* key){
    int index = hash(key)% d->size;
    if (d->table[index] == NULL)
        return -1;  
    
    if(strcmp(d->table[index]->key,key) == 0)
        {
            return d->table[index]->type;
        }
    else
    {
        dict_entry *entry = d->table[index];
        while (entry != NULL)
        {
            entry = entry->next;
            if (strcmp(entry->key, key) == 0)
            {
                return entry->type;
            }
        }
        return -1;
    }
}
// Function to get dictionary entry by key
void* dict_get(dict *d, char *key)
{
    int index = hash(key)% d->size;
    if(d->table[index] == NULL)
        return NULL;
    if(strcmp(d->table[index]->key,key) == 0)
        {
            
            return d->table[index]->value;
        }
    else
    {
        dict_entry *entry = d->table[index];
        while (entry != NULL)
        {
            entry = entry->next;
            if (strcmp(entry->key, key) == 0)
            {
                return entry->value;
            }
        }
        return NULL;
    }
}





// Function to update existing entry
void update_value(dict_entry *entry, enum types t, va_list args)
{
    switch (t)
    {
        case string:
            free(entry->value);
            char *strdata = va_arg(args, char*);
            entry->value = malloc(strlen(strdata)+1);
            strcpy((char*)entry->value, strdata);
            break;
        case integer:
            free(entry->value);
            int *intdata = malloc(sizeof(int));
            *intdata = va_arg(args, int);
            entry->value = intdata;
            break; 
        case floating:
            free(entry->value);
            double *data = malloc(sizeof(double));
            *data = va_arg(args, double);
            entry->value = data;
            break;
        default:
            entry->type = pointer;
            entry->value = va_arg(args, void*);
        break;
    }
    entry->type = t;
}



// Function to add a new entry
void add_new_entry(dict_entry *entry, enum types t, va_list args)
{
    switch (t)
    {
    case string:
        char *strdata = va_arg(args, char*);
        entry->value = malloc(strlen(strdata)+1);
        strcpy((char*)entry->value, strdata);
        break;
    case integer:
        int *intdata = malloc(sizeof(int));
        *intdata = va_arg(args, int);
        entry->value = intdata;
        break; 
    case floating:
        double *data = malloc(sizeof(double));
        *data = va_arg(args, double);
        entry->value = data;
        break;
    default:
        entry->type = pointer;
        entry->value = va_arg(args, void*);
        break;
    }
    entry->type = t;
    entry->next = NULL;
}



// insert function that accepts va_list
void dict_insert(dict *dic, char *key,enum types t, va_list args)
{
    
    int index = hash(key)%dic->size;

    if(dic->table[index] == NULL)
    {
        // Key does not exist, create new entry
        dic->table[index] = malloc(sizeof(dict_entry));
        dict_entry *entry = dic->table[index];
        add_new_entry(entry,t, args);
        entry->key = malloc(sizeof(char*));
        strcpy(entry->key, key);
        dic->key_count++;
    }
    else 
    {   
        if(strcmp(dic->table[index]->key,key) == 0)
        {
            // Key exists, update value
            update_value(dic->table[index], t, args); 
        }
        
        else
        {
            // Collision handling (simple chaining)
            dict_entry *entry = dic->table[index];
            while (entry->next != NULL)
            {
                entry = entry->next;
                if(strcmp(entry->key, key) == 0)
                {
                    // Key exists, update value
                    update_value(entry, t, args);
                    return;
                }
            }   
            entry->next = malloc(sizeof(dict_entry));
            entry = entry->next; 
            entry->key = malloc(sizeof(char*));
            strcpy(entry->key, key);
            add_new_entry(entry,t, args);
            dic->key_count++;
        }
    }
}

 
// used by the user
void insert(dict *dic,char *key,enum types t,...)
{
    va_list args;
    va_start(args,t);
    // Check load factor and resize if necessary
    if (dic->key_count >= (dic->size *2)) 
        *dic = resize_dict(dic, dic->size * 3);
    dict_insert(dic,key,t,args);
    va_end(args);
}

void dict_remove(dict *d,char* key)
{
    int index = hash(key)% d->size;
    dict_entry *entry = d->table[index];
    if (entry == NULL)
        return;
    if (strcmp(entry->key, key) == 0)
    {
        d->table[index] = entry->next;
        free(entry->key);
        free(entry->value);
        free(entry);
        d->key_count--;
        return;
    }
    while (entry->next != NULL)
    {
        if (strcmp(entry->next->key, key) == 0)
        {
            dict_entry *temp = entry->next;
            entry->next = entry->next->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            d->key_count--;
            return;
        }
        entry = entry->next;
    }
}