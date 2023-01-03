#pragma once

#include "json.hpp"

#include "CommandTools.h"

#include <iostream>
#include <fstream>

struct SDKDatas
{

};

class WAHUtils
{
public :
	static int Connect(std::string hubPath, std::string version, std::string ip)
	{
		std::string path = hubPath + version + "/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/platform-tools";
		//const char* path = "D:/Unity_Installs/2021.3.14f1/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/platform-tools";


		if (CommandTools::ExecuteCommand(path, "adb", "tcpip 5555") == 1)
		{
			return 1;

		}

		if (CommandTools::ExecuteCommand(path, "adb", "connect " + ip) == 1)
		{
			return 1;
		}

		return 0;

	}

	static void ReadJSON(std::string& hubPath, std::vector<std::string>& versions)
	{
		using json = nlohmann::json;

		std::ifstream file("config.json");
		if (file.is_open())
		{
			json data = json::parse(file);

			hubPath = data["HubPath"];

			for(int i = 0; i<data["SDKVersions"].size(); i++) 
			{
				versions.push_back(data["SDKVersions"][i]);
			};
		}
		else 
		{
			std::cout << "can't open config.json" << std::endl;
		}
	}

	static void KillAllAdbServer(const std::string& hubPath, const std::vector<std::string>& versions)
	{

		for (int i = 0; i < versions.size(); i++)
		{
			std::string path = hubPath + versions[i] + "/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/platform-tools";
			CommandTools::ExecuteCommand(path, "adb", "kill-server");
		}
	}
};
