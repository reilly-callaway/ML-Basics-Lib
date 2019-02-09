#include "Matrix.h"
#include <iostream>
#include <random>

template <class T>
Matrix<T>::Matrix(int rows, int colms): rows(rows), colms(colms)
{
	// Set the size of the vector matrix and initialise all values to 0.
	data.assign(rows, vector<T>(colms, 0));
}

template <class T>
Matrix<T>::Matrix()
{

}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix& m)
{
	Matrix new_matrix(this->rows, this->colms);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] + m.data[i][j];
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const T& item)
{
	Matrix new_matrix(this->rows, this->colms);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] + item;
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix& m)
{
	Matrix new_matrix(this->rows, this->colms);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] - m.data[i][j];
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const T& item)
{
	Matrix new_matrix(this->rows, this->colms);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] - item;
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix& m)
{
	Matrix new_matrix(this->rows, m.colms);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			for(int k = 0; k < this->colms; k++)
			{
				new_matrix.data[i][j] += this->data[i][k] * m.data[k][j];
			}
			
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T& item)
{
	Matrix new_matrix(this->rows, this->colms);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] * item;
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::transpose(const Matrix m)
{
	Matrix new_matrix(m.colms, m.rows);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = m.data[j][i];
		}
	}
	return new_matrix;
}

template <class T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix new_matrix(this->colms, this->rows);
	for(int i = 0; i < new_matrix.rows; i++)
	{
		for(int j = 0; j < new_matrix.colms; j++)
		{
			new_matrix.data[i][j] = this->data[j][i];
		}
	}
	return new_matrix;
}

template <class T>
void Matrix<T>::print()
{
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->colms; j++)
		{
			cout << this->data[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <class T>
void Matrix<T>::randomize(T lower, T upper)
{
	random_device seeder;
	mt19937 rd(seeder());
	uniform_real_distribution<float> dist(lower, upper);

	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->colms; j++)
		{
			this->data[i][j] = dist(rd);
		}
	}
}

template <class T>
void Matrix<T>::map(T (*func)(T))
{
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->colms; j++)
		{
			this->data[i][j] = func(this->data[i][j]);
		}

	}
}

template <class T>
Matrix<T> Matrix<T>::map(const Matrix m, T (*func)(T))
{
	Matrix new_matrix(m.rows, m.colms);
	for(int i = 0; i < m.rows; i++)
	{
		for(int j = 0; j < m.colms; j++)
		{
			new_matrix.data[i][j] = func(m.data[i][j]);
		}
	}
	return new_matrix;
}