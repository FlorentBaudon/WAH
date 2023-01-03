#include "CommandTools.h"

#include <string>
#include <iostream>
#include <array>
#include <filesystem>


using namespace std;

//using namespace subprocess;

int CommandTools::ExecuteCommand(string path, string cmd, string args)
{

	//const char* path = "D:/Unity_Installs/2021.3.14f1/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/platform-tools";
	
	filesystem::current_path(path);

	//std::string command("adb.exe");

	//std::string args("devices");

	string command = cmd + " " + args;


	std::array<char, 1024> buffer;
	std::string result;

	std::cout << "Opening reading pipe" << std::endl;
	FILE* pipe = _popen(command.c_str(), "r");
	if (!pipe)
	{
		std::cerr << "Couldn't start command." << std::endl;
		return 1;
	}
	while (fgets(buffer.data(), 128, pipe) != NULL) {
		std::cout << "Reading..." << std::endl;
		result += buffer.data();
	}
	auto returnCode = _pclose(pipe);

	std::cout << result << std::endl;
	std::cout << returnCode << std::endl;



	return returnCode;
}