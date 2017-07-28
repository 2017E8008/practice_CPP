
/*
	String ��Copy_On_Write ����ʵ�֣� ����ѿռ�ʱ��������sizeof(cahr)��С�ռ����ڱ������ü���ֵ
	
	Proxy ģʽ����operator[]�������write(���ü����Լ�) , read���  ��������Effective C++
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String{
public:
    class CharProxy;         //������ ��������Ϊ��Ԫ

	String();
	~String();
	String(const char* pstr);

	String(const String &rhs);            //2�ָ�������
	String & operator = (const String & rhs);

	CharProxy operator[] (size_t idx);    //����[]
	friend std::ostream & operator<< (std::ostream &os ,const String &rhs);

	const char* c_str() const{
		return _pstr;
	}
	size_t size() const{
		return strlen(_pstr);
	}
	size_t refcount() const{         //��ȡ���ü���ֵ
		return _pstr[size()+1];
	}

private:
	void initRefcount(){             //���ü�������غ���
		_pstr[(size()+1)] = 1;
	}
	void increaseRefcount(){
		++ _pstr[size()+1];
	}
	void decreaseRefcount(){
		-- _pstr[size()+1];
	}
	char * _pstr;
};

String::String()
:_pstr(new char [2]){
	//cout << "string()" << endl;
	initRefcount();
}

String::String(const char * pstr)
:_pstr(new char[strlen(pstr) + 2]){
	//cout << "String(const char *)" << endl;
	strcpy(_pstr,pstr);
	initRefcount();               //strcopy,��ʼ��refcount=1
}

String::String(const String & rhs)
:_pstr(rhs._pstr){      //��������->ǳ����->rhsָ�븳ֵ
	increaseRefcount();
}

String & String::operator = (const String &rhs){
	if(this != &rhs){
		decreaseRefcount();
		if(refcount() == 0){    //ֻ�е�this->refcount��Ϊ0ʱ����ȥ������������Ŀռ�
			delete [] _pstr;
			cout<< "delete left _pstr" << endl;
		}
		_pstr = rhs._pstr;   //��������->ǳ����->rhsָ�븳ֵ
		increaseRefcount();
	}
	return *this;       //ע�ⷵ��ֵ
}

String::~String(){
	decreaseRefcount();
	if(refcount()==0){
		delete [] _pstr;
		cout<< "~String" << endl;
	}
}

std::ostream & operator<< (std::ostream & os,const String &rhs){
	os << rhs._pstr;
	return os;
}



//*************************************CharProxy����
class String::CharProxy{
public:
	CharProxy(String &, int );
	CharProxy & operator=(const char);
	friend std::ostream& operator<<(std::ostream &os, const CharProxy &rhs)
    {
        return os << rhs._mystr.c_str()[rhs._idx];    //���� _mystr[idx]�ݹ�;
    }
private:
	String & _mystr;     //********����һ������!!!! �����಻��Ҫ��������
	size_t _idx;
};

String::CharProxy::CharProxy(String & mystr, int idx)
:_mystr(mystr)
,_idx(idx){
    cout<<"String::CharProxy::CharProxy(String & mystr, int idx)() ok"<<endl;
}

String::CharProxy & String::CharProxy::operator=(const char c){
	if(_idx < _mystr.size()){
		if(_mystr.refcount()>1){          //�����µ�str�������ʱ
			_mystr.decreaseRefcount();
			char * ptmp = new char[_mystr.size()+2];
			strcpy(ptmp,_mystr._pstr);
			ptmp[_idx]=c;       		//д����
			_mystr._pstr=ptmp;          //ǳ����,ͬһ�����
			_mystr.initRefcount();
		}
		return (*this);
	}
	else{
		String str;
		static CharProxy nullchar(str,0);
		cout<< "Proxy Խ��" << endl;
		return nullchar;
	}
}

//��֤CharProxy����complete  string operator��Ҫ�����
String::CharProxy String::operator[] (size_t idx){

     return CharProxy(*this , idx);
}

int main(int argc,char** argv){
	//*****************************************************���Ը�������
	String str1;
	String str2("hello,world");
	String str3(str2);
	cout << "str1 = " << str2 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str1's refcount = " << str1.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	printf("&str1 = %p\n", str3.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	cout<<"----------------------------------"<<endl;
	str1 = str2;                       //str2 str3ָ����ַ��� ���ü���+1
	cout << "str1 = " << str2 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str1's refcount = " << str2.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	printf("&str1 = %p\n", str3.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	cout<<"----------------------------------"<<endl;
	String str4 = "wangdao";
	String str5(str4);         //��ʱstr4���ü���=2
	str4=str2;                  //��ʱstr2 �����ü���=4
	cout << "str2 = " << str2 << endl;
	cout << "str4 = " << str4 << endl;
	cout << "str5 = " << str5 << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str4's refcount = " << str4.refcount() << endl;
	cout << "str5's refcount = " << str5.refcount() << endl;
	printf("&str2 = %p\n", str2.c_str());
	printf("&str4 = %p\n", str4.c_str());
	printf("&str5 = %p\n", str5.c_str());
	//*************************************************����operator [] д����
	cout<<"----------------------------------"<<endl;
	str1[0] = 'X';
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;
	cout << "str1's refcount = " << str1.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	cout << "str4's refcount = " << str4.refcount() << endl;
	printf("&str1 = %p\n", str1.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	printf("&str4 = %p\n", str4.c_str());
	//*************************************************����operator [] ������
	cout<<"----------------------------------"<<endl;
	cout<<"read str2[0]"<<str2[0]<<endl;       //read str[2] ���ᷢ��COW��� refcout ���ı�
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;
	cout << "str1's refcount = " << str1.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	cout << "str4's refcount = " << str4.refcount() << endl;
	printf("&str1 = %p\n", str1.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	printf("&str4 = %p\n", str4.c_str());

	return 0;

}

/*
	1.˼�� private static ���������ü���ֵ�Ĵ������
	2.String ����[]�����޷�������ֵ����ֵ�жϡ�=��ֻ���ش�������󣬽���ֵ��ֵ�жϷ���������ڲ�,�ٴ����ش������ operator<<����ֵ������� operator=����ֵ�����
*/
