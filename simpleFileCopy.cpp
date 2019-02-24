#include <iostream>
#include <fstream>

using namespace std;

const char *path = "C:\Users\hejmi\source\repos\Project11\Project11";

int main()
{
	/*Jesus christ this is so simple that it should be illegal*/
	ifstream fin("gil.jpg", ios::binary);
	ofstream out("copy.jpg", ios::binary);
	out << fin.rdbuf();

	fin.close();
	out.close();
	while (1);
}
