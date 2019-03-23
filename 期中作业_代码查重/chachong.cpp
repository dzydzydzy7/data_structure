//614 董泽宇
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

//相似度最大为1，最小为0
//通过比较语句中的操作(赋值 加减 -> ()等查重)
//无关语句的顺序和变量的名称
//此程序在MSCV(vs2017)和g++6.3(MinGW)下可运行
//函数的顺序大致为运行顺序

struct brackte	//大括号结构体，用于判断函数
{
	int rank;//第几层(从外向里比如函数的大括号秩为0，再往里一层为1，再往里为2)
	int posi;//大括号在代码中的位置
};

string readCode(string code)//读入(只能处理ANSI编码)
{
	ifstream inFileA;
	inFileA.open(code);
	string fileA;
	while (!inFileA.eof())
	{
		char getA;
		getA = inFileA.get();
		fileA += getA;
	}
	return fileA;
}

void remove(string &s, int a, int b)//被removeNotes调用
{
	for (int i = b, j = a; i < s.size(); i++, j++)
		s[j] = s[i];
	for (int i = 0; i < b - a; i++)
		s.pop_back();
}

string removeNotes(string code)//去掉注释和输出
{
	int startPosi, endPosi;
	for (int i = 1; i < code.size(); i++)
	{
		if (code[i] == '/' && code[i - 1] == '/') {//单行注释
			startPosi = i - 1;
			for (int j = startPosi; j < code.size(); j++) {
				if (code[j] == '\n') {
					endPosi = j;
					remove(code, startPosi, endPosi);
					break;
				}
			}
		}
		if (code[i] == '"') {//字符串
			startPosi = i;
			for (int j = startPosi + 1; j < code.size(); j++) {
				if (code[j] == '"') {
					endPosi = j;
					remove(code, startPosi, endPosi + 1);
					break;
				}
			}
		}
		if (code[i] == '*' && code[i - 1] == '/') {//多行注释
			startPosi = i - 1;
			for (int j = startPosi; j < code.size(); j++) {
				if (code[j - 1] == '*' && code[j] == '/') {
					endPosi = j;
					remove(code, startPosi, endPosi + 1);
					break;
				}
			}
		}
	}
	return code;
}

vector<brackte> allBracktePosi(string code)//所有括号位置
{
	vector<brackte> brac;
	brackte _now;
	bool _switch = true;
	for (int i = 0, j = 0; i < code.size(); i++)
	{
		if (code[i] == '{') {
			_now.posi = i;
			_now.rank = j++;
			brac.push_back(_now);
		}
		if (code[i] == '}') {
			_now.posi = i;
			_now.rank = --j;
			brac.push_back(_now);
		}
	}
	return brac;
}

int *buildNext(string P)  //构造next数组，被kmp调用
{
	int m = P.size(), j = 0;
    int *N = new int[m];
    int t = N[0] = -1;
    while (j < m - 1)
       if (0 > t || P[j] == P[t]) {
			j++; t++;
			if (P[j] == P[t])N[j] = N[t];
			else N[j] = t;
			//下面这句在MSVC14.15上可以运行，在g++6.3上N[0]和t都变成0导致死循环
			//N[j] = (P[++j] != P[++t] ? t : N[t]);
	}
		else t = N[t];
	return N;
}

int kmp(string P, string T)  //找字符串在代码中的位置，调用在markMain
 {
	int *next = buildNext(P);
    int n = T.size(), i = 0;
    int m = P.size(), j = 0;
    while (j < m  && i < n)
       if (0 > j || T[i] == P[j])
          { i++;  j++; }
       else
          j = next[j];
    delete[] next;
    return i;
}

vector<brackte> markMain(string code)//找出main函数的位置
{
	vector<brackte> brac = allBracktePosi(code);
	int posi = kmp(" main(", code);
	for (int i = 0, j = 0; i < brac.size(); i++)
	{
		if (brac[i].posi > posi && brac[i].rank == 0)
		{
			brac[i].rank = -1;//将main函数最外层的花括号的秩改为-1
			j++;
		}
		if (j > 1) break;
	}
	return brac;
}

