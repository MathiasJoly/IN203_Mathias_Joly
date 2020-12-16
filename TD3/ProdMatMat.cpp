#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "ProdMatMat.hpp"

namespace {
void prodSubBlocks(int iRowBlkA, int iColBlkB, int iColBlkA, int szBlock,
                   const Matrix& A, const Matrix& B, Matrix& C) 
{
//#	pragma omp parallel for
	for (int j = iColBlkB; j < std::min(B.nbCols, iColBlkB + szBlock); j++)
		for (int k = iColBlkA; k < std::min(A.nbCols, iColBlkA + szBlock); k++)
			for (int i = iRowBlkA; i < std::min(A.nbRows, iRowBlkA + szBlock); ++i)
				C(i, j) += A(i, k) * B(k, j);
}
const int szBlock = 128;
}  // namespace

Matrix operator*(const Matrix& A, const Matrix& B) 
{
	Matrix C(A.nbRows, B.nbCols, 0.0);
	#	pragma omp parallel for
	for (int jblock = 0; jblock < B.nbCols; jblock += szBlock)
		for (int kblock = 0; kblock < A.nbCols; kblock += szBlock)
			for (int iblock = 0; iblock < A.nbCols; iblock += szBlock)
				prodSubBlocks(iblock, kblock, jblock, szBlock, A, B, C);
//prodSubBlocks(0, 0, 0, std::max({A.nbRows, B.nbCols, A.nbCols}), A, B, C);
	return C;
}

// on veut paralliser sur la plus haute boucle (plus interessant)
// si on parallelise au niveau du k : plusieurs thread essaies de rajouter des valeur à C(i,j) en même temps : conflits de mémoires
