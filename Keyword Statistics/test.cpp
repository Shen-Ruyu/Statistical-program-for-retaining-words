#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <ctime> 
#include <iomanip> 
#include <conio.h> 
using namespace std;

int MAXDAY;
char g_str[128] = {0};
char h_str[128] = {0};
void Judge(int year, int month);

class Date
{
protected:
	char *pYMD;
public:
	Date(char *newd = '\0'){
		pYMD = new char[15];
		strcpy(pYMD, newd);
	}
	Date& Add(int add); //����n���Ժ��ǡ�****��**��**�ա�
    Date& Sub(int sub); //����n����ǰ�ǡ�****��**��**�ա�
    void Display(); //���Date��������ݡ�****��**��**�ա�
};

Date& Date::Add(int add) //����n���Ժ��ǡ�****��**��**�ա�
{
	int year, month, day;
	sscanf(pYMD, "%d", &year);
	sscanf(pYMD + 6, "%d", &month);
	sscanf(pYMD + 10, "%d", &day);
	day += add;
	Judge(year, month);
	while(day > MAXDAY){
		day -= MAXDAY;
		month++;
		if(month > 12){
			month = 1;
			year++;
		}
		Judge(year, month);
	}
	sprintf(pYMD, "%04d��%02d��%02d��", year, month, day);
	return *this;
}

Date& Date::Sub(int sub) //����n����ǰ�ǡ�****��**��**�ա�
{
	int year, month, day;
	sscanf(pYMD, "%d", &year);
	sscanf(pYMD + 6, "%d", &month);
	sscanf(pYMD + 10, "%d", &day);
	day -= sub;
	Judge(year, month - 1);
	while(day < 1){
		day += MAXDAY;
		month--;
		if(month < 1){
			month = 12;
			year--;
		}
	    Judge(year, month - 1);
	}
	sprintf(pYMD, "%04d��%02d��%02d��", year, month, day);
	return *this;
}

void Date::Display() //���Date��������ݡ�****��**��**�ա�
{
	cout<<pYMD<<endl;
}

void Judge(int year,int month) //�ж������ÿ������
{
	int leapyear = 0;
	if((year % 4 == 0&&year %100 != 0)||year % 400 == 0)
		leapyear=1;
	switch(month){
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: MAXDAY = 31; break;
		case 4: case 6: case 9: case 11: MAXDAY = 30; break;
		case 2: if(leapyear = 1){
			        MAXDAY = 29;
					break;
				}
				else MAXDAY = 28;
				break;
		default: break;
	}
}

class Time:public Date
{
protected:
	char *pTime;
public:
	Time(char *newd="\0", char *newt="\0")
		:Date(newd){
			pTime = new char[13];
			strcpy(pTime, newt);
	    }
	Time& Add(int addh, int addm, int adds);
	Time& Sub(int subh, int subm, int subs);
	void Display();
};

Time& Time::Add(int add_h, int add_m, int add_s)
{
	int hour, minute, second, add = 0;
	sscanf(pTime, "%d", &hour);
	sscanf(pTime + 3, "%d", &minute);
	sscanf(pTime + 6, "%d", &second);
	hour += add_h;
	minute += add_m;
	second += add_s;
	if(second >= 60){
		minute++;
		second -= 60;
	}
	if(minute>=60){
		hour++;
		minute -= 60;
	}
	if(hour >= 24){
		add += hour / 24;
		hour = hour % 24;
	}
	Date::Add(add);
	sprintf(pTime, "%02d:%02d:%02d", hour, minute, second);
	return *this;
}

Time& Time::Sub(int subh, int subm, int subs)
{
	int hour, minute, second, sub=0;
	sscanf(pTime, "%d", &hour);
	sscanf(pTime + 3, "%d", &minute);
	sscanf(pTime + 6, "%d", &second);
	hour -= subh;
	minute -= subm;
	second -= subs;
	if(second < 0){
		minute--;
		second = second + 60;;
	}
	if(minute < 0){
		hour--;
		minute = minute + 60;
	}
	if(hour < 0){
		sub += -hour / 24 + 1;
		while(hour < 0)
			hour += 24;
	}
	Date::Sub(sub);
	sprintf(pTime, "%02d:%02d:%02d", hour, minute, second);
	return *this;
}

