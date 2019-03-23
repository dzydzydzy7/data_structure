#pragma once
//ͼ�㷨����
#include <iostream>
#include <fstream>
#include <string>
#include "stack_and_kmp.h"
using namespace std;
#define MAXINT 999999
#define MAXNUM 30
#define NAMESIZE 16
#define INFOSIZE 50
#define MAXEDGE 64

class Graph
{
private:
	string vexs[MAXNUM][3];	//�������Ƽ���Ϣ
	bool visited[MAXNUM];
	int matrix[MAXNUM][MAXNUM];	//�ڽӾ���
	int vexnum;	//����
	int arcnum;	//����
	int edge[MAXEDGE][3];	//��ʾ��
public:
	Graph();
	int locate(string s);
	string* operator[](int r);	//���ȷ���
	void printToFile();	//������ļ�
	void printSites();	//������е�
	void printArcs();	//������б�
	void printInfo();	//������е㼰����Ϣ
	void serchByInfo(string s);	//�����ܲ�ѯ
	void dijkstra(int from, int to);	//��from��to�����·��
	void dfsAll(int from, int now, int to);	//��from��to������·��
	void matrixToEdge();//����ת��Ϊ��
	void creatHeap();//����
	void heapAdjust(int head, int tail);//������
	void HeapSort();//������
	void kruskal();	//��С������
	void insertVex(string &name, string info);	//����һ����
	void insterArc(int i, int j, int weight);	//����һ����
	void deleteVex(int n);	//ɾ��һ����
	void deleteArc(int m);	//ɾ��һ����
	int getvexnum();
	int getarcnum();
	string standardize(string &s, int length);	//�ַ���ת������ͬ����
	void showMatrix();
	void showEdge();
};


