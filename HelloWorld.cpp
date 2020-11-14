# include <cstdlib>
# include <sstream>
# include <string>
# include <fstream>
# include <iostream>
# include <iomanip>
# include <mpi.h>

int main( int nargs, char* argv[] )
{
	MPI_Init( &nargs, &argv );
	MPI_Comm globComm;
	MPI_Comm_dup(MPI_COMM_WORLD, &globComm);
	int nombre_taches;
	MPI_Comm_size(globComm, &nombre_taches);
	int rang_tache;
	MPI_Comm_rank(globComm, &rang_tache);

	// Création d'un fichier pour ma propre sortie en écriture :
	std::stringstream fileName;
	fileName << "Output" << std::setfill('0') << std::setw(5) << rang_tache << ".txt";
	std::ofstream output( fileName.str().c_str() );

	output << "Bonjour, je suis la tâche n° " << rang_tache << " sur " << nombre_taches << " tâches." << std::endl;

	output.close();

	MPI_Finalize();
	return EXIT_SUCCESS;
}
