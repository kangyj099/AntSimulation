module logManager;

import <iostream>;
import <vector>;

import common;
import console;

using namespace Constants;

LogManager::LogManager()
{
	logList.reserve(c_LOG_printLine);
}

LogManager::~LogManager()
{
}

void LogManager::AddLog(LogType _logType, std::string _logText) {
	if (logList.size() >= c_LOG_printLine)
	{
		logList.erase(logList.begin());
	}

	Log log;
	log.SetLog(_logType, _logText);

	logList.push_back(log);

}

void LogManager::PrintLog()
{
	for (auto log = logList.begin(); log != logList.end(); ++log)
	{
		switch (log->type)
		{
		case LogType::State: PrintText("◎ ", c_COLOR_defaultBG, Color::Blue); break;
		case LogType::Action: PrintText("■ ", c_COLOR_defaultBG, Color::Yellow); break;
		case LogType::Outcome: PrintText("● ", c_COLOR_defaultBG, Color::Green); break;

		case LogType::None: [[fallthrough]];
		default:;
		}

		PrintText(log->text);
		if (logList.end()-1 != log)
		{
			PrintText("\n");
		}
	}
}

void LogManager::Reset()
{
	logList.clear();
}
