#pragma once
#include <iostream>

#define ConsoleError 7
#define ConsoleWarning 8
#define ConsoleSuccess 9
#define ConsoleStandard 10

#define setConsoleColorBlack() printf("\033[1;30m");
#define setConsoleColorRed() printf("\033[1;31m");
#define setConsoleColorGreen() printf("\033[1;32m");
#define setConsoleColorYellow() printf("\033[1;33m");
#define setConsoleColorBlue() printf("\033[1;34m");
#define setConsoleColorPurple() printf("\033[1;35m");
#define setConsoleColorCyan() printf("\033[1;36m");
#define setConsoleColorWhite() printf("\033[1;37m");
#define consoleColorReset() printf("\033[0;37m");

#define printVA(format, ...) printf(format, __VA_ARGS__); printf("\n");

#define printError(reason, ...) \
	std::cout << "Error: " << __FILE__ << "::" << \
	__func__ << "::" << __LINE__ << std::endl << \
	"Reason: ";\
	printVA(reason, __VA_ARGS__)

#define LogError(message, ...) setConsoleColorRed() printError(message, __VA_ARGS__) consoleColorReset()

#define LogSuccess(message, ...) setConsoleColorGreen() std::cout << "Success: "; printVA(message, __VA_ARGS__) consoleColorReset()

#define LogWarning(message, ...) setConsoleColorYellow() std::cout << "Warning: "; printVA(message, __VA_ARGS__) consoleColorReset()

#define LogStandard(message, ...) printVA(message, __VA_ARGS__)

#define ConsoleLog(logType, message, ...) \
if (logType == ConsoleError) {\
	LogError(message, __VA_ARGS__) \
}\
else if (logType == ConsoleWarning) {\
	LogWarning(message, __VA_ARGS__) \
}\
else if (logType == ConsoleSuccess) {\
	LogSuccess(message, __VA_ARGS__) \
}\
else {\
	LogStandard(message, __VA_ARGS__) \
}