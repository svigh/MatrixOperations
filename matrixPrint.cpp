#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iomanip>

template <class T> class Kernel{
public:
	Kernel(int _sizeX, int _sizeY) : sizeX(_sizeX), sizeY(_sizeY) { allocateSize(); }
	Kernel(int _size) : sizeX(_size), sizeY(_size) { allocateSize(); }
	Kernel() : sizeX(1), sizeY(1) { allocateSize(); }

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

private:
	int sizeX, sizeY;
	int strideX, strideY;
	std::vector< std::vector<T>> values;

	void allocateSize()
	{
		values.resize(sizeX);
		for(int i = 0; i < sizeX; ++i)
		{
			values[i].resize(sizeY);
		}
	}
};

template <class T> class Matrix{
public:
	Matrix(int _sizeX, int _sizeY) : sizeX(_sizeX), sizeY(_sizeY) { allocateSize(); }
	Matrix(int _size) : sizeX(_size), sizeY(_size) { allocateSize(); }
	Matrix() : sizeX(1), sizeY(1) { allocateSize(); }

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

	T getElement(int index_X, int index_Y){
		if( index_X > sizeX || index_Y > sizeY )
		{
			std::cout << "Error: index out of range.";
			exit(-1);
		}
		return values[index_X][index_Y];
	}

private:
	int sizeX, sizeY;
	std::vector< std::vector<T>> values;

	void Compute();

	void allocateSize()
	{
		values.resize(sizeX);
		for(int i = 0; i < sizeX; ++i)
		{
			values[i].resize(sizeY);
		}
	}
};

template <class T, class N> class Operation{
public:
	Operation(Matrix<T> _mat, Kernel<N> _ker) : mat(_mat), ker(_ker){}
	Operation() : mat(1), ker(1){}
protected:
	Matrix <T> mat;
	Kernel <N> ker;
};

template <class T, class N> class Addition: public Operation <T, N>{
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

		// this->* is to access the protected members of the operation mat and ker
		// this->mat.printValues();
		// this->ker.printValues();
		// std::cout<<"bullshit\n";



		for(int matX = 1; matX < this->mat.getXsize() - 1; ++matX)
		{
			for(int matY = 1; matY < this->mat.getYsize() - 1; ++matY)
			{
				output[matX][matY] = this->ker.getValues()[0][0] * this->mat.getValues()[matX-1][matY-1] + this->ker.getValues()[1][0] * this->mat.getValues()[matX][matY-1] + this->ker.getValues()[2][0] * this->mat.getValues()[matX+1][matY-1] + this->ker.getValues()[0][1] * this->mat.getValues()[matX-1][matY] + this->ker.getValues()[1][1] * this->mat.getValues()[matX][matY] + this->ker.getValues()[2][1] * this->mat.getValues()[matX+1][matY] + this->ker.getValues()[0][2] * this->mat.getValues()[matX-1][matY+1] + this->ker.getValues()[1][2] * this->mat.getValues()[matX][matY+1] + this->ker.getValues()[2][2] * this->mat.getValues()[matX+1][matY+1];
				output[matX][matY] /= this->ker.getXsize() * this->ker.getYsize();
			}
		}

		return output;
	}

public:
	Addition(Matrix<T> _mat, Kernel<N> _ker) : Operation <T,N> (_mat, _ker)
	{
		if( (this->mat.getXsize() < this->ker.getXsize()) || (this->mat.getYsize() < this->ker.getYsize()) )
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
	// void printValues()
	// {
	// 	for(auto &col : output)
	// 	{
	// 		for(T &elem : col)
	// 		{
	// 			std::cout<<elem<<" ";
	// 		}
	// 		std::cout<<std::endl;
	// 	}
	// }
};

int main(int argc, char **argv)
{
	std::cout << std::setprecision(3);

	Matrix <float> m(6);
	Kernel <float> k(3);

	m.populateRand(1, 5);
	k.populateRand(0, 4);

	m.printValues();
	std::cout<<std::endl;
	k.printValues();
	std::cout<<std::endl;
	Addition <float, float> op(m, k);
	// op.printValues();

	return 0;
}