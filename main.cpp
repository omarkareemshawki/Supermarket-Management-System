/*
* Members: 
*	U2110268 - Tashyan Artyom
*	U2110249 - Safarov Akmaljon
*	U2110222 - Pavlova Albina
*	U2110246 - Malikahon Rustamova
*/

//impostring libraries
#include <iostream>
#include <string>
//importing headers
#include<windows.h>
#include"Interface.h"
// used namespaces
using namespace std;
using namespace INTER;
#pragma warning(disable : 4996) // disabling warning regargind unsafe error

int main()
{
	// Change font parametres in console
	CONSOLE_FONT_INFOEX cfi; cfi.cbSize = sizeof(cfi); cfi.nFont = 0;
	cfi.dwFontSize.X = 0; // Width of each character in the font
	cfi.dwFontSize.Y = 18; // Height of the font
	cfi.FontFamily = FF_DONTCARE; cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Arials"); // Font style
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	mainMenu(); // Calling menu function to start whole program
	system("pause");
	return 0;
}