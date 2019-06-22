#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "primitives.h"

namespace Operations {
    template <class T, class N>
    class Operation {
    protected:
        Primitives::Matrix <T> mat;
        Primitives::Kernel <N> ker;

    public:
        Operation(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker);
        Operation();
    };

    template <class T, class N>
	class Convolution: public Operation <T, N>{
    private:
        std::vector<std::vector <T>> Compute();
    public:
        Convolution(Primitives::Matrix<T> _mat, Primitives::Kernel<N> _ker);
    };
}
#endif
