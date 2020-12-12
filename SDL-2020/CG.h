#pragma once
#include "pch.h"
#include "LT.h"
#include "It.h"
#include "Log.h"

namespace CG
{
	class Generator
	{
	private:
		LT::LexTable lextable;
		IT::IdTable idtable;
		std::ofstream out;
		void Head();
		void Constants();
		void Data();
		void Code();
		void PrintComment(int position, const LT::LexTable& lextable);

	public:
		Generator(LT::LexTable lexT, IT::IdTable idT, wchar_t out[PARM_MAX_SIZE]);
		void Start(const Log::LOG& log);
	};
}

//#pragma once
//#include "pch.h"
//#include "LT.h"
//#include "IT.h"
//#include "Log.h"
//#define SEPSTREMP  "\n;------------------------------\n"
//#define SEPSTR(x)  "\n;----------- " + string(x) + " ------------\n"
//
//
//#define BEGIN ".586\n"\
//".model flat, stdcall\n"\
//"includelib libucrt.lib\n"\
//"includelib kernel32.lib\n"\
//"includelib ..\\SDL_Lib\\Debug\\SDL_Lib.lib\n"\
//"ExitProcess PROTO : DWORD \n"\
//"EXTRN compare\t\t: PROC\n"\
//"EXTRN strln\t\t: PROC\n"\
//"EXTRN out\t\t: PROC\n\n"\
//"EXTRN outstr: PROC\n"\
//"EXTRN outnum: PROC\n"\
//"EXTRN system_pause:PROC\n"\
//".stack 4096\n"
//
//namespace CG
//{
//	bool CodeGeneration(LT::LexTable& lextable, IT::IdTable& idtable, wchar_t out[PARM_MAX_SIZE]);
//	int GenExpHandler(std::ofstream& AsmFile, LT::LexTable& LEXTABLE, IT::IdTable& idtable, int pos);
//	IT::IDDATATYPE DetectType(LT::LexTable lextable, IT::IdTable idtable, int i);
//	void LogicOperations(std::ofstream& AsmFile, char lex, int sn);
//};