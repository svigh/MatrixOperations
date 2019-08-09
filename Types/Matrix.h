#pragma once

#include "Tensor.h"

template <typename T>
class Matrix : public Tensor <T>{
	public:
		~Matrix();
		Matrix(unsigned int _sizeX, unsigned int _sizeY);
		Matrix(unsigned int _size);
		Matrix();
};

// Can't have the definitions outside this file because of the templates
template <typename T>
Matrix<T>::~Matrix() {
	/* empty */
}

template <typename T>
Matrix<T>::Matrix(unsigned int _sizeX, unsigned int _sizeY) : Tensor <T> (_sizeX, _sizeY) {
	/* empty */
}

template <typename T>
Matrix<T>::Matrix(unsigned int _size) : Tensor <T> (_size) {
	/* empty */
}

template <typename T>
Matrix<T>::Matrix() : Tensor <T> () {
	/* empty */
}