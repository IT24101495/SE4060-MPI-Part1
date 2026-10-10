#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value;

    int buffer_size;
    void *buffer;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    buffer_size = sizeof(int) + MPI_BSEND_OVERHEAD;

    buffer = malloc(buffer_size);

    MPI_Buffer_attach(buffer, buffer_size);

    if (rank != 0)
    {
        value = rank * 10;

        MPI_Bsend(
            &value,
            1,
            MPI_INT,
            0,
            0,
            MPI_COMM_WORLD
        );
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(
                &value,
                1,
                MPI_INT,
                MPI_ANY_SOURCE,
                0,
                MPI_COMM_WORLD,
                &status
            );

            printf(
                "Received %d from process %d\n",
                value,
                status.MPI_SOURCE
            );
        }
    }

    MPI_Buffer_detach(&buffer, &buffer_size);

    free(buffer);

    MPI_Finalize();

    return 0;
}