void Time::Display()
{
	cout<<pYMD<<" "<<pTime<<endl;
}

char *NowTime() //��ȡ��ǰʱ��
{
	char buf[128] = {0};
	char sth[128] = {0};
	tm *local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	strftime(buf, 64, "%Y��%m��%d�� %H:%M:%S", local);
	strftime(sth, 64, "%H:%M:%S", local);
	strcpy(g_str, buf);
	strcpy(h_str, sth);
	return g_str, h_str;
}

void Pageturning()
{
    ifstream myfile;
    myfile.open("The Little Prince.txt");
    assert(myfile.is_open());
    int i = 0, j = 0, k = 0;
    string s, temp;
    vector<string> v;
    while(getline(myfile,temp))
        v.push_back(temp);
    while(1){
        int k = 0;
        while(k < 10){
            s = v[i];
            cout<<s<<endl;
            k++;
			i++;
            if(i == v.size())
				exit(0);
        }
        cout<<endl<<"1.��һҳ  0.����"<<endl;
        int x;
        cin>>x;
        if(x == 1) system("cls");
        else if(x == 0) break;
    }
	cout<<"����\n"<<endl;
}

void Merge()
{
	ifstream file1;
	ifstream file2;
	ofstream file3;
	file1.open("test1.txt");
	file2.open("test2.txt");
	file3.open("merge.txt");
	assert(file1.is_open());
	assert(file2.is_open());
	assert(file3.is_open());
	vector<string> v1;
	vector<string> v2;
	string s1;
	string s2;
	while (getline(file1, s1))
		file3<<s1<<'\n';
	file3<<endl;
	while (getline(file2, s2))
		file3<<s2<<'\n';
	file1.close();
	file2.close();
	file3.close();
	cout<<"�ϲ����\n"<<endl;
}

void Addnum()
{
	ifstream file1;
	ofstream file2;
	file1.open("test1.txt");
	file2.open("addnum.txt");
	assert(file1.is_open());
	assert(file2.is_open());
	string s1;
	int i = 1;
	while(getline(file1, s1)){
		file2<<i<<"-"<<s1<<'\n';
		i++;
	}
	file1.close();
	file2.close();
	cout<<"�������\n"<<endl;
}

void Transition()
{
	ifstream file1;
	ofstream file2;
	file1.open("test1.txt", ios::in); 
	file2.open("transition.txt");
	assert(file1.is_open());
	assert(file2.is_open());
	char ch;
	while (file1.get(ch)){ 
		if (ch >= 'a'&&ch <= 'z')
			ch = ch - 'a' + 'A';
		file2<<ch;
	}
	file1.close();
	file2.close();
	cout<<"ת�����\n"<<endl;
}

template<typename Type>
class List1
{
private:
    int size;
    int Length;
    Type *L;    
public:
    List1(){
		size = 0;
		Length = 0;
		Type *L = new Type[size]
	};
	~List1(){};
    List1(int s, int l, Type *L);
    void display(){
        for(int i = 0; i < Length; i++)
            cout<<L[i]<<" ";
		cout<<"\n";
    }
	int GetLength(){return Length;};
    void BubbleSort();
};

template<typename Type>
List1<Type>::List1(int s, int l, Type *Li)
{
    size = s;
    Length = l;
    L = new Type[size];
    for(int i = 0; i < Length; i++)
        L[i] = Li[i];
};

template<typename Type>
void List1<Type>::BubbleSort()
{
	Type t;
	for(int i = 0; i < Length; i++)
		for(int j = i + 1; j < Length; j++)
			if(L[j] < L[i]){
				t = L[j];
				L[j] = L[i];
				L[i] = t;
			}
};

template<typename Type>
class List2
{
private:
	Type *pl;
	int Length;
public:
	List2(){
		Length = 0;
		Type *pl = new Type[Length]
	};
	~List2(){};
	List2(int l, Type *li);
	void display(){
        for(int i = 0; i < Length; i++)
            cout<<pl[i]<<" ";
		cout<<"\n";
    };
};

