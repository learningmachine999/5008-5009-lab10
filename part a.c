#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

HashTable* createHashTable(int size) {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->size = size;
    newTable->table = (Node**)malloc(sizeof(Node*) * size);
    for(int i=0; i<size; i++)
        newTable->table[i] = NULL;
    return newTable;
}

void insert(HashTable* hashTable, int value) {
    int index = value % hashTable->size;
    Node* newNode = createNode(value);
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        Node *temp = hashTable->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printHashTable(HashTable* hashTable) {
    for(int i=0; i<hashTable->size; i++) {
        printf("Chain[%d] -> ", i);
        Node* temp = hashTable->table[i];
        while(temp) {
            printf("%d -> ", temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int size, numOfValues;
    printf("Chain Size:\n");
    scanf("%d", &size);
    
    HashTable* hashTable = createHashTable(size);

    printf("Number of values:\n");
    scanf("%d", &numOfValues);

    printf("Input Values:\n");
    for(int i=0; i<numOfValues; i++) {
        int value;
        scanf("%d", &value);
        insert(hashTable, value);
    }

    printHashTable(hashTable);

    return 0;
}