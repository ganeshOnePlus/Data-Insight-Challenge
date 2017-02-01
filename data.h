#pragma once
//using namespace std;
#include <string>
class data
{
public:
	data(void);
	void ReadData(void);
	void ParseLine(std::string Line,std::string& NewOutput);// finds the text and date section in line
	//void rolling_average();
	//bool invalidChar(char c);
	//int count_unicode(int n);
	~data(void);
};

