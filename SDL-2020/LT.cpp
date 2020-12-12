#include "pch.h"
#include "LT.h"
#include "Error.h"

LT::LexTable LT::Create(int size) {
	if (size > LT_MAXSIZE) {
		throw ERROR_THROW(120);
	}

	LexTable lextable;
	lextable.maxsize = size;
	lextable.size = 0;
	lextable.table = DBG_NEW Entry[size];
	return lextable;
}

void LT::Add(LexTable& lextable, Entry entry) {
	if (lextable.size + 1 > lextable.maxsize) {
		throw ERROR_THROW(121);
	}

	lextable.table[lextable.size] = entry;
	lextable.size++;
}

LT::Entry LT::GetEntry(LexTable& lextable, int n) {
	if (n < 0 || n > lextable.size - 1) {
		throw ERROR_THROW(122);
	}

	return lextable.table[n];
}

void LT::Delete(LexTable& lextable) {
	if (!lextable.table) {
		return;
	}

	delete[] lextable.table;
	lextable.table = nullptr;
}

std::string LT::LexTable::showLexTable(int startIndex, int endIndex)
{
	std::stringstream output;

	startIndex = std::clamp(startIndex, 0, size);
	if (endIndex == 0)
	{
		endIndex = size;
	}
	else
	{
		endIndex = std::clamp(endIndex, startIndex, size);
	}
	output << std::setw(4) << "index" << std::setw(20) << "lexeme" << std::setw(25) << "IdTable index\n";

	for (size_t i = startIndex; i < endIndex; ++i)
	{
		output << std::setw(4) << i << std::setw(18) << '\'' << table[i].lexeme << '\'';
		if (table[i].idxTI != LT_TI_NULLIDX)
		{
			output << std::setw(19) << table[i].idxTI;
		}
		output << '\n';
	}

	return output.str();
}
