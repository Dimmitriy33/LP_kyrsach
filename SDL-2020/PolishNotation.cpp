//#include "pch.h"
//#include "Error.h"
//#include "LT.h"
//#include "IT.h"
//#include "PolishNotation.h"
//
//template <typename T>
//struct container : T
//{
//	using T::T;
//	using T::c;
//};
//
//std::string To_string(int n) {
//	char buf[40];
//	sprintf_s(buf, "%d", n);
//	return buf;
//}
//
//bool PN::find_elem(std::stack<char> stack, size_t size, char elem) {
//	for (size_t i = 0; i < size; i++)
//		if (stack.top() == elem)
//			return true;
//		else
//			stack.pop();
//	return false;
//}
//
//int PN::get_priority(char lexem) {
//	std::vector<std::pair<int, char>> priority = { {0, LEX_LEFTHESIS}, {0, LEX_RIGHTHESIS},
//													{1, LEX_COMMA},
//													{2, LEX_PLUS}, {2, LEX_MINUS},
//													{3, LEX_STAR}, {3, LEX_DIRSLASH} };
//	for (size_t i = 0; i < priority.size(); i++)
//		if (lexem == priority[i].second)
//			return priority[i].first;
//	return 0;
//}
//
//void PN::fix_lextable(LT::LexTable& lextable, const std::string& str, size_t length, size_t pos, const std::vector<int>& ids) {
//	for (size_t i = 0, q = 0; i < str.size(); i++) {
//		lextable.table[pos + i].lexeme = str[i];
//		if (lextable.table[pos + i].lexeme == LEX_ID || lextable.table[pos + i].lexeme == LEX_LITERAL
//			|| lextable.table[pos + i].lexeme == LEX_COMPARE || lextable.table[pos + i].lexeme == LEX_STRLEN) {
//			lextable.table[pos + i].idxTI = ids[q];
//			q++;
//		}
//		else
//			lextable.table[pos + i].idxTI = LT_TI_NULLIDX;
//	}
//	int temp = str.size() + pos;
//	for (size_t i = 0; i < length - str.size(); i++) {
//		lextable.table[temp + i].idxTI = LT_TI_NULLIDX;
//		lextable.table[temp + i].lexeme = '!';
//		lextable.table[temp + i].sn = -1;
//	}
//}
//
//void PN::PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable) {
//	for (int i = 0; i < lextable.size; i++)
//		if (lextable.table[i].lexeme == LEX_EQUALS)
//			if (!Convertation(i + 1, lextable, idtable))
//				throw ERROR_THROW(130);
//}
//
//bool PN::Convertation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
//{
//	container<std::stack<char>> stack;
//	std::string PolishString;
//	std::vector<char> operators = { LEX_MINUS, LEX_PLUS, LEX_DIRSLASH, LEX_STAR };
//	std::vector<int> ids;
//	int operators_count = 0, operands_count = 0, iterator = 0, right_counter = 0, left_counter = 0, params_counter = 0;
//
//	for (int i = lextable_pos; i < lextable.size; i++, iterator++) {
//		char lexem = lextable.table[i].lexeme;
//		size_t stack_size = stack.size();
//		if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
//			stack.push(LEX_COMMERCIALAT);
//			operands_count--;
//		}
//		if (std::find(operators.begin(), operators.end(), lexem) != operators.end()) {
//			if (!stack.empty() && stack.top() != LEX_LEFTHESIS) {
//				while (!stack.empty() && PN::get_priority(lexem) <= PN::get_priority(stack.top())) {
//					PolishString += stack.top();
//					stack.pop();
//				}
//			}
//			stack.push(lexem);
//			operators_count++;
//		}
//		else if (lexem == LEX_COMMA) {
//			while (!stack.empty()) {
//				if (stack.top() == LEX_LEFTHESIS)
//					break;
//				PolishString += stack.top();
//				stack.pop();
//			}
//			operands_count--;
//		}
//		else if (lexem == LEX_LEFTHESIS) {
//			left_counter++;
//			stack.push(lexem);
//		}
//		else if (lexem == LEX_RIGHTHESIS) {
//			right_counter++;
//			if (!PN::find_elem(stack, stack_size, LEX_LEFTHESIS))
//				return false;
//			while (stack.top() != LEX_LEFTHESIS) {
//				PolishString += stack.top();
//				stack.pop();
//			}
//			stack.pop();
//			if (!stack.empty() && stack.top() == LEX_COMMERCIALAT) {
//				PolishString += stack.top() + To_string(params_counter - 1);
//				params_counter = 0;
//				stack.pop();
//			}
//		}
//		else if (lexem == LEX_SEMICOLON) {
//			if (operators_count != 0 && operands_count != 0)
//				if ((!stack.empty() && (stack.top() == LEX_RIGHTHESIS || stack.top() == LEX_LEFTHESIS))
//					|| right_counter != left_counter || operands_count - operators_count != 1)
//					return false;
//			while (!stack.empty()) {
//				PolishString += stack.top();
//				stack.pop();
//			}
//			PN::fix_lextable(lextable, PolishString, iterator, lextable_pos, ids);
//			break;
//		}
//		else if (lexem == LEX_ID || lexem == LEX_LITERAL || lexem == LEX_COMPARE || lexem == LEX_STRLEN) {
//			if (std::find(stack.c.begin(), stack.c.begin(), LEX_COMMERCIALAT) != stack.c.end())
//				params_counter++;
//			PolishString += lexem;
//			if (lextable.table[i].idxTI != LT_TI_NULLIDX)
//				ids.push_back(lextable.table[i].idxTI);
//			operands_count++;
//		}
//	}
//	return true;
//}


