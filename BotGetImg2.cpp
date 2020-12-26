#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <atlimage.h>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;

using Point = pair<int, int>;

#define CString

void TakeScreenShot(const std::string& path)
{
	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

	HBITMAP hBitmap = NULL;

	Sleep(100);

	OpenClipboard(NULL);
	hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
	CloseClipboard();

	std::vector<BYTE> buf;
	IStream* stream = NULL;
	HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
	CImage image;
	ULARGE_INTEGER liSize;

	image.Attach(hBitmap);
	image.Save(stream, Gdiplus::ImageFormatJPEG);
	IStream_Size(stream, &liSize);
	DWORD len = liSize.LowPart;
	IStream_Reset(stream);
	buf.resize(len);
	IStream_Read(stream, &buf[0], len);
	stream->Release();

	std::fstream f;
	f.open(path, std::fstream::binary | std::fstream::out);
	f.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(BYTE));
	f.close();
}

void SimulateMouseRightClick(int x, int y)
{
	INPUT Inputs[2] = { 0 };

	/*Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dx = x;
	Inputs[0].mi.dy = y;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;*/

	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

	Inputs[1].type = INPUT_MOUSE;
	Inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SetCursorPos(x, y);
	SendInput(2, Inputs, sizeof(INPUT));
	//SetCursorPos(x, y);
	//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void SimulateMouseLeftClick(int x, int y)
{
	INPUT Inputs[2] = { 0 };

	/*Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dx = x;
	Inputs[0].mi.dy = y;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;*/

	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	Inputs[1].type = INPUT_MOUSE;
	Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SetCursorPos(x, y);
	SendInput(2, Inputs, sizeof(INPUT));
	//SetCursorPos(x, y);
	//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void SimulateButtonPress(BYTE keyCode)
{
	keybd_event(keyCode, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(keyCode, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
LPPOINT closePos = new tagPOINT();
void GetImg(Point point)
{
	SimulateMouseRightClick(point.first, point.second);
	Sleep(200);
	SimulateButtonPress(0x53);
	Sleep(200);
	SimulateButtonPress(0x53);
	Sleep(200);
	SimulateButtonPress(0x53);
	Sleep(1000);
	SimulateButtonPress(VK_RETURN);
	Sleep(1000);
	SimulateButtonPress(VK_RETURN);
	Sleep(200);
	SimulateMouseLeftClick(closePos->x, closePos->y);
	Sleep(1000);
}

//int main()
//{
//	HWND consoleWindow = GetConsoleWindow();
//
//	std::cout << "Time for you to prepare for the process..." << std::endl;
//	system("pause");
//
//	LPPOINT curPos = new tagPOINT();
//
//	vector<LPPOINT> horiMousePos;
//	vector<LPPOINT> vertiMousePos;
//	LPPOINT changeListPos = new tagPOINT();
//	LPPOINT changeYearPos = new tagPOINT();
//
//	//std::cout << "Right click 3 times to get special Points..." << std::endl;
//	bool wait = true;
//	/*while (wait)
//	{
//		Sleep(1);
//		if (GetAsyncKeyState(VK_RBUTTON))
//		{
//			if (GetForegroundWindow() != consoleWindow)
//			{
//				GetCursorPos(changeListPos);
//				std::cout << "Cursor position: " << changeListPos->x << ", " << changeListPos->y << std::endl << std::endl;
//				wait = false;
//			}
//		}
//
//	}
//
//	while (GetAsyncKeyState(VK_RBUTTON))
//	{
//		Sleep(1);
//	}
//	wait = true;
//	while (wait)
//	{
//		Sleep(1);
//		if (GetAsyncKeyState(VK_RBUTTON))
//		{
//			if (GetForegroundWindow() != consoleWindow)
//			{
//				GetCursorPos(changeYearPos);
//				std::cout << "Cursor position: " << changeYearPos->x << ", " << changeYearPos->y << std::endl << std::endl;
//				wait = false;
//			}
//		}
//
//	}
//
//	while (GetAsyncKeyState(VK_RBUTTON))
//	{
//		Sleep(1);
//	}
//	wait = true;
//	while (wait)
//	{
//		Sleep(1);
//		if (GetAsyncKeyState(VK_RBUTTON))
//		{
//			if (GetForegroundWindow() != consoleWindow)
//			{
//				GetCursorPos(closePos);
//				std::cout << "Cursor position: " << closePos->x << ", " << closePos->y << std::endl << std::endl;
//				wait = false;
//			}
//		}
//
//	}*/
//
//	changeListPos->x = 1126;
//	changeListPos->y = 758;
//
//	changeYearPos->x = 726;
//	changeYearPos->y = 154;
//
//	closePos->x = 1521;
//	closePos->y = 798;
//
//	system("pause");
//	while (GetAsyncKeyState(VK_RETURN))
//	{
//		Sleep(1);
//	}
//
//	std::cout << "Right click mouse button to get cursor position horizontally !!!"
//		<< endl << "Press Enter to stop mouse recording..." << std::endl;
//
//	wait = true;
//	while (wait)
//	{
//		Sleep(1);
//		if (GetAsyncKeyState(VK_RBUTTON))
//		{
//			if (GetForegroundWindow() != consoleWindow)
//			{
//				GetCursorPos(curPos);
//				std::cout << "Cursor position: " << curPos->x << ", " << curPos->y << std::endl;
//				horiMousePos.push_back(new tagPOINT({ curPos->x, curPos->y }));
//			}
//			while (GetAsyncKeyState(VK_RBUTTON))
//			{
//				Sleep(1);
//			}
//		}
//
//		if (GetAsyncKeyState(VK_RETURN))
//		{
//			if (GetForegroundWindow() == consoleWindow)
//			{
//				wait = false;
//			}
//		}
//
//	}
//
//	std::cout << "Right click mouse button to get cursor position vertically !!!"
//		<< endl << "Press Enter to stop mouse recording..." << std::endl;
//
//	while (GetAsyncKeyState(VK_RETURN))
//	{
//		Sleep(1);
//	}
//
//	wait = true;
//	while (wait)
//	{
//		Sleep(1);
//		if (GetAsyncKeyState(VK_RBUTTON))
//		{
//			if (GetForegroundWindow() != consoleWindow)
//			{
//				GetCursorPos(curPos);
//				std::cout << "Cursor position: " << curPos->x << ", " << curPos->y << std::endl;
//				vertiMousePos.push_back(new tagPOINT({ curPos->x, curPos->y }));
//			}
//			while (GetAsyncKeyState(VK_RBUTTON))
//			{
//				Sleep(1);
//			}
//		}
//
//		if (GetAsyncKeyState(VK_RETURN))
//		{
//			if (GetForegroundWindow() == consoleWindow)
//			{
//				wait = false;
//			}
//		}
//	}
//
//	vector<vector<Point>> clickPoint;
//	for (int i = 0; i < vertiMousePos.size(); i++)
//	{
//		vector<Point> p;
//		for (int j = 0; j < horiMousePos.size(); j++)
//		{
//			p.push_back(pair<int, int>(horiMousePos[j]->x, vertiMousePos[i]->y));
//		}
//		clickPoint.push_back(p);
//	}
//
//	int hori = horiMousePos.size();
//	int verti = vertiMousePos.size();
//	for (int j = 0; j < horiMousePos.size(); j++)
//	{
//		delete horiMousePos[j];
//	}
//	horiMousePos.~vector();
//	for (int i = 0; i < vertiMousePos.size(); i++)
//	{
//		delete vertiMousePos[i];
//	}
//	vertiMousePos.~vector();
//
//	std::string path;
//	getline(std::cin, path);
//	getline(std::cin, path);
//
//	std::cout << "Path to save image: ";
//	std::getline(std::cin, path);
//	std::cout << "Your path: " << path << std::endl << std::endl << "Number of Image you want to take: ";
//
//	int numImg = 0;
//	//int curYear = 0;
//	cin >> numImg;
//	/*cout << "Current year: ";
//	cin >> curYear;*/
//	system("pause");
//
//	for (int i = 0; i < verti; i++)
//	{
//		for (int j = 0; j < hori; j++)
//		{
//			cout << "(" << clickPoint[i][j].first << ", " << clickPoint[i][j].second << ")" << "--";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	system("pause");
//
//	/*if (OpenClipboard(NULL))
//	{
//
//		CloseClipboard();
//	}*/
//
//	int curNum = 0;
//	while (curNum != numImg)
//	{
//		for (int k = 0; k < 4; k++)
//		{
//			for (int i = 0; i < verti; i++)
//			{
//				for (int j = 0; j < hori; j++)
//				{
//					GetImg(clickPoint[i][j]);
//					curNum++;
//				}
//			}
//			SimulateMouseLeftClick(changeListPos->x, changeListPos->y);
//			Sleep(1000);
//		}
//		//click change year pos, sleep 5s
//		SimulateMouseLeftClick(changeYearPos->x, changeYearPos->y);
//		Sleep(4000);
//	}
//
//	system("pause");
//
//	return 0;
//}