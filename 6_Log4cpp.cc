
//g++ log4cpp.cc  -llog4cpp -lpthread  -std=c++11

//����ģʽ�µ�log4cpp�򵥷�װ
//log4cpp PatternLayout(���������ʽ) FileAppender(��������ļ���ʽ)  Category(��־����),add ��������appender

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using namespace log4cpp;
#define RollingFileName "roll_log4cpp.log"

class Mylog4cpp{
public:
	static Mylog4cpp * getInstance(){            //����ģʽ
		if(_instance==NULL)
			_instance = new Mylog4cpp();
		return _instance;
	}
	~Mylog4cpp();
	void logInfo (const string & Message);	  
	void logError(const string & Message);
	void logWarn (const string & Message);
	void logDebug(const string & Message);
private:
	Category & _root;                   //���ñ������ٴθ���root����
private:
	static Mylog4cpp * _instance;
	Mylog4cpp();
};

Mylog4cpp * Mylog4cpp::_instance=NULL;          //��̬��Ա�����ʼ��

Mylog4cpp::Mylog4cpp()
:_root(Category::getRoot())
{
	PatternLayout * _ptnLyout = new PatternLayout();
	_ptnLyout->setConversionPattern("%d{%Y/%m/%d %H:%M:%S} [%5p] :%m%n");             //PatternLayout���岼�ָ�ʽ 
	RollingFileAppender * _rollingFileAppender = new RollingFileAppender("rollingFileAppender", RollingFileName,5 * 1024,2) ; //���ûؾ��ʽfileappender
	_rollingFileAppender->setLayout(_ptnLyout);
	
	_root.addAppender(_rollingFileAppender);   //���Զ��add��ͬ���͵�appender ʵ����ͬ�����
	_root.setPriority(Priority::DEBUG);
}

Mylog4cpp::~Mylog4cpp(){
	//delete _ptnLyout;
	//delete _rollingFileAppender;
	Category::shutdown();
}

void Mylog4cpp::logInfo (const string & Message){
	string Message2=Message;
	Message2 += __FILE__;
	Message2 += ".";
	Message2 += __FUNCTION__;
	Message2 += ".";
	Message2 += std::to_string(__LINE__);
	_root.info(Message2);     
}		
void Mylog4cpp::logError (const string & Message){
	string Message2=Message;
	Message2 += __FILE__;
	Message2 += ".";
	Message2 += __FUNCTION__;
	Message2 += ".";
	Message2 += std::to_string(__LINE__);
	_root.error(Message2);      
}
void Mylog4cpp::logWarn (const string & Message){
	string Message2=Message;
	Message2 += __FILE__;
	Message2 += ".";
	Message2 += __FUNCTION__;
	Message2 += ".";
	Message2 += std::to_string(__LINE__);
	_root.warn(Message2);      
}
void Mylog4cpp::logDebug (const string & Message){
	string Message2=Message;
	Message2 += __FILE__;
	Message2 += ".";
	Message2 += __FUNCTION__;
	Message2 += ".";
	Message2 += std::to_string(__LINE__);	
	_root.debug(Message2);     
}

int main(void)
{
    Mylog4cpp *mylog4cpp1=Mylog4cpp::getInstance();           //����ģʽ����
	Mylog4cpp *mylog4cpp2=Mylog4cpp::getInstance();
	Mylog4cpp *mylog4cpp3=Mylog4cpp::getInstance();
	Mylog4cpp *mylog4cpp4=Mylog4cpp::getInstance();
	cout<<"addr1: "<< mylog4cpp1<<endl;
	cout<<"addr1: "<< mylog4cpp2<<endl;
	cout<<"addr1: "<< mylog4cpp3<<endl;
	cout<<"addr1: "<< mylog4cpp4<<endl;
	
	for(size_t idx = 0; idx != 10; ++idx)
	{
		ostringstream oss;
		oss <<"  "<<__FUNCTION__<<".";
		mylog4cpp1->logInfo(oss.str());
		mylog4cpp2->logError(oss.str());
		mylog4cpp3->logWarn(oss.str());
		mylog4cpp4->logDebug(oss.str());
	}
	return 0;
}
