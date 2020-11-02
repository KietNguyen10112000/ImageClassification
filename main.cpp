#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "SoftmaxRegression.h"

using namespace std;

int main()
{
	ifstream f("D:\\Artificial Intelligence\\Dataset\\testSoftmax.txt");
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
	SoftmaxRegression softModel = SoftmaxRegression(2, 5);

	softModel.fit<float>(xTrain, yTrain, 10000, 0.05, 10, pow(10,-8));

	int ct = 0;
	for (int i = 0; i < 2500; i++)
	{
		int re = softModel.predict<float>(xTrain[i]);
		if (re == yTrain[i])
		{
			ct++;
		}
	}

	cout << ct << endl;

	return 0;
}