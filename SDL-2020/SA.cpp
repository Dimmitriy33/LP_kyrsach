#include "pch.h"
#include "SA.h"

SA::SemanticAnalyzer::SemanticAnalyzer(LT::LexTable lextable, IT::IdTable idtable)
{
	this->lextable = lextable;
	this->idtable = idtable;
}

void SA::SemanticAnalyzer::Start(const Log::LOG& log)
{
	CheckReturn();
	ParmsOfFunc();
	ParmsOfStandFunc();
	Types();
	FuncReturn();
	CorrectAmountOfParms();
	CheckIfParams();
	*log.stream << "\n";
	*log.stream << "  ==============############    —емантический анализ выполнен без ошибок   ############==============\n";
	*log.stream << "\n";
}

void SA::SemanticAnalyzer::CheckReturn()
{
	bool main = false;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexeme == LEX_RETURN) {
			if (main) {
				if ((lextable.table[i + 1].lexeme == LEX_ID || lextable.table[i + 1].lexeme == LEX_LITERAL)
					&& idtable.table[lextable.table[i + 1].idxTI].iddatatype != IT::IDDATATYPE::BZINT)
					throw ERROR_THROW_SEM(708, lextable.table[i].sn);
			}
			else if (lextable.table[i + 1].lexeme == LEX_ID) {
				if (idtable.table[lextable.table[i + 1].idxTI].idtype == IT::IDTYPE::F)
					throw ERROR_THROW_SEM(700, lextable.table[i].sn);
			}
		}
		else if (lextable.table[i].lexeme == LEX_MAIN)
			main = true;
}

void SA::SemanticAnalyzer::ParmsOfFunc()
{
	char buf[ID_MAXSIZE];
	int par = 0, funcpar = 0;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexeme == LEX_EQUALS) {
			while (lextable.table[i].lexeme == LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexeme == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
					strcpy(buf, idtable.table[lextable.table[i].idxTI].id);
					for (int j = 0; j < i; j++)
						if (lextable.table[j].lexeme == LEX_ID && lextable.table[j - 2].lexeme == LEX_FUNCTION
							&& !strcmp(buf, idtable.table[lextable.table[j].idxTI].id)) {
							j++;
							for (j; lextable.table[j].lexeme != LEX_RIGHTHESIS; j++)
								if (lextable.table[j].lexeme == LEX_ID) {
									funcpar++;
									i += 2;
									if (idtable.table[lextable.table[j].idxTI].iddatatype == IT::IDDATATYPE::BZINT) {
										if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L
											&& idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::BZINT)
											par++;
										if (lextable.table[i].lexeme == LEX_ID && idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::BZINT)
											par++;
									}
									if (idtable.table[lextable.table[j].idxTI].iddatatype == IT::IDDATATYPE::STR) {
										if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L
											&& idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
											par++;
										if (lextable.table[i].lexeme == LEX_ID)
											if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
												par++;
									}
								}
							if (funcpar != par || lextable.table[i + 2].lexeme != LEX_SEMICOLON)
								throw ERROR_THROW_SEM(701, lextable.table[i].sn);
						}
				}
			}
		}
}

void SA::SemanticAnalyzer::ParmsOfStandFunc()
{
	for (int i = 0; i < lextable.size; i++)
		switch (lextable.table[i].lexeme) {
		case LEX_OUT: {
			if (lextable.table[i + 1].lexeme != LEX_ID && lextable.table[i + 1].lexeme != LEX_LITERAL 
				&& lextable.table[i + 1].lexeme != LEX_COMPARE && lextable.table[i + 1].lexeme != LEX_STRLEN)
				throw ERROR_THROW_SEM(704, lextable.table[i].sn);
			break;
		}
		case LEX_COMPARE: {
			int parmsCount = 0;
			while (lextable.table[i].lexeme != LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexeme == LEX_ID || lextable.table[i].lexeme == LEX_LITERAL) {
					parmsCount++;
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::STR)
						throw ERROR_THROW_SEM(702, lextable.table[i].sn);
				}
			}
			if (parmsCount != 2)
				throw ERROR_THROW_SEM(703, lextable.table[i].sn);
			break;
		}
		case LEX_STRLEN: {
			int parmsCount = 0;
			while (lextable.table[i].lexeme != LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexeme == LEX_ID || lextable.table[i].lexeme == LEX_LITERAL) {
					parmsCount++;
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::STR)
						throw ERROR_THROW_SEM(702, lextable.table[i].sn);
				}
			}
			if (parmsCount != 1)
				throw ERROR_THROW_SEM(703, lextable.table[i].sn);
			break;
		}
		}
}

