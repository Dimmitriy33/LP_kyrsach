#pragma once
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "Log.h"

namespace LA {
	char Tokenize(const char* string);
	void Scan(LT::LexTable& lextable, IT::IdTable& idtable, In::IN& in, Parm::PARM& parm, Log::LOG& log);
}