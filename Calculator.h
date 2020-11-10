#pragma once
#include <algorithm> 

using namespace std;

class Calculator
{
public:
	//the result will be put to outMtReasult, you need to allocate it by yourself !!!
	template<typename T = float, typename P = double>
	static void mulMatrix(T** mt1, int row1, int col1, P** mt2, int row2, int col2, P** outMtResult);
	//the result will be put to outMtReasult, you need allocate it by yourself !!!
	//mul matrix to a number
	template<typename T>
	static void mulMatrix(T** mt, int row, int col, T coef, T** outMtResult);

	template<typename T>
	static void sumMatrix(T** mt1, int row1, int col1, T** mt2, int row2, int col2, T** outMtResult);

	//mt1 - mt2
	template<typename T>
	static void subMatrix(T** mt1, int row1, int col1, T** mt2, int row2, int col2, T** outMtResult);

	template<typename T = float, typename P = double>
	static void transposeMatrix(T** mt, int row, int col, P** outMtResult);

	static void shuffle(int* index, int size, int range);

};

template<typename T, typename P>
void Calculator::mulMatrix(T** mt1, int row1, int col1, P** mt2, int row2, int col2, P** outMtResult)
{
	if(col1 != row2) return;

	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col2; j++)
		{
			T res = 0;
			for (int k = 0; k < col1; k++)
			{
				res += mt1[i][k] * mt2[k][i];
			}
			outMtResult[i][j] = res;
		}
	}
}

template<typename T>
void Calculator::mulMatrix(T** mt, int row, int col, T coef, T** outMtResult)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			outMtResult[i][j] = mt[i][j] * coef;
		}
	}
}

template<typename T>
void Calculator::sumMatrix(T** mt1, int row1, int col1, T** mt2, int row2, int col2, T** outMtResult)
{
	if (col1 != col2) return;
	if (row1 != row2) return;
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col1; j++)
		{
			outMtResult[i][j] = mt1[i][j] + mt2[i][j];
		}
	}
}

template<typename T>
void Calculator::subMatrix(T** mt1, int row1, int col1, T** mt2, int row2, int col2, T** outMtResult)
{
	if (col1 != col2) return;
	if (row1 != row2) return;
	if (outMtResult == nullptr)
	{
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				mt1[i][j] -= mt2[i][j];
			}
		}
	}
	else 
	{
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				outMtResult[i][j] = mt1[i][j] - mt2[i][j];
			}
		}
	}
}

template<typename T, typename P>
void Calculator::transposeMatrix(T** mt, int row, int col, P** outMtResult)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			outMtResult[j][i] = mt[i][j];
		}
	}
}
void Calculator::shuffle(int* index, int size, int range)
{
	for (int i = 0; i < size; i++)
	{
		index[i] = rand() % range;
	}
}
