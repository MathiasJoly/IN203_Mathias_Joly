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
	MPI_Comm_size ( MPI_COMM_WORLD , &nbp ); //nbp=2
	MPI_Comm_rank ( MPI_COMM_WORLD , &rank);
	
	if (rank == 0)
	{
		jeton = 6;
		MPI_Send (&jeton , 1, MPI_INT , 1 , tag , MPI_COMM_WORLD );
	}
	else
	{
		MPI_Recv (&jeton , 1, MPI_INT , 0 , tag , MPI_COMM_WORLD , &stats);
	};

	std::cout << "tache n° " << rank << ", jeton = " << jeton << "." << std::endl;
	MPI_Finalize ();
	return EXIT_SUCCESS;
}