template<typename Type>
List2<Type>::List2(int l,Type *l1)
{
    Length = l;
    pl = new Type[Length];
    for(int i = 0; i < Length; i++)
        pl[i] = l1[i];
};

template<typename Type>
class Node
{
public:
	Node<Type>* next;
	Type data;
};

template<typename Type>
class List3
{
private:
	Node<Type>* head;
	int Length;
public:
	List3();
	~List3(){delete head;};
	int GetLength(){return this->Length;};
	int Append(const Type t);
	void Input();
	void display();
	int Insert(const Type t, int i);
	void BubbleSort();
	int Search(Type t);
};

template<typename Type>
List3<Type>::List3()
{
	Length = 0;
	head = new Node<Type>;
	head->data = 0;
	head->next = NULL;
};

template<typename Type>
void List3<Type>::display()
{
	Node<Type> *p = head;
	int l = Length;
	while(l){
		p = p->next;
		cout<<p->data<<" ";
		l--;
	}
	cout<<"\n";
};

template<typename Type>
int List3<Type>::Append(const Type t)
{
	Node<Type> *p = new Node<Type>;
	p->data = t;
	p->next = NULL;
	Node<Type> *c = head;
	while(c->next != NULL)
		c = c->next;
	c->next = p;
	this->Length++;
	return this->Length;
};

template<typename Type>
void List3<Type>::Input()
{
	int size, num;
	Node<Type> *p = NULL;
	Node<Type> *t = NULL;
	cout<<"Input size of list:";
	cin>>size;
	this->Length = size;
	p = this->head;
	for(int i = 1; i <= size; i++){
		t = new Node<Type>;
		cout<<"Input data "<<i<<" of list:";
		cin>>t->data;
		t->next = NULL;
		p->next = t;
		p = t;
	}
};

template<typename Type>
int List3<Type>::Insert(const Type t,int i)
{
	i--;
	Node<Type> *p = new Node<Type>;
	p->data = t;
	p->next = NULL;
	Node<Type> *c = head;
	while(c->next != NULL && i){
		c = c->next;
		i--;
	}
	if(c->next == NULL) return 0;
	if(i == 0){
		p->next = c->next;
		c->next = p;
		this->Length++;
		return 1;
	}
};

template<typename Type>
void List3<Type>::BubbleSort()
{
	Node<Type> *p;
	Node<Type> *t = NULL;
	Type d;
	while(t != head->next->next){
		for(p = head; p->next->next != t; p = p->next){
			if(p->next->data > p->next->next->data){
				d = p->next->next->data;
				p->next->next->data = p->next->data;
				p->next->data = d;
			}
		}
		t = p->next;
	}
};

template<typename Type>
int List3<Type>::Search(Type t)
{
	int num, flag;
	Node<Type> *p;
	for(p = head, num = 1; p->next != NULL; p = p->next, num++){
		if(p->next->data == t) flag = num;
	}
	cout<<"Location of data "<<t<<" is "<<flag<<endl;
	return flag;
};

class CStudent
{
	char No[10], Name[7];
	int DegChinese, DegMaths, DegEnglish;
	int Sum, Num, Ave;
public:
	int GetChinese(){return DegChinese;}
	int GetMaths(){return DegMaths;}
	int GetEnglish(){return DegEnglish;}
	CStudent(){
		No[0] = Name[0] = '\0';
		DegChinese = DegMaths = DegEnglish = Sum = 0;
	}
	void SetData();
	void Display();
	int Average();
};

void CStudent::SetData()
{
	cin>>No>>Name>>DegChinese>>DegMaths>>DegEnglish;
	Sum = DegChinese + DegMaths + DegEnglish;
	Ave = Sum / (float)3;
}

int CStudent::Average()
{
	Ave = Sum / (float)3;
	return Ave;
}

void CStudent::Display()
{
	cout<<No<<setw(8)<<Name<<setw(7)<<DegChinese<<setw(7)<<DegMaths<<setw(7)<<DegEnglish<<setw(7)<<Sum<<setw(7)<<Ave;
}

