#pragma once
//图算法声明
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
	string vexs[MAXNUM][3];	//景点名称及信息
	bool visited[MAXNUM];
	int matrix[MAXNUM][MAXNUM];	//邻接矩阵
	int vexnum;	//点数
	int arcnum;	//边数
	int edge[MAXEDGE][3];	//表示边
public:
	Graph();
	int locate(string s);
	string* operator[](int r);	//徇秩访问
	void printToFile();	//输出到文件
	void printSites();	//输出所有点
	void printArcs();	//输出所有边
	void printInfo();	//输出所有点及其信息
	void serchByInfo(string s);	//按功能查询
	void dijkstra(int from, int to);	//从from到to的最短路径
	void dfsAll(int from, int now, int to);	//从from到to的所有路径
	void matrixToEdge();//矩阵转换为边
	void creatHeap();//建堆
	void heapAdjust(int head, int tail);//调整堆
	void HeapSort();//堆排序
	void kruskal();	//最小生成树
	void insertVex(string &name, string info);	//增加一个点
	void insterArc(int i, int j, int weight);	//增加一个边
	void deleteVex(int n);	//删除一个点
	void deleteArc(int m);	//删除一个边
	int getvexnum();
	int getarcnum();
	string standardize(string &s, int length);	//字符串转换成相同长度
	void showMatrix();
	void showEdge();
};


