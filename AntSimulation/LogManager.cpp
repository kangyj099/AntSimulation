module logManager;

import contains;

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
	for (auto log : logList)
	{
		switch (log.logType)
		{
		case LogType::State: printf("¡Ý "); break;
		case LogType::Action: printf("¡á "); break;
		case LogType::Outcome: printf("¡Ü "); break;

		case LogType::None: [[fallthrough]];
		default:;
		}

		printf("%s\n", log.logText.c_str());
	}
}

void LogManager::Reset()
{
	logList.clear();
}
