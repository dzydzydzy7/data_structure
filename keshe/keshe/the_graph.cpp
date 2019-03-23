#include "the_graph.h"
//ͼ�㷨����
using namespace std;

Graph::Graph() {
	for(auto &i : matrix)
		for (auto &j : i)j = MAXINT;
	for (int i = 0; i < MAXNUM; i++)matrix[i][i] = 0;
	ifstream fin("map.txt");
	fin >> vexnum >> arcnum;
	for (int i = 0; i < vexnum; i++)
		fin >> vexs[i][0] >> vexs[i][1];
	string s1, s2;
	int length;
	for (int i = 0; i < arcnum; i++)
	{
		fin >> s1 >> s2 >> length;
		matrix[locate(s1)][locate(s2)] = length;
		matrix[locate(s2)][locate(s1)] = length;
	}
	fin.close();
	for (auto &i : vexs)
	{
		i[2] = i[0];
		standardize(i[0], NAMESIZE);
		standardize(i[1], INFOSIZE);
	}
}

int Graph::locate(string s)
{
	for (int i = 0; i < vexnum; i++)
		if (s == vexs[i][0])return i;
}

string * Graph::operator[](int r)
{
	return vexs[r];
}

void Graph::printToFile()
{
	ofstream fout("map.txt");
	fout << vexnum << "\t" << arcnum << endl;
	for (int i = 0; i < vexnum; i++)
		fout << vexs[i][0] <<" "<< vexs[i][1] << endl;
	for (int i = 0; i < vexnum; i++)
		for (int j = i; j < vexnum; j++)
		{
			if (matrix[i][j] && matrix[i][j] < MAXINT)
				fout << vexs[i][0] << "\t" << vexs[j][0] << "\t" << matrix[i][j] << endl;
		}
	fout.close();
}

void Graph::printSites()
{
	for (int i = 0; i < vexnum; i++)
	{
		cout<<i+1<<"."<<vexs[i][0]<<"\t";
		if (0 == (i+1) % 3)cout << endl;
	}
	cout << endl;
}

void Graph::printArcs()
{
	int k = 1;
	for(int i = 0; i < vexnum;i++)
		for (int j = i; j < vexnum; j++)
		{
			if (matrix[i][j] && matrix[i][j] < MAXINT)
				cout << k++ << ". " << vexs[i][0] << "\t" << vexs[j][0] << "\t" << matrix[i][j] << endl;
		}
}

void Graph::printInfo()
{
	for (int i = 0; i < vexnum; i++)
		cout << i + 1 << ". " <<vexs[i][0] << vexs[i][1] << endl;
}

void Graph::serchByInfo(string s)
{
	bool isfind = false;
	for (int i = 0; i < vexnum; i++)
		if (kmp(s, vexs[i][1]) < INFOSIZE)
		{
			isfind = true;
			cout << vexs[i][0];
		}
	if (!isfind)cout << "δ�ҵ��ù���";
	cout << endl;
}

void Graph::dijkstra(int from, int to)//n�����, ���յ�
{
	bool s[MAXNUM];	//�Ƿ��ѱ�ȷ�����·��
	int dim[MAXNUM];//��ǰ���·������
	int path[MAXNUM];//·��
	for (int i = 0; i < vexnum; i++)//��ʼ��
	{
		s[i] = false;
		dim[i] = matrix[from][i];
		if (dim[i] < MAXINT)path[i] = from;
		else path[i] = -1;
	}
	s[from] = true;	//��������·����ȷ��
	dim[from] = 0;		//�����·������Ϊ0
	for (int i = 0; i < vexnum; i++)
	{
		if (i == from)continue;
		int min = MAXINT;
		int v = 0;
		for (int j = 0; j < vexnum; j++)
			if (!s[j] && dim[j] < min)//ѡ�����·��
			{
				min = dim[j];
				v = j;
			}
		s[v] = true;	//��ȷ��n��j�����·��
		for (int k = 0; k < vexnum; k++)
			if (!s[k] && dim[v] + matrix[v][k] < dim[k])//�����k��·����������
			{
				dim[k] = dim[v] + matrix[v][k];	//�޸�k��·����
				path[k] = v;	//�ӵ�v����k
			}
	}
	Stack ss;
	int distance = 0;
	int p = to;
	ss.push(p);
	while (p != from)
	{
		distance += matrix[p][path[p]];
		ss.push(p = path[p]);
	}
	cout << vexs[ss.pop()][2];
	while (ss.notEmpty())cout << "-->" << vexs[ss.pop()][2];
	cout << "\t" << distance << endl;
}

Stack S;

void Graph::dfsAll(int from, int now, int to)
{
	S.push(now);
	if (now == to)
	{
		int distance = 0;
		cout << vexs[S.elem[0]][2];
		for (int i = 1; i < S.top; i++)
		{
			cout << "-->" << vexs[S.elem[i]][2]; 
			distance += matrix[S.elem[i]][S.elem[i - 1]];
		}
		cout << "\t" << distance << endl << endl;
		S.pop();
	}
	else {
		bool nNotInPath = true;
		int n;
		for (int i = 0; i < vexnum; i++)
		{
			nNotInPath = true;
			if (matrix[now][i] > 0 && matrix[now][i] < MAXINT) {
				for (int j = 0; j < S.top; j++)
					if (S.elem[j] == i)nNotInPath = false;//����γ��˻�·(��һ������·����)
				if (nNotInPath)dfsAll(from, i, to);
			}
		}
		S.pop();	
	}
}

