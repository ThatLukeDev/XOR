#include <iostream>

#include "matrix.hpp"

int main() {
	matrix<int, 2, 3> M1;
	matrix<int, 3, 2> M2;
	matrix<int, 2, 3> M3;

	M1[0][0] = 4;
	M1[1][0] = 3;
	M1[0][1] = 2;
	M1[1][1] = 3;
	M1[0][2] = 1;
	M1[1][2] = 2;

	M2[0][0] = 2;
	M2[1][0] = 3;
	M2[2][0] = 3;
	M2[0][1] = 1;
	M2[1][1] = 1;
	M2[2][1] = 2;

	M3[0][0] = 2;
	M3[1][0] = 3;
	M3[0][1] = 3;
	M3[1][1] = 1;
	M3[0][2] = 1;
	M3[1][2] = 2;

	std::cout << "M1:\n" << M1 << std::endl;
	std::cout << "M2:\n" << M2 << std::endl;
	std::cout << "M3:\n" << M3 << std::endl;
	std::cout << "M1*M2:\n" << M1*M2 << std::endl;
	std::cout << "M1+M3:\n" << M1+M3 << std::endl;
	std::cout << "M1-M3:\n" << M1-M3 << std::endl;
	std::cout << "M1*2:\n" << M1*2 << std::endl;

	return 0;
}
