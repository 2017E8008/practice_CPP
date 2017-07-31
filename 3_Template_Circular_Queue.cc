#include <iostream>
using std::cout;
using std::endl;
//#define MaxSize 10

template <typename T, int MaxSize = 10>
class queue{
private:
	T * _member;
	unsigned int _front;
	unsigned int _rear;
public:
	queue();
	~queue();
	void push (const T &);
	void pop();
	T & front();
	T & back();
	bool empty() const;
	bool full() const;
};

template <typename T , int MaxSize>   //��Ա�������ⶨ�嶼��Ҫ����template �Լ� class <>
queue<T,MaxSize>::queue()
:_front(0)
,_rear(0)
,_member(new T[MaxSize]){}

template <typename T , int MaxSize>
queue<T,MaxSize>::~queue(){
		delete [] _member;
}

template <typename T , int MaxSize>
void queue<T,MaxSize>::push(const T & value){
	if((_rear+1)%MaxSize == _front) cout<<"��������"<<endl;
	else{
		_member[_rear]=value;
		_rear = (_rear+1)%MaxSize;
	}
}

template <typename T , int MaxSize>
void queue<T,MaxSize>::pop(){
	if(_rear == _front)  cout<<"����Ϊ��"<<endl;
	else _front = (_front+1)%MaxSize;
}

template <typename T , int MaxSize>
T & queue<T,MaxSize>::front(){
	if(_rear != _front) return _member[_front];
}

template <typename T , int MaxSize>
T & queue<T,MaxSize>::back(){
	 //����Ԫ�ز���pop,push��rear==0ʱ,rear-1��Ϊ����
	if(_rear != _front) return _member[(_rear-1+MaxSize)%MaxSize];
}

template <typename T , int MaxSize>
bool queue<T,MaxSize>::empty() const{
	return _rear == _front?true:false;
}

template <typename T , int MaxSize>
bool queue<T,MaxSize>::full() const{
	return (_rear+1)%MaxSize == _front;
}

//***********************�Զ���������
class Xvalue{
private:
	int _xnum;
public:
	Xvalue();
	Xvalue(int );
	friend std::ostream & operator<<(std::ostream &, const Xvalue &rhs);
};
//���޲εĹ��캯�������ϵĻ�,��template  _arr(new T[kSize]()�г���
//error: no matching function for call to ��X::X()��  , _arr(new T[kSize]())
Xvalue::Xvalue(){}

Xvalue::Xvalue(int xnum)
:_xnum(xnum){}

//��Ԫ���� ���ǳ�Ա���� operator<<()  ���ܼ���Xvalue������
std::ostream & operator<<(std::ostream & oss,const Xvalue & rhs){
	oss<< rhs._xnum ;
	return oss;
}


void test0(){
	queue<int> queueInt;
	cout<<"�����Ƿ�Ϊ��?"<<" "<<queueInt.empty()<<endl;
	queueInt.push(1);
	cout<<"�����Ƿ�Ϊ��?"<<" "<<queueInt.empty()<<endl;
	for(int idx=2;idx!=11;++idx){
		queueInt.push(idx);
	}
	
	cout << "��ʱ�����Ƿ�����?" << queueInt.full() << endl;
	while(!queueInt.empty()){
		cout << queueInt.front() << " ";
		queueInt.pop();
	}
	cout << "��ʱ�����Ƿ�Ϊ��?" << queueInt.empty() << endl;
	return ;
}

void test1(){
	queue<Xvalue> queueX;
	cout<<"�����Ƿ�Ϊ��?"<<" "<<queueX.empty()<<endl;
	queueX.push(Xvalue(1));
	cout<<"�����Ƿ�Ϊ��?"<<" "<<queueX.empty()<<endl;
	for(int idx=2;idx!=11;++idx){
		queueX.push(Xvalue(idx));
	}
	
	cout << "��ʱ�����Ƿ�����?" << queueX.full() << endl;
	while(!queueX.empty()){
		cout << queueX.front() << " ";
		queueX.pop();
	}
	cout << "��ʱ�����Ƿ�Ϊ��?" << queueX.empty() << endl;
	return ;
}

int main(int argc,char** argv){
	//test0();
	test1();
	
	return 0;
}