class CStatistic
{
	int Nums, Ave;
	float AveChinese, AveMaths, AveEnglish, AveSum, Sums;
	CStudent *StuArray,*a;
public:
	CStatistic(int num);
	void Sort();
	void Display();
};

void CStatistic::Sort()
{
	int i,j;
	for(j = 0; j < Nums; j++){
		for(i = 0; i < Nums; i++){
			if(StuArray[i].Average() < StuArray[i+1].Average()){
				a[0] = StuArray[i];
				StuArray[i] = StuArray[i+1];
				StuArray[i+1] = a[0];
			}
		}
	}
}

void CStatistic::Display()
{
	int n =1;
	for(int i = 0; i < Nums; i++){
		StuArray[i].Display();
		cout<<setw(7)<<n<<endl;
		n++;
	}
	cout<<"               "<<setw(7)<<setprecision(2)<<fixed<<AveChinese<<setw(7)<<setprecision(2)<<fixed<<AveMaths<<setw(7)<<setprecision(2)<<fixed<<AveEnglish<<setw(7)<<setprecision(2)<<fixed<<Sums<<setw(7)<<setprecision(2)<<fixed<<AveSum<<endl;
}

CStatistic::CStatistic(int num)
{
	Nums = num;
	StuArray = new CStudent[Nums];
	a = new CStudent[1];
	AveChinese = AveMaths = AveEnglish = 0.0;
	for(int i = 0; i < Nums; i++){
		StuArray[i].SetData();
		AveChinese += StuArray[i].GetChinese();
		AveMaths += StuArray[i].GetMaths();
		AveEnglish += StuArray[i].GetEnglish();
	}
	AveChinese = AveChinese / (float)Nums;
	AveMaths = AveMaths / (float)Nums;
	AveEnglish = AveEnglish / (float)Nums;
	Sums=AveChinese + AveMaths + AveEnglish;
	AveSum = Sums / (float)3;
}

class Point
{
protected:
	int x ,y;
public:
	Point(){
		x = y = 0;
	}
    Point(int i, int j){
		x = i; y = j;
	}
	Point(Point &p){
		x = p.x; y = p.y;
	}
    ~Point(){}
    void Display(){
		cout<<"("<<x<<", "<<y<<")"<<endl;
	}
	void offert(int i, int j);//ʵ�ֵ��ƫ�ƣ�������ƫ����
    void offert(Point &);//ʵ�ֵ��ƫ�ƣ�����Point�������ƫ����
	bool operator == (Point &);//�ж�����������Ƿ����
    bool operator != (Point &);//�ж�����������Ƿ����
    void operator += (Point &);//��������������
    void operator -= (Point &);//��������������
    void operator ++ ();//����ǰ��������1��ǰ׺��
    void operator ++ (int k);//����ǰ��������10����׺��
    void operator -- ();//����ǰ�����Լ�1��ǰ׺��
    void operator -- (int k);//����ǰ�����Լ�10����׺��
    friend Point& operator + (Point &, Point &);//��������������
    friend Point& operator - (Point &, Point &);//��������������
	int GetX(){return x;};//�ṩʵ�������˽������x�ķ���
	int GetY(){return y;};//�ṩʵ�������˽������y�ķ���
};

void Point::offert(int i, int j)
{
	x += i;
	y += j;
}

void Point::offert(Point& p)
{
	x += p.x;
	y += p.y;
}

bool Point::operator==(Point& p)
{
	if(x == p.GetX() && y == p.GetY()) return 1;
    else return 0;
}

bool Point::operator!=(Point& p)
{
	if(x != p.GetX() || y != p.GetY()) return 1;
    else return 0;
}

void Point::operator+=(Point& p)
{
	x += p.GetX();
	y += p.GetY();
}

void Point::operator-=(Point& p)
{
	x -= p.GetX();
	y -= p.GetY();
}

void Point::operator++()
{
	this->x += 1;
	this->y += 1;
}

void Point::operator++(int k)
{
	Point old = *this;
    this->x += 10; 
	this->y += 10;
}

void Point::operator--()
{
	this->x -= 1;
	this->y -= 1;
}

