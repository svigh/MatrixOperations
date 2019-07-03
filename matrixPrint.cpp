#include <stdio.h>
#include <iomanip>
#include <stdlib.h>

#include "primitives.h"
#include "operations.h"

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

// Maybe define the operations between matrices by themselvs containing the operations, not make a separate operation type
// Actually no, but maybe
// template<typename M, typename K>
// class Operations {
// public:
//     static Primitives::Matrix<M> convolution(const Primitives::Matrix<M>& matrix,
//                                                 const Primitives::Kernel<K>& kernel) {
//         // heavy computations...
//         return Primitives::Matrix<M>();
//     }
// };

int main(int argc, char **argv)
{
	std::cout << std::setprecision(3);

	Primitives::Matrix<float> m(6);

	// TODO: only 3x3 kernel works with current conv
	Primitives::Kernel<float> k(3);

	// TODO: when int tensors are given the same lower and upper range it segfaults
	m.populateRand(1, 2);
	k.populateRand(1, 1);

	m.printValues();
	std::cout<<std::endl;
	k.printValues();
	std::cout<<std::endl;

	Operations::Convolution<float, float> op(m, k);
	// next milestone
	// Primitives::Matrix<float> m2 = m + k;
	// m2.printValues();

	return 0;
}