//#pragma once
//#include <Windows.h>
////#include <fstream>
////#include <vector>
//#include <atlimage.h>
//#include <cassert>
//#include <gdiplus.h>
//#include <string>
//#include <ctime>
//#include <iostream>
//#include <filesystem>
//
//#define CString
//
//using namespace std;
//
//
//
//void cropImage(const wchar_t* path, int x, int y, int width, int height, const wchar_t* savePath)
//{
//	CImage image;
//	CImage saveImg;
//
//	image.Load(path);
//
//	assert(x + width < image.GetWidth());
//	assert(y + height < image.GetHeight());
//
//	saveImg.Create(width, height, image.GetBPP());
//
//	for (int i = 0; i < width; i++)
//	{
//		for (int j = 0; j < height; j++)
//		{
//			saveImg.SetPixel(i, j, image.GetPixel(i + x, j + y));
//		}
//	}
//
//	saveImg.Save(savePath, Gdiplus::ImageFormatJPEG);
//
//}
//
//std::wstring Format(time_t time)
//{
//	tm dateTime;
//	localtime_s(&dateTime, &time);
//
//	return std::to_wstring(dateTime.tm_mday) + L"-"
//		+ std::to_wstring(dateTime.tm_mon + 1) + L"-" + std::to_wstring(1900 + dateTime.tm_year);
//}
//
//int main()
//{
//	wstring fileName;
//	wstring path;
//	wstring save;
//
//	cout << "Raw Data path: ";
//	getline(wcin, path);
//
//	cout << "Save Data path: ";
//	getline(wcin, save);
//
//	cout << "First file: ";
//	getline(wcin, fileName);
//
//	size_t index = fileName.find(L".bmp");
//
//	fileName.erase(index, sizeof(".bmp"));
//
//	time_t time = std::time(0);
//	wstring fo = Format(time);
//
//	while (wcscmp(fileName.c_str(), fo.c_str()) != 0)
//	{
//		time -= 24 * 60 * 60;
//		fo = Format(time);
//	}
//
//
//	int count = 1;
//	//cout << filesystem::exists(path + L"20-10-2020" + L".bmp") << endl;
//	while (filesystem::exists(path + fo + L".bmp"))
//	{
//		time -= 24 * 60 * 60;
//		cropImage((path + fo + L".bmp").c_str(), 760, 295, 1080, 625,
//			(save + Format(time) + L".bmp").c_str());
//
//		cout << "Current proccessing: " << count << " images ";
//
//		fo = Format(time);
//		wcout << fo << endl;
//		count++;
//	}
//
//	system("pause");
//
//	return 0;
//}

#pragma once
#include <Windows.h>
//#include <fstream>
//#include <vector>
#include <atlimage.h>
#include <cassert>
#include <gdiplus.h>
#include <string>
#include <ctime>
#include <iostream>
#include <filesystem>

#define CString

using namespace std;



void cropImage(const wchar_t* path, int x, int y, int width, int height, const wchar_t* savePath)
{
	CImage image;
	CImage saveImg;

	image.Load(path);

	assert(x + width < image.GetWidth());
	assert(y + height < image.GetHeight());

	saveImg.Create(width, height, image.GetBPP());

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			saveImg.SetPixel(i, j, image.GetPixel(i + x, j + y));
		}
	}

	saveImg.Save(savePath, Gdiplus::ImageFormatPNG);

}

std::wstring Format(time_t time)
{
	tm dateTime;
	localtime_s(&dateTime, &time);

	return std::to_wstring(dateTime.tm_mday) + L"-"
		+ std::to_wstring(dateTime.tm_mon + 1) + L"-" + std::to_wstring(1900 + dateTime.tm_year);
}

//int main()
//{
//	wstring fileName;
//	wstring path;
//	wstring save;
//
//	cout << "Raw Data path: ";
//	getline(wcin, path);
//
//	cout << "Save Data path: ";
//	getline(wcin, save);
//
//	cout << "First file: ";
//	getline(wcin, fileName);
//
//	size_t index = fileName.find(L".bmp");
//
//	fileName.erase(index, sizeof(".bmp"));
//
//	time_t time = std::time(0);
//	wstring fo = Format(time);
//
//	while (wcscmp(fileName.c_str(), fo.c_str()) != 0)
//	{
//		time -= 24 * 60 * 60;
//		fo = Format(time);
//	}
//
//
//	int count = 1;
//	//cout << filesystem::exists(path + L"20-10-2020" + L".bmp") << endl;
//	while (filesystem::exists(path + fo + L".bmp"))
//	{
//		time -= 24 * 60 * 60;
//		cropImage((path + fo + L".bmp").c_str(), 745, 185, 1135, 823,
//			(save + Format(time) + L".png").c_str());
//
//		cout << "Current proccessing: " << count << " images ";
//
//		fo = Format(time);
//		wcout << fo << endl;
//		count++;
//	}
//
//	system("pause");
//
//	return 0;
//}