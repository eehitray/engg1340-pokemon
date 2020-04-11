#ifndef SCREEN_RENDERER
#define SCREEN_RENDERER

#include <string>
#include <map>

class Map;

class ScreenRenderer {
	std::map<char, std::string> colorCharMap;

	public:
		ScreenRenderer();
		void clearScreen();
		void printToScreen(std::string s = "");
		char inputCharNoEnter(std::string s = "");
		std::string inputString(std::string s = "");
		int inputInt(std::string s = "");
		void printRenderableMap(Map);
		void printLoadingScreen();
};
#endif
