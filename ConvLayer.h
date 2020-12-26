#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ConvLayer
{
private:
	bool isPooling = false;

	vector<Mat> filter;
	vector<Mat> output;

	vector<Mat> dF;
	vector<Mat> dO;

	friend class ConvNeuralNet;

public:
	double (*activeFunc)(double arg) = 0;
	double (*gradFunc)(double arg) = 0;

public:
	ConvLayer();
	ConvLayer(int outputW, int outputH, int filterSize, int numfilter, bool isPoolingLayer);
	ConvLayer(ConvLayer& preLayer, int filterSize, int numfilter, bool isPoolingLayer);
	~ConvLayer();

private:
	template<typename T>
	T max(T a, T b, T c, T d);

public:
	void blindActiveFunc(double (*activeFunc)(double arg));
	void blindGradFunc(double (*gradFunc)(double arg));
	void forwardUpdate(ConvLayer& preLayer);
	void backwardUpdate(ConvLayer& preLayer, ConvLayer& nextLayer);
	void updatefilter(Mat dfilter);

};

ConvLayer::ConvLayer()
{
}

ConvLayer::ConvLayer(int outputW, int outputH, int filterSize, int numfilter, bool isPoolingLayer)
{
}

ConvLayer::ConvLayer(ConvLayer& preLayer, int filterSize, int numfilter, bool isPoolingLayer)
{
	this->isPooling = isPoolingLayer;
	filter = vector<Mat>(numfilter, Mat(filterSize, filterSize, CV_32F));
	output = vector<Mat>(preLayer.output.size() * preLayer.filter.size());

	dO = vector<Mat>(output.size(), Mat(output[0].cols, output[0].rows, CV_32F));
	dF = vector<Mat>(numfilter, Mat(filterSize, filterSize, CV_32F));
}

ConvLayer::~ConvLayer()
{
}

inline void ConvLayer::blindActiveFunc(double (*activeFunc)(double arg))
{
	this->activeFunc = activeFunc;
}

inline void ConvLayer::blindGradFunc(double(*gradFunc)(double arg))
{
	this->gradFunc = gradFunc;
}

template<typename T>
inline T ConvLayer::max(T a, T b, T c, T d)
{
	T temp1 = a > b ? a : b;
	T temp2 = c > d ? c : d;

	return temp1 > temp2 ? temp1 : temp2;
}

void ConvLayer::forwardUpdate(ConvLayer& preLayer)
{
	int index = 0;
	for (int i = 0; i < preLayer.output.size(); i++)
	{
		for (int j = 0; j < preLayer.filter.size(); j++)
		{
			filter2D(preLayer.output.at(i), output.at(index), -1, preLayer.filter.at(j), Point(-1, -1), 0, BORDER_ISOLATED);
			index++;
		}
	}
	if (isPooling)
	{
		Mat temp = Mat(output[0].cols / 2, output[0].rows / 2, output[0].type());
		for (int i = 0; i < output.size(); i++)
		{
			for (int j = 0; j < output[i].rows; j += 2)
			{
				for (int k = 0; k < output[i].cols; k += 2)
				{
					Vec3b v1 = output[i].at<Vec3b>(j, k);
					Vec3b v2 = output[i].at<Vec3b>(j, k + 1);
					Vec3b v3 = output[i].at<Vec3b>(j + 1, k);
					Vec3b v4 = output[i].at<Vec3b>(j + 1, k + 1);
					Vec3b re = Vec3b(
						max(v1[0], v2[0], v3[0], v4[0]),
						max(v1[1], v2[1], v3[1], v4[1]),
						max(v1[2], v2[2], v3[2], v4[2])
						);
					temp.at<Vec3b>(j, k) = re;
				}
			}
		}
	}
}

void ConvLayer::backwardUpdate(ConvLayer& preLayer, ConvLayer& nextLayer)
{
	for (int i = 0; i < filter.size(); i++)
	{
		filter2D(preLayer.output.at(i), dF.at(i), -1, nextLayer.dO.at(i), Point(-1, -1), 0, BORDER_ISOLATED);
	}



}

void ConvLayer::updatefilter(Mat dfilter)
{
}
