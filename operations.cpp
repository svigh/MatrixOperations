#include <vector>
#include <iostream>

#include "operations.h"

template <class T, class N>
Operations::Operation <T,N>::Operation(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker) : mat(_mat), ker(_ker) {
	/* empty */
}

template <class T, class N>
Operations::Operation <T,N>::Operation() : mat(1), ker(1) {
	/* empty */
}

template <class T, class N>
Operations::Convolution <T,N>::Convolution(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker) : Operation <T,N> (_mat, _ker) {
	if((_mat.getXsize() < _ker.getXsize()) || (_mat.getYsize() < _ker.getYsize()))
	{
		std::cout<<"Any matrix dimension cannot be smaller than corresponding kernel dimension.";
		exit(-1);
	}

	std::vector<std::vector <T>> output = Compute();
	for(auto &col : output)
	{
		for(T &elem : col)
		{
			std::cout<<elem<<"\t";
		}
		std::cout<<std::endl;
	}
}

template <class T, class N>
std::vector<std::vector <T>> Operations::Convolution <T,N>::Compute() {
	// Declare the output matrix here so it dies when the operation is finished
	std::vector<std::vector <T>> output;

	output.resize(this->mat.getXsize());
	for(int i = 0; i < this->mat.getXsize(); ++i)
	{
		output[i].resize(this->mat.getYsize());
	}

	for(int matX = 1; matX < this->mat.getXsize() - 1; ++matX)
	{
		for(int matY = 1; matY < this->mat.getYsize() - 1; ++matY)
		{
			output[matX][matY] = this->ker.getValues()[0][0] * this->mat.getValues()[matX-1][matY-1] +
									this->ker.getValues()[1][0] * this->mat.getValues()[matX][matY-1] +
									this->ker.getValues()[2][0] * this->mat.getValues()[matX+1][matY-1] +
									this->ker.getValues()[0][1] * this->mat.getValues()[matX-1][matY] +
									this->ker.getValues()[1][1] * this->mat.getValues()[matX][matY] +
									this->ker.getValues()[2][1] * this->mat.getValues()[matX+1][matY] +
									this->ker.getValues()[0][2] * this->mat.getValues()[matX-1][matY+1] +
									this->ker.getValues()[1][2] * this->mat.getValues()[matX][matY+1] +
									this->ker.getValues()[2][2] * this->mat.getValues()[matX+1][matY+1];
			output[matX][matY] /= this->ker.getXsize() * this->ker.getYsize();
		}
	}

	return output;
}
