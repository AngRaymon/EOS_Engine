#include "EosStd.h"
#include "EOSLogger.h"

EOSLogger* EOSLogger::m_instance = 0;

EOSLogger::EOSLogger() {

}

EOSLogger::~EOSLogger() {

}

EOSLogger* EOSLogger::GetInstance() {
	if (!m_instance) m_instance = new EOSLogger();
	return m_instance;
}

LogMessage EOSLogger::Log(LogLevel level) {
	return LogMessage(level);
}

LogMessage::LogMessage(EOSLogger::LogLevel level) {
	switch (level) {
	case EOSLogger::MESSAGE:
		m_sstream << "[MESSAGE]: ";
		break;
	case EOSLogger::WARN:
		m_sstream << "[WARN]: ";
		break;
	case EOSLogger::DEBUG:
		m_sstream << "[DEBUG]: ";
		break;
	case EOSLogger::ERROR:
		m_sstream << "[ERROR]: ";
		break;
	case EOSLogger::FATAL:
		m_sstream << "[FATAL]: ";
		break;
	}
}

LogMessage::LogMessage(const LogMessage& message) 
{

}

std::ostringstream& LogMessage::Get() {
	return m_sstream;
}

LogMessage::~LogMessage() {
	m_sstream << std::endl;
	printf(m_sstream.str().c_str());
}