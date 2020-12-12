#include "pch.h"
#include "Lexer.h"
#include "FST.h"

char LA::Tokenize(const char* string) {
	FST::FST nanomachinesSon[] = {
		FST_BZINT, FST_STR, FST_FUNCTION, FST_DECLARE, FST_IF, FST_ELSE, FST_COMPARE, FST_STRLEN,
		FST_RETURN, FST_OUT, FST_MAIN,
		FST_LEFTHESIS, FST_RIGHTHESIS, FST_SEMICOLON, FST_COMMA, FST_SQUARE_CLOSE, FST_SQUARE_OPEN,
		FST_LEFTBRACE, FST_BRACELET,
		FST_PLUS, FST_MINUS, FST_STAR, FST_DIRSLASH, FST_EQUALS,FST_MORE,FST_LESS,FST_LESSOREQUALS,FST_MOREOREQUALS, FST_FULLEQUALS, FST_NOTFULLEQUALS,
		FST_ID, FST_STRING_LITERAL, FST_INTEGER_LITERAL
	};
	const int size = sizeof(nanomachinesSon) / sizeof(nanomachinesSon[0]);
	const char tokens[] = {
		LEX_BZINT, LEX_STR, LEX_FUNCTION, LEX_DECLARE, LEX_IF, LEX_ELSE, LEX_COMPARE, LEX_STRLEN,
		LEX_RETURN, LEX_OUT, LEX_MAIN,
		LEX_LEFTHESIS, LEX_RIGHTHESIS, LEX_SEMICOLON, LEX_COMMA, LEX_SQUARE_CLOSE, LEX_SQUARE_OPEN,
		LEX_LEFTBRACE, LEX_BRACELET,
		LEX_PLUS, LEX_MINUS, LEX_STAR, LEX_DIRSLASH, LEX_EQUALS, LEX_MORE, LEX_LESS, LEX_LESSOREQUALS,LEX_MOREOREQUALS,LEX_FULLEQUALS, LEX_NOTFULLEQUALS,
		LEX_ID, LEX_STR_LITERAL, LEX_BZINT_LITERAL
	};

	for (int i = 0; i < size; ++i) {
		if (execute(string, nanomachinesSon[i])) {
			return tokens[i];
		}
	}

	return EOF;
}

