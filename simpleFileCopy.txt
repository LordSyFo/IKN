#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

const char *path = "C:\Users\hejmi\source\repos\Project11\Project11";
string findField(const string field, string mes);

int main()
{
	/*Jesus christ this is so simple that it should be illegal*/
	ifstream fin("gil.jpg", ios::binary);
	ofstream out("copy.jpg", ios::binary);
	stringstream sstr;
	stringstream newsstr;
	string str;

	/*Read file binary into string*/
	sstr << fin.rdbuf();			//Read into stream first since its native with filestream
	str = sstr.str();				//Convert to string

	/*Send size here*/

	/*Send file*/
	size_t sendSize = 1000;
	double len = str.length();
	double iterations = ceil(len / sendSize); /*Round up*/
	string newstr;

	for (size_t i = 0; i < iterations*sendSize; i+= sendSize)
	{
		if (i + sendSize > len)
		{
			newstr.append(str.substr(i, (size_t)len));
			cout << "Sent " << i << " to " << len << endl;
		} else
		{ 
			newstr.append(str.substr(i, sendSize));
			cout << "Sent " << i << " to " << i + sendSize << endl;
		}
	}

	cout << newstr.length();
	out << newstr;

	/*Handling of headers*/
	string header_example = "Request: /somefile\n"
							"Content: something\n"
							"Size: 10029\n";

	cout << stoi(findField("Size:",header_example)) << endl;

	fin.close();
	out.close();
	while (1);
}

string findField(const string field, string mes) {
	size_t start = mes.find(field);
	size_t end = mes.find('\n', start);
	return mes.substr(start + field.length(),end - (start + field.length()));
}
