#ifndef _HASHMAP_H_
#define _HASHMAP_H_

typedef int (*HashFunc)(int);

typedef struct LList {
   int key;
   int value;
   struct LList *next;
} LList;

typedef struct HashMap {

   HashFunc hashFunc;
   LList **hashArray;
   int arraySize;
   int itemCount;

} HashMap;

HashMap* createHashMap(HashFunc func);
void addHashMap(HashMap* map, int key, int value);
int containsKeyHashMap(HashMap* map, int key);
void deleteHashMap(HashMap* map, int key);
int getHashMap(HashMap* map, int key);
int countHashMap(HashMap* map);
void printHashMap(HashMap* map);


#endif
