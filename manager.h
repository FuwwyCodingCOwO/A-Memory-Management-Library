//
// Created by uwu on 3/1/25.
//

#ifndef MANAGER_H
#define MANAGER_H

struct pair {
    char *name;
    void *addr;
    void (*destructor)(void *);
};

struct memory_manager {
    struct pair **memory;
    size_t size;
    size_t length;
};

struct memory_manager *memory_manager_init(void);

int memory_manager_add(struct memory_manager *manager, char *name, void *addr, void (destructor)(void *));

int memory_manager_set(struct memory_manager *manager, char *name, void *addr, void (destructor)(void *));

void *memory_manager_get(struct memory_manager *manager, char *name);

int memory_manager_remove(struct memory_manager *manager, char *name);

#endif //MANAGER_H
