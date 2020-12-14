
#pragma once
#include "IT.h"
#include "LT.h"
#include <stack>
#include <iostream>
#include "Error.h"


#define ELEMIT			lexTable.table[j].lexeme == LEX_ID ||\
	lexTable.table[j].lexeme == LEX_LITERAL
namespace PN
{
	struct Check
	{
		short operand = 0;
		short operation = 0;

	};

	int GetExpr(LT::LexTable lexTable, int i);
	void PolishNotation(LT::LexTable& lexTable, IT::IdTable& idTable);
	int Priorities(char operation);
	int ConverExpr(LT::Entry* expr, LT::LexTable lexTable, IT::IdTable idtable, int pos);
	void AddNewExpr(LT::LexTable& lexTable, IT::IdTable& idTable, LT::Entry* expr, int numConver, int sizeExpr);
	void DelNULLEntryLT(LT::LexTable& lexTable, IT::IdTable& idTable, int numConver, int sizeExpr, int endExpr);
}