string getMain(string code)//main函数提取为字符串
{
	vector<brackte> brac = markMain(code);
	string _main;
	int a[2];
	for (int i = 0, j = 0; i < brac.size(); i++)
		if (brac[i].rank == -1)a[j++] = brac[i].posi;//通过-1标记找到main的始末位置
	for (int i = a[0] + 1; i <= a[1] - 1; i++)
		_main += code[i];
	return _main;
}

string getFunc(string code)//其他函数提取为字符串
{
	vector<brackte> brac = markMain(code);
	string func;
	vector<int> a;
	for (int i = 0, j = 0; i < brac.size(); i++)
		if (brac[i].rank == 0)a.push_back(brac[i].posi);
	for (int i = 0; i < a.size(); i += 2)
	{
		for (int j = a[i] + 1; j < a[i + 1]; j++)
			func += code[j];		
	}
	return func;
}

string getAll(string code)//所有函数提取为字符串
{
	vector<brackte> brac = markMain(code);
	string func;
	vector<int> a;
	for (int i = 0, j = 0; i < brac.size(); i++)
		if (brac[i].rank <= 0)a.push_back(brac[i].posi);
	for (int i = 0; i < a.size(); i += 2)
	{
		for (int j = a[i] + 1; j < a[i + 1]; j++)
			func += code[j];
	}
	return func;
}

int isUseful(char c)//判断字符是否有用(非字母数字下划线空格)调用于standlize
{
	if (c >= 'a' &&c <= 'z' || c >= 'A' &&c <= 'Z' \
		|| c >= '0' &&c <= '9' || c == '\n' || c == '}'\
		|| c == '\t' || c == ' ' || c == '_')
		return 1;
	if (c == ';') return 2;
	return 0;
}

vector<string> standlize(string code)//提取有用字符
{
	string str;
	vector<string> usefulCode;
	for (int i = 0, j = 0; i < code.size(); i++) {
		if (isUseful(code[i]) == 0)str.push_back(code[i]);
		else if (isUseful(code[i]) == 2 && !str.empty()) {
			//cout << str << endl;//用于测试
			usefulCode.push_back(str);
			str.clear();
		}
	}
	return usefulCode;
}

double compare(vector<string>a, vector<string>b)//比较相似度
{
	double aSize = a.size();
	double bSize = b.size();
	if (aSize == 0 || bSize == 0) return 0;
	int same = 0;
	for (int i = 0; i < aSize; i++)
	{
		for (int j = 0; j < bSize; j++)
		{
			if (a[i] == b[j]) {
				a[i] = "a";//因为字符串只提取了非字母数字下划线
				b[j] = "b";//所以把比较过的标为不同的字母避免混淆
				same++;
				break;
			}
		}
	}//相同语句/a的语句量 和 相同语句/b的语句量 取平均即为相似度
	double rate = (same / aSize + same / bSize) / 2.0;
	return rate;
}

void printResult(string a, string b)//输出最终结果
{
	cout << "compare(" << a << ", " << b << "): " << endl;
	string codeA = readCode(a);
	codeA = removeNotes(codeA);
	vector<string> strA = standlize(getMain(codeA));
	string codeB = readCode(b);
	codeB = removeNotes(codeB);
	vector<string> strB = standlize(getMain(codeB));
	cout << "\tmain similar: " << compare(strA, strB) << endl;
	strA = standlize(getFunc(codeA));
	strB = standlize(getFunc(codeB));
	cout << "\tother functions similar: " << compare(strA, strB) << endl;
	strA = standlize(getAll(codeA));
	strB = standlize(getAll(codeB));
	cout << "\tall similar: " << compare(strA, strB) << endl;
}

int main()
{
	//给出的样例
	string a = "sample1.txt";
	string b = "sample2.txt";
	printResult(a, b);
	//我的八队列和另一同学的八皇后(主函数相同)
	string c = "eq.txt";
	string d = "qeqe.txt";
	printResult(c, d);
	return 0;
}