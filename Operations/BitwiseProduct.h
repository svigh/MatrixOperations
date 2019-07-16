#include "Operation.h"

template <typename T, typename N>
	class BitwiseProduct: public Operation <T, N>{
	private:
		Tensor<T> Compute();
	public:
	BitwiseProduct(Matrix<T> _mat, Kernel<N> _ker);
};

template <typename T, typename N>
BitwiseProduct <T,N>::BitwiseProduct(Matrix<T> _mat, Kernel<N> _ker) : Operation <T,N> (_mat, _ker) {
	if((_mat.getXsize() < _ker.getXsize()) || (_mat.getYsize() < _ker.getYsize()))
	{
		std::cout<<"Any matrix dimension cannot be smaller than corresponding kernel dimension.";
		exit(-1);
	}

	Tensor<T> output = Compute();

	// Why print here the output
	unsigned int i = 0;
	for( T &elem : output.getValues() ){
		std::cout << elem << "\t";
		if( !(++i % output.getYsize()) )
			std::cout << std::endl;
	}
}

template <typename T, typename N>
Tensor<T> BitwiseProduct <T,N>::Compute() {
	// Declare the output matrix here so it dies when the operation is finished

	unsigned int outX = this->mat.getXsize();
	unsigned int outY = this->mat.getYsize();
	unsigned int matLimit = outX * outY;

	Tensor<T> output(outX, outY);

	// This aint conv chief, keep it till it good
	for(unsigned int matIndex = 0; matIndex < matLimit; ++matIndex){
		output[matIndex] = this->ker[ matIndex % (this->ker.getXsize() * this->ker.getXsize()) ] * this->mat[matIndex];
	}

	return output;
}