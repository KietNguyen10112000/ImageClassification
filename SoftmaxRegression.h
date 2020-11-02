#pragma once
#include <vector>
#include <algorithm> 
#include <cmath>
#include <iostream>

using namespace std;

class SoftmaxRegression
{
private:
	int dimension = 1;
	long double norm = 0;
	//w[i] is weight vector for class i
	vector<vector<double>> w;
	vector<vector<double>> a;
	vector<vector<double>> z;
	//bias[i] is bias of class i
	vector<double> bias;

public:
	//dimension of a input value
	//numClass is number of class to classify
	SoftmaxRegression(int dimension = 1, int numClass = 1);
	~SoftmaxRegression();

private:
	double softmax(int index, int col, int max);
	void shuffle(int* index, int size, int xTrainSize);
	void subMtSoftmax(int* vec, int vecSize);

	template <typename T>
	void updateWeights(double leaningRate, int* index, int size, vector<vector<T>>& xTrain, vector<int>& yTrain);

	template <typename T>
	void updateZ(vector<T>& x, int index);

	template <typename T>
	void updateNetwork(int* index, int size, vector<vector<T>>& xTrain);
	
public:
	int getDimension();
	//dimension of xTrain[i] = dimension
	template <typename T>
	void fit(vector<vector<T>>& xTrain, vector<int>& yTrain, int nEps, float leaningRate, int batchSize = 10, double limit = pow(10, -5));
	template <typename T>
	int predict(vector<T> x);
	
};

SoftmaxRegression::SoftmaxRegression(int dimension, int numClass)
{
	this->dimension = dimension;
	w = vector<vector<double>>(numClass, vector<double>(dimension));
	bias = vector<double>(numClass, 1);
}

SoftmaxRegression::~SoftmaxRegression()
{
}

inline int SoftmaxRegression::getDimension()
{
	return dimension;
}

void SoftmaxRegression::subMtSoftmax(int* vec, int vecSize)
{
	for (int i = 0; i < vecSize; i++)
	{
		a[i][vec[i]] -= 1;
	}
}

double SoftmaxRegression::softmax(int index, int locate, int max)
{
	double sum = 0;
	for (int i = 0; i < z[0].size(); i++)
	{
		sum = sum + exp(z[index][i] - z[index][max]);
	}
	return exp(z[index][locate] - z[index][max]) / sum;
}

template <typename T>
void SoftmaxRegression::updateWeights(double leaningRate, int* index, int size, vector<vector<T>>& xTrain, vector<int>& yTrain)
{
	vector<double*> e(size);
	//vector<vector<double>> e(size);

	subMtSoftmax(&yTrain[0], yTrain.size());

	vector<T*> xB(size);
	//vector<vector<double>> xB(size);

	for (int i = 0; i < size; i++)
	{
		e[i] = &(a[index[i]][0]);
		xB[i] = &(xTrain[index[i]][0]);
		//e[i] = (a[index[i]]);
		//xB[i] = (xTrain[index[i]]);
	}

	vector<vector<double>> eT(w.size(), vector<double>(size));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < w.size(); j++)
		{
			eT[j][i] = e[i][j];
		}
	}

	vector<vector<double>> dW(w.size(), vector<double>(dimension));
	vector<double> dBias(w.size());


	for (int i = 0; i < dW.size(); i++)
	{
		for (int j = 0; j < dW[0].size(); j++)
		{
			double res = 0;
			for (int k = 0; k < size; k++)
			{
				res += xB[k][j] * eT[i][k];
			}
			dW[i][j] = res + eT[i][(long long)size - 1];

			res = 0;
			for (int k = 0; k < size; k++)
			{
				res += eT[i][k];
			}
			dBias[i] = res;
		}
	}
	norm = 0;
	double t = leaningRate / size;
	for (int i = 0; i != w.size(); i++)
	{
		for (int j = 0; j < w[0].size(); j++)
		{
			w[i][j] -= t * dW[i][j];
			bias[i] -= t * dBias[i];
			norm += (t * dW[i][j]) * (t * dW[i][j]);
		}
	}

}

template <typename T>
void SoftmaxRegression::updateZ(vector<T>& x, int index)
{
	for (int j = 0; j < z[0].size(); j++)
	{
		z[index][j] = bias[j];
		for (int k = 0; k < w[0].size(); k++)
		{
			z[index][j] = z[index][j] + x[k] * w[j][k];
		}
	}

	int max = 0;
	for (int i = 0; i < z[0].size(); i++)
	{
		if (z[index][max] < z[index][i])
		{
			max = i;
		}
	}


	for (int j = 0; j < a[0].size(); j++)
	{
		a[index][j] = softmax(index, j, max);
	}

}

template <typename T>
void SoftmaxRegression::updateNetwork(int* index, int size, vector<vector<T>>& xTrain)
{
	for (int i = 0; i < size; i++)
	{
		updateZ(xTrain[index[i]], index[i]);
	}
}

template <typename T>
int SoftmaxRegression::predict(vector<T> x)
{
	int max = 0;
	updateZ(x, 0);
	for (int i = 0; i < a[0].size(); i++)
	{
		if (a[0][i] > a[0][max]) max = i;
	}

	return max;
}

void SoftmaxRegression::shuffle(int* index, int size, int xTrainSize)
{
	for (int i = 0; i < size; i++)
	{
		index[i] = rand() % xTrainSize;
	}
}

template <typename T>
void SoftmaxRegression::fit(vector<vector<T>>& xTrain, vector<int>& yTrain, int nEps, float leaningRate, int batchSize, double limit)
{
	vector<int> index(batchSize);

	int i = 0;

	z = vector<vector<double>>(xTrain.size(), vector<double>(w.size()));
	a = vector<vector<double>>(xTrain.size(), vector<double>(w.size()));

	while (i != nEps)
	{
		shuffle(&index[0], index.size(), xTrain.size());
		updateNetwork(&index[0], batchSize, xTrain);
		updateWeights(leaningRate, &index[0], batchSize, xTrain, yTrain);
		if (norm < limit)
		{
			cout << i << endl;
			break;
		}
		i++;
	}
}
