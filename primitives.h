#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#include <vector>

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
#endif
