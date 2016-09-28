#include "Debug.h"
#include "ParameterList.h"
#include <iostream>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	std::vector<unsigned char> buffer;
	ParameterList plpl = ParameterList();

	// save to buffer
	{
		ParameterList pl = ParameterList();

		pl.Add(0, 3);

		std::string s = "akjsdb";
		pl.Add(3, s);

		std::vector<unsigned char> value;
		value.push_back('s');
		value.push_back('b');
		value.push_back('t');
		pl.Add(1, value);

		// -- //
		plpl.Add(4, pl);
		// -- //

		pl.SaveToBuffer(buffer);
		std::cout << "Buffer: ";
		for (std::vector<unsigned char>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
			std::cout << *it;
		}
		std::cout << std::endl;
	}

	// -- //
	{
		ParameterList pl = ParameterList();
		plpl.Get(4, pl);
		pl.SaveToBuffer(buffer);
		std::cout << "Buffer: ";
		for (std::vector<unsigned char>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
			std::cout << *it;
		}
		std::cout << std::endl;
	}
	// -- //

	// load from buffer
	{
		ParameterList pl = ParameterList();
		pl.LoadFromBuffer(buffer);

		int a;
		pl.Get(0, a);
		std::cout << a << " ";

		std::string ss;
		pl.Get(3, ss);
		std::cout << ss << " ";

		std::vector<unsigned char> valuev;
		pl.Get(1, valuev);
		for (std::vector<unsigned char>::iterator it = valuev.begin(); it != valuev.end(); ++it) {
			std::cout << ' ' << *it;
		}
	}

	getchar();
	return 0;
}
