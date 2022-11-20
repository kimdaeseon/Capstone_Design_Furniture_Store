#pragma once
#define interface class

interface Parser {
public:
	virtual void parse(const char* line) {}
};
