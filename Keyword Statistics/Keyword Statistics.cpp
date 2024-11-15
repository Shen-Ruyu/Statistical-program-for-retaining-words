// Keyword Statistics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "time.h"
using namespace std;

const int TOTAL = 1000;
const int MAXLEN = 100;

class KeyWord {
	char keyword[TOTAL][MAXLEN]; //保留字符串集合
	char no_keyword[TOTAL][MAXLEN]; //非保留字符串集合
	int keyoccur[TOTAL]; //保留字出现次数
	int no_keyoccur[TOTAL]; //非保留字符串出现次数
	int keycount; //保留字个数
	int no_keycount; //非保留字个数
	int time; //扫描次数
public:
	KeyWord(); //构造函数
	~KeyWord();
	void KeySave(); //保存保留字
	void Origin(FILE *fp); //源文件及非保留字统计
	void TablePrint(); //输出两张表文件
	void Print(); //输出统计结果
};

KeyWord::KeyWord() {
	keyword[0][0] = '\0'; //初始化变量
	no_keyword[0][0] = '\0';
	keycount = no_keycount = time = 0;
	for(int i = 0; i < TOTAL; i++){
		no_keyoccur[i] = 0;
		keyoccur[i] = 0;
	}
}

void KeyWord::KeySave() { //流操作
	ifstream file;
	file.open("keywords.txt"); //打开存储保留字的文件
	int i = 0;
	while(!file.eof()){
		file >> keyword[i]; //将保留字符串分别写入keyword中保存（按行读取）
		i++;
	}
	cout<<"保留字扫描完毕！"<<endl;
	keycount = i;
}

void KeyWord::Origin(FILE *fp) { //指针操作
	char current[MAXLEN] = {'\0'};
	char tmp; //读取字符
	int i, j, length = 0;
	int flag; //标志

	while(!feof(fp)){
		time++; //扫描次数加一
		fscanf(fp, "%c", &tmp);
		if((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9') || tmp == '_') { //有效字符则进入字符串
			current[length++] = tmp;
			continue; //遇到空格、换行或无效字符中止
		}
		else if(length > 0) {
			flag = 0; //与保留字匹配
			if ((current[0] >= '0' && current[0] <= '9') || (current[0] == '_' && current[1] == '\0'))
				flag =1; //除去只有数字和符号的情况
			for(i = 0; i < keycount; i++) {	
				if(strcmp(keyword[i], current) == 0) {
					keyoccur[i]++;
					flag = 1;
				}
			}
			if(flag == 0) { //不匹配
				if(no_keycount > 0) { //已经有非保留字被读取储存
					for(j = 0; j < no_keycount; j++){
						if(strcmp(no_keyword[j], current) == 0) { //若匹配上之前已出现过的非保留字
							no_keyoccur[j]++;
							flag = 1;
						}
					}
				}
			}
			if(flag == 0) { //非保留字且尚未被储存
				strcpy(no_keyword[no_keycount], current); //存储此非保留字
				no_keyoccur[no_keycount]++;
				no_keycount++;
				flag = 1;
			}	
			for(i = 0; i < length; i++) //current清零
				current[i] = '\0';
			length = 0;
			continue;
		}
	}
	cout<<"原文件保留字全部统计完毕！"<<endl;
	cout<<"扫描次数："<<time<<endl;
}

void KeyWord::TablePrint() { //数据输出到表文件中
	FILE *f1, *f2;
	int i = 0;
	f1 = fopen("4-Keywords Statistical Results.xls", "w"); //保留字文件
	if(f1 == NULL){
		cout<<"Failed to open table file 1！"<<endl; //打开文件失败
		fclose(f1); //关闭文件
		exit(1);  
	}
	f2 = fopen("4-NON-Keywords Statistical Results.xls", "w"); //非保留字文件
	if(f2 == NULL) {
		cout<<"Failed to open table file 2！"<<endl; //打开文件失败
		fclose(f2); //关闭文件
		exit(1);  
	}

	fprintf(f1, "%s\t%s\t%s\n", "序号", "保留字", "个数");
	for(i = 0; i < keycount; i++) { //依次存储保留字的统计数据
		fprintf(f1, "%d\t%s\t%d\n", i + 1, keyword[i], keyoccur[i]);
	}
	fclose(f1); //关闭文件
	fprintf(f2, "%s\t%s\t%s\n", "序号", "非保留字", "个数");
	for(i = 0; i < no_keycount; i++) { //依次存储非保留字的统计数据
		fprintf(f2,"%d\t%s\t%d\n", i + 1, no_keyword[i], no_keyoccur[i]);
	}
	fclose(f2); //关闭文件
}

void KeyWord::Print() { //输出统计结果
	int i = 0;
	cout<<endl<<"================================================================================"<<endl;
	cout<<left<<setw(20)<<"序号"<<setw(25)<<"保留字"<<setw(25)<<"个数"<<endl;
	for(i = 0; i < keycount; i++) //输出保留字的统计数据
		cout<<left<<setw(20)<<i + 1<<setw(25)<<keyword[i]<<setw(25)<<keyoccur[i]<<endl;

	cout<<endl<<"================================================================================"<<endl;
	cout<<left<<setw(20)<<"序号"<<setw(25)<<"非保留字"<<setw(25)<<"个数"<<endl;
	for(i = 0; i < no_keycount; i++) //输出非保留字的统计数据
		cout<<left<<setw(20)<<i + 1<<setw(25)<<no_keyword[i]<<setw(25)<<no_keyoccur[i]<<endl;
}

KeyWord::~KeyWord() {}

int _tmain(int argc, _TCHAR* argv[]) {
	KeyWord k;
	FILE *fp, *fk;
	clock_t stime, ftime;
	double scan_time = 0.0; 
	string filename;
	cout<<"**** 文件中保留字（关键字）的统计程序 ****"<<endl;
	fp = fopen("test.cpp", "r+");
	if(fp == NULL) {
		cout<<"打开源文件失败！"<<endl;
		fclose(fp);
		exit(1);
	}
	else {
		cout<<"打开源文件成功！"<<endl;
		fk = fopen("keywords.txt", "r");
		if(fk == NULL) { //打开保留字文件
			cout<<"打开保留字文件失败！"<<endl;
			fclose(fp);
			exit(1); 
		}
		else {
			cout<<"打开保留字文件成功！"<<endl;
			stime = clock(); //获取当前时间
			k.KeySave();
			fclose(fk);
			k.Origin(fp);
			ftime = clock();
			scan_time = (double)(ftime-stime) / CLOCKS_PER_SEC; //计算扫描时间
			cout<<"扫描时间："<<scan_time<<"s"<<endl;
		}
		fclose(fp);
	}
	k.TablePrint();
	k.Print();

	return 0;
}


   //                      _oo0oo_        
   //                     o8888888o      
   //                     88" . "88        
   //                     (| -_- |)        
   //                      0\ = /0         
   //                  ____/^---^\____
   //                 .   *\\| |//*   .
   //                 / \\||| : |||// \
   //               / _||||| -:- |||||_\
   //                 | | \\\ - /// | |
   //               | \_| ^^\---/^^ |_/ |
   //                \ .-\__ ^-^ __/-. /
   //            ____^. .^ /--.--\ ^. .^____
   //         ."" ^< ^.____\_<|>_/____.^ >^ "".
   //        |  | ：^- \^.;^\___/^;.^/ -^ : |  |
   //          \  \ ^-. \_ __\ /__ _/ .-^ /  /
   //******^-._____^-._____\_____/_____.-^_____.-^******
   //                      ^*---*^