#include "Matrix.h"

// int double_plus_one(int n)
// {
// 	return 2*n + 1;
// }

int main(int argc, char** argv)
{
	Matrix<float> m1(2, 1);
	Matrix<float> m2(2, 3);
	Matrix<float> m3;

	m1.randomize();
	m2.randomize();

	m1.print();
	m2.print();

	m1 = m1.transpose();
	m1.print();
	
	m3 = ((m1 - 1) * m2 + 1) * 2;
	m3.print();

	m3 = m3 + m3;
	m3.print();

	//m1.map(double_plus_one);
	m1.print();

	//Matrix<int>::map(m1, double_plus_one).print();
}

