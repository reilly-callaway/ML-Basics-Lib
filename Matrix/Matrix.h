#ifndef Matrix_h
#define Matrix_h

#include <vector>

template<class T>
class Matrix
{
	public:
		std::vector< std::vector<T> > data;
		int rows;
		int colms;

		Matrix(int rows, int colms);
		Matrix();
		Matrix operator+(const Matrix& m);
		Matrix operator+(const T& item);
		Matrix operator-(const Matrix& m);
		Matrix operator-(const T& item);
		Matrix operator*(const Matrix& m);
		Matrix operator*(const T& item);
		static Matrix transpose(const Matrix m);
		Matrix transpose();
		void print();
		void randomize(T lower = -1.0, T upper = 1.0);
		void map(T (*func)(T));
		static Matrix map(const Matrix m, T (*func)(T));

	private:
};

#include "Matrix.tpp"
#endif