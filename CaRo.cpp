//ThuanPT_KayStar
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
#define MAX 500

void set_Color(int colorBackground, int colorText);
void taoBanCo(vector<vector<int>>& a);
void xuatBanCo(vector<vector<int>> a);
int danhCo(vector<vector<int>>& a, bool& flag);
int du5Nuoc(vector<vector<int>> a, int vt);


int main()
{
	vector<vector<int>> a;
	bool flag = true;
	taoBanCo(a);
	xuatBanCo(a);

	while (true)
	{
		int vt = danhCo(a, flag);
		system("cls");
		xuatBanCo(a);
		int x = du5Nuoc(a, vt);
		if (x != 1)
		{
			if (x == -1)
			{
				set_Color(0, 9);
				cout << "X chien thang!" << endl;
			}
			else
			{
				set_Color(0, 4);
				cout << "O chien thang!" << endl;
			}
			break;
		}
	}
	set_Color(0, 2);
	return 0;
}



void set_Color(int colorBackground, int colorText)
{
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, colorBackground * 16 + colorText);
}

void taoBanCo(vector<vector<int>>& a)
{
	//Kích thước bàn cờ: n * n
	int n = 20;
	a.resize(n + 1);
	int dem = 1;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < n + 1; j++)
		{
			if(i == 0 || j == 0)
				a[i].push_back(-10);	//Vị trí bìa
			else
				a[i].push_back(dem++);
		}
}

void xuatBanCo(vector<vector<int>> a)
{
	int m = a.size();
	int n = a[0].size();
	for (int i = -1; i <= m; i++)
	{
		for (int j = -1; j <= n; j++)
		{
			set_Color(0, 2);
			//Đánh STT
			if (i == -1)
			{
				if (0 < j && j < n)
					printf("%5d", j);
				else
					printf("%5c", ' ');
			}
			else if (j == -1)
			{
				if (0 < i && i < m)
					printf("%5d", i);
				else
					printf("%5c", ' ');
			}
			//4 góc
			else if (i == 0 && j == 0 || i == m && j == 0)
				printf("%5c", 3);
			else if(i == m && j == n || i == 0 && j == n)
				printf("%c%c%c%c%c", 196, 196, 196, 196, 3);
			//Các cạnh bìa
			else if (i == 0 || i == m)
				printf("%c%c%c%c%c", 196, 196, 196, 196, 196);
			else if(j == 0 || j == n)
				printf("%5c", 179);
			else
			{
				if (a[i][j] == 0)
				{
					set_Color(0, 4);
					printf("%5c", 'O');
				}
				else if (a[i][j] == -1)
				{
					set_Color(0, 9);
					printf("%5c", 'X');
				}
				else
					printf("%5d", a[i][j]);
			}
		}
		cout << endl;
	}
	set_Color(0, 2);
}

int danhCo(vector<vector<int>>& a, bool& flag)
{
	int vt;
	int n = a.size();
	cout << "Chon vi tri ban muon di: ";
	cin >> vt;
	while (vt < 1 || n * n < vt)
	{
		nhapLai:
		cout << "Vi tri ban chon khong hop le!" << endl;
		cout << "Vui long chon lai: ";
		cin >> vt;
	}
	int c = vt % (n - 1);
	int d;
	if (c == 0)
	{
		c = n - 1;
		d = vt / (n - 1);
	}
	else
		d = (vt / (n - 1)) + 1;
	if (a[d][c] == -1 || a[d][c] == 0)
		goto nhapLai;
	if (flag)
	{
		a[d][c] = -1;
		flag = false;
	}
	else
	{
		a[d][c] = 0;
		flag = true;
	}
	return vt;
}

int du5Nuoc(vector<vector<int>> a, int vt)
{
	int n = a.size();
	int c = vt % (n - 1);
	int d;
	//Lấy chỉ số
	if (c == 0)
	{
		c = n - 1;
		d = vt / (n - 1);
	}
	else
		d = (vt / (n - 1)) + 1;
	
	//Kiểm tra
	if (a[d][c] != -1 && a[d][c] != 0)
		return 1;

	int co = a[d][c];
	int dem;
	//Dọc
	dem = 0;
	for (int i = d; i < n - 1; i++)
		if (a[i][c] == co)
			dem++;
		else
			break;
	for (int i = d; i > 0; i--)
		if (a[i][c] == co)
			dem++;
		else
			break;
	if (dem - 1 >= 5)
		return co;

	//Ngang
	dem = 0;
	for (int i = c; i < n - 1; i++)
		if (a[d][i] == co)
			dem++;
		else
			break;
	for (int i = c; i > 0; i--)
		if (a[d][i] == co)
			dem++;
		else
			break;
	if (dem - 1 >= 5)
		return co;

	//Chéo 1
	dem = 0;
	for (int i = d, j = c; i < n - 1 && j < n - 1; i++, j++)
		if (a[i][j] == co)
			dem++;
		else
			break;
	for (int i = d, j = c; i > 0 && j > 0; i--, j--)
		if (a[i][j] == co)
			dem++;
		else
			break;
	if (dem - 1 >= 5)
		return co;

	//Chéo 2
	dem = 0;
	for (int i = d, j = c; i < n - 1 && j > 0; i++, j--)
		if (a[i][j] == co)
			dem++;
		else
			break;
	for (int i = d, j = c; i > 0 && j < n - 1; i--, j++)
		if (a[i][j] == co)
			dem++;
		else
			break;
	if (dem - 1 >= 5)
		return co;
	return 1;
}