export module console;

import <string>;
import common;

/// <summary>
/// 콘솔창 크기 조절, 이름 변경
/// </summary>
export void ConsoleSetting(int _consoleWidth, int _consoleHeight, std::string _title);
/// <summary>
/// 콘솔 커서 세팅
/// </summary>
/// <param name="_size">콘솔 커서 크기</param>
/// <param name="_isVisible">콘솔 커서 보이게 할지</param>
export void CursorSetting(int _size, bool _isVisible);
/// <summary>
/// 콘솔 스크린버퍼 세팅
/// </summary>
export void ScreenBufferSetting();

/// <summary>
/// 특정 위치로 커서 이동 (ScreenRegion::Game 기준)
/// </summary>
/// <param name="_x">가로 위치(크기비율상 1당 0.5칸)</param>
/// <param name="_y">세로 위치(크기비율상 1당 1칸)</param>
export bool GotoXY(ConsolePos _pos);


/// <summary>
/// 스크린버퍼 교체하기 (화면 갱신)
/// </summary>
/// <param name="_screenRegion">어떤거 출력인지 (ScreenRegion::Game/Log/All)</param>
export void SwapScreenBuffer();
void ClearBuffer();

export void PrintText(std::string _printText, Constants::Color _bgColor = Constants::c_COLOR_defaultBG, Constants::Color _textColor = Constants::c_COLOR_defaultText);
