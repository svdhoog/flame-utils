#include <stdio.h>
#include <string.h>
#include "mpi.h"

#include "clone.h"

int main(int argc, char* argv[]) {

    int err;

    int update = 0;
    int offset = 0;
    int node_id = 0;
    int totalnodes = 0;

    err = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &totalnodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &node_id);

    if (argc == 1) {
        printf("Usage: %s <original number of agents>\n", argv[0]);
        return 0;
    }
    else if (argc == 2) {
        sscanf(argv[1], "%d", &update);
        update *= node_id;
        printf("Update value = %d\n", update);
    }
    else if (argc == 3) {
        sscanf(argv[1], "%d", &update);
        sscanf(argv[2], "%d", &offset);
        update *= (node_id+offset);
        printf("Update value = %d\n", update);
    }

    clone_households(update, node_id);
    /*clone_region(update, node_id+offset);*/

    MPI_Finalize();
    return 1;

}


