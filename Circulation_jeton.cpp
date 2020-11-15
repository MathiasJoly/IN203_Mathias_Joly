# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>
# include <fstream>
# include <stdio.h>

int main(int argc , char *argv []) 
{
	int nbp , rank , next , prev , tag=1 , jeton;
	MPI_Status stats;
	MPI_Init (& argc ,& argv);
	MPI_Comm_size ( MPI_COMM_WORLD , &nbp );
	MPI_Comm_rank ( MPI_COMM_WORLD , &rank);
	prev = rank -1;
	next = rank +1;
	if (rank == ( nbp - 1)) next = 0;
	if (rank == 0) prev = nbp-1;
	jeton = rank*10;
	MPI_Send (&jeton , 1, MPI_INT , next , tag , MPI_COMM_WORLD );
	MPI_Recv (&jeton , 1, MPI_INT , prev , tag , MPI_COMM_WORLD , &stats);
	jeton += 1 ;
	std::cout << "tache n° " << rank << ", jeton = " << jeton << "." << std::endl;
	MPI_Finalize ();
	return EXIT_SUCCESS;
}
