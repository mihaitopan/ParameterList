#include "Debug.h"
#include "RawTester.h"
#include "ReadPL.h"
#include "WritePL.h"
#include <iostream>

int main(int argc, char *argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// rawTester();

	// help
	if (argc == 2 && std::string(argv[1]) == "-help") {
		std::cout << "\t-help\n";
		std::cout << "\tread <fisier_intrare> <id> <tip> <fisier_iesire>\n";
		std::cout << "\twrite <fisier_intrare> <fisier_iesire> <id> <tip> <continut>\n";
		return 0;
	}

	// read
	if (argc == 6 && std::string(argv[1]) == "read") {
		try { // verify id to be integer
			int a = stoi(std::string(argv[3])); a;
		} catch (...) {
			std::cout << "id should be an integer" << std::endl;
			return 1;
		}
		ReadPL rpl = ReadPL{};
		rpl.setInputFile(argv[2]);
		rpl.setID(stoi(std::string(argv[3])));
		rpl.setType(std::string(argv[4]));
		rpl.setOutputFile(argv[5]);

		try {
			rpl.run();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		return 0;
	}

	// write
	if (argc == 7 && std::string(argv[1]) == "write") {
		try { // verify id to be integer
			int a = stoi(std::string(argv[4])); a;
		} catch (...) {
			std::cout << "id should be an integer" << std::endl;
			return 1;
		}
		WritePL wpl = WritePL{};
		wpl.setInputFile(argv[2]);
		wpl.setOutputFile(argv[3]);
		wpl.setID(stoi(std::string(argv[4])));
		wpl.setType(std::string(argv[5]));
		wpl.setContent(std::string(argv[6]));

		try { 
			wpl.run();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		return 0;
	}

	std::cout << "Invalid arguments\n";
	std::cout << "\t see -help\n";
	return 1;
}
