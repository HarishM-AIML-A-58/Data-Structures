    /*Done By M.Harish AIML A 231501058*/
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct HashTable {
        int size;
        int count; // Number of elements in the table
        int* keys;
        int* values;
        bool* isOccupied; // Indicates if a slot is occupied
    } HashTable;

    HashTable* createTable(int size) {
        HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
        newTable->size = size;
        newTable->count = 0;
        newTable->keys = (int*)malloc(sizeof(int) * size);
        newTable->values = (int*)malloc(sizeof(int) * size);
        newTable->isOccupied = (bool*)malloc(sizeof(bool) * size);
        for (int i = 0; i < size; i++) {
            newTable->isOccupied[i] = false;
        }
        return newTable;
    }

    int hashFunction(int key, int size) {
        return key % size;
    }

    void rehash(HashTable* hashTable);

    void insert(HashTable* hashTable, int key, int value) {
        if ((float)hashTable->count / hashTable->size >= 0.75) {
            rehash(hashTable);
        }

        int hashIndex = hashFunction(key, hashTable->size);
        int originalIndex = hashIndex;
        int i = 1;
        
        while (hashTable->isOccupied[hashIndex]) {
            if (hashTable->keys[hashIndex] == key) {
                // If the key already exists, update the value
                hashTable->values[hashIndex] = value;
                return;
            }
            // Linear probing
            hashIndex = (originalIndex + i) % hashTable->size;
            i++;
        }
        
        hashTable->keys[hashIndex] = key;
        hashTable->values[hashIndex] = value;
        hashTable->isOccupied[hashIndex] = true;
        hashTable->count++;
    }

    void rehash(HashTable* hashTable) {
        int oldSize = hashTable->size;
        int* oldKeys = hashTable->keys;
        int* oldValues = hashTable->values;
        bool* oldIsOccupied = hashTable->isOccupied;
        
        int newSize = oldSize * 2;
        hashTable->keys = (int*)malloc(sizeof(int) * newSize);
        hashTable->values = (int*)malloc(sizeof(int) * newSize);
        hashTable->isOccupied = (bool*)malloc(sizeof(bool) * newSize);
        hashTable->size = newSize;
        hashTable->count = 0;
        
        for (int i = 0; i < newSize; i++) {
            hashTable->isOccupied[i] = false;
        }
        
        for (int i = 0; i < oldSize; i++) {
            if (oldIsOccupied[i]) {
                insert(hashTable, oldKeys[i], oldValues[i]);
            }
        }
        
        free(oldKeys);
        free(oldValues);
        free(oldIsOccupied);
    }

    int search(HashTable* hashTable, int key) {
        int hashIndex = hashFunction(key, hashTable->size);
        int originalIndex = hashIndex;
        int i = 1;
        
        while (hashTable->isOccupied[hashIndex]) {
            if (hashTable->keys[hashIndex] == key) {
                return hashTable->values[hashIndex];
            }
            // Linear probing
            hashIndex = (originalIndex + i) % hashTable->size;
            i++;
            if (hashIndex == originalIndex) {
                break; // We have circled back to the original index
            }
        }
        return -1; // Key not found
    }

    void delete(HashTable* hashTable, int key) {
        int hashIndex = hashFunction(key, hashTable->size);
        int originalIndex = hashIndex;
        int i = 1;
        
        while (hashTable->isOccupied[hashIndex]) {
            if (hashTable->keys[hashIndex] == key) {
                hashTable->isOccupied[hashIndex] = false;
                hashTable->count--;
                return;
            }
            // Linear probing
            hashIndex = (originalIndex + i) % hashTable->size;
            i++;
            if (hashIndex == originalIndex) {
                break; // We have circled back to the original index
            }
        }
    }

    void freeTable(HashTable* hashTable) {
        free(hashTable->keys);
        free(hashTable->values);
        free(hashTable->isOccupied);
        free(hashTable);
    }

    int main() {
        HashTable* hashTable = createTable(5);
        insert(hashTable, 1, 10);
        insert(hashTable, 2, 20);
        insert(hashTable, 3, 30);
        insert(hashTable, 4, 40);
        insert(hashTable, 5, 50);
        insert(hashTable, 6, 60); // This should trigger rehashing
        printf("Value for key 1: %d\n", search(hashTable, 1));
        printf("Value for key 2: %d\n", search(hashTable, 2));
        printf("Value for key 3: %d\n", search(hashTable, 3));
        printf("Value for key 4: %d\n", search(hashTable, 4));
        printf("Value for key 5: %d\n", search(hashTable, 5));
        printf("Value for key 6: %d\n", search(hashTable, 6));
        delete(hashTable, 3);
        printf("Value for key 3 after deletion: %d\n", search(hashTable, 3));
        freeTable(hashTable);
        return 0;
    }
/*Done By M.Harish AIML A 231501058*/