#include <stdio.h>
#include <iomanip>
#include <stdlib.h>

#include "Types/Matrix.h"
#include "Types/Kernel.h"
#include "Operations/BitwiseProduct.h"

// virtual function
// friend classes
// forward declarations
// extern "C"
// callbacks
// algorithm
// lambdas

int main()
{
	// 'fixed' says that there will be a fixed number of decimal digits after the decimal point
	std::cout << std::fixed << std::setprecision(2);

	Matrix<int> m(10);

	Kernel<int> k(10);

	// TODO: when int tensors are given the same lower and upper range it segfaults
	m.populateRand(1, 12);
	k.populateRand(1, 13);

	m.printValues();
	std::cout<<std::endl;
	k.printValues();
	std::cout<<std::endl;

	BitwiseProduct <int, int> op(m, k);

	// next milestone
	// Matrix<float> m2 = m + k;
	// m2.printValues();

	return 0;
}