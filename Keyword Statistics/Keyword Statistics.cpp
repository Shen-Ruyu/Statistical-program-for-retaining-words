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
	char keyword[TOTAL][MAXLEN]; //�����ַ�������
	char no_keyword[TOTAL][MAXLEN]; //�Ǳ����ַ�������
	int keyoccur[TOTAL]; //�����ֳ��ִ���
	int no_keyoccur[TOTAL]; //�Ǳ����ַ������ִ���
	int keycount; //�����ָ���
	int no_keycount; //�Ǳ����ָ���
	int time; //ɨ�����
public:
	KeyWord(); //���캯��
	~KeyWord();
	void KeySave(); //���汣����
	void Origin(FILE *fp); //Դ�ļ����Ǳ�����ͳ��
	void TablePrint(); //������ű��ļ�
	void Print(); //���ͳ�ƽ��
};

KeyWord::KeyWord() {
	keyword[0][0] = '\0'; //��ʼ������
	no_keyword[0][0] = '\0';
	keycount = no_keycount = time = 0;
	for(int i = 0; i < TOTAL; i++){
		no_keyoccur[i] = 0;
		keyoccur[i] = 0;
	}
}

void KeyWord::KeySave() { //������
	ifstream file;
	file.open("keywords.txt"); //�򿪴洢�����ֵ��ļ�
	int i = 0;
	while(!file.eof()){
		file >> keyword[i]; //�������ַ����ֱ�д��keyword�б��棨���ж�ȡ��
		i++;
	}
	cout<<"������ɨ����ϣ�"<<endl;
	keycount = i;
}

void KeyWord::Origin(FILE *fp) { //ָ�����
	char current[MAXLEN] = {'\0'};
	char tmp; //��ȡ�ַ�
	int i, j, length = 0;
	int flag; //��־

	while(!feof(fp)){
		time++; //ɨ�������һ
		fscanf(fp, "%c", &tmp);
		if((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9') || tmp == '_') { //��Ч�ַ�������ַ���
			current[length++] = tmp;
			continue; //�����ո񡢻��л���Ч�ַ���ֹ
		}
		else if(length > 0) {
			flag = 0; //�뱣����ƥ��
			if ((current[0] >= '0' && current[0] <= '9') || (current[0] == '_' && current[1] == '\0'))
				flag =1; //��ȥֻ�����ֺͷ��ŵ����
			for(i = 0; i < keycount; i++) {	
				if(strcmp(keyword[i], current) == 0) {
					keyoccur[i]++;
					flag = 1;
				}
			}
			if(flag == 0) { //��ƥ��
				if(no_keycount > 0) { //�Ѿ��зǱ����ֱ���ȡ����
					for(j = 0; j < no_keycount; j++){
						if(strcmp(no_keyword[j], current) == 0) { //��ƥ����֮ǰ�ѳ��ֹ��ķǱ�����
							no_keyoccur[j]++;
							flag = 1;
						}
					}
				}
			}
			if(flag == 0) { //�Ǳ���������δ������
				strcpy(no_keyword[no_keycount], current); //�洢�˷Ǳ�����
				no_keyoccur[no_keycount]++;
				no_keycount++;
				flag = 1;
			}	
			for(i = 0; i < length; i++) //current����
				current[i] = '\0';
			length = 0;
			continue;
		}
	}
	cout<<"ԭ�ļ�������ȫ��ͳ����ϣ�"<<endl;
	cout<<"ɨ�������"<<time<<endl;
}

void KeyWord::TablePrint() { //������������ļ���
	FILE *f1, *f2;
	int i = 0;
	f1 = fopen("4-Keywords Statistical Results.xls", "w"); //�������ļ�
	if(f1 == NULL){
		cout<<"Failed to open table file 1��"<<endl; //���ļ�ʧ��
		fclose(f1); //�ر��ļ�
		exit(1);  
	}
	f2 = fopen("4-NON-Keywords Statistical Results.xls", "w"); //�Ǳ������ļ�
	if(f2 == NULL) {
		cout<<"Failed to open table file 2��"<<endl; //���ļ�ʧ��
		fclose(f2); //�ر��ļ�
		exit(1);  
	}

	fprintf(f1, "%s\t%s\t%s\n", "���", "������", "����");
	for(i = 0; i < keycount; i++) { //���δ洢�����ֵ�ͳ������
		fprintf(f1, "%d\t%s\t%d\n", i + 1, keyword[i], keyoccur[i]);
	}
	fclose(f1); //�ر��ļ�
	fprintf(f2, "%s\t%s\t%s\n", "���", "�Ǳ�����", "����");
	for(i = 0; i < no_keycount; i++) { //���δ洢�Ǳ����ֵ�ͳ������
		fprintf(f2,"%d\t%s\t%d\n", i + 1, no_keyword[i], no_keyoccur[i]);
	}
	fclose(f2); //�ر��ļ�
}

void KeyWord::Print() { //���ͳ�ƽ��
	int i = 0;
	cout<<endl<<"================================================================================"<<endl;
	cout<<left<<setw(20)<<"���"<<setw(25)<<"������"<<setw(25)<<"����"<<endl;
	for(i = 0; i < keycount; i++) //��������ֵ�ͳ������
		cout<<left<<setw(20)<<i + 1<<setw(25)<<keyword[i]<<setw(25)<<keyoccur[i]<<endl;

	cout<<endl<<"================================================================================"<<endl;
	cout<<left<<setw(20)<<"���"<<setw(25)<<"�Ǳ�����"<<setw(25)<<"����"<<endl;
	for(i = 0; i < no_keycount; i++) //����Ǳ����ֵ�ͳ������
		cout<<left<<setw(20)<<i + 1<<setw(25)<<no_keyword[i]<<setw(25)<<no_keyoccur[i]<<endl;
}

KeyWord::~KeyWord() {}

int _tmain(int argc, _TCHAR* argv[]) {
	KeyWord k;
	FILE *fp, *fk;
	clock_t stime, ftime;
	double scan_time = 0.0; 
	string filename;
	cout<<"**** �ļ��б����֣��ؼ��֣���ͳ�Ƴ��� ****"<<endl;
	fp = fopen("test.cpp", "r+");
	if(fp == NULL) {
		cout<<"��Դ�ļ�ʧ�ܣ�"<<endl;
		fclose(fp);
		exit(1);
	}
	else {
		cout<<"��Դ�ļ��ɹ���"<<endl;
		fk = fopen("keywords.txt", "r");
		if(fk == NULL) { //�򿪱������ļ�
			cout<<"�򿪱������ļ�ʧ�ܣ�"<<endl;
			fclose(fp);
			exit(1); 
		}
		else {
			cout<<"�򿪱������ļ��ɹ���"<<endl;
			stime = clock(); //��ȡ��ǰʱ��
			k.KeySave();
			fclose(fk);
			k.Origin(fp);
			ftime = clock();
			scan_time = (double)(ftime-stime) / CLOCKS_PER_SEC; //����ɨ��ʱ��
			cout<<"ɨ��ʱ�䣺"<<scan_time<<"s"<<endl;
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
   //        |  | ��^- \^.;^\___/^;.^/ -^ : |  |
   //          \  \ ^-. \_ __\ /__ _/ .-^ /  /
   //******^-._____^-._____\_____/_____.-^_____.-^******
   //                      ^*---*^