void LA::Scan(LT::LexTable& lextable, IT::IdTable& idtable, In::IN& in, Parm::PARM& parm, Log::LOG& log) {
	std::ofstream outfile(parm.out);
	outfile << "01 ";

	std::string accumulator = "";
	std::string curScope = "";
	std::string prevScope = "";
	std::string curFunction = "";

	int Schetchik = 0;

	bool declaredNewFunction = false;

	for (int i = 0, line = 1; in.text[i]; ++i) {
		IT::IDDATATYPE iddatatype;
		auto fillTables = [&] {
			char token = Tokenize(accumulator.c_str());
			if (token == EOF) {
				Log::Write(log, accumulator.c_str(), " - ", "");
				throw ERROR_THROW(129);
			}

			int ti_idx = TI_NULLIDX;

			iddatatype = (token == LEX_BZINT || token == LEX_BZINT_LITERAL) ? IT::IDDATATYPE::BZINT :
				(token == LEX_STR || token == LEX_STR_LITERAL) ? IT::IDDATATYPE::STR : iddatatype;

			if (token == LEX_LEFTHESIS) {
				declaredNewFunction = lextable.size >= 2 && lextable.table[lextable.size - 2].lexeme == LEX_FUNCTION;

				if (declaredNewFunction) {
					prevScope = curScope;
					curScope += curFunction;
				}
			}
			else if (token == LEX_RIGHTHESIS && declaredNewFunction) {
				curScope = prevScope;
				declaredNewFunction = false;
			}
			else if (token == LEX_LEFTBRACE) {
				prevScope = curScope;
				curScope += curFunction;
			}
			else if (token == LEX_BRACELET) {
				curScope.clear();
				curFunction.clear();
			}
			else if (token == LEX_BZINT_LITERAL) {
				int literal = std::stoi(accumulator);
				ti_idx = IT::IsLiteral(idtable, literal);

				if (ti_idx == TI_NULLIDX) {
					std::string name = "L";
					name += std::to_string(Schetchik);
					IT::Add(idtable, { lextable.size, "", name.c_str(), IT::IDTYPE::L, literal });
					++Schetchik;
				}

				token = LEX_LITERAL;
			}
			else if (token == LEX_STR_LITERAL) {
				std::string literal = accumulator.substr(1, accumulator.size() - 2);
				ti_idx = IT::IsLiteral(idtable, literal.c_str());

				if (ti_idx == TI_NULLIDX) {
					std::string name = "L";
					name += std::to_string(Schetchik);
					IT::Add(idtable, { lextable.size, "", name.c_str(), IT::IDTYPE::L, literal.c_str() });
					++Schetchik;
				}

				token = LEX_LITERAL;
			}
			else if (token == LEX_ID || token == LEX_COMPARE || token == LEX_STRLEN) {
				std::string id = accumulator.substr(0, ID_MAXSIZE);
				ti_idx = IT::IsId(idtable, curScope.c_str(), id.c_str());

				if (ti_idx == TI_NULLIDX) {
					if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexeme == LEX_DECLARE
						&& lextable.table[lextable.size - 1].lexeme == LEX_DATATYPE) {
						IT::Add(idtable, { lextable.size,  curScope.c_str(), id.c_str(), iddatatype, IT::IDTYPE::V });
					}
					else if (lextable.size >= 1 && ((lextable.table[lextable.size - 1].lexeme == LEX_FUNCTION) &&
						(token == LEX_STRLEN) || token == LEX_COMPARE)) {
						curFunction = id;

						IT::Add(idtable, { lextable.size,  "", id.c_str(), iddatatype, IT::IDTYPE::F });
					}
					else if (lextable.size >= 1 && (lextable.table[lextable.size - 1].lexeme == LEX_FUNCTION)) {
						curFunction = id;
						IT::Add(idtable, { lextable.size,  curScope.c_str(), id.c_str(), iddatatype, IT::IDTYPE::F });
					}
					else if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexeme == LEX_DATATYPE
						&& declaredNewFunction) {
						IT::Add(idtable, { lextable.size,  curScope.c_str(), id.c_str(), iddatatype, IT::IDTYPE::P });
					}
					else {
						Log::Write(log, accumulator.c_str(), " - ", "");
						throw ERROR_THROW(124);
					}
				}
				else if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexeme == LEX_DECLARE
					|| lextable.size >= 1 && lextable.table[lextable.size - 1].lexeme == LEX_FUNCTION) {
					Log::Write(log, accumulator.c_str(), " - ", "");
					throw ERROR_THROW(123);
				}
			}
			else if (token == LEX_MAIN && curScope.empty()) {
				ti_idx = IT::IsId(idtable, "", accumulator.c_str());

				if (ti_idx != TI_NULLIDX) {
					Log::Write(log, accumulator.c_str(), " - ", "");
					throw ERROR_THROW(131);
				}
				curScope.clear();
				curFunction = accumulator;

				IT::Add(idtable, { lextable.size, "", accumulator.c_str(), IT::IDTYPE::F, 0 });
			}

			token = (token == LEX_BZINT || token == LEX_STR) ? LEX_DATATYPE : token;

			if (token == LEX_ID || token == LEX_LITERAL || token == LEX_MAIN) {
				if (ti_idx == TI_NULLIDX) {
					LT::Add(lextable, { token, line, idtable.size - 1 });
				}
				else {
					LT::Add(lextable, { token, line, ti_idx });
				}
			}
			else if (token == LEX_COMPARE || token == LEX_STRLEN)
			{
				LT::Add(lextable, { token, line, idtable.size - 1});
			}
			else {
				LT::Add(lextable, { token, line, LT_TI_NULLIDX });
			}

			outfile << token;
			accumulator.clear();
		};

		unsigned char& ch = in.text[i];
		if (in.code[ch] == In::IN::T) {
			accumulator += ch;
		}
		else if (in.code[ch] == In::IN::Q) {
			do {
				accumulator += ch;
				i++;
				ch = in.text[i];
			} while (in.code[ch] != In::IN::Q);
			accumulator += ch;
			fillTables();
		}
		else if (in.code[ch] == In::IN::S || in.code[ch] == In::IN::O || ch == IN_CODE_DELIM) {
			if (!accumulator.empty()) {
				fillTables();
			}
			if (in.code[ch] == In::IN::O) {
				accumulator = ch;
				fillTables();
			}
		}

		if (ch == IN_CODE_DELIM) {
			line++;
			if (in.text[i + 1]) {
				outfile << "\n" << std::setw(2) << std::setfill('0') << line << " ";
				i++;
			}
		}

	}

	if (IT::IsId(idtable, "", "main") == TI_NULLIDX) {
		throw ERROR_THROW(130);
	}

	outfile.close();
}