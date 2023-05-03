#include "stdafx.h"

static Log g_log;
static UILoggerComponent g_logComp;
static UILoggerComponent g_devLogComp;
void Log::Initialize() {
	if (m_allocated) return;

	AllocConsole();

	SetConsoleTitleA("Impulse");

	//Set output
	freopen_s(&m_stream, "CONIN$", "w", stdin);
	freopen_s(&m_stream, "CONOUT$", "w", stdout);
	freopen_s(&m_stream, "CONOUT$", "w", stderr);

	m_outputHandle = GetStdHandle((DWORD)-11);

	const int width = 120;
	const int height = 30;

	SMALL_RECT rectangle;
	rectangle.Left = rectangle.Top = 0;
	rectangle.Right = width - 1;
	rectangle.Bottom = height - 1;
	SetConsoleWindowInfo(m_outputHandle, true, &rectangle);

	ClearLog();
	system("cls");

	g_logComp = UILoggerComponent(20);
	g_devLogComp = UILoggerComponent(20);

	m_allocated = true;
	m_firstEntry = true;
	m_firstPrint = true;

	LOG_PRINT("[Console] Console allocated");
	LOG_PRINT("[Service] Version %s", GetAuth()->GetCurrentMenuVersion());
}

void Log::SetTextColor(const int color) {
	if (!m_allocated) return;

	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
	GetConsoleScreenBufferInfo(m_outputHandle, &screenBuffer);

	WORD attributes = screenBuffer.wAttributes & ~FOREGROUND_RED & ~FOREGROUND_GREEN & ~FOREGROUND_BLUE & ~FOREGROUND_INTENSITY;
	attributes |= color;

	SetConsoleTextAttribute(m_outputHandle, attributes);
}

void Log::ClearLog() {
	ofstream ofs;
	ofs.open(GetConfig()->GetLogPath(), ofstream::out | ofstream::trunc);
	ofs.close();
}

void Log::LogToFile(String message) {
	ofstream logFile;
	logFile.open(GetConfig()->GetLogPath(), ios_base::app);
	if (m_firstEntry) {
		logFile << endl;
		m_firstEntry = false;
	}
	logFile << message;
}

String Log::GetTimeAsString() {
	struct tm timeStruct;
	time_t currentTime = time(nullptr);
	localtime_s(&timeStruct, &currentTime);

	static char buffer[48];
	sprintf_s(buffer, "[%02d:%02d:%02d]", timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec);
	return buffer;
}

void Log::MessageEnhanced(int color, String type, String fmt, ...) {
#ifndef HARD_DEV
	return;
#endif

	char buffer[0x10000] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buffer, fmt, va_alist);
	va_end(va_alist);

	SetTextColor(color);
	m_lastColor = color;

	char buffer2[0x10000] = { 0 };
	if (m_firstEntry) {
		sprintf_s(buffer2, "%s%s %s", GetTimeAsString(), type, buffer);
		m_firstEntry = false;
	}
	else sprintf_s(buffer2, "\n%s%s %s", GetTimeAsString(), type, buffer);

	// Write to log file
	LogToFile(buffer2);

	// Print to console
	printf(buffer2);

	g_devLogComp.addLine(color, buffer2);
}


void Log::MessageDev(int color, String type, String fmt, ...) {
#ifndef HARD_DEV
	return;
#endif
	char buffer[8192] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buffer, fmt, va_alist);
	va_end(va_alist);

	SetTextColor(color);
	m_lastColor = color;

	char buffer2[8192] = { 0 };
	if (m_firstEntry) {
		sprintf_s(buffer2, "%s%s %s", GetTimeAsString(), type, buffer);
		m_firstEntry = false;
	} else sprintf_s(buffer2, "\n%s%s %s", GetTimeAsString(), type, buffer);

	// Write to log file
	LogToFile(buffer2);

	// Print to console
	printf(buffer2);

	g_devLogComp.addLine(color, buffer2);
}

void Log::Message(int color, String type, String fmt, ...) {
	char buffer[512] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buffer, fmt, va_alist);
	va_end(va_alist);

	SetTextColor(color);
	m_lastColor = color;

	char buffer2[512] = { 0 };
	if (m_firstEntry) {
		sprintf_s(buffer2, "%s%s %s", GetTimeAsString(), type, buffer);
		m_firstEntry = false;
	} else sprintf_s(buffer2, "\n%s%s %s", GetTimeAsString(), type, buffer);

	// Write to log file
	LogToFile(buffer2);

	// Print to console
	printf(buffer2);

	g_logComp.addLine(color, buffer2);
}

UILoggerComponent* Log::GetLogComponent() { return &g_logComp; }
UILoggerComponent* Log::GetDevLogComponent() { return &g_devLogComp; }
void Log::MessageAppend(int color, String fmt, ...) {
	if (!m_allocated) return;
	char buffer[512] = { 0 };

	va_list args;

	va_start(args, fmt);
	vsprintf_s(buffer, fmt, args);
	va_end(args);

	SetTextColor(color);

	// Write to log file
	LogToFile(buffer);

	// Print to console
	printf(buffer);
}

void Log::Cleanup() {
	if (!m_allocated) return;
	LOG_DEBUG("[Console] Disabled console");
	LOG_PRINT("You can now close this console...");
	FreeConsole();
	PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
	LOG_DEBUG("[Console] Disabled console");
}

void Log::DisableCloseButton() {
#ifndef HARD_DEV
	if (GetAuth()->IsDev())return;
	auto hwnd = GetConsoleWindow();
	if (hwnd != nullptr) {
		auto hMenu = GetSystemMenu(hwnd, FALSE);
		if (hMenu != nullptr) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
#endif
}

Log* GetLog() { return &g_log; }
