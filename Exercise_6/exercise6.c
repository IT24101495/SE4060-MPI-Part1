#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 3)
    {
        if (rank == 0)
        {
            printf("Please run using at least 3 processes.\n");
        }

        MPI_Finalize();
        return 0;
    }

    if (rank != 0)
    {
        value = rank * 10;

        MPI_Send(
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

    MPI_Finalize();

    return 0;
}
