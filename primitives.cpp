#include <vector>
#include <iostream>

#include "primitives.h"

#define PTR_ARRAYS 0

template <class T>
void Primitives::Tensor<T>::allocateSize() {
#if PTR_ARRAYS
		values = new T*[sizeX];
		for(int i = 0; i < sizeX; ++i)
		{
			values[i] = new T[sizeY];
		}
#else
		values.resize(sizeX);
		for(int i = 0; i < sizeX; ++i)
		{
			values[i].resize(sizeY);
		}
#endif
}

template <class T>
Primitives::Tensor<T>::~Tensor() {
#if PTR_ARRAYS
            for(int i = 0; i < sizeX; ++i){
                delete[] values[i];
            }
            delete[] values;
#else
			// How to free memory of a vector ??
#endif
}

template <class T>
Primitives::Tensor<T>::Tensor(int _sizeX, int _sizeY): sizeX(_sizeX), sizeY(_sizeY) {
	allocateSize();
}

template <class T>
Primitives::Tensor<T>::Tensor(int _size): sizeX(_size), sizeY(_size) {
	allocateSize();
}

template <class T>
Primitives::Tensor<T>::Tensor(): sizeX(1), sizeY(1) {
	allocateSize();
}

template <class T>
std::vector< std::vector <T>> Primitives::Tensor<T>::getValues(){
	return values;
}

template <class T>
void Primitives::Tensor<T>::printValues(){
	for(auto &col : values)
	{
		for(T &elem : col)
		{
			std::cout<<elem<<"\t";
		}
		std::cout<<std::endl;
	}
}

template <class T>
void Primitives::Tensor<T>::populateRand(T lowerLimit, T upperLimit){
	for(auto &col : values)
	{
		for(T &elem : col)
		{
			elem = lowerLimit + static_cast <float> (rand()) / (static_cast <float>(RAND_MAX/(upperLimit-lowerLimit))); // static cast for generating float numbers
		}
	}
}

template <class T>
int Primitives::Tensor<T>::getXsize(){
	return sizeX;
}

template <class T>
int Primitives::Tensor<T>::getYsize(){
	return sizeY;
}

template <class T>
Primitives::Kernel<T>::~Kernel() {}

template <class T>
Primitives::Kernel<T>::Kernel(int _sizeX, int _sizeY) : Tensor <T> (_sizeX, _sizeY) {}

template <class T>
Primitives::Kernel<T>::Kernel(int _size) : Tensor <T> (_size) {}

template <class T>
Primitives::Kernel<T>::Kernel() : Tensor <T> () {}

template <class T>
Primitives::Matrix<T>::~Matrix() {}

template <class T>
Primitives::Matrix<T>::Matrix(int _sizeX, int _sizeY) : Tensor <T> (_sizeX, _sizeY) {}

template <class T>
Primitives::Matrix<T>::Matrix(int _size) : Tensor <T> (_size) {}

template <class T>
Primitives::Matrix<T>::Matrix() : Tensor <T> () {}
