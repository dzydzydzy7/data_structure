#pragma once
#include <string>
#include <conio.h>
#include "print.h"
#include "the_graph.h"
//ǰ̨�����ӳ���������Ͷ���
using namespace std;
extern Graph g;

//��1�����ݾ������Ʋ�ѯ�����뾰��ȫ�ƣ�����˾��������Ϣ�Ľ��ܣ�
void frontFunc_1_1()
{
	frontPrint_1_1();
	g.printSites();
	cout << "������Ҫ��ѯ�ľ�����ţ�" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getvexnum()))cout << "�����������������" << endl;
	cout << "���㹦�����£�" << endl;
	cout << g[n - 1][1] << endl;
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//��2�����ݾ��㹦�ܲ�ѯ���������ѯ�Ĺ��ܣ�������о߱��˹��ܵľ������ơ�
//ѡ��1������KMP�ַ���ģʽƥ���㷨ʵ��ǰ̨����ġ����ݾ��㹦�ܲ�ѯ�����ܡ�
void frontFunc_1_2()
{
	frontPrint_1_2();
	string s;
	cin >> s;
	cout << "��" << s << "���ܵľ������£�" << endl;
	g.serchByInfo(s);
	PrintBack();
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//1. ������Ϣ��ѯ
void frontFunc_1()
{
	int c;
	frontPrint_1();
	while (cin >> c)
	{
		system("cls");
		if (c == 1) frontFunc_1_1();
		else if (c == 2) frontFunc_1_2();
		else break;
		frontPrint_1();
	}
}

//2. ��·��ѯ���������������������ƣ��������֮������·��
//ѡ��2��Ϊ���ÿ����ṩУ԰������������֮�������·����
void frontFunc_2()
{
	frontPrint_2();
	g.printSites();
	int from, to;
	cout << endl << "�����������ţ�" << endl;
	while (cin >> from && (from <= 0 || from > g.getvexnum()))cout << "�����������������" << endl;
	cout << "�������յ���ţ�" << endl;
	while (cin >> to && (to <= 0 || to > g.getvexnum()))cout << "�����������������" << endl;
	cout << endl << "���·�����£�" << endl;
	g.dijkstra(from - 1, to - 1);
	cout << endl << "����·�����£�" << endl;
	g.dfsAll(from - 1, from - 1, to - 1);
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//ѡ��3�����Ų���·����ƣ����ƻ���У԰���������ߣ��������ŵĲ���·��
void frontFunc_3()
{
	frontPrint_3();
	g.kruskal();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����
	getch();
	system("cls");
}

//ǰ̨����˵�
void frontFunc()
{
	int c;
	frontPrint();
	while (cin >> c)
	{
		system("cls");
		if (c == 1) frontFunc_1();
		else if (c == 2) frontFunc_2();
		else if (c == 3) frontFunc_3();
		else break;
		frontPrint();
	}
}