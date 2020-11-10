#pragma once
#include "AbstractVectorLayer.h"

template <typename T>
class VectorLayerReLU : public AbstractVectorLayer<T>
{
private:

public:
	VectorLayerReLU(int numUnits, int numInputUnits, bool isOutputLayer);
	~VectorLayerReLU();

public:
	// Inherited via VectorLayerInterface
	double activeFunc(double arg) override; //ReLU
	double gradFunc(double arg) override;
};

template<typename T>
VectorLayerReLU<T>::VectorLayerReLU(int numUnits, int numInputUnits, bool isOutputLayer) 
	: AbstractVectorLayer<T>(numUnits, numInputUnits, isOutputLayer)
{
}

template<typename T>
VectorLayerReLU<T>::~VectorLayerReLU()
{
}

template<typename T>
inline double VectorLayerReLU<T>::activeFunc(double arg)
{
	return arg > 0 ? arg : 0;
}

template<typename T>
inline double VectorLayerReLU<T>::gradFunc(double arg)
{
	return arg > 0 ? 1 : 0;
}
