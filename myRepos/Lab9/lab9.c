#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
    struct RecordType *next; // Chaining
};

// Fill out this structure
struct HashType
{
    struct RecordType **table; 
    int size; 
};

// Compute the hash function
int hash(int x, int size)
{
    return x % size;
}

// Initialize the hash table with given size
struct HashType* initHashTable(int size)
{
    struct HashType* ht = (struct HashType*)malloc(sizeof(struct HashType));
    ht->size = size;
    ht->table = (struct RecordType**)malloc(sizeof(struct RecordType*) * size);
    
    for(int i = 0; i < size; i++)
    {
        ht->table[i] = NULL;
    }
    
    return ht;
}

// Insert a record into the hash table
void insertRecord(struct HashType* ht, struct RecordType* record)
{
    int index = hash(record->id, ht->size);
    struct RecordType* current = ht->table[index];
    if (current == NULL)
    {
        ht->table[index] = record;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = record;
    }
    record->next = NULL;
}

// Display hash table
void displayHashTable(struct HashType* ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        struct RecordType* current = ht->table[i];
        printf("Index %d:", i);
        while (current != NULL)
        {
            printf(" -> [ID: %d, Name: %c, Order: %d]", current->id, current->name, current->order);
            current = current->next;
        }
        printf("\n");
    }
}

// Free hash table
void freeHashTable(struct HashType* ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        struct RecordType* current = ht->table[i];
        struct RecordType* next;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
    }
    free(ht->table);
    free(ht);
}

// Main function
int main()
{
    struct HashType* myHashTable = initHashTable(10);
    // Example usage
    struct RecordType* newRecord = malloc(sizeof(struct RecordType));
    newRecord->id = 102;
    newRecord->name = 'A';
    newRecord->order = 1;
    insertRecord(myHashTable, newRecord);

    displayHashTable(myHashTable);
    freeHashTable(myHashTable);
    return 0;
}