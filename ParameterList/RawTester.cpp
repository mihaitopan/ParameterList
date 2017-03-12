#include "RawTester.h"
#include "ParameterList.h"
#include <iostream>
#include <assert.h>

void rawTester() {
	std::vector<unsigned char> buffer;
	ParameterList plpl = ParameterList();

	/* save to buffer */ {
		ParameterList pl = ParameterList();
		pl.Add(0, 3);
		std::string s = "akjsdb";
		pl.Add(3, s);
		std::vector<unsigned char> value;
		value.push_back('s');
		value.push_back('b');
		value.push_back('t');
		pl.Add(1, value);
		/* -- */ plpl.Add(4, pl);
		pl.SaveToBuffer(buffer);
	}

	/* -- */ {
		ParameterList pl = ParameterList();
		plpl.Get(4, pl);
		pl.SaveToBuffer(buffer);
	}

	/* load from buffer */ {
		ParameterList pl = ParameterList();
		pl.LoadFromBuffer(buffer);
		int a;
		pl.Get(0, a);
		assert(a == 3);
		std::string ss;
		pl.Get(3, ss);
		assert(ss == "akjsdb");
		std::vector<unsigned char> valuev;
		pl.Get(1, valuev);
	}
}
