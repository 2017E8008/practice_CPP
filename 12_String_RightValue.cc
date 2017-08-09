
//���  �ƶ�����Ĺ��캯������ֵ����    ��ֵ����&&

#include <iostream>
#include <string.h>
#include <stdio.h>
using std::cout;
using std::cin;
using std::endl;

class String {
public:
	String();
	String(const char *);
	String(const String&);
	~String();
	String &operator=(const String &);
	String &operator=(const char *);
	
	//��ֵ���� 
    String(String &&rhs);             //�ƶ�����Ĺ��캯��
    String & operator=(String &&rhs); //�ƶ������operator=��ֵ����
   
   
	String &operator+=(const String &);
	String &operator+=(const char *);

	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;          //const����ֻ�ܵ���const��Ա����;��ͨ������ܵ���

	std::size_t size() const;
	const char* c_str() const;

	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &, const String &);
	friend std::istream &operator>>(std::istream &, String &);

private:
	char * _pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

String::String()
:_pstr(new char[1])
{
}

String::String(const char* pstr)
:_pstr(new char[strlen(pstr)+1])
{
	cout<< "String(const char *)" <<endl;
	strcpy(_pstr,pstr);
}

String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr)+1])
{
	cout<< "String (const Sting &)"<<endl;
	strcpy(_pstr,rhs._pstr);
}
//*********************************************��ʱ������ֵ����&&  
String::String(String && rhs)
:_pstr(rhs._pstr)
{
	cout << "Sting(Sting && rhs)" <<endl;
	rhs._pstr = NULL;            //��ֵrhs�Զ��ͷ�ʱ
}

String & String::operator=(String && rhs){
	cout << "operator = (Sting && rhs)" <<endl;
	if(this != &rhs){
		delete [] _pstr;
		this->_pstr = rhs._pstr;
		rhs._pstr =  NULL;
	}
	return *this;
}
//***********************************************
String::~String(){
	delete [] _pstr;
}

String & String::operator=(const String &rhs){
	if(this != &rhs){        //�����Ը������� ���Ҿ�Ϊָ��
		delete [] _pstr;
		_pstr=new char [strlen(rhs._pstr)+1];
		strcpy(_pstr,rhs._pstr);
	}
	return *this;
}
	
String & String::operator=(const char * pstr){
	if(!strcmp(this->_pstr,pstr)){         //�ж��ַ��������Ƿ���ͬ;pstr�����ֳ�����,_pstr��ջ��,�׵�ַ�϶�����ͬ
		cout << "operator = (const char *)" <<endl;
		delete [] _pstr;
		_pstr=new char [strlen(pstr)+1];
		strcpy(_pstr,pstr);
	}
	return *this;
}

String & String::operator+=(const String& rhs){
	int need_length=strlen(this->_pstr)+strlen(rhs._pstr)+1;
	char *temp=new char [strlen(_pstr)+1];
	strcpy(temp,_pstr);
	delete [] _pstr;
	_pstr = new char [need_length];
	strcpy(_pstr,temp);
	delete [] temp;
	strcat(_pstr,rhs._pstr);
	return *this;
}
	
String & String::operator+=(const char* pstr){
	int need_length=strlen(this->_pstr)+strlen(pstr)+1;
	char *temp=new char [strlen(_pstr)+1];
	strcpy(temp,_pstr);
	delete [] _pstr;
	_pstr = new char [need_length];
	strcpy(_pstr,temp);
	delete [] temp;
	strcat(_pstr,pstr);
	return *this;
}
	
char & String::operator[](std::size_t index){
	static char nullchar = '\0';
	if(index>=0 && index<strlen(_pstr)){
		return _pstr[index];
	}
	return nullchar;
	//return '\0';     //���ò�Ҫ���ؾֲ�����
}

const char & String::operator[](std::size_t index) const{          //const����ֻ�ܵ���const��Ա����;��ͨ������ܵ���
	static char nullchar = '\0';
	if(index>=0 && index<strlen(_pstr)){
		return _pstr[index];
	}
	return nullchar;
}
	
std::size_t String::size() const{
	if(*(this->_pstr)=='\0') return 0;
	return strlen(this->_pstr);
}

const char* String::c_str() const{
	return _pstr;                    //����char* 
}

//A�����Ԫ���� ��ֱ�ӷ���A���private��Ա����

bool operator==(const String &left, const String &right){
	return !strcmp(left._pstr,right._pstr);
}

bool operator!=(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr);
}

bool operator<(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)<0?true:false;
}

bool operator>(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)>0?true:false;
}

bool operator<=(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)<=0?true:false;
}

bool operator>=(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)>=0?true:false;
}

std::ostream &operator<<(std::ostream &os, const String &rhs){       //����String�� ���������
	os << rhs._pstr;
	return os;
}
	
std::istream &operator>>(std::istream &is, String &rhs){
	delete [] rhs._pstr;
	rhs._pstr=new char[256]{0};
	is >> rhs._pstr;          
	return is;
}
	
	
	String operator+(const String &, const String &);
	String operator+(const String &, const char *);
	String operator+(const char *, const String &);
String operator+(const String &left, const String &right){   //String += String
	String temp1(left);
	String temp2(right);    //��ʼ������ʵ��
	temp1 +=temp2;
	return temp1;           //����String ����
}
String operator+(const String &left, const char *right){    //String += char*
	String temp1(left);
	//String temp2(right);    
	temp1 +=right;
	return temp1;           //����String ����
}
String operator+(const char *left, const String &right){     //Ҫ�� left��ǰ
	String temp1(left);
	String temp2(right);    
	temp1 +=temp2;
	return temp1;           //����String ����
}	
	
int main(int argc,char ** argv){

	//������ֻ����ֵ���ò��ܵ���ת�ƹ��캯����ת�Ƹ�ֵ����
	//********************** ��ֵ����&&����
	String str15 ("hello");             //���캯��(const char *)
	String str16 ("world");
	String str17(std::move(str15));     //��ֵ���캯��
	cout<<str17<<endl;
	cout<<"---------------------"<<endl;
	str15 = std::move(str16);            //��ֵ��ֵ����
	cout<<str15<<endl;
	
	return 0;
}
