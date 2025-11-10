module utils;

using namespace Constants;

bool Utils::IsSameSign(short _a, short _b)
{
	return 0 <= (_a ^ _b);
}

bool Utils::IsSameSign(int _a, int _b)
{
	return 0 <= (_a ^ _b);
}

bool Utils::IsSameSign(float _a, float _b)
{
	return std::signbit(_a) == std::signbit(_b);
}

bool Utils::IsSameSign(double _a, double _b)
{
	return std::signbit(_a) == std::signbit(_b);
}

bool Utils::IsValidDirection(Direction8 _dir)
{
	if (Direction8::None >= _dir || Direction8::Count <= _dir)
	{
		return false;
	}

	return true;
}

ConsolePos Utils::FieldPositionToConsolePos(FieldPos _position)
{
	ConsolePos consolePos(_position.x * c_FIELD_toScreenXScale + c_SCREEN_fieldStartX, _position.y + c_SCREEN_fieldStartY);
	return consolePos;
}

FieldPos Utils::ConsolePositionToFieldPos(ConsolePos _position)
{
	FieldPos fieldPos(_position.x / c_FIELD_toScreenXScale - c_SCREEN_fieldStartX, _position.y - c_SCREEN_fieldStartY);

	return fieldPos;
}

std::mt19937 randEngine(std::random_device{}());

int Utils::GetRandomInt(int _min, int _max)
{
	std::uniform_int_distribution dist(_min, _max);
	int randomvalue = dist(randEngine);

	return randomvalue;
}

float Utils::GetRandomFloat(float _min, float _max, int decimalPlaces)
{
	std::uniform_real_distribution<float> dist(_min, _max);
	float randomValue = dist(randEngine);

	// 소수점 자리수 맞추기
	float factor = std::pow(10.0f, decimalPlaces);
	randomValue = std::round(randomValue * factor) / factor;

	return randomValue;
}

