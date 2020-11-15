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
	MPI_Comm_size ( MPI_COMM_WORLD , &nbp ); //nbp=8
	MPI_Comm_rank ( MPI_COMM_WORLD , &rank);
	
	if (rank == 0)
	{
		jeton = 6;
		MPI_Send (&jeton, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send (&jeton, 1, MPI_INT, 2, 2, MPI_COMM_WORLD);
		MPI_Send (&jeton, 1, MPI_INT, 4, 4, MPI_COMM_WORLD);
		// dest = 2^0, 2^1, 2^2
		// tag = dest
	}
	else if (rank == 1)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 0, 1 , MPI_COMM_WORLD, &stats);
		// source = 0 car 1 est une puissance de 2
		// tag = rank
		MPI_Send (&jeton, 1, MPI_INT, 3, 3 , MPI_COMM_WORLD);
		MPI_Send (&jeton, 1, MPI_INT, 5, 5 , MPI_COMM_WORLD);
		// dest = 2^1 + 1, 2^2 + 1
		// tag = dest
	}
	else if (rank == 2)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 0, 2 , MPI_COMM_WORLD, &stats);
		// source = 0 car 2 est une puissance de 2
		// tag = rank
		MPI_Send (&jeton, 1, MPI_INT, 6, 6 , MPI_COMM_WORLD);
		// dest = 2^2 + 2
		// tag = dest
	}
	else if (rank == 3)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 1, 3 , MPI_COMM_WORLD, &stats);
		// source = 1 car 3 = 2^1 + 1
		// tag = rank
		MPI_Send (&jeton, 1, MPI_INT, 7, 7 , MPI_COMM_WORLD);
		// dest = 2^2 + 3
		// tag = dest
	}
	else if (rank == 4)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 0, 4 , MPI_COMM_WORLD, &stats);
		// source = 0 car 4 est une puissance de 2
		// tag = rank
	}
	else if (rank == 5)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 1, 5 , MPI_COMM_WORLD, &stats);
		// source = 1 car 5 = 2^2 + 1
		// tag = rank
	}
	else if (rank == 6)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 2, 6 , MPI_COMM_WORLD, &stats);
		// source = 2 car 6 = 2^2 + 2
		// tag = rank
	}
	else if (rank == 7)
	{
		MPI_Recv (&jeton, 1, MPI_INT, 3, 7 , MPI_COMM_WORLD, &stats);
		// source = 3 car 7 = 2^2 + 3
		// tag = rank
	};

	std::cout << "tache n° " << rank << ", jeton = " << jeton << "." << std::endl;
	MPI_Finalize ();
	return EXIT_SUCCESS;
}
