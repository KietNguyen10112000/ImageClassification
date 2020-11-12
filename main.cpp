#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "SoftmaxRegression.h"
#include "MultiLayerNeuralNet.h"

using namespace std;

int main()
{
	ifstream f("testSoftmax.txt");
	string line;
	istringstream in(line);
	
	double a = 0, b = 0, c= 0;

	vector<vector<float>> xTrain;

	while (!f.eof())
	{
		getline(f, line);

		line.erase(line.begin());
		
		in.str(line);
		in >> a >> b;// >> c;

		vector<float> temp;
		temp.push_back(a);
		temp.push_back(b);
		//temp.push_back(c);
		xTrain.push_back(temp);

	}


	vector<int> yTrain = vector<int>(2500);
	int count = 0;
	for (int i = 0; i < 2500; i++)
	{
		if (i % 500 == 0 && i != 0)
		{
			count++;
		}
		yTrain[i] = count;
	}
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
	int max = 0;
	int index = 0;
	for (int k = 2; k < 100; k++)
	{
		vector<int> layersDisc = { k,5 };
		MultiLayerNeuralNet model = MultiLayerNeuralNet<float>(xTrain[0].size(), layersDisc);
		model.fit(xTrain, yTrain, 10000, 0.05, 5, 1e-8);
		int ct = 0;
		for (int i = 0; i < 2500; i++)
		{
			int re = model.predict(xTrain[i]);
			if (re == yTrain[i])
			{
				ct++;
			}
		}
		cout << "k = " << k << "--> " << ct << endl;
		if (ct > max)
		{
			max = ct;
			index = k;
		}
	}

	

	//cout << ct << endl;
	//
	//cout << "haha" << endl;
	//VectorLayerReLU<float> reLu = VectorLayerReLU<float>(1, 2, false);
	//cout << reLu.activeFunc(10) << endl;

	return 0;
}