void Graph::matrixToEdge()
{
	int k = 0;
	for (int i = 0; i < vexnum; i++)
		for (int j = i; j < vexnum; j++)
			if (matrix[i][j] && matrix[i][j] < MAXINT)
			{
				edge[k][0] = i;
				edge[k][1] = j;
				edge[k][2] = matrix[i][j];
				k++;
			}
}

void Graph::creatHeap()
{
	for (int i = arcnum / 2 - 1; i >= 0; i--)
		heapAdjust(i, arcnum);
}

void Graph::heapAdjust(int head, int tail)
{
	if (head == tail)return;
	int root[3];	
	for (int i = 0; i < 3; i++)root[i] = edge[head][i];
	for (int i = 2 * head; i <= tail; i *= 2)
	{
		if (edge[i][2] < edge[i + 1][2] && i < tail)++i;	//�ҳ������ӽڵ�
		if (root[2] >= edge[i][2])break;	//������������������
		for (int j = 0; j < 3; j++)edge[head][j] = edge[i][j];	//���򽻻�
		head = i;	//�����µ���
	}
	for (int i = 0; i < 3; i++) edge[head][i]= root[i];	//��ɽ���
}

void Graph::HeapSort()
{
	creatHeap();
	for (int i = arcnum - 1; i > 0; i--)
	{
		int top[3];
		for (int j = 0; j < 3; j++) top[j] = edge[0][j];
		for (int j = 0; j < 3; j++) edge[0][j] = edge[i][j];
		for (int j = 0; j < 3; j++) edge[i][j] = top[j];	//�����Ѷ��Ͷ�δ���򲿷ֵĵ�
		heapAdjust(0, i - 1);//����δ����Ķ�
	}
}

void Graph::kruskal()
{
	matrixToEdge();
	HeapSort();
	int vexSet[MAXNUM];	//����������ͨ����
	int comp1;	//�����������ͨ����
	int comp2;	//����������ͨ����
	for (int i = 0; i < vexnum; i++) vexSet[i] = i;
	for (int i = 0; i < arcnum; i++)
	{
		comp1 = vexSet[edge[i][0]];
		comp2 = vexSet[edge[i][1]];
	
		if (comp1 != comp2)
		{
			cout << vexs[edge[i][0]][0] << "-->" << vexs[edge[i][1]][0] << endl;
			for (int j = 0; j < vexnum; j++)
				if (vexSet[j] == comp2) vexSet[j] = comp1;
		}
	}
}

void Graph::insertVex(string &name, string info)
{
	if (vexnum + 1 > MAXNUM)
	{
		cout << "error" << endl;
		return;
	}
	standardize(name, NAMESIZE);
	vexs[vexnum][0] = name;
	vexs[vexnum][1] = info;
	vexnum++;
	printToFile();
}

void Graph::insterArc(int i, int j, int weight)
{
	matrix[i - 1][j - 1] = weight;
	matrix[j - 1][i - 1] = weight;
	arcnum++;
	printToFile();
}

void Graph::deleteVex(int n)
{
	int m = n - 1;
	int arcToDelete = 0;
	for (int i = 0; i < vexnum; i++)
		if (matrix[m][i] && matrix[m][i] < MAXINT) arcToDelete++;
	for (int i = n; i < vexnum; i++)
	{
		vexs[i - 1][0] = vexs[i][0];
		vexs[i - 1][1] = vexs[i][1];
	}
	for (int i = n; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			matrix[i - 1][j] = matrix[i][j];
	for (int j = n; j < vexnum; j++)
		for (int i = 0; i < vexnum - 1; i++)
			matrix[i][j - 1] = matrix[i][j];
	vexnum--;
	arcnum -= arcToDelete;
	printToFile();
}

void Graph::deleteArc(int m)
{
	int k = 0;
	for (int i = 0; i < vexnum; i++)
		for (int j = i; j < vexnum; j++)
		{
			if (matrix[i][j] && matrix[i][j] < MAXINT)k++;
			if (k == m) {
				matrix[i][j] = 0;
				matrix[j][i] = 0;
			}
		}
	arcnum--;
	printToFile();
}

int Graph::getvexnum()
{
	return vexnum;
}

int Graph::getarcnum()
{
	return arcnum;
}

string Graph::standardize(string &s, int len)
{
	int ss = s.size();
	int c = len-ss;
	while (c--)
		s += " ";
	return s;
}

void Graph::showMatrix()
{
	for (int i = 0; i < vexnum; i++)//��ʱ�ٸĳ��ļ���ĸ�ʽ
	{
		for (int j = 0; j < vexnum; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void Graph::showEdge()
{
	for (int i = 0; i < arcnum; i++)
		cout << edge[i][0] << "\t" << edge[i][1] << "\t" << edge[i][2] << "\n";
}