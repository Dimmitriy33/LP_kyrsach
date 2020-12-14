#pragma once
#include "pch.h"
#include "LT.h"
#include "It.h"
#include "Log.h"

namespace CG
{
	class Generation
	{
	private:
		LT::LexTable lextable;
		IT::IdTable idtable;
		std::ofstream out;
		void Head();
		void Constants();
		void Data();
		void Code();

	public:
		Generation(LT::LexTable lexT, IT::IdTable idT, const wchar_t out[PARM_MAX_SIZE]);
		void Start(const Log::LOG& log);
	};
}
