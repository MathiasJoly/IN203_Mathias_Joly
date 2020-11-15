# include <chrono>
# include <random>
# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>
# include <fstream>
# include <stdio.h>

int main(int argc , char *argv []) 
{
	int nbp , rank , tag=1;
	unsigned long nbs=100;
  //unsigned long nbs=1000;
  //unsigned long nbs=10000;
  
	MPI_Status stats;
	MPI_Init (& argc ,& argv);
	MPI_Comm_size (MPI_COMM_WORLD, &nbp);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	int maitre = nbp-1 ;

	// approximate_pi
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();
	myclock::duration d = myclock::now() - beginning ;
	unsigned seed = d.count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution (-1.0 ,1.0);
	unsigned long nbDarts = 0, nbd = 0; //nbd = nbDarts_total

	// Throw nbSamples darts in the unit square [ -1:1] x [ -1:1]
	for ( unsigned sample = 0; sample < nbs ; ++ sample ) 
	{
		int reste = sample % maitre;
		if ( rank == reste )
		{
			double x = distribution (generator);
			double y = distribution (generator);
			if ( x*x+y*y <=1 ) 
			{
			nbDarts = 1 ;
			}
			else
			{
			nbDarts = 0 ;
			};
			MPI_Send (&nbDarts, 1, MPI_INT, maitre, tag, MPI_COMM_WORLD);	
		};
		if ( rank == maitre )
		{
			MPI_Recv (&nbDarts, 1, MPI_INT, reste, tag, MPI_COMM_WORLD, &stats);
			nbd += nbDarts ;
		}
	};
	
	if (rank == maitre) std::cout << " pi = " << 4*double(nbd)/double(nbs) << std::endl;

	MPI_Finalize ();
	return EXIT_SUCCESS;
}
