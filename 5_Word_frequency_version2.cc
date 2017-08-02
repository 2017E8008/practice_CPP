//**********************************************�汾��  ֧�ֵ��ʲ�ѯ********
/*��ѯ�Ľ���Ǹõ��ʳ��ֵĴ��������г�ÿ�γ������ڵ��С�
���ĳ������ͬһ���ж�γ��֣�����ֻ��ʾ����һ�Ρ��кŰ�������ʾ��	
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::vector;
using std::ifstream;
using std::stringstream;
#define inputfilename "./The_Holy_Bible.txt"
class TextQuery
{
public:
	TextQuery(){};
	~TextQuery(){};
    void readFile(const string );
    void query(const string &);
private:
    vector<string> _lines;               //��˳�򱣴�ÿһ������
    map<string, set<int> > _word2Line;   //���浥�ʡ������к�
    map<string, int> _wordFreq;          //���浥�ʳ����ܴ���
	
	void erasePunct(string &s);             //ȥ�����
	void stringToLower(string &s);          //תΪСд
	bool isAllDigit(const string &s);  		//ȥ������
};
 void TextQuery::erasePunct(string &s)
{
    string::iterator it = s.begin();
    while(it != s.end())
    {
        if(ispunct(*it))
            it = s.erase(it);
        else
            ++it;
    }
}
void TextQuery::stringToLower(string &s)
{
    for(string::iterator it = s.begin();
        it != s.end();
        ++it)
    {
        if(isupper(*it))
            *it = tolower(*it);
    }
}
bool TextQuery::isAllDigit(const std::string &s)
{
    for(string::const_iterator it = s.begin();
        it != s.end();
        ++it)
    {
        if(!isdigit(*it))
            return false;
    }

    return true;
}
void TextQuery::readFile(const string filename){
	ifstream ifs(filename.c_str());
	string temp;
	stringstream ss;
	while(getline(ifs,temp)){
		_lines.push_back(temp);
	}
	cout<< "readfile ok" <<endl; 
	int count=0;
	for(auto & strline : _lines){
		ss << strline;
		while(ss >> temp){
			erasePunct(temp);         //ȥ�����
			stringToLower(temp);      //תΪСд
			if(isAllDigit(temp))      //ȥ������
			continue;	
			_word2Line[temp].insert(count);
			_wordFreq[temp]++;
		}
		count++;	
		ss.clear();     //��Ҫ��� ����ÿ��"\n"��Ȼ����ss����??????
	}
}
 
void TextQuery::query(const string & word){
	cout<< "total " << _wordFreq[word] << endl;
	for(auto & i : _word2Line[word]){
		cout<< i << " ";
		cout<<_lines[i]<<endl;
	}
	cout<<endl;
}
 
int main(int ac,char** av){
	 string filename = inputfilename;
	 TextQuery textquery;
	 textquery.readFile(filename);
	 // textquery.query("genesis"); 
	 textquery.query("10");
	 return 0;
 }