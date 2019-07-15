#pragma once

#include "primitives.h"

namespace Operations {

	template <typename T, typename N>
	class Operation {
	protected:
		Primitives::Matrix <T> mat;
		Primitives::Kernel <N> ker;

	public:
		Operation(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker);
		Operation();
	};

	template <typename T, typename N>
	class Convolution: public Operation <T, N>{
	private:
		Primitives::Tensor<T> Compute();
	public:
		Convolution(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker);
	};
}

template <typename T, typename N>
Operations::Operation <T,N>::Operation(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker) : mat(_mat), ker(_ker) {
	/* empty */
}

template <typename T, typename N>
Operations::Operation <T,N>::Operation() : mat(1), ker(1) {
	/* empty */
}

template <typename T, typename N>
Operations::Convolution <T,N>::Convolution(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker) : Operation <T,N> (_mat, _ker) {
	if((_mat.getXsize() < _ker.getXsize()) || (_mat.getYsize() < _ker.getYsize()))
	{
		std::cout<<"Any matrix dimension cannot be smaller than corresponding kernel dimension.";
		exit(-1);
	}

	Primitives::Tensor<T> output = Compute();

	// Why print here the output
	unsigned int i = 0;
	for( T &elem : output.getValues() ){
		std::cout << elem << "\t";
		if( !(++i % output.getYsize()) )
			std::cout << std::endl;
	}
}

template <typename T, typename N>
Primitives::Tensor<T> Operations::Convolution <T,N>::Compute() {
	// Declare the output matrix here so it dies when the operation is finished

	unsigned int outX = this->mat.getXsize();
	unsigned int outY = this->mat.getYsize();
	unsigned int matLimit = outX * outY;

	Primitives::Tensor<T> output(outX, outY);

	// This aint conv chief, keep it till it good
	for(unsigned int matIndex = 0; matIndex < matLimit; ++matIndex){
		output[matIndex] = this->ker[ matIndex % (this->ker.getXsize() * this->ker.getXsize()) ] * this->mat[matIndex];
	}

	return output;
}
