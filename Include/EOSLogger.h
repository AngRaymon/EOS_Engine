#pragma once
#include <stdio.h>
#include <sstream>

#define MLOG EOSLogger::GetInstance()->Log(EOSLogger::MESSAGE).Get()
#define WLOG EOSLogger::GetInstance()->Log(EOSLogger::WARN).Get()
#define DLOG EOSLogger::GetInstance()->Log(EOSLogger::DEBUG).Get()
#define ELOG EOSLogger::GetInstance()->Log(EOSLogger::ERROR).Get()
#define FLOG EOSLogger::GetInstance()->Log(EOSLogger::FATAL).Get()

class LogMessage;

class EOSLogger {
public:
	enum LogLevel {
		MESSAGE = 0,
		WARN,
		DEBUG,
		ERROR,
		FATAL
	};
	static EOSLogger* GetInstance();
	LogMessage Log(LogLevel level);
private:
	static EOSLogger* m_instance;
	EOSLogger();
	~EOSLogger();
};


class LogMessage {
private:
	std::ostringstream m_sstream;
public:
	LogMessage(EOSLogger::LogLevel level);
	LogMessage(const LogMessage& message);
	~LogMessage();

	std::ostringstream& Get();
};
