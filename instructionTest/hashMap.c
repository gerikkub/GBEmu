
#include <stdio.h>
#include <stdlib.h>
#include "hashMap.h"

#define HASHMAP_INIT_SIZE 10


HashMap* createHashMap(HashFunc func) {
   HashMap* hashMap = calloc(1, sizeof(HashMap));
   
   hashMap->hashFunc = func;
   hashMap->hashArray = calloc(HASHMAP_INIT_SIZE, sizeof(LList*));
   hashMap->arraySize = HASHMAP_INIT_SIZE;
   hashMap->itemCount = 0;
}

void growHashMap(HashMap* map) {
   LList **oldArray;
   int oldSize;
   LList *cursor, *prev;
   
   oldArray = map->hashArray;
   oldSize = map->arraySize;
   
   map->arraySize *= 2;
   map->hashArray = calloc(map->arraySize, sizeof(LList));
   map->itemCount = 0;

   int i;
   for(i = 0; i < oldSize; i++) {
      cursor = oldArray[i];
      while(cursor) {
         addHashMap(map, cursor->key, cursor->value);
         prev = cursor;
         cursor = cursor->next;
         free(prev);
      }
   }
   
   free(oldArray);
}
 


void addHashMap(HashMap* map, int key, int value) {
   
   int hash;
   LList *cursor;

   if(containsKeyHashMap(map, key)){
      return;
   }

   map->itemCount++;

   if(map->itemCount == map->arraySize) {
      growHashMap(map);
      map->itemCount++;
   }

   hash = map->hashFunc(key) % map->arraySize;
   
   if(map->hashArray[hash] == NULL) {
      map->hashArray[hash] = calloc(1, sizeof(LList));
      map->hashArray[hash]->key = key;
      map->hashArray[hash]->value = value;
   } else {

      cursor = map->hashArray[hash];
      while(cursor->next){
         cursor = cursor->next;
      }

      cursor->next = calloc(1, sizeof(LList));
      cursor = cursor->next;
      cursor->key = key;
      cursor->value = value;
   }
}

int containsKeyHashMap(HashMap* map, int key) {
   
   int hash;
   LList *cursor;

   hash = map->hashFunc(key) % map->arraySize;
   
   if(map->hashArray[hash] == NULL) {
      return 0;
   }

   cursor = map->hashArray[hash];
   
   while(cursor) {
      if(cursor->key == key) {
         return 1;
      }
      cursor = cursor->next;
   }
   return 0;
}

int getHashMap(HashMap* map, int key) {
   
   int hash;
   LList *cursor;

   hash = map->hashFunc(key) % map->arraySize;
   
   if(map->hashArray[hash] == NULL) {
      return -1;
   }

   cursor = map->hashArray[hash];
   
   while(cursor) {
      if(cursor->key == key) {
         return cursor->value;
      }
      cursor = cursor->next;
   }
   return -1;
}

void deleteHashMap(HashMap* map, int key) {
   
   int hash;
   LList *cursor, *prev = NULL;

   hash = map->hashFunc(key) % map->arraySize;
   
   if(map->hashArray[hash] == NULL) {
      return;
   }

   cursor = map->hashArray[hash];
   
   while(cursor) {
      if(cursor->key == key) {
         break;
      }
      prev = cursor;
      cursor = cursor->next;
   }

   if(cursor){

      if(prev == NULL) {
         map->hashArray[hash] = cursor->next;
      } else {
         prev->next = cursor->next;
      }

      map->itemCount--;
      free(cursor);
   }
   
}

int countHashMap(HashMap* map) {
   return map->itemCount;
}

void printHashMap(HashMap* map) {

   LList *cursor;
   
   int i;
   for(i = 0; i < map->arraySize; i++) {
      printf("[%d] ", i);
      cursor = map->hashArray[i];
      if(cursor) {
         printf("%d: %d", cursor->key, cursor->value);
         cursor = cursor->next;
         while(cursor) {
            printf(" -> %d: %d", cursor->key, cursor->value);
            cursor = cursor->next;
         }
      }
      printf("\n");
   }
   
}
