#pragma once
export module logManager;

import <string>;
import <vector>;

export enum class LogType
{
	None,   // 로그 종류 없음
	State,  // 개미 상태 관찰 로그
	Action, // 개미 행동 로그
	Outcome, // 개미 행동 결과 로그
};

struct Log {
	LogType logType;
	std::string logText;

	void SetLog(LogType _logType, std::string _logText)
	{
		logType = _logType;
		logText = _logText;
	}
};

export class LogManager
{
	std::vector<Log> logList;

public:
	LogManager();
	~LogManager();

	void AddLog(LogType _logType, std::string _logText);
	void PrintLog();
	void Reset();
};