void SA::SemanticAnalyzer::Types()
{
	IT::IDDATATYPE datatype;
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexeme == LEX_EQUALS) {
			if (lextable.table[i + 2].lexeme == LEX_MINUS)
				throw ERROR_THROW_SEM(712, lextable.table[i].sn);
			datatype = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
			while (lextable.table[i].lexeme != LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexeme == LEX_COMPARE || lextable.table[i].lexeme == LEX_STRLEN)
					if (datatype != IT::IDDATATYPE::BZINT)
						throw ERROR_THROW_SEM(706, lextable.table[i].sn);
					else {
						while (lextable.table[i].lexeme != LEX_SEMICOLON)
							i++;
					}

				if ((lextable.table[i].lexeme == LEX_ID || lextable.table[i].lexeme == LEX_LITERAL)
					&& idtable.table[lextable.table[i].idxTI].iddatatype != datatype) {
					if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
						throw ERROR_THROW_SEM(705, lextable.table[i].sn);
					else
						throw ERROR_THROW_SEM(706, lextable.table[i].sn);
				}
				else if (lextable.table[i].lexeme == LEX_ID
					&& idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F
					&& lextable.table[i + 1].lexeme == LEX_LEFTHESIS)
					throw ERROR_THROW_SEM(709, lextable.table[i].sn);
				else if (lextable.table[i].lexeme == LEX_STRLEN && datatype != IT::IDDATATYPE::BZINT
					|| lextable.table[i].lexeme == LEX_COMPARE && datatype != IT::IDDATATYPE::BZINT)
					throw ERROR_THROW_SEM(705, lextable.table[i].sn);
			}
		}
	}
}

void SA::SemanticAnalyzer::FuncReturn()
{
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexeme == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F
			&& lextable.table[i - 1].lexeme == LEX_FUNCTION) {
			IT::IDDATATYPE iddatatype = idtable.table[lextable.table[i].idxTI].iddatatype;
			while (lextable.table[i].lexeme != LEX_RETURN)
				i++;
			if (idtable.table[lextable.table[i + 1].idxTI].iddatatype != iddatatype)
				throw ERROR_THROW_SEM(707, lextable.table[i].sn);
		}
}

void SA::SemanticAnalyzer::CorrectAmountOfParms()
{
	std::string buf;
	buf.reserve(ID_MAXSIZE);
	int parms = 0, funcparms = 0;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexeme == LEX_EQUALS) {
			while (lextable.table[i].lexeme != LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexeme == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
					buf = idtable.table[lextable.table[i].idxTI].id;
					while (lextable.table[i].lexeme != LEX_RIGHTHESIS) {
						i++;
						if (lextable.table[i].lexeme == LEX_ID || lextable.table[i].lexeme == LEX_LITERAL)
							parms++;
					}
					for (int j = 0; j < i; j++)
						if (lextable.table[j].lexeme == LEX_ID && idtable.table[lextable.table[j].idxTI].idtype == IT::IDTYPE::F
							&& buf == idtable.table[lextable.table[j].idxTI].id) {
							j++;
							for (j; lextable.table[j].lexeme != LEX_RIGHTHESIS; j++)
								if (lextable.table[j].lexeme == LEX_ID)
									funcparms++;
							break;
						}
				}
			}
			if (funcparms != parms)
				throw ERROR_THROW_SEM(701, lextable.table[i].sn);
		}
}

void SA::SemanticAnalyzer::CheckIfParams()
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexeme == LEX_IF)
		{
			if (idtable.table[lextable.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::BZINT ||
				idtable.table[lextable.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::BZINT)
					throw ERROR_THROW_SEM(711, lextable.table[i].sn);
				
		}


	}
}

