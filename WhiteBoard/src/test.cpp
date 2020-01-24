


#include <iostream>
#include <vector>
#include <string.h>
#include <Windows.h>
using namespace std;

void ConvertWCtoC(wchar_t* str, char* str2 , int size)
{
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, str2, size+2, NULL, NULL);
}


int main() {

	wchar_t* s = L"dfsffef";
	char s2[100];
	ConvertWCtoC(s,s2,7);
	cout << s2 << endl;
	//cout << typeid(s2).name() << endl;

}