#include "pch.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"

namespace PN
{


	int GetExpr(LT::LexTable lexTable, int i)
	{
		for (; lexTable.table[i].lexeme != LEX_SEMICOLON; i++);
		return i;
	}

	int Priorities(char operation)
	{
		if (operation == LEX_LEFTHESIS || operation == LEX_RIGHTHESIS)
			return 1;
		if (operation == LEX_MINUS || operation == LEX_PLUS)
			return 2;
		if (operation == LEX_DIRSLASH || operation == LEX_STAR)
			return 3;
	}

	int ConverExpr(LT::Entry* expr, LT::LexTable lexTable, IT::IdTable idtable, int pos)
	{
		std::stack<LT::Entry> stack;
		int sizeExpr = 0;
		short leftBracket = 0;

		for (int j = GetExpr(lexTable, pos); pos < j; pos++)
		{
			if ((lexTable.table[pos].lexeme == LEX_ID || lexTable.table[pos].lexeme == LEX_LITERAL) && !(idtable.table[lexTable.table[pos].idxTI].idtype == IT::IDTYPE::F)&&
				lexTable.table[pos].lexeme!=LEX_COMPARE && !lexTable.table[pos].lexeme != LEX_STRLEN)
			{
				expr[sizeExpr++] = lexTable.table[pos];
			}
			else if (lexTable.table[pos].lexeme == LEX_COMPARE || lexTable.table[pos].lexeme == LEX_STRLEN ||
				(idtable.table[lexTable.table[pos].idxTI].idtype == IT::IDTYPE::F))
			{
				LT::Entry Copy = lexTable.table[pos];
				Copy.lexeme = LEX_COMMERCIALAT;
				if (lexTable.table[pos].lexeme == LEX_COMPARE)
				{
					Copy.idxTI = IT::IsId(idtable ,"", "compare");
				}
				else if (lexTable.table[pos].lexeme == LEX_STRLEN)
				{
					Copy.idxTI = IT::IsId(idtable, "", "strln");
				}
				pos++;
				int par = 1;
				while (lexTable.table[pos].lexeme != LEX_RIGHTHESIS)
				{
					if (lexTable.table[pos].lexeme == LEX_COMMA)
						par++;
					if (((lexTable.table[pos].lexeme != LEX_COMMA) && (lexTable.table[pos].lexeme == LEX_ID || lexTable.table[pos].lexeme == LEX_LITERAL)))
					{
						expr[sizeExpr++] = lexTable.table[pos];
					}
					pos++;
				}
				expr[sizeExpr++] = Copy;
				expr[sizeExpr].lexeme = std::to_string(par).front();
				expr[sizeExpr++].idxTI = LT_TI_NULLIDX;
			}
			else if (lexTable.table[pos].lexeme == LEX_RIGHTHESIS)
			{

				while (stack.size())
				{
					if (stack.top().lexeme == LEX_LEFTHESIS)	break;
					expr[sizeExpr++] = stack.top();
					stack.pop();
				}
				stack.pop();	leftBracket--;
			}
			else if (lexTable.table[pos].lexeme == LEX_LEFTHESIS)
			{
				leftBracket++;
				stack.push(lexTable.table[pos]);
			}
			else if (stack.size() == 0 || stack.top().lexeme == LEX_LEFTHESIS)
			{

				stack.push(lexTable.table[pos]);
			}
			else
			{

				while (stack.size())
				{
					if (Priorities(lexTable.table[pos].lexeme) > Priorities(stack.top().lexeme)) break;
					expr[sizeExpr++] = stack.top();
					stack.pop();
				}
				stack.push(lexTable.table[pos]);
			}
		}

		while (stack.size() != 0)
		{
			expr[sizeExpr++] = stack.top();
			stack.pop();
		}
		/*for (int m = 0; m < sizeExpr; m++)
		{
			std::cout << expr[m].lexeme;
		}*/
		std::cout << std::endl;
		return sizeExpr;
	}

	void AddNewExpr(LT::LexTable& lexTable, IT::IdTable& idTable, LT::Entry* expr, int numConver, int sizeExpr)
	{
		for (int j = numConver, g = 0; g < sizeExpr; j++, g++)
		{
			lexTable.table[j] = expr[g];
			if (ELEMIT)		idTable.table[lexTable.table[j].idxTI].idxfirstLE = j;
		}
	}

	void DelNULLEntryLT(LT::LexTable& lexTable, IT::IdTable& idTable, int numConver, int sizeExpr, int endExpr)
	{
		for (int r = endExpr - (numConver + sizeExpr), g = 0; g < r; g++)
		{
			for (int j = numConver + sizeExpr; j < lexTable.size; j++)
			{
				lexTable.table[j] = lexTable.table[j + 1];
				if (ELEMIT)		idTable.table[lexTable.table[j].idxTI].idxfirstLE = j;
			}
			lexTable.size--;
		}
	}

	void PolishNotation(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		Check check;
		LT::Entry expr[200];
		int numConver = 0;
		for (int i = 0; i < lexTable.size; i++)
		{
			if (lexTable.table[i].lexeme == LEX_EQUALS || lexTable.table[i].lexeme == LEX_RETURN || lexTable.table[i].lexeme == LEX_OUT)
			{

				numConver = i + 1;
				int endExpr = GetExpr(lexTable, numConver);
				int sizeExpr = ConverExpr(expr, lexTable, idTable, numConver);
				AddNewExpr(lexTable, idTable, expr, numConver, sizeExpr);
				DelNULLEntryLT(lexTable, idTable, numConver, sizeExpr, endExpr);
			}
		}
	}
}

