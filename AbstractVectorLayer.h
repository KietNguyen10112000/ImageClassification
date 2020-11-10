#pragma once
#include <vector>

using namespace std;

template <typename T>
class AbstractVectorLayer
{
private:
	bool isOutputLayer = false;

public:
	//z.size() == a.size() --> true
	vector<double> a;
	vector<double> z;

	//w.size() == z.size() --> true
	//w[0].size() == xInput.size() --> true
	vector<vector<double>> w;
	vector<double> b;

	//e.size() == z.size() --> true
	vector<double> e;

public:
	AbstractVectorLayer();
	AbstractVectorLayer(int numUnits, int numInputUnits, bool isOutputLayer);
	~AbstractVectorLayer();

public:
	virtual double activeFunc(double arg) = 0;
	virtual double gradFunc(double arg) = 0;

public:
	//result of update processing is put in public vectors
	template <typename P>
	void forwardUpdate(vector<P>& x);
	void backwardUpdate(AbstractVectorLayer<T>& layer);
	void updateWeight(vector<vector<double>>& dW, vector<double>& dBias);
	bool isInvalid();
};

template<typename T>
AbstractVectorLayer<T>::AbstractVectorLayer()
{
}

template<typename T>
AbstractVectorLayer<T>::AbstractVectorLayer(int numUnits, int numInputUnits, bool isOutputLayer)
{
	a = vector<double>(numUnits);
	z = vector<double>(numUnits);
	w = vector<vector<double>>(numUnits, vector<double>(numInputUnits, 0.001));
	e = vector<double>(numUnits);

	b = vector<double>(numUnits);
	this->isOutputLayer = isOutputLayer;
}

template<typename T>
AbstractVectorLayer<T>::~AbstractVectorLayer()
{
}

template<typename T>
template <typename P>
void AbstractVectorLayer<T>::forwardUpdate(vector<P>& x)
{
	for (int i = 0; i < w.size(); i++)
	{
		double sum = b[i];
		for (int j = 0; j < w[0].size(); j++)
		{
			sum += w[i][j] * x[j];
		}
		z[i] = sum;
		a[i] = activeFunc(sum);
	}
}

template<typename T>
void AbstractVectorLayer<T>::backwardUpdate(AbstractVectorLayer<T>& layer)
{
	for (int i = 0; i < layer.w[0].size(); i++)
	{
		double sum = 0;
		for (int j = 0; j < layer.w.size(); j++)
		{
			sum += layer.w[j][i] * layer.e[j];
		}
		e[i] = sum * gradFunc(z[i]);
	}
}

template<typename T>
void AbstractVectorLayer<T>::updateWeight(vector<vector<double>>& dW, vector<double>& dBias)
{
	for (int i = 0; i < w.size(); i++)
	{
		for (int j = 0; j < w[0].size(); j++)
		{
			w[i][j] += dW[i][j];
		}
		b[i] += dBias[i];
	}
}

template<typename T>
inline bool AbstractVectorLayer<T>::isInvalid()
{
	if (z.size() != a.size() 
		|| w.size() == z.size()) 
			return false;

	return true;
}
