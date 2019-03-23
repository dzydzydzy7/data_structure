#pragma once
//后台服务子程序的声明和定义
#include <string>
#include <conio.h>
#include "print.h"
#include "the_graph.h"
using namespace std;
static string PASSWORD = "1234";
extern Graph g;

//1.修改一个已有景点的相关信息
void backFunc1()
{
	backPrint_1();
	g.printSites();
	cout << "请输入要修改信息的景点序号：" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getvexnum()))cout << "输入有误请出现输入" << endl;
	cout << "原信息为：" << endl;
	cout << g[n - 1][1] << endl << endl;
	cout << "请输入修改后的信息：" << endl;
	cout << g[n - 1][0];
	string info;
	cin >> g[n-1][1];
	cout << endl << "修改后的景点信息为：" << endl;
	cout << g[n - 1][1];
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	g.printToFile();
	system("cls");
}

//2.增加一个新景点及其相关信息
void backFunc2()
{
	backPrint_2();
	string name, info;
	cout << "已有的的景点如下：" << endl;
	g.printSites();
	cout << "请输入新景点名称：" << endl;
	cin >> name;
	cout << "请输入新景点信息:" << endl;
	cin >> info;
	g.insertVex(name, info);
	cout << "---------------------修改成功---------------------" << endl;
	cout << "修改后的景点如下：" << endl;
	g.printSites();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//3. 增加一条新的路径
void backFunc3()
{
	backPrint_3();
	cout << "现有的所有路径为：" << endl;
	g.printArcs();
	cout << endl << "可供选择的点有:" << endl;
	g.printSites();
	cout << endl << "请输入新增边的起点序号:" << endl;
	int i, j, w;
	cin >> i;
	cout << "请输入新增边的终点序号:" << endl;
	cin >> j;
	cout << "请输入起点和终点间的距离:" << endl;
	cin >> w;
	g.insterArc(i, j, w);
	cout << "---------------------添加成功---------------------" << endl;
	cout << "添加后的所有路径为：" << endl;
	g.printArcs();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//4. 删除一个景点及其相关信息
void backFunc4()
{
	backPrint_4();
	cout << "现有的所有边为：" << endl;
	g.printArcs();
	cout << endl << "现有的点为:" << endl;
	g.printSites();
	cout << "请输入要删除的景点序号:" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getvexnum()))cout << "输入有误请出现输入" << endl;
	g.deleteVex(n);
	cout << "---------------------添加成功---------------------" << endl;
	cout << "删除后的所有点为：" << endl;
	g.printSites();
	cout << endl << "删除后所有边为：" << endl;
	g.printArcs();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//5. 删除一条路径
void backFunc5()
{
	backPrint_5();
	g.printArcs();
	cout << "请输入要删除的边的序号:" << endl;
	int n;
	while (cin >> n && (n <= 0 || n > g.getarcnum()))cout << "输入有误请出现输入" << endl;
	g.deleteArc(n);
	cout << "---------------------删除成功---------------------" << endl;
	cout << "删除后的所有边为:" << endl;
	g.printArcs();
	char ch;
	PrintBack();
	while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
	getch();
	system("cls");
}

//后台菜单及密码验证
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
			while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区
			getchar();
			system("cls");
			return;
		}
		if (i > 0)cout << endl << "密码错误,请重试：" << endl;
		char c;
		while (c = getch())//输入密码
		{
			if (c == '\n' || c == '\r')break;	//回车是\r!
			if (c == '\b')	//退格
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