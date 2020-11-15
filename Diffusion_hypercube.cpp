# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>
# include <fstream>
# include <stdio.h>

int main(int argc , char *argv []) 
{
	int nbp , rank, tag=1 , jeton;
	MPI_Status stats;
	
	MPI_Init (& argc ,& argv);
	MPI_Comm_size ( MPI_COMM_WORLD , &nbp ); //nbp=4
	MPI_Comm_rank ( MPI_COMM_WORLD , &rank);
	
	if (rank == 0)
	{
		jeton = 6;
		MPI_Send (&jeton, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send (&jeton, 1, MPI_INT, 3, 3, MPI_COMM_WORLD);
	}
	else if (rank == 1)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 0, 1 , MPI_COMM_WORLD, &stats);
		MPI_Send (&jeton, 1, MPI_INT, 2, 2 , MPI_COMM_WORLD);
	}
	else if (rank == 2)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 1, 2 , MPI_COMM_WORLD, &stats);
	}
	else if (rank == 3)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 0, 3 , MPI_COMM_WORLD, &stats);
	};

	std::cout << "tache n° " << rank << ", jeton = " << jeton << "." << std::endl;
	MPI_Finalize ();
	return EXIT_SUCCESS;
}
