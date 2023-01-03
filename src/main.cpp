#pragma once

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "WAHUtils.h"


int main(int argc, char* argv[])
{
	//Datas 
	std::string hubPath = "";
	std::vector<std::string> sdkVersions;
	WAHUtils::ReadJSON(hubPath, sdkVersions);

	std::cout << sdkVersions[0] << std::endl;

	std::string sdkUnityVersions;

	for (int i = 0; i < sdkVersions.size(); i++)
	{
		if( i > 0 ) sdkUnityVersions.append(";"); 
		sdkUnityVersions.append(sdkVersions[i]);
	}

	/*******************/
	float wWidth = 400, wHeight = 100;	// Window size
	
	bool bIPEdit = 0, bSDKSelect = 0;
	int sdkActive = 0;

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

		if (GuiDropdownBox(Rectangle{ 140, 10, 120, 24 }, sdkUnityVersions.c_str(), &sdkActive, bSDKSelect))	bSDKSelect = !bSDKSelect;

		if (GuiButton(Rectangle{ wWidth - 160 - 20, wHeight - 32 - 10, 160, 32 }, "Connect"))
		{
			WAHUtils::Connect(hubPath, sdkVersions[sdkActive], ipAddress);
		}

		if (GuiButton(Rectangle{ 20, wHeight - 32 - 10, 160, 32 }, "Kill all adb servers"))
		{
			//WAHUtils::KillAllAdbServer(hubPath, sdkVersions);
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

