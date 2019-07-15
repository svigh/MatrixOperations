#pragma once

#include <vector>
#include <iostream>
#include "helpers.h"

#define PTR_ARRAYS 0

// TODO: have all tensors be just vectors of elements, not matrices
namespace Primitives {

	template <typename T>
	class Tensor{
	protected:
		unsigned int sizeX, sizeY;
		unsigned int strideX, strideY;
#if PTR_ARRAYS	//This thing breaks the C++11 range-based fors. Make a pointer the entire size of the matrix for faster cache hits.
		T** values;
#else
		std::vector<T> values;
#endif

		void allocateSize();

	public:
		~Tensor();
		Tensor(unsigned int _sizeX, unsigned int _sizeY);
		Tensor(unsigned int _size);
		Tensor();

		std::vector <T> getValues();

		void printValues();

		void populateRand(T lowerLimit, T upperLimit);

		unsigned int getXsize();
		unsigned int getYsize();

		T &operator[](unsigned int index);
		Tensor &operator = (const Tensor& t);

	};

	template <typename T>
	class Kernel: public Tensor <T>{
	public:
		~Kernel();
		Kernel(unsigned int _sizeX, unsigned int _sizeY);
		Kernel(unsigned int _size);
		Kernel();
	};

	template <typename T>
	class Matrix: public Tensor <T>{
	public:
		~Matrix();
		Matrix(unsigned int _sizeX, unsigned int _sizeY);
		Matrix(unsigned int _size);
		Matrix();
	};
}

// Have the implementation in the same header so theres
// no need to explicitly say which types the class should use
// Like this:
// template class Primitives::Tensor<float>;
// template class Primitives::Tensor<int>;
// template class Primitives::Kernel<float>;
// template class Primitives::Matrix<int>;

template <typename T>
void Primitives::Tensor<T>::allocateSize() {
#if PTR_ARRAYS
		values = new T*[sizeX];
		for(unsigned int i = 0; i < sizeX; ++i)
		{
			values[i] = new T[sizeY];
		}
#else
		values.resize(sizeX * sizeY);
#endif
}

template <typename T>
Primitives::Tensor<T>::~Tensor() {
#if PTR_ARRAYS
			for(unsigned int i = 0; i < sizeX; ++i){
				delete[] values[i];
			}
			delete[] values;
#else
			// How to free memory of a vector ??
#endif
}

template <typename T>
Primitives::Tensor<T>::Tensor(unsigned int _sizeX, unsigned int _sizeY): sizeX(_sizeX), sizeY(_sizeY) {
	allocateSize();
}

template <typename T>
Primitives::Tensor<T>::Tensor(unsigned int _size): sizeX(_size), sizeY(_size) {
	allocateSize();
}

template <typename T>
Primitives::Tensor<T>::Tensor(): sizeX(1), sizeY(1) {
	allocateSize();
}

template <typename T>
T &Primitives::Tensor<T>::operator[](unsigned int index){
	if ( index > (sizeX * sizeY) ){
		std::cout << "Index out of bounds" << std::endl;
		return values[0];
	}

	return values[index];
}

template <typename T>
Primitives::Tensor<T> &Primitives::Tensor<T>::operator=(const Primitives::Tensor<T>& t){

	auto tensorSize = t.sizeX * t.sizeY;

	values.resize(tensorSize);

	for( unsigned int i = 0; i < tensorSize; ++i){
		values[i] = t[i];
	}
}

template <typename T>
std::vector <T> Primitives::Tensor<T>::getValues(){
	return values;
}

template <typename T>
void Primitives::Tensor<T>::printValues(){
	unsigned int i = 0;

	for(T &elem : values)
	{
		std::cout<<elem<<"\t";

		if( !(++i % sizeY) ){
			std::cout<<std::endl;
		}
	}
}

template <typename T>
void Primitives::Tensor<T>::populateRand(T lowerLimit, T upperLimit){
	for(T &elem : values)
	{
		// static cast for generating float numbers not needed ?? also +1 to get [low, high] interval
		elem = lowerLimit + static_cast <float> (rand()) / (static_cast <float>(RAND_MAX/(upperLimit-lowerLimit+1)));
	}
}

template <typename T>
unsigned int Primitives::Tensor<T>::getXsize(){
	return sizeX;
}

template <typename T>
unsigned int Primitives::Tensor<T>::getYsize(){
	return sizeY;
}

template <typename T>
Primitives::Kernel<T>::~Kernel() {}

template <typename T>
Primitives::Kernel<T>::Kernel(unsigned int _sizeX, unsigned int _sizeY) : Tensor <T> (_sizeX, _sizeY) {}

template <typename T>
Primitives::Kernel<T>::Kernel(unsigned int _size) : Tensor <T> (_size) {}

template <typename T>
Primitives::Kernel<T>::Kernel() : Tensor <T> () {}

template <typename T>
Primitives::Matrix<T>::~Matrix() {}

template <typename T>
Primitives::Matrix<T>::Matrix(unsigned int _sizeX, unsigned int _sizeY) : Tensor <T> (_sizeX, _sizeY) {}

template <typename T>
Primitives::Matrix<T>::Matrix(unsigned int _size) : Tensor <T> (_size) {}

template <typename T>
Primitives::Matrix<T>::Matrix() : Tensor <T> () {}
