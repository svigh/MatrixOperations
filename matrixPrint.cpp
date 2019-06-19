#include <vector>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <iostream>

#define PTR_ARRAYS 0

// virtual function
// friend classes
// forward declarations
// extern "C"
// callbacks
// algorithm
// lambdas

// #define HELP_OFFSET 'h'
// #define READ_OFFSET 'r'
// #define DUMP_OFFSET 'd'

// void help(){
// }

// void readFile(){
// }

// void dumpFile(){
// }

// int a[2] = {
//     [0] = 1,
//     [1] = 5
// };

// array of functions
// void (*func)(void) table[5] = {
//     [HELP_OFFSET] = help,
//     [READ_OFFSET] = readFIle,
//     [DUMP_OFFSET] = dumpFile
// };


// table[arg]();

// malloc
// |     |  -> |      |
//

// new a[12]         new a
// |     |  n  |   a[12]
// |  |  n  |   a

// delete[]
// delete

// array[12]    *(array + sizeof(array[0]) * 12)
//
// list       element, next --->  element, next ----> element, next -----> NULL
// list[2]

namespace MatrixOperations {

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

        void allocateSize()
        {
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

    public:
        ~Tensor(){
#if PTR_ARRAYS
            for(int i = 0; i < sizeX; ++i){
                delete[] values[i];
            }
            delete[] values;
#else
			// How to free memory of a vector ??
#endif
        }
        Tensor(int _sizeX, int _sizeY) : sizeX(_sizeX), sizeY(_sizeY) { allocateSize(); }
        Tensor(int _size) : sizeX(_size), sizeY(_size) { allocateSize(); }
        Tensor() : sizeX(1), sizeY(1) { allocateSize(); }

        std::vector< std::vector <T>> getValues()
        {
            return values;
        }

        void printValues()
        {
            for(auto &col : values)
            {
                for(T &elem : col)
                {
                    std::cout<<elem<<"\t";
                }
                std::cout<<std::endl;
            }
        }

        void populateRand(T lowerLimit, T upperLimit)
        {
            for(auto &col : values)
            {
                for(T &elem : col)
                {
                    elem = lowerLimit + static_cast <float> (rand()) / (static_cast <float>(RAND_MAX/(upperLimit-lowerLimit))); // static cast for generating float numbers
                }
            }
        }

        int getXsize() { return sizeX; }
        int getYsize() { return sizeY; }

    };

	template <class T>
	class Kernel: public Tensor <T>{
    private:
        void allocateSize();

    public:
        ~Kernel(){};
        Kernel(int _sizeX, int _sizeY) : Tensor <T> (_sizeX, _sizeY) {}
        Kernel(int _size) : Tensor <T> (_size) {}
        Kernel() : Tensor <T> () {}
    };

	template <class T>
	class Matrix: public Tensor <T>{
    private:
        void allocateSize();

    public:
        ~Matrix(){}
        Matrix(int _sizeX, int _sizeY) : Tensor <T> (_sizeX, _sizeY) {}
        Matrix(int _size) : Tensor <T> (_size) {}
        Matrix() : Tensor <T> () {}

    };

    template <class T, class N> class Operation{
    protected:
        Matrix <T> mat;
        Kernel <N> ker;

    public:
        Operation(Matrix<T> _mat, Kernel<N> _ker) : mat(_mat), ker(_ker){}
        Operation() : mat(1), ker(1){}
    };

    template <class T, class N>
	class Convolution: public Operation <T, N>{
    private:
        std::vector<std::vector <T>> Compute()
        {
            // Declare the output matrix here so it dies when the operation is finished
            std::vector<std::vector <T>> output;

            output.resize(this->mat.getXsize());
            for(int i = 0; i < this->mat.getXsize(); ++i)
            {
                output[i].resize(this->mat.getYsize());
            }

            for(int matX = 1; matX < this->mat.getXsize() - 1; ++matX)
            {
                for(int matY = 1; matY < this->mat.getYsize() - 1; ++matY)
                {
                    output[matX][matY] = this->ker.getValues()[0][0] * this->mat.getValues()[matX-1][matY-1] +
                                         this->ker.getValues()[1][0] * this->mat.getValues()[matX][matY-1] +
                                         this->ker.getValues()[2][0] * this->mat.getValues()[matX+1][matY-1] +
                                         this->ker.getValues()[0][1] * this->mat.getValues()[matX-1][matY] +
                                         this->ker.getValues()[1][1] * this->mat.getValues()[matX][matY] +
                                         this->ker.getValues()[2][1] * this->mat.getValues()[matX+1][matY] +
                                         this->ker.getValues()[0][2] * this->mat.getValues()[matX-1][matY+1] +
                                         this->ker.getValues()[1][2] * this->mat.getValues()[matX][matY+1] +
                                         this->ker.getValues()[2][2] * this->mat.getValues()[matX+1][matY+1];
                    output[matX][matY] /= this->ker.getXsize() * this->ker.getYsize();
                }
            }

            return output;
        }

    public:
        Convolution(Matrix<T> _mat, Kernel<N> _ker) : Operation <T,N> (_mat, _ker)
        {
            if((_mat.getXsize() < _ker.getXsize()) || (_mat.getYsize() < _ker.getYsize()))
            {
                std::cout<<"Any matrix dimension cannot be smaller than corresponding kernel dimension.";
                exit(-1);
            }

            std::vector<std::vector <T>> output = Compute();
            for(auto &col : output)
            {
                for(T &elem : col)
                {
                    std::cout<<elem<<"\t";
                }
                std::cout<<std::endl;
            }
        }
    };
}


// Maybe define the operations between matrices by themselvs containing the operations, not make a separate operation type
// Actually no, but maybe
template<typename M, typename K>
class Operations {
public:
    static MatrixOperations::Matrix<M> convolution(const MatrixOperations::Matrix<M>& matrix,
                                                const MatrixOperations::Kernel<K>& kernel) {
        // heavy computations...
        return MatrixOperations::Matrix<M>();
    }
};

int main(int argc, char **argv)
{
	std::cout << std::setprecision(3);

	MatrixOperations::Matrix<int> m(6);
	MatrixOperations::Kernel<float> k(3);

	m.populateRand(1, 5);
	k.populateRand(0, 4);

	m.printValues();
	std::cout<<std::endl;
	k.printValues();
	std::cout<<std::endl;

	MatrixOperations::Convolution<int, float> op(m, k);
	// next milestone
	// MatrixOperations::Matrix<float> m2 = m + k;
	// m2.printValues();

	return 0;
}