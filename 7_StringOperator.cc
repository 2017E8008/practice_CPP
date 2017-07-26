
//ʵ��Stinrg ���� ���캯���������= += == != > < >= <=�����������istream ostream������

#include <iostream>
//#include <String>    //�������ͷ�ļ�
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
	*_pstr='\0';
}

String::String(const char* pstr)
:_pstr(new char[strlen(pstr)+1])
{
	strcpy(_pstr,pstr);
}

String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr)+1])
{
	strcpy(_pstr,rhs._pstr);
}

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
	os << rhs._pstr<<endl;
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
	//**********************���캯������
	String str1;
    String str2("hello,world");
	String str3(str2);
	cout<<str1;
	cout<<str2;
	cout<<str3;
	cout<< String("---------------------");
	
	//***********************  = ���������
	const char *pstr="hello,world,cui";
	String str4=pstr;
	String str5=str4;
	cout<<str4;
	cout<<str5;
	cout<< String("---------------------");
	
	//********************** += ���������
	String str6("hello,");
	str6 +=str6;
	cout<<str6;
	str6 += "cuixuange";
	cout<<str6;
	cout<< String("---------------------");

	//********************** [] ���������
	String str7("Hello");
    const String str8("CUIXUANGE");
	cout<<str7[0]<<endl;             //�����ַ����������� ���ص�string���;  ������ϻ��з�
	cout<<str8[8]<<endl;
	cout<< String("---------------------");
	
	//********************** size c_str ��������
    cout << "size():"<<str8.size()<<endl;
	cout<<str8.c_str()<<endl;
	cout<< String("---------------------");
	
	//********************** == != > < >= <= ���������
	String str9="hello";
	String str10="Hello";
	cout<<"NOTE: true is 1 ; false is 0"<<endl;
	cout<<"==? "<<(str9==str10)<<endl;
	cout<<"!=? "<<(str9!=str10)<<endl;
	cout<<"> ? "<<(str9> str10)<<endl;
	cout<<"< ? "<<(str9< str10)<<endl;
	cout<<">=? "<<(str9>=str10)<<endl;
	cout<<"<=? "<<(str9<=str10)<<endl;
	cout<< String("---------------------");
	
	//********************** << >>��������� 
	String str11;
	cout<<"input something...."<<endl;
	cin>>str11;
	cout<<"cin:"<<str11;
	cout<< String("---------------------");   //���� << ��
	
	//********************** + ��������� 
	String str12;
	String str13("hello");
	String str14(",world");
	const char *pstr2=",world";
	str12 = str13 + str14;
	cout<<"string + string:       "<<str12;
	str12 =str13 + pstr2;
	cout<<"string + const char*: " << str12;
	str12 = pstr2 + str13 ;
	cout<<"const char* + string: " << str12;
 	
	return 0;
}
/*
1.��Ԫ����
���������� ���ɺ�����������ĳ�Ա����, ��Ԫ�� �� ���������Ԫ���� �ܹ�ֱ�ӷ��ʵ�ǰ���private ˽�г�Ա����

2.���������ԭ��
����������Ϊ�û��Զ�����ࡢö���ࣻ�����ԡ�������ǹ̶��ģ�һ�㲻���� && || ���߼������

3.�������ص������
��Ա���ʷ� .       ��Աָ���������� .*            ������� ::
��������� sizeof	         ����������� ?:

4.�����������ʽ
���ɺ�������operator  ���� + ��-������һ���µ�ʵ�� 
��Ԫ��������operator   �ܷ�����˽�г�Ա
��Ա��������operator  ���� ++ += ������һ��ʵ��������,��Ϊ��ֵһ���Ѿ�����,���ⷵ����ʵ�� ǳ�������� Ҳ�����Ч��

5.ǰ��++ ����++����
ǰ��++ ����this������   ;   ����++ ����this�ĸ��ƶ���
ǰ��++ �������ĵ�������ʹ�������ʹ��Ч��
ǰ��++�ͺ���++�����ͷ���ֵ���Ͳ�ͬ
����++��һ��(int)���Ͳ���������ʱ����������һ��0��Ϊ��(int)��ֵ

*/