void Point::operator--(int k)
{
	Point old = *this;
    this->x -= 10; 
	this->y -= 10;
}

Point &operator+(Point &p, Point &q)
{
	p.x += q.x;
    p.y += q.y;
    return p;
}

Point &operator-(Point &p, Point &q)
{
	p.x -= q.x;
    p.y -= q.y;
    return p;
}

class BaseString
{
protected:
	char Data[50];
	unsigned int Length;
public:
	BaseString(){//�ַ����ĳ�ʼ��
		Data[0] = '\0';
		Length = 0;
	}
	void Input();
	unsigned int GetLength();
	void Display();
	char * GetData();
};

char * BaseString::GetData()//�����ַ�����
{
	return Data;
}

void BaseString::Input()//����һ���ַ���
{
	cout<<"������һ���ַ�����"<<endl;
	cin>>Data;
	for(Length = 0; Data[Length] != '\0'; Length++);
}

unsigned int BaseString::GetLength()//���ַ����ĳ���
{
	for(Length = 0; Data[Length] != '\0'; Length++);
	return Length;
}

void BaseString::Display()//����ַ���
{
	cout<<"������ַ���Ϊ��"<<Data<<endl;
}

class ReString:public BaseString//����������
{
public:
	void Inverse();
};

void ReString::Inverse()//ʵ���ַ����ĵ���
{
	char temp;
	int L = Length - 1;
	for(int i = 0; i < L / 2; i++){
		temp = Data[i];
		Data[i] = Data[L - i];
		Data[L - i] = temp;
	}
	cout<<"���ú���ַ���Ϊ��"<<Data<<endl;
}

class CopyString:public BaseString//����������
{
public:
	void Copy(CopyString &ob);
};

void CopyString::Copy(CopyString &ob)//�����ַ���
{
	char *temp = ob.GetData();
	int i;
	for(i = 0; i < ob.GetLength(); i++)
		Data[i] = temp[i];
	Data[i] = '\0';
	Length = ob.GetLength();
	cout<<"���ƺ���ַ���Ϊ��"<<Data<<endl;
}

class CmpString:private BaseString//˽��������
{
public:
	int Compare(CopyString &ob);
};

int CmpString::Compare(CopyString &ob)//�Ƚ�������ַ�������һ���ַ����ĳ���
{
	CmpString str4;
	str4.Input();
	int len1, len2;
	len1 = ob.GetLength();
	len2 = str4.GetLength();
	if(len1 < len2) return 1;
	if(len1 == len2) return 0;
	if(len1 > len2) return -1;
}

class NewString:public BaseString,public ReString, public CopyString, public CmpString
{
public:
	NewString(){};
};

class Person
{
public:
	char *surname, *name, *sex;
	int age;
	string Fname, Mname;
public:
	Person(char *Sur, char *Name, char *Sex, int Age);
	void Setdata(char *Sur, char *Name, char *Sex, int Age);
	void Display();
	string GetSur(){
		return surname;
	}
	string GetName(){
		return name;
	}
};

Person::Person(char *Sur = NULL, char *Name = NULL, char *Sex = NULL, int Age = 0)
{
	surname = Sur;
	name = Name;
	sex = Sex;
	age = Age;
}

void Person::Setdata(char *Sur, char *Name, char *Sex, int Age)
{
	Person::surname = Sur;
	Person::name = Name;
	Person::sex = Sex;
	Person::age = Age;
}

void Person::Display()
{
	cout<<surname<<name<<" "<<setw(4)<<sex<<" "<<setw(4)<<age<<" "<<"����"<<" "<<"����"<<endl;
}

class Father:virtual public Person
{
public:
	char *father;
	Father(char *fsur = NULL, char *fname = NULL, char *fsex = NULL, int fage = 0)
		:Person(surname, name, sex, age){}
	void Setdata(char *fsur, char *fname, int fage){
		Person::surname = fsur;
		Person::name = fname;
		Person::age = fage;
		Person::sex = "��";
	}
};

