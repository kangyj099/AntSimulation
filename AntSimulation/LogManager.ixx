#pragma once
export module logManager;

import <string>;
import <vector>;

import singleton;
import common;

// 개미 로그 종류
export enum class LogType
{
	None,   // 로그 종류 없음
	State,  // 개미 상태 관찰 로그
	Action, // 개미 행동 로그
	Outcome, // 개미 행동 결과 로그
};

// 개미 로그
struct Log {
	LogType type;
	std::string text;

	void SetLog(LogType _logType, std::string _logText)
	{
		type = _logType;
		text = _logText;
	}
};

// 개미 로그 출력 매니저
export class LogManager : public Singleton<LogManager>
{
	std::vector<Log> logList;

public:
	LogManager();
	~LogManager() override;

	/// <summary>
	/// 로그 리스트에 로그 추가 (최대 개수 제한됨)
	/// </summary>
	/// <param name="_logType">추가할 로그 타입</param>
	/// <param name="_logText">추가할 로그 내용</param>
	void AddLog(LogType _logType, std::string _logText);
	/// <summary>
	/// 로그 출력하기
	/// </summary>
	void PrintLog();
	/// <summary>
	/// 로그 초기화하기(쌓인 로그 모두 지우기)
	/// </summary>
	void Reset();
};

