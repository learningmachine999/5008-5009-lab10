#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1
#define DELETED -2

typedef struct HashTable {
    int size;
    int* table;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->size = size;
    newTable->table = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
        newTable->table[i] = EMPTY;
    return newTable;
}

int hash(int value, int size) {
    return value % size;
}

int hash2(int value) {
    return 7 - (value % 7);
}

void insertLinearProbing(HashTable* hashTable, int value) {
    int index = hash(value, hashTable->size);
    while(hashTable->table[index] != EMPTY && hashTable->table[index] != DELETED) {
        index = (index + 1) % hashTable->size;
    }
    hashTable->table[index] = value;
}

void insertQuadraticProbing(HashTable* hashTable, int value) {
    int index = hash(value, hashTable->size);
    int i = 0;
    while(hashTable->table[index] != EMPTY && hashTable->table[index] != DELETED) {
        i++;
        index = (index + i*i) % hashTable->size;
    }
    hashTable->table[index] = value;
}

void insertDoubleHashing(HashTable* hashTable, int value) {
    int index = hash(value, hashTable->size);
    int i = 0;
    int index2 = hash2(value);
    while(hashTable->table[index] != EMPTY && hashTable->table[index] != DELETED) {
        i++;
        index = (index + i*index2) % hashTable->size;
    }
    hashTable->table[index] = value;
}

void printHashTable(HashTable* hashTable) {
    for(int i = 0; i < hashTable->size; i++) {
        if(hashTable->table[i] != EMPTY && hashTable->table[i] != DELETED)
            printf("Slot[%d]: %d\n", i, hashTable->table[i]);
        else
            printf("Slot[%d]: EMPTY\n", i);
    }
}

int main() {
    int size, numOfValues, method;
    printf("Enter size of the hash table:\n");
    scanf("%d", &size);
    
    HashTable* hashTable = createHashTable(size);

    printf("Enter number of values:\n");
    scanf("%d", &numOfValues);

    printf("Select probing method (1: Linear, 2: Quadratic, 3: Double Hashing):\n");
    scanf("%d", &method);

    printf("Input Values:\n");
    for(int i = 0; i < numOfValues; i++) {
        int value;
        scanf("%d", &value);
        switch(method) {
            case 1:
                insertLinearProbing(hashTable, value);
                break;
            case 2:
                insertQuadraticProbing(hashTable, value);
                break;
            case 3:
                insertDoubleHashing(hashTable, value);
                break;
            default:
                printf("Invalid method selected.\n");
                return -1;
        }
    }

    printHashTable(hashTable);

    return 0;
}