#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <atlimage.h>
#include <ctime>
#include <algorithm>
#include <sstream>

#define CString

//void TakeScreenShot(const std::string& path)
//{
//	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
//	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
//
//	HBITMAP hBitmap = NULL;
//
//	Sleep(100);
//
//	OpenClipboard(NULL);
//	hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
//	CloseClipboard();
//
//	std::vector<BYTE> buf;
//	IStream* stream = NULL;
//	HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
//	CImage image;
//	ULARGE_INTEGER liSize;
//
//	image.Attach(hBitmap);
//	image.Save(stream, Gdiplus::ImageFormatJPEG);
//	IStream_Size(stream, &liSize);
//	DWORD len = liSize.LowPart;
//	IStream_Reset(stream);
//	buf.resize(len);
//	IStream_Read(stream, &buf[0], len);
//	stream->Release();
//
//	std::fstream f;
//	f.open(path, std::fstream::binary | std::fstream::out);
//	f.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(BYTE));
//	f.close();
//}
//
//void SimulateMouseClick(int x, int y)
//{
//	INPUT Inputs[2] = { 0 };
//
//	/*Inputs[0].type = INPUT_MOUSE;
//	Inputs[0].mi.dx = x;
//	Inputs[0].mi.dy = y;
//	Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;*/
//
//	Inputs[0].type = INPUT_MOUSE;
//	Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//
//	Inputs[1].type = INPUT_MOUSE;
//	Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
//	SetCursorPos(x, y);
//	SendInput(2, Inputs, sizeof(INPUT));
//	//SetCursorPos(x, y);
//	//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
//	//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
//}
//
////day/month/year
//std::string Format(time_t time)
//{
//	tm dateTime;
//	localtime_s(&dateTime, &time);
//	std::string result = "";
//	result = std::to_string(dateTime.tm_mday) + "-"
//		+ std::to_string(dateTime.tm_mon + 1) + "-" + std::to_string(1900 + dateTime.tm_year);
//	return result;
//}

//int main()
//{
	//HWND consoleWindow = GetConsoleWindow();

	//std::cout << "Time for you to prepare for the process..." << std::endl;
	//system("pause");

	//LPPOINT curPos = new tagPOINT();
	//std::cout << "Click mouse button to get cursor position... " << std::endl;

	//bool wait = true;
	//while (wait)
	//{
	//	Sleep(1);
	//	if (GetAsyncKeyState(VK_LBUTTON))
	//	{
	//		if (GetForegroundWindow() != consoleWindow)
	//		{
	//			GetCursorPos(curPos);
	//			wait = false;
	//		}
	//	}
	//}

	//std::cout << "Cursor position: " << curPos->x << ", " << curPos->y << std::endl << std::endl;

	//std::cout << "Path to save image: ";
	//std::string path;
	//std::getline(std::cin, path);
	//std::cout << "Your path: " << path << std::endl << std::endl << "Number of Image you want to take: ";

	//int numImg = 0;
	//std::cin >> numImg;

	//std::string temp;
	//std::cout << "Enter start date time (day/month/year) : ";
	//std::getline(std::cin, temp);

	//std::replace(temp.begin(), temp.end(), '/', '-');

	//time_t time = std::time(0);
	//std::string fo = Format(time);

	//while (strcmp(temp.c_str(), fo.c_str()) != 0)
	//{
	//	time -= 24 * 60 * 60;
	//	fo = Format(time);
	//}

	//system("pause");
	////time_t time = std::time(0);
	//time -= 24 * 60 * 60;

	//for (int i = 0; i < numImg; i++)
	//{
	//	SimulateMouseClick(curPos->x, curPos->y);
	//	Sleep(5000);
	//	TakeScreenShot(path + Format(time) + ".bmp");
	//	time -= 24 * 60 * 60;
	//}

	//return 0;
//}