class Mother:virtual public Person
{
public:
	char *mother;
	Mother(char *msur = NULL, char *mname = NULL, char *msex = NULL, int mage = 0)
		:Person(surname, name, sex, age){}
	void Setdata(char *msur,char *mname,int mage){
		Person::surname = msur;
		Person::name = mname;
		Person::age = mage;
		Person::sex = "Ů";
	}
};

class Child:public Father,public Mother
{
public:
	char *child;
	Child(char *fsur = NULL, char *fname = NULL, char *fsex = NULL, int *fage = NULL, 
		char *msur = NULL, char *mname = NULL, char *msex = NULL, int mage = 0, 
		char *csur = NULL, char *cname = NULL, char *csex = NULL, int cage = 0)
		:Father(surname, name, sex, age), Mother(surname, name, sex, age), Person(surname, name, sex, age)
	{
		char *Myfather = NULL;
		char *Mymother = NULL;
	}
	void Setdata(char *Name, char *Sex, int Age, Father f, Mother m)
	{
		Person::surname = f.surname;
		Person::name = Name;
		Person::sex = Sex;
		Person::age = Age;
		Fname = f.GetSur() + f.GetName();
		Mname = m.GetSur() + m.GetName(); 
	}
	void Display(){
		cout<<surname<<name<<" "<<setw(4)<<sex<<" "<<setw(4)<<age<<" "<<Fname<<" "<<Mname<<endl;
	}
};

class Point
{
protected:
	int x, y;
public:
	Point(){
		x = y = 0;
	}
	void SetXY(int m, int n){
		x = m; y = n;
	}
    void Draw(){
		cout<<"Point:("<<x<<", "<<y<<")"<<endl;
	}
	int GetX(){return x;};
	int GetY(){return y;};
};

class Line:public Point
{
protected:
	int x1, y1;
public:
	Line(){
		x = y = x1 = y1 = 0;
	}
	void SetXY(int m, int n, int l, int k);
	void Draw(){
		cout<<"Line:("<<x<<", "<<y<<")----("<<x1<<", "<<y1<<")"<<endl;
	}
};

void Line::SetXY(int m,int n, int l, int k)
{
	x = m; y = n;
	x1 = l; y1 = k;
}

class Circle:public Point
{
protected:
	int x1, y1;
public:
	Circle(){
		x = y = x1 = y1 = 0;
	}
	void SetXY(int m, int n, int l, int k);
	void Draw(){
		cout<<"Circle:("<<x<<", "<<y<<")----("<<x1<<", "<<y1<<")"<<endl;
	}
};

void Circle::SetXY(int m,int n, int l, int k)
{
	x = m; y = n;
	x1 = l; y1 = k;
}

void DrawObject(Point *p)
{
	p->Draw();
}

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

int _tmain(int argc, _TCHAR* argv[])
{
	int add, sub;
	int hour, minute, second;
	char *pYMD;
	char buf[128] = {0};
	NowTime();
	std::cout<<"��ǰʱ�䣺"<<g_str<<std::endl;

	Date date1(g_str); //���ڼ�
	cout<<"������Ҫ��ѯ�����������ڣ�";
	cin>>add;
	date1.Add(add);
	cout<<add<<"�������Ϊ��";
	date1.Display();
	cout<<"\n";

	Date date2(g_str); //���ڼ�
	cout<<"������Ҫ��ѯ������ǰ�����ڣ�";
	cin>>sub;
	date2.Sub(sub);
	cout<<sub<<"��ǰ����Ϊ��";
	date2.Display();
	cout<<"\n";

	Time time1(g_str, h_str);
	cout<<"������Ҫ��ѯ�೤ʱ����ʱ�䣺";
	cin>>hour>>minute>>second;
	time1.Add(hour, minute, second);
	cout<<hour<<"ʱ"<<minute<<"��"<<second<<"���Ϊ��";
	time1.Display();
	cout<<"\n";

	Time time2(g_str, h_str);
	cout<<"������Ҫ��ѯ�೤ʱ��ǰ��ʱ�䣺";
	cin>>hour>>minute>>second;
	time2.Sub(hour, minute, second);
	cout<<hour<<"ʱ"<<minute<<"��"<<second<<"��ǰΪ��";
	time2.Display();

	return 0;
}