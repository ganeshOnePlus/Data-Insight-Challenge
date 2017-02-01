#include "data.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

data::data(void)
{
}

void data::ReadData()
{
	std::ifstream readtweetfile;
	std::ofstream writetweetfile;
	readtweetfile.open("tweets.txt");
	writetweetfile.open("ft1.txt");
	std::string output;
	std::string NewOutput;
	int unicode_count = 0;

	if (readtweetfile.is_open()) 
	{
		while (!readtweetfile.eof()) 
		{
			getline(readtweetfile,output); 
			ParseLine(output,NewOutput);  

			if(NewOutput!=" ")
			{
			
			std::string firstChar="Check";
			std::string secondChar;
			std::string checkingChar="";
			for (std::string::iterator it = NewOutput.begin(), end = NewOutput.end(); it != end; ++it)
			{
				if(firstChar=="Check")
					firstChar = *it;
				else
				{
					secondChar = *it;
					checkingChar = firstChar + secondChar;

					if(checkingChar=="\\\"")
					{
						writetweetfile << secondChar ; 
						firstChar="Check";
						continue;
					}
					else if(checkingChar=="\\/")
					{
						writetweetfile << secondChar; 
						firstChar="Check";
						continue;
					}
					else if(checkingChar=="\\\'")
					{
						writetweetfile << secondChar; 
						firstChar="Check";
						continue;
					}
					else if(checkingChar=="\\\n")
					{
						writetweetfile << " " ; 
						firstChar="Check";
						continue;
					}
					else if(checkingChar=="\\\t")
					{
						writetweetfile <<  " "; 
						firstChar="Check";
						continue;
					}
					else if(checkingChar=="\\  ")
					{
						writetweetfile <<  " "; 
						firstChar="Check";
						continue;
					}
					
					else if(checkingChar=="\\\\")
					{
						writetweetfile << secondChar;
						firstChar="Check";
						continue;
					}

					writetweetfile << firstChar; 
					firstChar=secondChar;

					if(checkingChar!="\\u")
					{
						writetweetfile << secondChar;
						firstChar="Check";
						continue;
				
					}
				}	
			}
			unicode_count++;
		}
			writetweetfile << std::endl ;
		}
	}
	writetweetfile << std::endl << unicode_count <<" tweets contained unicode.";
	readtweetfile.close();
	writetweetfile.close();
}

void data::ParseLine(std::string Line,std::string &NewOutput)
{
	std::string Text="";
	std::string Textvalue="";
	std::string CreatedAt;

	int PositionOfCreatedAt=15;
	char* test="";
	CreatedAt= Line.substr (PositionOfCreatedAt,30); 
	Line.erase(0,109);								 
	std::string firstChar="Check";
	std::string secondChar;
	std::string checkingChar="";	

	for (std::string::iterator it = Line.begin(), end = Line.end(); it != end; ++it)
	{
		if(firstChar=="Check")
			firstChar = *it;
		else
		{
			secondChar = *it;
			checkingChar = firstChar + secondChar;

			if(checkingChar!="\",")
			{
				Text+=firstChar;

			}
			firstChar=secondChar;
		}	
		

		if(checkingChar=="\",")
			break;
	}

	std::string check =CreatedAt.substr (3,1);

	if(check==" ")
	{
		NewOutput=Text+" (timestamp: "+CreatedAt+"))";
	}
	else
	{
		NewOutput=" ";
	}
}

data::~data(void)
{
}

//void data::rolling_average()
//{
//
//}
