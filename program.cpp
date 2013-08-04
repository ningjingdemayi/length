#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;



template <class Type>  Type stringToNum(const string& str)  
{  
  istringstream iss(str);  
	Type num;  
	iss >> num;  
	return num;      
}  

class Rule{

public:
	Rule(string & _nameSingle , float _rule)
		: nameMulti(_nameSingle), nameSingle(_nameSingle) , rule(_rule)
	{
		if(nameSingle == "inch")
		{
			nameMulti.append("es");
		}
		else if(nameSingle == "foot")
			nameMulti = "feet";
		else
			nameMulti.push_back('s');
	}

	void printRule()
	{
		cout << this->nameSingle << "(" << this->nameMulti << "):" << rule << endl;
	}

	bool operator == (string &str)
	{
		if(str == nameSingle || str == nameMulti)
			return true;
		return false;
	}
private:
	string nameSingle;
	string nameMulti;
public:
	float rule;
};

class Exepssion
{

public:
	Exepssion();
	void addExp(string & exp)
	{
		this->exps.push_back(exp);
	}

private:
	vector<string> exps;
};


template< typename T> void printVector(T & rules)
{
	T::iterator it = rules.begin();
	while(it != rules.end())
	{
		it->printRule() ;
		++ it;
	}
}

vector<Rule> rules;
vector<float> rslts;

float parseRule(string & exp)
{
	vector<Rule>::iterator it = rules.begin();
	while(it != rules.end() )
	{
		if(*it == exp)
			return it->rule;
		++ it;
	}
	return 0;
}

struct oprt
{
	char op;
	int index;
};

float calc(char * buf)
{
	float rslt = 0;
	vector<oprt> oprts;
	unsigned int i = 0;
	while(buf[i] != '\0')
	{
		if(buf[i] == '-' || buf[i] == '+')
		{
			oprt oprttemp ;
			oprttemp.index = i;
			oprttemp.op = buf[i];
			oprts.push_back(oprttemp);
		}
		i ++ ;
	}

	string temp = buf;
	if(oprts.size() == 0)
	{
		string tt1 = temp.substr(0 ,temp.find_first_of(' '));
		string tt2 = temp.substr(temp.find_first_of(' ') + 1 , temp.size());
		float t1 = stringToNum<float>(temp.substr(0 ,temp.find_first_of(' '))) ;
		float t2 = parseRule(temp.substr(temp.find_first_of(' ') + 1 , temp.size()));
		//rslt += stringToNum<float>(temp.substr(0 ,temp.find_first_of(' '))) * parseRule(temp.substr(temp.find_first_of(' ') + 1 , temp.size()));
		rslt += t1 * t2;
		return rslt;
	}
	if(1)
	{
		string tt1 = temp.substr(0 ,temp.find_first_of(' '));
		string tt2 = temp.substr(temp.find_first_of(' ') + 1 , temp.size());
		string tt3 = tt2.substr(0 , tt2.find_first_of(' '));
		float t1 = stringToNum<float>(temp.substr(0 ,temp.find_first_of(' '))) ;
		float t2 = parseRule(tt3);
		rslt += t1 * t2;
	}
	string temp2 = temp;
	for(i = 0 ;i < oprts.size() ; i ++)
	{
		temp = temp2.substr(oprts[i].index + 2 , temp.size());
		if(oprts[i].op == '+')
		{
			//string tt1 = temp.substr(0 ,temp.find_first_of(' '));
			string tt1 = temp.substr(0 , temp.find_first_of(' '));
			//string tt2 = temp.substr(temp.find_first_of(' ') + 1 , oprts[i].index - 3);/
			string tt2 = temp.substr(temp.find_first_of(' ') + 1 , temp.size());
			float t1 = stringToNum<float>(tt1) ;
			float t2 = 0;
			if(i + 1 >= oprts.size())
				t2 = parseRule(tt2);
			else
				t2 = parseRule(tt2.substr(0 , tt2.find_first_of(' ')));
			rslt += t1 * t2;
		}
		if(oprts[i].op == '-')
		{
			//string tt1 = temp.substr(0 ,temp.find_first_of(' '));
			string tt1 = temp.substr(0 , temp.find_first_of(' '));
			//string tt2 = temp.substr(temp.find_first_of(' ') + 1 , oprts[i].index - 3);/
			string tt2 = temp.substr(temp.find_first_of(' ') + 1 , temp.size());
			float t1 = stringToNum<float>(tt1) ;
			float t2 = 0;
			if(i + 1 >= oprts.size())
				t2 = parseRule(tt2);
			else
				t2 = parseRule(tt2.substr(0 , tt2.find_first_of(' ')));
			rslt -= t1 * t2;
			//rslt -= stringToNum<float>(temp.substr(0 ,temp.find_first_of(' '))) * parseRule(temp.substr(temp.find_first_of(' ') + 1 , i ));
		}
	}

	return rslt;
}

int main()
{
	char buf[64] = "";

	ifstream infile;
	infile.open("input.txt");
	
	//read Rules
	while(infile.getline(buf , 64))
	{
		string temp = buf;
		if(temp == "")
			break;
		string nameSingle = temp.substr(2 ,temp.find_first_of('=') - 3);
		temp = temp.substr(temp.find_first_of('='));
		string ruleStr = temp.substr(2 , temp.find_first_of('m') - 3);
		float rule = stringToNum<float>(ruleStr);
		rules.push_back(Rule(nameSingle , rule));

		//cout << rule << endl;
		//cout << nameSingle<< ruleStr << "m"  << endl;;
	}

	stringstream sss;
	sss << "ningjingliujie@126.com" << endl << endl;
	cout << "ningjingliujie@126.com" << endl << endl;


	//calculate results
	while(infile.getline(buf , 64))
	{
		string temp = buf;
		sss <<  calc(buf) << " m" << endl;
		cout << calc(buf) << " m" << endl;
	}
	infile.close();

	ofstream ofile;
	ofile.open("output.txt");
	ofile << sss.str();
	ofile.close();

	//printVector(rules);	
	getchar();
	return 0;
}
