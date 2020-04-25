#include <stdio.h>
#include <string.h>

#include "clone.h"

int main(int argc, char* argv[]) {

    int update;
    int clone_id;

    if (argc == 1) {
        printf("Usage: %s <original number of agents> <clone_id>\n", argv[0]);
        return 0;
    }
    else if (argc == 3) {
        sscanf(argv[1], "%d", &update);
        sscanf(argv[2], "%d", &clone_id);
        update *= clone_id;
        printf("Clone id = %d\n", clone_id);
        printf("Update value = %d\n", update);
    }

    clone_households(update, clone_id);
    /*clone_region(update, clone_id);*/

    return 1;

}


