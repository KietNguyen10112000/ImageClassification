#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern class MonHoc;

class SinhVien
{
public:
	vector<MonHoc> monHoc;
	string hoTen;
	string gioiTinh;
	int soMonHoc;
	double CPA;
	string xepLoai;
public:
	SinhVien();
	~SinhVien();

public:
	void calCPA();
	void printInf();
	void input();

};

class MonHoc
{
public:
	string maMonHoc;
	int soTinChi;
	float diemQT, diemCK;
	float trongSoCK;
	float diemMH;
	string ketQuaMH;
public:
	MonHoc();
	~MonHoc();

public:
	void danhGia();
	void print();
	void input();
};

MonHoc::MonHoc()
{
}

MonHoc::~MonHoc()
{
}

void MonHoc::danhGia()
{
	diemMH = diemCK * trongSoCK + diemQT * (1 - trongSoCK);
	if (diemMH > 5)
	{
		ketQuaMH = "qua mon";
	}
	else
	{
		ketQuaMH = "hoc lai";
	}
}

void MonHoc::print()
{
	cout << maMonHoc << "\t\t"
		<< soTinChi << "\t\t"
		<< trongSoCK << "\t\t"
		<< diemQT << "\t\t"
		<< diemCK << "\t\t"
		<< diemMH << "\t\t"
		<< ketQuaMH << endl;
}

void MonHoc::input()
{
	cout << "Ma MH: ";
	cin >> maMonHoc;
	cout << "So tin chi: ";
	cin >> soTinChi;
	cout << "Trong so CK (> 0, < 1): ";
	cin >> trongSoCK;
	while (!(trongSoCK > 0 && trongSoCK < 1))
	{
		cout << "Trong so CK sai !!!";
		cin >> trongSoCK;
	}
	cout << "Diem QT: ";
	cin >> diemQT;
	cout << "Diem CK: ";
	cin >> diemCK;
}


SinhVien::SinhVien()
{
}

SinhVien::~SinhVien()
{
}

void SinhVien::calCPA()
{
	double sum = 0;
	int sumTinChi = 0;
	for (int i = 0; i < monHoc.size(); i++)
	{
		monHoc[i].danhGia();
		sum += monHoc[i].diemMH * monHoc[i].soTinChi;
		sumTinChi += monHoc[i].soTinChi;
	}
	CPA = sum / (double)sumTinChi;
	if (CPA >= 9) xepLoai = "A+";
	else if (CPA >= 8.5) xepLoai = "A";
	else if (CPA >= 7.5) xepLoai = "B+";
	else if (CPA >= 6.5) xepLoai = "C";
	else if (CPA >= 4) xepLoai = "D";
	else xepLoai = "F";

}

void SinhVien::printInf()
{
	cout << endl << "Ten sinh vien: " << hoTen << endl;
	cout << "Gioi tinh: " << gioiTinh << endl;
	cout << "So mon hoc: " << soMonHoc << endl;
	cout << "Ket qua hoc tap: " << endl;
	cout << "Ma mon hoc\tSo tin chi\tTrong so\tDiemQT\t\tDiemCK\t\tDiemMH\t\tKetQuaMH" << endl;
	for (size_t i = 0; i < monHoc.size(); i++)
	{
		monHoc[i].print();
	}
	cout << "Diem CPA: " << CPA << endl;
	cout << "Xep loai: " << xepLoai << endl;
}

void SinhVien::input()
{
	getline(cin, hoTen);
	cout << endl << "Ho ten SV: ";
	getline(cin, hoTen);
	cout << "Gioi tinh: ";
	getline(cin, gioiTinh);
	cout << "So mon hoc: ";
	cin >> soMonHoc;
	monHoc = vector<MonHoc>(soMonHoc);
	for (size_t i = 0; i < monHoc.size(); i++)
	{
		cout << endl << "Nhap mon hoc thu " << (i + 1) << ":" << endl;
		monHoc[i].input();
	}
}


int main() 
{
	cout << "Ho ten: Nguyen Huu Kiet" << endl << "MSSV: 20183571" << endl;
	cout << "\tCHUONG TRINH QUAN LY SINH VIEN" << endl;
	cout << "\t1. Nhap thong tin sinh vien." << endl;
	cout << "\t2. In thong tin sinh vien." << endl;
	cout << "\t0. Thoat !!!." << endl;

	int choose = -1;
	vector<SinhVien> sinhVien;
	int soSinhVien;
	while (true)
	{
		cout << endl << "Chon lua chon: ";
		cin >> choose;
		if (choose == 0) break;
		else if (choose == 1)
		{
			cout << endl << "NHAP THONG TIN SINH VIEN: " << endl;
			cout << "Nhap so luong sinh vien: ";
			cin >> soSinhVien;
			sinhVien = vector<SinhVien>(soSinhVien);
			for (size_t i = 0; i < soSinhVien; i++)
			{
				sinhVien[i].input();
			}
			/*string temp = "+";
			getline(cin, temp);
			while (true)
			{
				SinhVien sv;
				sv.input();
				sinhVien.push_back(sv);
				cout << "Enter to cont"
				getline(cin, temp);
				getline(cin, temp);
				if (temp == "") break;
			}
			soSinhVien = sinhVien.size();*/
		}
		else if (choose == 2)
		{
			cout << endl << "THONG TIN SINH VIEN: " << endl;
			for (size_t i = 0; i < soSinhVien; i++)
			{
				sinhVien[i].calCPA();
				sinhVien[i].printInf();
			}
		}
	}

    return 0;
}