#pragma once
//�˵������������Ͷ���
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
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "----------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "������";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "----------------------" << endl;
	cout << "1.ǰ̨����" << endl;
	cout << "2.��̨����" << endl;
	cout << "0.�˳�ϵͳ" << endl;
	cout << "�밴��Ӧ���ּ�����ѡ��" << endl;
}

void frontPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "ǰ̨������ϵͳ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "1.������Ϣ��ѯ" << endl;
	cout << "2.��·��ѯ" << endl;
	cout << "3.���Ų��߲�ѯ" << endl;
	cout << "0.����������" << endl;
	cout << "�밴��Ӧ���ּ�����ѡ��" << endl;
}

void backPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "1.�޸�һ������������Ϣ" << endl;
	cout << "2.����һ�����㼫�������Ϣ" << endl;
	cout << "3.����һ���µ�·��" << endl;
	cout << "4.ɾ��һ�����㼫�������Ϣ" << endl;
	cout << "5.ɾ��һ��·��" << endl;
	cout << "0.����������" << endl;
	cout << "�밴��Ӧ���ּ�����ѡ��" << endl;
}

void frontPrint_1()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "������Ϣ��ѯ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "1.���ݾ������Ʋ�ѯ" << endl;
	cout << "2.���ݾ��㹦�ܲ�ѯ" << endl;
	cout << "0.����ǰ̨������ϵͳ" << endl;
	cout << "�밴��Ӧ���ּ�����ѡ��" << endl;
}
void frontPrint_1_1()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "-----------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "���ݾ�����Ϣ��ѯ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "-----------------" << endl;
	cout << "��ϵͳ�ṩ���¾������" << endl;
}

void frontPrint_1_2()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "-----------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "���ݾ��㹦�ܲ�ѯ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "-----------------" << endl;
	cout << "�����뾰�㹦�ܣ�" << endl;
}

void frontPrint_2()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "---------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��·��ѯ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "---------------------" << endl;
	cout << "��ϵͳ�ṩ���¾������" << endl;
}

void frontPrint_3()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "���Ų��߲�ѯ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "����Ϊ���Ų��ߣ�" << endl;
}

void PasswordPrint()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "------------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------------" << endl;
	cout << "���������룺" << endl;
}

void WorngPasswordPrint()
{
	cout << endl << "��������ѳ�������Դ����������������������" << endl;
}

void backPrint_1()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ-������Ϣ�޸�";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "------------" << endl;
	cout << "���еľ�����Ϣ��" << endl;
}

void backPrint_2()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ-��������";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
}

void backPrint_3()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ-����·��";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
}

void backPrint_4()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ-ɾ������";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
	cout << "��ɾ���ľ����У�" << endl;
}

void backPrint_5()
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "/***********�����������μ���Ϣ����ϵͳ***********/" << endl;
	cout << "--------------";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "��̨������ϵͳ-ɾ��·��";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "--------------" << endl;
	cout << "��ɾ����·���У�" << endl;
}

void PrintBack()
{
	cout << endl << "��������ص���һҳ" << endl;
}