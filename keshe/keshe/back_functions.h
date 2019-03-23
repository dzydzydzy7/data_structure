#pragma once
//��̨�����ӳ���������Ͷ���
#include <string>
#include <conio.h>
#include "print.h"
#include "the_graph.h"
using namespace std;
static string PASSWORD = "1234";
extern Graph g;

//1.�޸�һ�����о���������Ϣ
void backFunc1()
{
	backPrint_1();
	g.printSites();
	cout << "������Ҫ�޸���Ϣ�ľ�����ţ�" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getvexnum()))cout << "�����������������" << endl;
	cout << "ԭ��ϢΪ��" << endl;
	cout << g[n - 1][1] << endl << endl;
	cout << "�������޸ĺ����Ϣ��" << endl;
	cout << g[n - 1][0];
	string info;
	cin >> g[n-1][1];
	cout << endl << "�޸ĺ�ľ�����ϢΪ��" << endl;
	cout << g[n - 1][1];
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	g.printToFile();
	system("cls");
}

//2.����һ���¾��㼰�������Ϣ
void backFunc2()
{
	backPrint_2();
	string name, info;
	cout << "���еĵľ������£�" << endl;
	g.printSites();
	cout << "�������¾������ƣ�" << endl;
	cin >> name;
	cout << "�������¾�����Ϣ:" << endl;
	cin >> info;
	g.insertVex(name, info);
	cout << "---------------------�޸ĳɹ�---------------------" << endl;
	cout << "�޸ĺ�ľ������£�" << endl;
	g.printSites();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//3. ����һ���µ�·��
void backFunc3()
{
	backPrint_3();
	cout << "���е�����·��Ϊ��" << endl;
	g.printArcs();
	cout << endl << "�ɹ�ѡ��ĵ���:" << endl;
	g.printSites();
	cout << endl << "�����������ߵ�������:" << endl;
	int i, j, w;
	cin >> i;
	cout << "�����������ߵ��յ����:" << endl;
	cin >> j;
	cout << "�����������յ��ľ���:" << endl;
	cin >> w;
	g.insterArc(i, j, w);
	cout << "---------------------��ӳɹ�---------------------" << endl;
	cout << "��Ӻ������·��Ϊ��" << endl;
	g.printArcs();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//4. ɾ��һ�����㼰�������Ϣ
void backFunc4()
{
	backPrint_4();
	cout << "���е����б�Ϊ��" << endl;
	g.printArcs();
	cout << endl << "���еĵ�Ϊ:" << endl;
	g.printSites();
	cout << "������Ҫɾ���ľ������:" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getvexnum()))cout << "�����������������" << endl;
	g.deleteVex(n);
	cout << "---------------------��ӳɹ�---------------------" << endl;
	cout << "ɾ��������е�Ϊ��" << endl;
	g.printSites();
	cout << endl << "ɾ�������б�Ϊ��" << endl;
	g.printArcs();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//5. ɾ��һ��·��
void backFunc5()
{
	backPrint_5();
	g.printArcs();
	cout << "������Ҫɾ���ıߵ����:" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getarcnum()))cout << "�����������������" << endl;
	g.deleteArc(n);
	cout << "---------------------ɾ���ɹ�---------------------" << endl;
	cout << "ɾ��������б�Ϊ:" << endl;
	g.printArcs();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//��̨�˵���������֤
void backFunc()
{
	string password = "";
	PasswordPrint();
	for (int i = 0; i < 4; i++)
	{
		password = "";
		if (i >= 3) {
			WorngPasswordPrint();
			char ch;
			while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
			getchar();
			system("cls");
			return;
		}
		if (i > 0)cout << endl << "�������,�����ԣ�" << endl;
		char c;
		while (c = getch())//��������
		{
			if (c == '\n' || c == '\r')break;	//�س���\r!
			if (c == '\b')	//�˸�
			{
				if (password.size() == 0)continue;
				cout << "\b \b";
				password.erase(password.end() - 1);
				continue;
			}
			password += c;
			printf("*");
		}
		cout << endl;
		if (password == PASSWORD) {
			system("cls");
			backPrint();
			break;
		}
	}
	int c;
	while (cin >> c)
	{
		if (c < 0 || c > 5)break;
		system("cls");
		switch (c)
		{
		case 1:
			backFunc1();
			backPrint();
			continue;
		case 2:
			backFunc2();
			backPrint();
			continue;
		case 3:
			backFunc3();
			backPrint();
			continue;
		case 4:
			backFunc4();
			backPrint();
			continue;
		case 5:
			backFunc5();
			backPrint();
			continue;
		}
		if (c == 0)break;
	}
}