
//ģ����Heapsort  HeapSort<int>  HeapSort<�Զ�����> ���ж��������

#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

template <typename T >
class HeapSort{
public:
    HeapSort(T * arr, int size);   
	void shift(T  r[], int k, int m);	
    void heapAdjust(); 
private:
	T * & _arr;
	int _size;
};

template <typename T >
HeapSort<T>::HeapSort(T * arr, int size)
:_arr(arr)
,_size(size){
	for (int i = _size / 2; i > 0; i--)  //����
        shift(_arr, i, _size);
    for (int j = _size; j > 0; j--)
    {
        T temp = _arr[j];
        _arr[j] = _arr[1];
        _arr[1] = temp;
        shift(_arr, 1, j - 1);  //��ǰ���ֵ����Ƶ��������,������ ǰj-1��Ԫ��
    }
}

template <typename T >
void HeapSort<T>::shift(T r[], int k, int m)
{//Ҫɸѡ�Ľڵ���Ϊk���������һ���ڵ�Ϊm
    int i, j;
	T	temp;
    i = k;
    j = 2*i;  //���Ϊk�Ľڵ������
    temp = r[i];//��ɸѡ��¼�ݴ�(��Ҫ������λ��)
    while(j<=m)//ɸѡ��û���е���Ҷ��
    {
        if(j<m && r[j]<r[j+1])//j<m˵��i�ڵ㻹��һ���Һ��ӣ�Ϊ���Ƚڵ�
        {
            j++;//i���������ӣ�ȡ����
        }

        //һ�����ӻ������ӱ��Һ��Ӵ�
        if(r[i] > r[j])
        {
            break;//���ӱȸ���С
        }

        else//���ӱȸ��״�
        {
            r[i] = r[j];//���ϴ�Ľڵ��Ƶ����ϡ�
            i = j;
            j = 2*i;
            //��iָ�򽻻���λ�ã�Ϊ��һ���ƶ���׼����
        }
        r[i] = temp;//��ɸѡ��¼�Ƶ���ȷλ��
    }
}

//***********************************************************Point����
class Point
{
public:
	/*     //�ṩ�޲�(������Ĭ�ϳ�ʼֵ)�Ĺ��캯��,����template��ʼ��error
	Point()
	:_ix(0)
	,_iy(0){}
	*/
	Point(int ix=0, int iy=0)
	: _ix(ix)
	, _iy(iy)
	{}

	friend std::ostream & operator<<(std::ostream & os, const Point &rhs);
	friend bool operator<(const Point & lhs, const Point & rhs);
	friend bool operator>(const Point & lhs, const Point & rhs);

	float distance() const
	{
		return sqrt(_ix * _ix + _iy * _iy);
	}

private:
	int _ix;
	int _iy;
};

std::ostream & operator<<(std::ostream & os, const Point &rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

bool operator<(const Point & lhs, const Point & rhs)
{
	return lhs.distance() < rhs.distance();
}

bool operator>(const Point & lhs, const Point & rhs)
{
	return lhs.distance() > rhs.distance();
}


void test_int(){
	int size=10;
    int a[] = {0,4,5,8,2,1,6,7,9,10,3};    //a[0]����������
    cout << "�󶥶�����ǰ������:" << endl;
    for (int i = 1; i <= size; i++)
    {
       cout << a[i] << "  ";
    }
    HeapSort<int>(a, size);
	cout<<endl;
    cout << "�󶥶�����������:" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << a[i] << "  ";
    }
	cout<<endl;
}

void test_Point(){
	int size=10;
    Point a[] = {Point(0,0),Point(1,1),Point(2,2),Point(-1,-1),Point(-2,2),Point(3,3),Point(5,5),Point(7,7),Point(4,4),Point(6,6),Point(0,1)};    //a[0]����������
    cout << "�󶥶�����ǰ������:" << endl;
    for (int i = 1; i <= size; i++)
    {
       cout << a[i] << "  ";
    } 
     HeapSort<Point>(a, size);        
	cout<<endl;
    cout << "�󶥶�����������:" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << a[i] << "  ";
    }
	cout<<endl;
}

int main(){
	//test_int();
	
	test_Point();
    return 0;
}