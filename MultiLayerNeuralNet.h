#pragma once
#include "VectorLayerReLU.h"
#include "Calculator.h"
#include <algorithm> 
#include <cmath>

template <typename T>
class MultiLayerNeuralNet
{
private:
	vector<VectorLayerReLU<T>> layers;
	vector<vector<double>> dW;

	//eMat[0] is eMatrix of first layer ...
	vector<vector<vector<double>>> eMat;
	//aMat[0] is aMatrix of first layer ...
	vector<vector<vector<double>>> aMat;
	vector<double> dB;

	vector<vector<T>>* xTrain = nullptr;
	vector<int>* yTrain = nullptr;
	AbstractVectorLayer<T>* output = nullptr;

	double leaningRate = 0;
	vector<double> normDW;

public:
	/*
	MultiLayerNeuralNet use mini bacth to optimize
	I------------------------I
	How to use this class?
	I------------------------I
	dimension is dimension of each input for fit processing
	I------------------------I
	layersDescription is discription for each layer of MultiLayerNeuralNet
	example {3, 3, 4} is presenting a MultiLayerNeuralNet which has 2 hidden layers and 1 output layer
	2 hidden layers - each one has 3 hidden unit,
	and 1 output layer has 4 output unit of 4 class to classify
	*/
	MultiLayerNeuralNet(int dimension, vector<int> layersDescription);
	~MultiLayerNeuralNet();

private:
	void update(int* index, int size);
	void softmax();
	bool hasEffect(double limit);

public:
	void fit(vector<vector<T>>& xTrain, vector<int>& yTrain, int nEps,
		float leaningRate, int batchSize = 10, double limit = 1e-5);
	int predict(vector<T>& x);

};

template<typename T>
MultiLayerNeuralNet<T>::MultiLayerNeuralNet(int dimension, vector<int> layersDescription)
{
	layers.push_back(VectorLayerReLU<T>(layersDescription[0], dimension, false));
	for (int i = 1; i < layersDescription.size(); i++)
	{
		layers.push_back(VectorLayerReLU<T>(layersDescription[i], layersDescription[i - 1], false));
	}

	//make temp dW and dB to update weight and bias of each layer
	int maxX = 0, maxY = 0;
	for (int i = 0; i < layers.size(); i++)
	{
		if (maxX < layers[i].w.size()) maxX = layers[i].w.size();
		if (maxY < layers[i].w[0].size()) maxY = layers[i].w[0].size();
	}
	dB = vector<double>(maxX);
	dW = vector<vector<double>>(maxX, vector<double>(maxY));

	output = &layers[layers.size() - 1];

	normDW = vector<double>(layersDescription.size());

}

template<typename T>
MultiLayerNeuralNet<T>::~MultiLayerNeuralNet()
{
}

