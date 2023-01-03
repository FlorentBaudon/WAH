#pragma once

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>
#include <chrono>

#include "CommandTools.h"

int connect()
{
	//const char* path = "C:\\Program Files\\Unity\\Hub\\Editor\\2022.2.1f1\\Editor\\Data\\PlaybackEngines\\AndroidPlayer\\SDK\\platform-tools\\adb.exe";
	const char* path = "D:/Unity_Installs/2021.3.14f1/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/platform-tools";

	if (CommandTools::ExecuteCommand(path, "adb", "tcpip 5555") == 1)
	{
		return 1;
		//CommandTools::ExecuteCommand(path, "adb", "connect");
	}

	return 0;

}



int main(int argc, char* argv[])
{
	float wWidth = 500, wHeight = 300;	// Window size
	
	bool bIPEdit = 0, bSDKSelect = 0;
	int sdkActive = 0;
	char* sdkUnityVersions = "2020.3.43f1;2021.3.16f1;2022.2.1f1";

	char ipAddress[32] = "127.0.0.1";

	InitWindow(wWidth, wHeight, "WAD");

	int errorCode = -1;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		int viewportOffset = 200;

		GuiGroupBox(Rectangle{ 5, 5, wWidth - 10, wHeight - 52 }, "Settings");

		if (GuiTextBox(Rectangle{ 10, 10, 120, 24}, ipAddress, 32, bIPEdit))	bIPEdit = !bIPEdit;

		if (GuiDropdownBox(Rectangle{ 10, 39, 120, 24 }, sdkUnityVersions, &sdkActive, bSDKSelect))	bSDKSelect = !bSDKSelect;

		if (GuiButton(Rectangle{ wWidth - 160 - 20, wHeight - 32 - 10, 160, 32 }, "Connect"))
		{
			connect();
		}

		if (errorCode >= 0)
		{
			if (0)
			{
				GuiLabel(Rectangle{ 20, wHeight - 32 - 10, 160, 32 }, "Success");
			}
			else 
			{
				GuiLabel(Rectangle{ 20, wHeight - 32 - 10, 160, 32 }, "Success");
			}
		}

		//if (GuiValueBox(Rectangle{ 70, 70, 60, 32 }, "Samples", &samples_per_pixel, 0, 500, bSamplesEdit))	bSamplesEdit = !bSamplesEdit;

		//if (GuiValueBox(Rectangle{ 70, 120, 60, 32 }, "Bounces", &max_bounces, 0, 500, bBounceEdit) )		bBounceEdit = !bBounceEdit;
		//
		//GuiDrawText(TextFormat("%i ms", timeElapsed), Rectangle{10, (float)GetScreenHeight() - 100, 180, 50}, TEXT_ALIGN_RIGHT, BLACK);

		EndDrawing();
	}

	std::cerr << "\\Done\\n";
}

