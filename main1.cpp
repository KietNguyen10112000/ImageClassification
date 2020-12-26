#include <iostream>
//#include <sstream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include "SoftmaxRegression.h"
//#include "MultiLayerNeuralNet.h"
//#include <opencv2/opencv.hpp>
//#include "ConvLayer.h"
//#include "CropImage.h"
//#include <string>
//#include <ctime>
//#include <fstream>
//#include <filesystem>

using namespace std;
//using namespace cv;

//int main()
//{
	//ifstream f("testSoftmax.txt");
	//string line;
	//istringstream in(line);
	//
	//double a = 0, b = 0, c= 0;

	//vector<vector<float>> xTrain;

	//while (!f.eof())
	//{
	//	getline(f, line);

	//	line.erase(line.begin());
	//	
	//	in.str(line);
	//	in >> a >> b;// >> c;

	//	vector<float> temp;
	//	temp.push_back(a);
	//	temp.push_back(b);
	//	//temp.push_back(c);
	//	xTrain.push_back(temp);

	//}


	//vector<int> yTrain = vector<int>(2500);
	//int count = 0;
	//for (int i = 0; i < 2500; i++)
	//{
	//	if (i % 500 == 0 && i != 0)
	//	{
	//		count++;
	//	}
	//	yTrain[i] = count;
	//}
	/*SoftmaxRegression softModel = SoftmaxRegression(2, 5);

	softModel.fit<float>(xTrain, yTrain, 10000, 0.05, 10, pow(10,-8));

	int ct = 0;
	for (int i = 0; i < 2500; i++)
	{
		int re = softModel.predict<float>(xTrain[i]);
		if (re == yTrain[i])
		{
			ct++;
		}
	}*/



	/*SoftmaxRegression model = SoftmaxRegression(2, 5);

	model.fit<float>(xTrain, yTrain, 10000, 0.05, 10, 1e-8);*/
	/*int max = 0;
	int index = 0;
	for (int q = 2; q < 100; q++)
	{
		for (int k = 2; k < 100; k++)
		{
			vector<int> layersDisc = { k,q,5 };
			MultiLayerNeuralNet model = MultiLayerNeuralNet<float>(xTrain[0].size(), layersDisc);
			model.fit(xTrain, yTrain, 10000, 0.05, 10, 0);
			int ct = 0;
			for (int i = 0; i < 2500; i++)
			{
				int re = model.predict(xTrain[i]);
				if (re == yTrain[i])
				{
					ct++;
				}
			}
			cout << "k = " << k << ", q = " << q << " --> " << ct << "/2500"<< endl;
			if (ct > max)
			{
				max = ct;
				index = k;
			}
		}
	}

	system("pause");*/

	//Mat img = cv::imread("D:\\Artificial Intelligence\\Dataset\\test.bmp");

	//

	//cv::Mat kernelH = Mat(3, 3, CV_32F);

	//for (int i = 0; i < kernelH.rows; i++)
	//{
	//	for (int j = 0; j < kernelH.cols; j++)
	//	{
	//		kernelH.at<float>(i, j) = -1.0f;
	//	}
	//}

	//kernelH.at<float>(1, 1) = 8.0f;

	////cout << img.at<float>(0, 0) << ", " << img.at<float>(0, 1) << ", " << img.at<float>(0, 2) << endl;

	///*Mat bgr[3];
	//split(img, bgr);*/

	//Mat dest = Mat(3,3, CV_8U);
	////cv::dnn::Net net = cv::dnn::readNet("e://xor.pb");

	////cvtColor(img, dest, COLOR_BGR2GRAY);

	//filter2D(img, dest, CV_8U, kernelH, Point(1, 1), 0, BORDER_ISOLATED);

	//cout << img.size[0] << ", " << img.size[1] << endl;
	//cout << dest.size[0] << ", " << dest.size[1] << endl;

	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		cout << img.at<Vec3b>(i, j) << "--";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		cout << dest.at<Vec3b>(i, j) << "--";
	//	}
	//	cout << endl;
	//}

	////Mat dest2;
	////filter2D(dest, dest2, CV_8U, kernelH, Point(-1, -1), 0, BORDER_DEFAULT);

	////cout << dest.at<float>(10, 2) << endl;

	//imshow("haha", dest);

	//waitKey();

	//cropImage(L"D:\\Artificial Intelligence\\Dataset\\14-11-2020.bmp", 760, 295, 1080, 625,
		//L"D:\\Artificial Intelligence\\Dataset\\14-11-2020_croped.bmp");

	//wstring path;


	//return 0;
//}