template<typename T>
void MultiLayerNeuralNet<T>::update(int* index, int size)
{
	for (int i = 0; i < size; i++)
	{
		layers[0].forwardUpdate<T>((*xTrain)[index[i]]);
		for (int j = 1; j < layers.size(); j++)
		{
			layers[j].forwardUpdate<double>(layers[j - 1].a);
		}
		//last forward update for output layer because we use softmax for last layer
		softmax();
		
		//start backward update from output layer
		for (int j = 0; j < output->a.size(); j++)
		{
			output->e[j] = output->a[j] / (double)size;
		}
		output->e[(*yTrain)[index[i]]] -= 1 / (double)size;

		//backward update for hidden layers
		for (int j = layers.size() - 2; j > -1; j--)
		{
			layers[j].backwardUpdate(layers[j + 1]);
		}
		for (int j = 0; j < layers.size(); j++)
		{
			aMat[j][i] = layers[j].a;
			eMat[j][i] = layers[j].e;
		}
	}

	//update weights
	//first layer
	normDW[0] = 0;
	for (int i = 0; i < layers[0].w.size(); i++)
	{
		for (int j = 0; j < layers[0].w[0].size(); j++)
		{
			double res = 0;
			for (int k = 0; k < size; k++)
			{
				res += (*xTrain)[index[k]][j] * eMat[0][k][i];
			}
			dW[i][j] = -res * leaningRate;
			normDW[0] += dW[i][j] * dW[i][j];

			res = 0;
			for (int k = 0; k < size; k++)
			{
				res += eMat[0][k][i];
			}
			dB[i] = -res * leaningRate;
		}
	}

	layers[0].updateWeight(dW, dB);

	//all layers behind
	for (int q = 1; q < layers.size(); q++)
	{
		normDW[q] = 0;
		for (int i = 0; i < layers[q].w.size(); i++)
		{
			//int y = 0;
			for (int j = 0; j < layers[q].w[0].size(); j++)
			{
				double res = 0;
				for (int k = 0; k < size; k++)
				{
					res += aMat[(long long)q - 1][k][j] * eMat[q][k][i];
				}
				dW[i][j] = -res * leaningRate;
				normDW[q] += dW[i][j] * dW[i][j];

				res = 0;
				for (int k = 0; k < size; k++)
				{
					res += eMat[q][k][i];
				}
				dB[i] = -res * leaningRate;
			}
			//int x = 0;
		}

		layers[q].updateWeight(dW, dB);

	}
}

template<typename T>
void MultiLayerNeuralNet<T>::softmax()
{
	/*int max = 0;
	for (int i = 0; i < z.size(); i++)
	{
		if (z[i] > z[max]) max = i;
	}
	double sum = 0;
	for (int i = 0; i < z.size(); i++)
	{
		sum = sum + exp(z[i] - z[max]);
	}
	return exp(z[index] - z[max]) / sum;*/
	double max = 0;
	double sum = 0;
	for (int j = 0; j < output->z.size(); j++)
	{
		if (max < output->z[j]) max = output->z[j];
	}

	for (int i = 0; i < output->z.size(); i++)
	{
		sum += exp(output->z[i] - max);
	}

	for (int j = 0; j < output->z.size(); j++)
	{
		output->a[j] = exp(output->z[j] - max) / sum;
	}
}

template<typename T>
inline bool MultiLayerNeuralNet<T>::hasEffect(double limit)
{
	double max = 0;
	for (int i = 0; i < normDW.size(); i++)
	{
		if (max < normDW[i]) max = normDW[i];
	}

	if (sqrt(max) >= limit) return true;

	return false;
}

template<typename T>
void MultiLayerNeuralNet<T>::fit(vector<vector<T>>& xTrain, vector<int>& yTrain, int nEps, float leaningRate, int batchSize, double limit)
{
	this->xTrain = &xTrain;
	this->yTrain = &yTrain;
	this->leaningRate = leaningRate;

	//eMat[i].size = batchSize;
	eMat = vector<vector<vector<double>>>(layers.size());
	//aMat[i].size = batchSize;
	aMat = vector<vector<vector<double>>>(layers.size());

	for (int i = 0; i < layers.size(); i++)
	{
		eMat[i] = vector<vector<double>>(batchSize, vector<double>(layers[i].e.size()));
		aMat[i] = vector<vector<double>>(batchSize, vector<double>(layers[i].a.size()));
	}

	vector<int> index(batchSize);
	//index[0] = 0;
	for (int i = 0; i < nEps; i++)
	{
		Calculator::shuffle(&index[0], index.size(), xTrain.size());
		//index[0] = (index[0] + 1) % yTrain.size();
		update(&index[0], index.size());
		if (!hasEffect(limit))
		{
			break;
		}
	}

}

template<typename T>
int MultiLayerNeuralNet<T>::predict(vector<T>& x)
{
	layers[0].forwardUpdate<T>(x);
	for (int j = 1; j < layers.size(); j++)
	{
		layers[j].forwardUpdate<double>(layers[j - 1].a);
	}

	softmax();

	int max = 0;
	for (int i = 0; i < output->a.size(); i++)
	{
		if (output->a[max] < output->a[i]) max = i;
	}

	return max;
}
