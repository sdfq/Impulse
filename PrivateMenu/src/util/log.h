//#pragma once
#define LOG_PRINT( fmt, ...)			GetLog()->Message(ConsoleForeground::WHITE,		" [Info]",		fmt, ##__VA_ARGS__ )
#define LOG_DEBUG( fmt, ...)			GetLog()->Message(ConsoleForeground::GRAY,		" [Debg]",		fmt, ##__VA_ARGS__ )
#define LOG_WARN( fmt, ...)				GetLog()->Message(ConsoleForeground::DARKYELLOW," [Warn]",		fmt, ##__VA_ARGS__ )
#define LOG_ERROR( fmt, ...)			GetLog()->Message(ConsoleForeground::RED,		" [Fail]",		fmt, ##__VA_ARGS__ )
#define LOG_CUSTOM( color, fmt, ...)	GetLog()->Message(color,						" [Info]",		fmt, ##__VA_ARGS__ )
#define LOG_ADDC( color, fmt, ...)		GetLog()->MessageAppend(color, fmt, ##__VA_ARGS__ )
#define LOG_ADD( fmt, ...)				GetLog()->MessageAppend(GetLog()->m_lastColor, fmt, ##__VA_ARGS__ )

#define LOG_DEVPRINT( fmt, ...)			GetLog()->MessageDev(ConsoleForeground::WHITE,		" [DevI]",		fmt, ##__VA_ARGS__ )
#define LOG_DEVDEBUG( fmt, ...)			GetLog()->MessageDev(ConsoleForeground::GRAY,		" [DevD]",		fmt, ##__VA_ARGS__ )
#define LOG_DEVWARN( fmt, ...)			GetLog()->MessageDev(ConsoleForeground::DARKYELLOW,	" [DevW]",		fmt, ##__VA_ARGS__ )
#define LOG_DEVERROR( fmt, ...)			GetLog()->MessageDev(ConsoleForeground::RED,		" [DevF]",		fmt, ##__VA_ARGS__ )
#define LOG_DEVCUSTOM( color, fmt, ...)	GetLog()->MessageDev(color,							" [DevI]",		fmt, ##__VA_ARGS__ )
#define LOG_DEVENH( fmt, ...)			GetLog()->MessageEnhanced(ConsoleForeground::WHITE, " [DevE]",		fmt, ##__VA_ARGS__ )

class UILoggerComponent;

namespace ConsoleForeground {
	enum {
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
}

namespace ConsoleBackground {
	enum {
		BLACK = 0,
		DARKBLUE = BACKGROUND_BLUE,
		DARKGREEN = BACKGROUND_GREEN,
		DARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
		DARKRED = BACKGROUND_RED,
		DARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
		DARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
		DARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		GRAY = BACKGROUND_INTENSITY,
		BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		CYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
		MAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	};
}

class Log {
public:
	int m_lastColor;
	String GetTimeAsString();

	void Initialize();
	void Cleanup();
	void MessageEnhanced(int color, String type, String fmt, ...);
	void MessageDev(int color, String type, String fmt, ...);
	void Message(int color, String type, String fmt, ...);
	void MessageAppend(int color, String fmt, ...);
	void LogToFile(String message);
	void DisableCloseButton();
	UILoggerComponent* GetLogComponent();
	UILoggerComponent* GetDevLogComponent();

private:
	bool m_allocated;
	bool m_firstEntry = true;
	bool m_firstPrint = true;

	FILE *m_stream;
	HANDLE m_outputHandle = INVALID_HANDLE_VALUE;

	void ClearLog();
	void SetTextColor(const int color);
};

Log* GetLog();
