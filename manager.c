//THIS IS OUTDATED, wait for version 2.2
//
// Created by uwu on 3/1/25.
//

#include <string.h>
#include <stdlib.h>

#include "manager.h"


void memory_manager_free(int status, void *mng) {
    struct memory_manager *manager = mng;
    if (!manager) return;
    if (!manager->memory) {
        free(manager);
        return;
    }

    for (size_t i = 0; i < manager->length; i++) if (manager->memory[i]) manager->memory[i]->destructor(manager->memory[i]);

    free(manager->memory);
    free(manager);
}

struct memory_manager *memory_manager_init(void) {
    struct memory_manager *manager = malloc(sizeof(struct memory_manager));
    if (!manager) return manager;

    manager->length = 0;
    manager->size = 10;
    manager->memory = malloc(manager->size * sizeof(struct pair **));

    int status = on_exit(memory_manager_free, *(void**)manager);

    if (status) exit(EXIT_FAILURE);

    return manager;
}

size_t index_of(const struct memory_manager *manager, char *name) {
    if (!manager) return 0;
    if (!manager->memory) return 0;
    if (!name) return 0;

    for (size_t i = 0; i < manager->length; i++) if (manager->memory[i]) if (manager->memory[i]->name) if (!strcmp(manager->memory[i]->name, name)) return i;
    return 0;
}

int memory_manager_memory_resize(struct memory_manager *manager, size_t new_size) {
    if (!manager) return 0;
    if (!manager->memory) return 0;

    struct pair **memory = malloc(new_size * sizeof(struct pair **));
    if (!memory) return 0;

    for (size_t i = 0; i < manager->length; i++) memory[i] = manager->memory[i];
    free(manager->memory);

    manager->memory = memory;
    manager->size = new_size;

    return 1;
}

int memory_manager_add(struct memory_manager *manager, char *name, void *addr, void (destructor)(void *)) {
    if (!manager) return 0;
    if (!manager->memory) return 0;
    if (!name) return 0;
    if (!addr) return 0;
    if (index_of(manager, name) > 0) return 0;
    if (manager->size <= manager->length + 1) if (!memory_manager_memory_resize(manager, manager->size + 10)) return 0;

    struct pair *memory = malloc(sizeof(struct pair *));
    if (!memory) return 0;

    memory->name = name;
    memory->addr = addr;
    memory->destructor = destructor;

    manager->memory[manager->length] = memory;
    manager->length++;

    return 1;
}

int memory_manager_set(struct memory_manager *manager, char *name, void *addr, void (destructor)(void *)) {
    if (!manager) return 0;
    if (!manager->memory) return 0;
    if (!name) return 0;
    if (!addr) return memory_manager_remove(manager, name);

    size_t index = index_of(manager, name);
    if (index == 0) return 0;
    index--;

    manager->memory[index]->addr = addr;
    manager->memory[index]->destructor = destructor;

    return 1;
}

void *memory_manager_get(struct memory_manager *manager, char *name) {
    if (!manager) return NULL;
    if (!manager->memory) return NULL;
    if (!name) return NULL;

    size_t index = index_of(manager, name);
    if (index == 0) return NULL;

    return manager->memory[index]->addr;
}

int memory_manager_remove(struct memory_manager *manager, char *name) {
    if (!manager) return 0;
    if (!manager->memory) return 0;
    if (!name) return 0;

    size_t index = index_of(manager, name);
    if (index == 0) return 0;
    index--;

    struct pair *memory = manager->memory[index]; //NULL check is not required because index_of() performs one

    memory->destructor(memory->addr);
    free(memory);

    manager->length--;

    return 1;
}
