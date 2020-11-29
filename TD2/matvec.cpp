// Produit matrice-vecteur
# include <cassert>
# include <vector>
# include <iostream>
# include <mpi.h>

// ---------------------------------------------------------------------
class Matrix : public std::vector<double>
{
public:
    Matrix (int dim);
    Matrix( int nrows, int ncols );
    Matrix( const Matrix& A ) = delete;
    Matrix( Matrix&& A ) = default;
    ~Matrix() = default;

    Matrix& operator = ( const Matrix& A ) = delete;
    Matrix& operator = ( Matrix&& A ) = default;
    
    double& operator () ( int i, int j ) {
        return m_arr_coefs[i + j*m_nrows];
    }
    double  operator () ( int i, int j ) const {
        return m_arr_coefs[i + j*m_nrows];
    }
    
    std::vector<double> operator * ( const std::vector<double>& u ) const;
    
    std::ostream& print( std::ostream& out ) const
    {
        const Matrix& A = *this;
        out << "[\n";
        for ( int i = 0; i < m_nrows; ++i ) {
            out << " [ ";
            for ( int j = 0; j < m_ncols; ++j ) {
                out << A(i,j) << " ";
            }
            out << " ]\n";
        }
        out << "]";
        return out;
    }
private:
    int m_nrows, m_ncols;
    std::vector<double> m_arr_coefs;
};
// ---------------------------------------------------------------------
inline std::ostream& 
operator << ( std::ostream& out, const Matrix& A )
{
    return A.print(out);
}
// ---------------------------------------------------------------------
inline std::ostream&
operator << ( std::ostream& out, const std::vector<double>& u )
{
    out << "[ ";
    for ( const auto& x : u )
        out << x << " ";
    out << " ]";
    return out;
}
// ---------------------------------------------------------------------
std::vector<double> 
Matrix::operator * ( const std::vector<double>& u ) const
{
    const Matrix& A = *this;
    assert( u.size() == unsigned(m_ncols) );
    std::vector<double> v(m_nrows, 0.);
    for ( int i = 0; i < m_nrows; ++i ) {
        for ( int j = 0; j < m_ncols; ++j ) {
            v[i] += A(i,j)*u[j];
        }            
    }
    return v;
}

// =====================================================================
Matrix::Matrix (int dim) : m_nrows(dim), m_ncols(dim),
                           m_arr_coefs(dim*dim)
{
    for ( int i = 0; i < dim; ++ i ) {
        for ( int j = 0; j < dim; ++j ) {
            (*this)(i,j) = (i+j)%dim;
        }
    }
}
// ---------------------------------------------------------------------
Matrix::Matrix( int nrows, int ncols ) : m_nrows(nrows), m_ncols(ncols),
                                         m_arr_coefs(nrows*ncols)
{
    int dim = (nrows > ncols ? nrows : ncols );
    for ( int i = 0; i < nrows; ++ i ) {
        for ( int j = 0; j < ncols; ++j ) {
            (*this)(i,j) = (i+j)%dim;
        }
    }    
}
// =====================================================================
int main( int argc, char* argv[] )
{
    int numtasks, rank;

    MPI_Init(&argc ,&argv) ;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank ) ;
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks ) ;    
    
    const int N = 120;
    const int Nloc = N / numtasks; // on prendra toujours numtasks diviseur de N
    int first_col = Nloc*rank ;

    Matrix A(N);

    Matrix Aloc(N,Nloc);
    for (int i = 0; i < N; ++i)
    {
        for (int j =0; j < Nloc; ++j)
        {
            Aloc(i,j) = A(i, first_col + j) ;
        };
    };

    std::vector<double> uloc(Nloc);
    for ( int i = 0; i < Nloc; ++i ) { uloc[i] = first_col + i + 1; };

    std::vector<double> w = Aloc*uloc ;
    // pour verifier les resultats intermediaires :
    // std::cout << "tache " << rank << ", w = " << w << std::endl ; 

    std::vector<double> v(N) ;
    MPI_Allreduce(w.data(), v.data(), N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    // pour verifier les resultats finaux : 
    // std::cout << "tache " << rank << ", v = " << v << std::endl ; 

    MPI_Finalize () ;
    return EXIT_SUCCESS;
}
