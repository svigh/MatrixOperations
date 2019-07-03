#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#include <vector>
#include <iostream>

#define PTR_ARRAYS 0

namespace Primitives {

    template <class T>
    class Tensor{
    protected:
        int sizeX, sizeY;
        int strideX, strideY;
#if PTR_ARRAYS	//This thing breaks the C++11 range-based fors. Make a pointer the entire size of the matrix for faster cache hits.
        T** values;
#else
        std::vector< std::vector<T>> values;
#endif

        void allocateSize();

    public:
        ~Tensor();
        Tensor(int _sizeX, int _sizeY);
        Tensor(int _size);
        Tensor();

        std::vector< std::vector <T>> getValues();

        void printValues();

        void populateRand(T lowerLimit, T upperLimit);

        int getXsize();
        int getYsize();

    };

	template <class T>
	class Kernel: public Tensor <T>{
    public:
        ~Kernel();
        Kernel(int _sizeX, int _sizeY);
        Kernel(int _size);
        Kernel();
    };

	template <class T>
	class Matrix: public Tensor <T>{
    public:
        ~Matrix();
        Matrix(int _sizeX, int _sizeY);
        Matrix(int _size);
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

#endif
