#include <iostream>
#include <stack>
#include<string>
#include<fstream>
using namespace std;
class formatchecker {
	string arr;
	string sub(string arr, int start, int end)
	{
		char* temp = new char[end - start + 1];
		int i;
		for (i = start; i <= end; i++)
		{
			temp[i - start] = arr[i];
		}
		temp[i - start] = '\0';
		return temp;
	}
public:
	formatchecker()
	{
		
	}
	void setstring(ifstream& fin)
	{
		string temp;
		while (getline(fin, temp))
		{
			arr += temp;
		}
	}
	bool analizearr()
	{
		stack<string> s;
		int startind = 0;
		int endind = 0;
		bool tagend = false;
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] == '<')
			{
				if (arr[i + 1] == '\0')
					return false;

				if (arr[i + 1] != '/')
				{
					startind = i + 1;
				}
				else if (arr[i + 1] == '/')
				{
					startind = i + 2;
					tagend = true;
					i++;
				}
			}
			if (startind > 0 && arr[i + 1] != '\0')
			{
				if (arr[i + 1] == '>' && tagend)
				{
					endind = i;
					if (!s.empty() && !(s.top() == sub(arr, startind, endind)))
					{
						return false;
					}
					else
						s.pop();
					startind = 0;
					endind = 0;
					tagend = false;
					i++;
				}
				else if (arr[i + 1] == '>')
				{
					endind = i;
					s.push(sub(arr, startind, endind));
					startind = 0;
					endind = 0;
					i++;
				}

			}
		}
		return (s.empty());
	}
	~formatchecker()
	{

	}
};
int main()
{
	string filename = ("html.txt");
	ifstream fin(filename);
	if (fin.is_open())
	{
		formatchecker f;
		f.setstring(fin);
		if (f.analizearr())
			cout << "The html file is well formated.\n";
		else
			cout << "The html file is not well formatted.\n";
		fin.close();
	}
	else
		cout << "\nFile not opened\n";
	return 0;
}
