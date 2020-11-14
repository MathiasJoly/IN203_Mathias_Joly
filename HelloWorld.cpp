# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>
# include <fstream>

int main( int nargs, char* argv[] )
{
    MPI_Init(&nargs, &argv);
    int rang_tache, nombre_taches;

    MPI_Comm_rank(MPI_COMM_WORLD,
                  &rang_tache);
    MPI_Comm_size(MPI_COMM_WORLD, 
                  &nombre_taches);
    std::cout << "Bonjour, je suis la tâche n° " 
              << rand_tache << " sur "
              << nombre_taches << " tâche." 
              << std::endl;
    MPI_Finalize();
    return EXIT_SUCCESS;
}
