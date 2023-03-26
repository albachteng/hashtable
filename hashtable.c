#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person *)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
  char name[MAX_NAME];
  int age;
  struct person *next;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
  int length = strnlen(name, MAX_NAME);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++) {
    hash_value += name[i];
    hash_value = hash_value * name[i];
  }
  return hash_value % TABLE_SIZE;
};

void init_hash_table() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

void print_table() {
  printf("---\nstart\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == NULL) {
      printf("\t%i\t---\n", i);
    } else {
      printf("\t%i\t%s\n", i, hash_table[i]->name);
    }
  }
  printf("end\n---\n");
}

bool hash_table_insert(person *p) {
  if (p == NULL)
    return false;
  int index = hash(p->name);
  for (int i = 0; i < TABLE_SIZE; i++) {
    int try = (i + index) % TABLE_SIZE;
    if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
      hash_table[try] = p;
      return true;
    }
  }
  return false;
}

person *hash_table_lookup(char *name) {
  int index = hash(name);
  for (int i = 0; i < TABLE_SIZE; i++) {
    int try = (i + index) % TABLE_SIZE;
    if (hash_table[try] == NULL)
      return false;
    if (hash_table[try] == DELETED_NODE)
      continue;
    if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
      return hash_table[try];
    }
  }
  return NULL;
}

person *hash_table_delete(char *name) {
  int index = hash(name);
  for (int i = 0; i < TABLE_SIZE; i++) {
    int try = (i + index) % TABLE_SIZE;
    if (hash_table[try] == NULL)
      return false;
    if (hash_table[try] == DELETED_NODE)
      continue;
    if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
      person *tmp = hash_table[try];
      hash_table[try] = DELETED_NODE;
      return tmp;
    }
  }
  return NULL;
}

int main() {
  init_hash_table();
  person graham = {.name = "Graham", .age = 32};
  person griffin = {.name = "Griffin", .age = 32};
  person andrew = {.name = "andrew", .age = 32};
  hash_table_insert(&graham);
  hash_table_insert(&griffin);
  hash_table_insert(&andrew);
  print_table();
  person *tmp = hash_table_lookup(graham.name);
  printf("%s", tmp->name);
}
