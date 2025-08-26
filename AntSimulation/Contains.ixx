#pragma once
export module contains;

/////////////////////////////////
// 로그
export const short c_LOG_printLine = 5;	// 로그 출력 줄 수

/////////////////////////////////
// 화면 출력 관련
export const short c_SCREEN_width = 80;
export const short c_SCREEN_height = 26;

export const short c_SCREEN_fieldStartX = 0;
export const short c_SCREEN_fieldStartY = 0;

export const short c_SCREEN_logStartX = 0;
export const short c_SCREEN_logStartY = c_SCREEN_height - c_LOG_printLine;

/////////////////////////////////
// 색상 정의
export enum class Color : unsigned short
{
	Black = 0,
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkMagenta = 5,
	DarkYellow = 6,
	Gray = 7,
	DarkGray = 8,
	Blue = 9,
	Green = 10,
	Cyan = 11,
	Red = 12,
	Magenta = 13,
	Yellow = 14,
	White = 15,
};

export const Color c_COLOR_defaultBG = Color::Black;
export const Color c_COLOR_defaultText = Color::White;
