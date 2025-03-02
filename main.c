#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"


int main(void) {
    //NOTE: there is no memory_manager_free() because it's handled when the program is preparing to exit
    struct memory_manager *memory_manager = memory_manager_init();
    if (!memory_manager) return 1;

    char *string = malloc(1024);
    if (!string) return 1;

    int status = memory_manager_add(memory_manager, "test", string, free);
    if (status) return 1;

    char *string2 = memory_manager_get(memory_manager, "test");
    if (!string2) return 1;

    strcpy(string2, "this is a test string");
    printf("%s\n", string);

    status = memory_manager_remove(memory_manager, "test");
    if (status) return 1;

    return 0;
}
