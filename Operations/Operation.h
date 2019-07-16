#pragma once

#include "../Types/Tensor.h"

template <typename T, typename N>
class Operation {
	protected:
		Matrix <T> mat;
		Kernel <N> ker;

	public:
		Operation(Matrix<T> _mat, Kernel<N> _ker);
		Operation();
	};

template <typename T, typename N>
Operation <T,N>::Operation(Matrix<T> _mat, Kernel<N> _ker) : mat(_mat), ker(_ker) {
	/* empty */
}

template <typename T, typename N>
Operation <T,N>::Operation() : mat(1), ker(1) {
	/* empty */
}
