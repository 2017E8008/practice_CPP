#include <iostream>
#include <string.h>    //���������ַ����Ĵ�����
using std::cout;
using std::endl;

class string{
public:
	string();
	string(const char* pstr);
	string(const string & rhs);
	string & operator=(const string & rhs);
	~string();
	void print();
private:
	char *_pstr;
};

string::string()
:_pstr(new char [1])
{
	//*_pstr='\0';
	cout<< "string()"<<endl;
}

string::string(const char* pstr)             //�������Ĺ��캯����ʼ��
:_pstr(new char [strlen(pstr)+1])
{
	cout<< "string(const char* pstr)"<<endl;
	strcpy(_pstr,pstr);
}

string::string(const string & rhs)       //���ƹ��캯��  ����ĸ���
:_pstr(new char [strlen(rhs._pstr)+1])
{
	cout<< "string(const string & rhs)"<<endl;
	strcpy(_pstr,rhs._pstr);                
}

#if 0
string & string::operator=(const string & rhs)
{
	cout<< "string & operator=(const string & rhs)"<<endl;
	_pstr=new char [strlen(rhs._pstr)+1];    //��ʼ�����ʽֻ�����ڹ��캯����ʼ����Ա����
	strcpy(_pstr,rhs._pstr);                  //strcpyh�Ჹ��'\0'
}
#endif

string & string::operator=(const string & rhs)
{
	if(this != &rhs) //1. �����Ը���
	{
		delete [] _pstr;//2. ������������Ŀռ�,�������¶���ռ��С
		_pstr = new char[strlen(rhs._pstr) + 1]();//3. ��ȥ�������
		strcpy(_pstr, rhs._pstr);
	}
	return *this;
}


string::~string()
{
	delete  _pstr;
	_pstr=NULL;                            //�������Ұָ��
	cout<<"~string() ok"<<endl;
}

void string::print(){
	cout<<"str = "<< _pstr <<endl;
}

int main(int argc,char** argv)
{
	string str1;
	str1.print();                        //�޲����Ĺ��캯��
	
	string str2 = "Hello";    
	string str3("world");                //�������Ĺ��캯��
	
	str2.print();		
	str3.print();	
	
	string str4 = str3;    // ������ƹ��캯��     ����(const ���� & rhs)
	str4.print();
	
	str4 = str2;     //�����������        ���� & operator=(const ���� & rhs)
	str4.print();
	
	return 0;
}