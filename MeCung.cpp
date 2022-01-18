//ThuanPT-KayStar
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <Windows.h>
using namespace std;
#define	MAX 125
#define VC 32767

struct Graph
{
	int n, m[MAX][MAX];
};

void set_Color(int colorBackground, int colorText);
void docFile(string fileName, Graph& g);
void inputStartEnd(Graph g, int& start, int& end);
int timDuongDiNganNhat_Floyd(Graph g, int P[][MAX], int start, int end);
void xuatBanCo(Graph g);
bool kiemTraDinhCoLap(Graph g, int dinh);


//Hình ảnh minh họa mê cung được đính kèm theo File này
int main()
{
	set_Color(0, 3);
	Graph g;
	string fileName = "Bai5.txt";
	docFile(fileName, g);

	xuatBanCo(g);

	int start = 2, end = 100;
	//inputStartEnd(g, start, end);//có thể nhập đỉnh bắt đầu và kết thúc trong đoạn [1, 110]

	int P[MAX][MAX];
	int len = timDuongDiNganNhat_Floyd(g, P, start, end);

	if (len == VC)
	{
		cout << "Khong co duong di!" << endl;
		return 0;
	}
	cout << "Do dai duong di tu dinh " << start << " toi dinh " << end << " la: " << len << endl;
	cout << "Qua trinh di: " << endl;

	set_Color(0, 4);
	//truy vet
	stack <int> S1;
	stack <int> S2;

	S1.push(start);
	S1.push(end);
	int dich, tg;
	while (!S1.empty())
	{
		dich = S1.top();
		S1.pop();
		S2.push(dich);
		if (!S1.empty())
		{
			tg = S1.top();
			while (P[tg][dich] != -1)
			{
				S1.push(P[tg][dich]);
				tg = S1.top();
			}
		}
	}
	cout << S2.top();
	S2.pop();

	while (!S2.empty())
	{
		cout << " ==> " << S2.top();
		S2.pop();
	}
	cout << endl;
	set_Color(0, 3);
	system("pause");
	return 0;
}

void set_Color(int colorBackground, int colorText)
{
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, colorBackground * 16 + colorText);
}

void docFile(string fileName, Graph& g)
{
	fstream f(fileName);
	if (f.fail())
	{
		cout << "File khong ton tai!" << endl;
		return;
	}
	f >> g.n;
	for (int i = 1; i <= g.n; i++)
		for (int j = 1; j <= g.n; j++)
			g.m[i][j] = 0;
	while (!f.eof())
	{
		int a, b;
		f >> a;
		f >> b;
		f >> g.m[a][b];
		g.m[b][a] = g.m[a][b];
	}
	cout << "Doc File thanh cong!" << endl;
}

void xuatBanCo(Graph g)
{
	int dem = 1;
	for (int i = -1; i <= 11; i++)
	{
		for (int j = -1; j <= 10; j++)
		{
			set_Color(0, 2);
			//4 góc
			if (i == -1 && j == -1)
				printf("%5c", 3);
			else if (i == -1 && j == 10)
				printf("%c%c%c%c%c", 196, 196, 196, 196, 3);
			else if (i == 11 && j == 10)
				printf("%c%c%c%c%c", 196, 196, 196, 196, 3);
			else if (i == 11 && j == -1)
				printf("%5c", 3);
			//Các cạnh bìa
			else if (i == -1 || i == 11)
				printf("%c%c%c%c%c", 196, 196, 196, 196, 196);
			else if (j == -1 || j == 10)
				printf("%5c", 179);
			else
			{
				if(kiemTraDinhCoLap(g, dem))
					set_Color(0, 9);
				else
					set_Color(0, 4);
				printf("%5d", dem++);
			}
		}
		cout << endl;
	}
	set_Color(0, 3);
}

void inputStartEnd(Graph g, int& start, int& end)
{
	cout << "Cac dinh duoc danh so tu 1 toi " << g.n << endl;
	cout << "Nhap vao dinh bat dau: ";
	cin >> start;
	while (start < 1 || start > g.n)
	{
		cout << "Dinh ban nhap khong hop le!" << endl;
		cout << "Vui long nhap lai: ";
		cin >> start;
	}
	cout << "Nhap vao dinh ket thuc: ";
	cin >> end;
	while (end < 1 || end > g.n)
	{
		cout << "Dinh ban nhap khong hop le!" << endl;
		cout << "Vui long nhap lai: ";
		cin >> end;
	}
}

int timDuongDiNganNhat_Floyd(Graph g, int P[][MAX], int start, int end)
{
	int A[MAX][MAX];

	for (int i = 1; i <= g.n; i++)
	{
		for (int j = 1; j <= g.n; j++)
		{
			if (g.m[i][j] != 0)
				A[i][j] = g.m[i][j];
			else
				A[i][j] = VC;
			P[i][j] = -1;
		}
	}

	for (int k = 1; k <= g.n; k++)
		for (int i = 1; i <= g.n; i++)
			for (int j = 1; j <= g.n; j++)
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					P[i][j] = k;
				}
	return A[start][end];
}

bool kiemTraDinhCoLap(Graph g, int dinh)
{
	for (int i = 1; i <= g.n; i++)
	{
		if (g.m[i][dinh] != 0 || g.m[dinh][i] != 0)
			return false;
	}
	return true;
}
