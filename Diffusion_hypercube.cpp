# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>
# include <fstream>
# include <stdio.h>

// pour récupérer la dimension (d) du plus grand hypercube possible :
int logarithme2 (int nbp)
{
	int d = 0;
	int n = 1; //n = 2^d
	while (n<nbp)
	{
		d += 1;
		n *= 2;
	};
	if (n>nbp)
	{
		d = d-1;
		n = n/2;
	};
	return d;	
};

int main(int argc , char *argv []) 
{
	int nbp , rank, tag=1 , jeton;
	MPI_Status stats;
	
	MPI_Init (& argc ,& argv);
	MPI_Comm_size ( MPI_COMM_WORLD , &nbp );
	MPI_Comm_rank ( MPI_COMM_WORLD , &rank);
	
	int d = logarithme2(nbp) ; // 2^d <= nbp

	if (rank == 0) jeton = 6 ; // création hypercube de dimension 0

	int m=1; // m = 2^0
	int source,dest;
	for (int i=0; i<d; i++)
	{
		// passage de l'hypercube de dimension i à l'hypercube de dimension i+1 (m = 2^i) :
		// pour chaque tache de rang2 >= m, il y a une tache de rang1 < m qui lui envoit le jeton
		dest = rank + m ; // rang2 (dest) = rang1 + m
		if (rank < m) MPI_Send (&jeton, 1, MPI_INT, dest, dest, MPI_COMM_WORLD); 
		// la tache de rang < m envoit un message à la destination
		source = rank - m ; // rang1 (source) = rang2 - m
		if (rank < 2*m && rank >= m) MPI_Recv (&jeton, 1, MPI_INT, source, rank , MPI_COMM_WORLD, &stats);
		// la tache de rang >= m recoit un message de la source 
		m = m*2 ;  // m = 2^(i+1)			
	};		

	if (rank < m) std::cout << "tache n° " << rank << ", jeton = " << jeton << "." << std::endl;
	
	MPI_Finalize ();
	return EXIT_SUCCESS;
}
