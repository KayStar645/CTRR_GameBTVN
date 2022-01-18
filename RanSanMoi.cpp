//ThuanPT-KayStar
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <Windows.h>
using namespace std;
#define	MAX 110
#define VC 32767


struct Graph
{
	int n, m[MAX][MAX];
};

void set_Color(int colorBackground, int colorText);
void khoiTao(Graph& g);
void inputStart(Graph g, int& start);
void inputEnd(Graph g, int& end, int start);
int timDuongDiNganNhat_Floyd(Graph g, int P[][MAX], int start, int end);
void xuatBanCo(Graph g, list<int> l);
bool kiemTraDinhCoLap(Graph g, int dinh);

int main()
{
	set_Color(0, 3);
	Graph g;
	list<int> l;
	string fileName = "Bai6.txt";
	khoiTao(g);
	xuatBanCo(g, l);
	int start, end;
	inputStart(g, start);
	do
	{
		cout << "Luu y: Ran khong the di xuyen tuong xung quanh!" << endl;
		
		cout << "Ran dang o vi tri thu: " << start << endl;
		inputEnd(g, end, start);
		system("cls");
		int P[MAX][MAX];
		int len = timDuongDiNganNhat_Floyd(g, P, start, end);

		if (len == VC)
		{
			cout << "Khong co duong di!" << endl;
			return 0;
		}
		cout << "Do dai ran phai di tu " << start << " toi vi tri cua con moi " << end << " la: " << len << endl;
		cout << "Qua trinh di cua ran: ";

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
		l.push_back(S2.top());
		cout << S2.top();
		S2.pop();

		while (!S2.empty())
		{
			l.push_back(S2.top());
			cout << " ==> " << S2.top();
			S2.pop();
		}
		cout << endl;
		xuatBanCo(g, l);
		l.clear();
		cout << endl;
		start = end;
		cout << "Nhap 1 phim bat ki de tiep tuc" << endl;
		system("pause");
		
	} while (true);
	
	return 0;
}

void set_Color(int colorBackground, int colorText)
{
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, colorBackground * 16 + colorText);
}

bool kiemTraXungQuanh(int x1, int y1, int x2, int y2);

void khoiTao(Graph& g)
{
	g.n = 100;
	for (int i = 1; i <= g.n; i++)
		for (int j = 1; j <= g.n; j++)
			g.m[i][j] = 0;
	for (int i = 1; i <= g.n; i++)
		for (int j = 1; j <= g.n; j++)
		{
			if (j - i == 1 && i % 10 != 0)
			{
				g.m[i][j] = 1;
				g.m[j][i] = 1;
			}
			else if (j - i == 10)
			{
				g.m[i][j] = 1;
				g.m[j][i] = 1;
			}
		}
}

void xuatBanCo(Graph g, list<int> l)
{
	int dem = 1;
	for (int i = -1; i <= sqrt(g.n); i++)
	{
		for (int j = -1; j <= sqrt(g.n); j++)
		{
			set_Color(0, 2);
			//4 góc
			if (i == -1 && j == -1)
				printf("%5c", 3);
			else if (i == -1 && j == sqrt(g.n))
				printf("%c%c%c%c%c", 196, 196, 196, 196, 3);
			else if (i == sqrt(g.n) && j == sqrt(g.n))
				printf("%c%c%c%c%c", 196, 196, 196, 196, 3);
			else if (i == sqrt(g.n) && j == -1)
				printf("%5c", 3);
			//Các cạnh bìa
			else if (i == -1 || i == sqrt(g.n))
				printf("%c%c%c%c%c", 196, 196, 196, 196, 196);
			else if (j == -1 || j == sqrt(g.n))
				printf("%5c", 179);
			else
			{
				bool flag = false;
				for (list<int>::iterator i = l.begin(); i != l.end(); i++)
					if (i.operator*() == dem)
					{
						flag = true; 
						break;
					}
				if(flag)
					set_Color(0, 4);
				else
					set_Color(0, 9);
				
				printf("%5d", dem++);
			}
		}
		cout << endl;
	}
	set_Color(0, 3);
}

void inputStart(Graph g, int& start)
{
	cout << "Cac dinh duoc danh so tu 1 toi " << g.n << endl;
	cout << "Nhap vao vi tri cua ran: ";
	cin >> start;
	while (start < 1 || start > g.n)
	{
		cout << "Vi tri khong hop le!" << endl;
		cout << "Vui long nhap lai: ";
		cin >> start;
	}
}

void inputEnd(Graph g, int& end, int start)
{
	cout << "Cac dinh duoc danh so tu 1 toi " << g.n << endl;
	cout << "Nhap vao vi tri cua con moi: ";
	cin >> end;
	while (end < 1 || end > g.n || end == start)
	{
		cout << "Vi tri khong hop le!" << endl;
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
