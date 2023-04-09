#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
#define OK 1
#define TRUE 1
#define ERROR 0
//#define OVERFLOW -2
#define MAX_STR_LEN 255 // 用户可在 255(1 个字节)以内定义最大串长
typedef int Status; //Status 是函数返回值类型，其值是函数结果状态代码。
typedef int ElemType; //ElemType 为可定义的数据类型，此设为 int 类型
typedef char SString[MAX_STR_LEN + 1]; // 0 号单元存放串的长度
int Index_BF(SString S, SString T, int pos);//BF 模式匹配
Status Index_KMP(SString S, SString T, int pos, int next[]);//KMP 模式匹配
Status StrAssign(SString T, char* chars);//生成一个其值等于 chars 的串 T
Status StrPrint(SString T);// 输出字符串 T
int StrLength(SString S);//返回串 S 的元素个数
Status Concat(SString T, SString S1, SString S2);// 用 T 返回 S1 和 S2 联接而成的新串。
int Index_BF(SString S, SString T, int pos = 1)
{
	int i = 1; int j = 1;
	for (; i <= S[0] && j <= T[0];) {
		if (S[i] == T[j]) { i++; j++; }
		else { i = i - j + 2; j = 1; }
	}
	if (j > T[0])return i - j + 1;
	if (i > S[0])return ERROR;
}
Status StrAssign(SString T, char* chars)
{
	int i;
	if (strlen(chars) > MAX_STR_LEN)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = chars[i - 1];//补充语句, chars 的字符放 T 中
		return OK;
	}
}
Status StrPrint(SString T)
{
	int i;
	for (i = 1; i <= T[0]; i++)
		cout << T[i];
	printf("\n");
	return OK;
}
int StrLength(SString S)
{
	return S[0];//补充语句，返回串 S 的元素个数
}
Status Concat(SString T, SString S1, SString S2)
{
	int i;
	if (S1[0] < 0 || S2[0] < 0) return ERROR;
	if (S1[0] + S2[0] <= MAX_STR_LEN)
	{ // 未截断
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];//补充语句，先放 S1 进入 T 中
		for (i = 1; i <= S2[0]; i++)
			T[i + S1[0]] = S2[i];//补充语句，再放 S2 进入 T 中
		T[0] = S1[0] + S2[0]; //设置 T 的长度
		return TRUE;
	}
	else
	{ // 截断 S2
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= MAX_STR_LEN - S1[0]; i++)
			T[i + S1[0]] = S2[i];//补充语句，再放 S2 进入 T 中
		T[0] = MAX_STR_LEN; //设置 T 的长度
		return TRUE;
	}
}
Status get_nextval(SString SUB, int* next) {
	next[0] = 0;
	int i = 2;
	int j = 0;
	for (; i <= SUB[0]; i++) {
		while (j && SUB[i] != SUB[j + 1])j = next[j - 1];
		if (SUB[j + 1] == SUB[i]) { next[i - 1] = ++j; }
		else { next[i - 1] = j; }
	}
	return OK;
}
Status get_next(SString SUB, int* next) {
	next[0] = 0;
	int i = 2;
	int j = 0;
	for (; i <= SUB[0]; i++) {
		while (j && SUB[i] != SUB[j + 1])j = next[j - 1];
		if (SUB[j + 1] == SUB[i]) { next[i - 1] = ++j; }
		else { next[i - 1] = j; }
	}
	return OK;
}
Status Index_KMP(SString S, SString T, int pos, int next[]) {
	int i = 1; int j = 0;
	for (; i <= S[0]; i++) {
		if (S[i] != T[++j]) {
			do { j = next[j - 1]; } while (j && S[i] != T[j + 1]);
			if (S[i] == T[j + 1])j++;
		}
		if (j == T[0]) { pos = i - j + 1; break; }
	}
	if (i > S[0])  pos = 0;
	return pos;
}//KMP 模式匹配
int main()
{
	int i, * next;
	char ch1[80], ch2[80];
	SString S1 = { 0 };
	SString S2 = { 0 };
	SString S = { 0 };
	SString SUB = { 0 }; // 定义串，第一个单元存储串的长度
	cout << "请输入第一个字符串:";
	cin >> ch1;
	StrAssign(S1, ch1);
	StrPrint(S1);
	cout << "请输入第二个字符串:";
	cin >> ch2;
	StrAssign(S2, ch2);
	StrPrint(S2);
	cout << "------------------------------------------------\n";
	cout << "第一个字符串长度为：" << StrLength(S1) << endl;
	cout << "第二个字符串长度为：" << StrLength(S2) << endl;
	cout << "============连接两个字符串构造主串==============\n";
	Concat(S,S1,S2); //用 S 返回 S1 和 S2 联接而成的新串
	cout << "主串长度为：" << StrLength(S) << endl;
	cout << "主串为：";
	StrPrint(S);
	cout << "请输入子串:";
	cin >> ch2;
	StrAssign(SUB, ch2);
	cout << "子串长度为：" << StrLength(SUB) << endl;
	cout << "---------------BE 匹配算法及实现-------------------\n";
	i = Index_BF(S, SUB, 1); 
	if (i)
		printf("主串和子串在第%d 个字符处首次匹配\n", i);
	else
		printf("主串和子串匹配不成功\n");
	cout << "---------------KMP 匹配算法及实现-------------------\n";
	next = new int[StrLength(SUB) + 1];
	get_next(SUB, next); 
	printf("子串的 next 数组为: ");
	for (i = 1; i <= StrLength(SUB); i++)
		cout << *(next + i-1)<<" ";
	printf("\n"); 
	i = Index_KMP(S, SUB, i, next);
		if (i)
			printf("主串和子串在第%d 个字符处首次匹配\n", i);
		else
			printf("主串和子串匹配不成功\n");
	cout << "---------------KMP 改进匹配算法及实现---------------\n";
	get_nextval(SUB, next); 
	printf("子串的 nextval 数组为: ");
	for (i = 1; i <= StrLength(SUB); i++)
	cout << *(next + i-1)<<" ";
	printf("\n");
	i = Index_KMP(S, SUB, i, next);
		if (i)
			printf("主串和子串在第%d 个字符处首次匹配\n", i);
		else
			printf("主串和子串匹配不成功\n");
}
