#pragma once
//菜单里的输出声明和定义
#include <iostream>
#include <windows.h>
using namespace std;

BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}

void mainPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "----------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "主界面";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "----------------------" << endl;
	cout << "1.前台服务" << endl;
	cout << "2.后台管理" << endl;
	cout << "0.退出系统" << endl;
	cout << "请按相应数字键进行选择" << endl;
}

void frontPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "前台服务子系统";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "1.景点信息查询" << endl;
	cout << "2.问路查询" << endl;
	cout << "3.最优布线查询" << endl;
	cout << "0.返回主界面" << endl;
	cout << "请按相应数字键进行选择" << endl;
}

void backPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "1.修改一个景点的相关信息" << endl;
	cout << "2.增加一个景点极其相关信息" << endl;
	cout << "3.增加一条新的路径" << endl;
	cout << "4.删除一个景点极其相关信息" << endl;
	cout << "5.删除一条路径" << endl;
	cout << "0.返回主界面" << endl;
	cout << "请按相应数字键进行选择" << endl;
}

void frontPrint_1()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "景点信息查询";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "1.根据景点名称查询" << endl;
	cout << "2.根据景点功能查询" << endl;
	cout << "0.返回前台服务子系统" << endl;
	cout << "请按相应数字键进行选择" << endl;
}
void frontPrint_1_1()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "-----------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "根据景点信息查询";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "-----------------" << endl;
	cout << "本系统提供以下景点服务：" << endl;
}

void frontPrint_1_2()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "-----------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "根据景点功能查询";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "-----------------" << endl;
	cout << "请输入景点功能：" << endl;
}

void frontPrint_2()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "---------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "问路查询";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "---------------------" << endl;
	cout << "本系统提供以下景点服务：" << endl;
}

void frontPrint_3()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "最优布线查询";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "以下为最优布线：" << endl;
}

void PasswordPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "请输入密码：" << endl;
}

void WorngPasswordPrint()
{
	cout << endl << "密码错误已超过最大尝试次数，按任意键返回主界面" << endl;
}

void backPrint_1()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统-景点信息修改";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------" << endl;
	cout << "所有的景点信息：" << endl;
}

void backPrint_2()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统-新增景点";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
}

void backPrint_3()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统-新增路径";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
}

void backPrint_4()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统-删除景点";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
	cout << "可删除的景点有：" << endl;
}

void backPrint_5()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********北林自助导游及信息服务系统***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "后台管理子系统-删除路径";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
	cout << "可删除的路径有：" << endl;
}

void PrintBack()
{
	cout << endl << "按任意键回到上一页" << endl;
}