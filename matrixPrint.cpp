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

int main()
{
	// fixed says that there will be a fixed number of decimal digits after the decimal point
	std::cout << std::fixed << std::setprecision(2);

	Primitives::Matrix<float> m(10);

	// TODO: only 3x3 kernel works with current conv
	Primitives::Kernel<int> k(4);

	// TODO: when int tensors are given the same lower and upper range it segfaults
	m.populateRand(1, 1245);
	k.populateRand(1, 1233);

	m.printValues();
	std::cout<<std::endl;
	k.printValues();
	std::cout<<std::endl;

	Operations::Convolution <float, int> op(m, k);

	// next milestone
	// Primitives::Matrix<float> m2 = m + k;
	// m2.printValues();

	return 0;
}