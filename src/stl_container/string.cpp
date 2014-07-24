#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str;

	/* --- append --- */
	str = "hoge";
	cout << str.append("fuga") << '/' << str << endl;
	// hogefuga/hogefuga

	/* --- insert --- */
	str = "hoge";
	cout << str.insert(2, "fuga") << '/' << str << endl;
	// hofugage/hohugage
	
	/* --- substr --- */
	str = "abcdefghijklmn";
	cout << str.substr(3,7) << '/' << str << endl;
	// defghij/abcdefghijklmn
	
	/* --- find, rfind --- */
	str = "hogefugahogefugahogefuga";
	cout << str.find("fuga") << '/' << str.find("fuga",6) << endl;
	// 4/12
	cout << str.rfind("fuga") << '/' << str.rfind("fuga",18) << endl;
	// 20/12

	/* --- find_first_of, find_last_of --- */
	str = "abcdefghijk";
	size_t pos = 0;
	while ((pos = str.find_first_of("aiueo", pos)) != string::npos)
		str[pos++] = '*';
	cout << str << endl;
	// *bcd*fgh*jk

	/* --- find_first_not_of, find_last_not_of --- */
	str = "abcdefghijk";
	pos = 0;
	while ((pos = str.find_first_not_of("aiueo", pos)) != string::npos)
		str[pos++] = '*';

	cout << str << endl;
	// a***e***i**

	/* replace */
	str = "hogehoge";
	cout << str.replace(2, 4, "_fugafuga_") << '/' << str << endl;
	// ho_fugafuga_ge/ho_fugafuga_ge
}
