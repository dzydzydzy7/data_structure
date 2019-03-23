#pragma once
#include <string>
#include <conio.h>
#include "print.h"
#include "the_graph.h"
//前台服务子程序的声明和定义
using namespace std;
extern Graph g;

//（1）根据景点名称查询：输入景点全称，输出此景点相关信息的介绍；
void frontFunc_1_1()
{
	frontPrint_1_1();
	g.printSites();
	cout << "请输入要查询的景点序号：" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getvexnum()))cout << "输入有误请出现输入" << endl;
	cout << "景点功能如下：" << endl;
	cout << g[n - 1][1] << endl;
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//（2）根据景点功能查询：输入待查询的功能，输出所有具备此功能的景点名称。
//选做1：利用KMP字符串模式匹配算法实现前台服务的“根据景点功能查询”功能。
void frontFunc_1_2()
{
	frontPrint_1_2();
	string s;
	cin >> s;
	cout << "有" << s << "功能的景点如下：" << endl;
	g.serchByInfo(s);
	PrintBack();
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//1. 景点信息查询
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

//2. 问路查询：输入任意两个景点名称，输出两点之间的最短路径
//选做2：为来访客人提供校园任意两个景点之间的所有路径。
void frontFunc_2()
{
	frontPrint_2();
	g.printSites();
	int from, to;
	cout << endl << "请输入起点序号：" << endl;
	while (cin >> from && (from <= 0 || from > g.getvexnum()))cout << "输入有误请出现输入" << endl;
	cout << "请输入终点序号：" << endl;
	while (cin >> to && (to <= 0 || to > g.getvexnum()))cout << "输入有误请出现输入" << endl;
	cout << endl << "最短路径如下：" << endl;
	g.dijkstra(from - 1, to - 1);
	cout << endl << "所有路径如下：" << endl;
	g.dfsAll(from - 1, from - 1, to - 1);
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//选做3：最优布线路径设计，即计划在校园里铺设网线，给出最优的布线路径
void frontFunc_3()
{
	frontPrint_3();
	g.kruskal();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//前台服务菜单
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