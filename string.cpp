#include <iostream>
#include <cstring>
#include <cstddef>
using namespace std;
int match_a(char *P, char *T)//(T中找P)
{
	size_t n = strlen(T), i = 0;//size_t是strlen的参类型
	size_t m = strlen(P), j = 0;//是无符号整数
	while(j < m && i < n)
		if(T[i] == P[j]){i++; j++;}//匹配则继续
		else{ i -= j - 1; j = 0;}//失配则T回退，p归零
	return i - j;//返回起始位置
}

int match_b(char *P, char *T)
{
	size_t n = strlen(T), i = 0;
	size_t m = strlen(P), j;
	for (i = 0; i < n - m + 1; ++i)
	{
		for (j = 0; j < m; ++j)
			if(T[i + j] != P[j]) break;
		if(m <= j)break;
	}
	return i;
}

// int *buildNext(char *P)//第一个星号表示返回指针
// {
// 	size_t m = strlen(P), j = 0;
// 	int *N = new int[m];
// 	int t = N[0] = -1;
// 	while(j < m - 1)
// 		if (0 > t || P[j] == P[t])
// 			N[++j] = ++t;
// 		else t = N[t];
// 	return N;
// }

int* buildNext ( char* P ) { //构造模式串P的next表（改进版本）
    size_t m = strlen ( P ), j = 0; //“主”串指针
    int* N = new int[m]; //next表
    int t = N[0] = -1; //模式串指针
    while ( j < m - 1 )
       if ( 0 > t || P[j] == P[t] ) { //匹配
       		j++;t++;
       		if(P[j] == P[t])N[j] = N[t];
       		else N[j] = t;
          //N[j] = ( P[++j] != P[++t] ? t : N[t] ); //注意此句与未改进之前的区别
       } else //失配
          t = N[t];
    return N;
}

int kmp(char *P, char *T)
{
	int *next = buildNext(P);
	int n = (int)strlen(T), i = 0;//长串指针
	int m = (int)strlen(P), j = 0;//短串指针
	while(j < m && i < n)
		if(0 > j || T[i] == P[j]){i++; j++;}
		else j = next[j];//若失配P右移T不回退
	delete[] next;
	return i - j;
}

int main(int argc, char const *argv[])
{
	char a[] = "argc";
	char b[] = "asdfghasgkl";
	char c[] = "qwertyuargcrtg";
	cout<<match_a(a, b)<<endl;
	cout<<match_a(a, c)<<endl;
	cout<<match_a(a, b)<<endl;
	cout<<match_a(a, c)<<endl;
	cout<<kmp(a, b)<<endl;
	cout<<kmp(a, c)<<endl;
	return 0;
}