#pragma once

#include "Tensor.h"

template <typename T>
class Kernel: public Tensor <T>{
	public:
		~Kernel();
		Kernel(unsigned int _sizeX, unsigned int _sizeY);
		Kernel(unsigned int _size);
		Kernel();
};

// Can't have the definitions outside this file because of the templates
template <typename T>
Kernel<T>::~Kernel() {
	/* empty */
}

template <typename T>
Kernel<T>::Kernel(unsigned int _sizeX, unsigned int _sizeY) : Tensor <T> (_sizeX, _sizeY) {
	/* empty */
}

template <typename T>
Kernel<T>::Kernel(unsigned int _size) : Tensor <T> (_size) {
	/* empty */
}

template <typename T>
Kernel<T>::Kernel() : Tensor <T> () {
	/* empty */
}