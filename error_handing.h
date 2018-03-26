#include <string>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// error() simply disguises throws:
inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
	error(s + s2);
}

inline void error(const string& s, int i)
{
	ostringstream os;
	os << s << ": " << i;
	error(os.str());
}
#if _MSC_VER<1500
// disgusting macro hack to get a range checked string:
#define string String
// MS C++ 9.0 have a built-in assert for string range check
// and uses "std::string" in several places so that macro substitution fails
#endif

template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
	void* addr = &i;	// get the address of the first byte
						// of memory used to store the object
	return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}
