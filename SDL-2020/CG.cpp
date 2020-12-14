
#include "pch.h"
#include "CG.h"

CG::Generation::Generation(LT::LexTable lexT, IT::IdTable idT, const wchar_t outfile[PARM_MAX_SIZE])
{
	lextable = lexT;
	idtable = idT;
	out = std::ofstream(outfile);
}

void CG::Generation::Start(const Log::LOG& log)
{
	Head();
	Constants();
	Data();
	Code();
}

void CG::Generation::Head()
{
	out << ".586\n";
	out << ".model flat, stdcall\n";
	out << "includelib libucrt.lib\n";
	out << "includelib kernel32.lib\n";
	out << "includelib ../Debug/SDL_Lib.lib\n";
	out << "ExitProcess PROTO : DWORD\n";
	out << "_compare PROTO : DWORD, :DWORD\n";
	out << "_strln PROTO : DWORD\n";
	out << "_out PROTO : DWORD\n";
	out << "_outInt PROTO : DWORD\n\n";
	out << "\n.stack 4096\n";
}

void CG::Generation::Constants()
{
	out << ".const\n";
	out << "\t_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0\n";
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::L)
		{
			out << "\t" << idtable.table[i].id;
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR)
				out << " BYTE " << '\''<< idtable.table[i].value.vstr.str << '\'' << ", 0";
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::BZINT)
				out << " DWORD " << idtable.table[i].value.vint;
			out << '\n';
		}
}

void CG::Generation::Data()
{
	out << ".data\n";
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::V) {
			out << '\t';
			out << '_' << idtable.table[i].scope << idtable.table[i].id;
			out << "\t\tDWORD 0 ";
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR)
				out << "; str\n";
			else
				out << "; bzint\n";
		}
}

void CG::Generation::Code()
{
	out << "\n.code\n";
	int indOfFunc = -1;
	int indOflex = -1;
	bool func = false;
	bool main = false;
	int stackRet = 0;
	int Ifsn = 0;
	int flagelse = 0;
	char operation;
	for (int i = 0; i < lextable.size; i++) {
		switch (lextable.table[i].lexeme) {
		case LEX_FUNCTION: {
			if (func || main)
				break;
			indOfFunc = i + 1;
			out << '_' << idtable.table[lextable.table[indOfFunc].idxTI].id << " PROC ";
			func = true;
			int backup = i;
			while (lextable.table[i].lexeme != LEX_RIGHTHESIS)
				i++;
			while (lextable.table[i].lexeme != LEX_LEFTHESIS)
			{
				if (lextable.table[i].lexeme == LEX_ID)
				{
					stackRet += 4;
					out << '_' << idtable.table[lextable.table[i].idxTI].id << ": DWORD";
					if (lextable.table[i - 2].lexeme != LEX_LEFTHESIS)
						out << ", ";
				}
				i--;
			}
			i = backup;
			out << std::endl;
			break;
		}
		case LEX_MAIN: {
			main = true;
			out << "main PROC\n";
			break;
		}
		case LEX_BRACELET: {
			if (func)
			{
				out << '_' << idtable.table[lextable.table[indOfFunc].idxTI].id << " ENDP\n\n";
				func = false;
			}
			else
				out << "\tcall\t\tExitProcess\nmain ENDP\n";
			indOfFunc = 0;
			break;
		}
		case LEX_RETURN: {
			if (main) {
				out << "\tpush\t\t";
				if (lextable.table[i + 1].lexeme == LEX_ID) {
					out << '_' << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
				}
				else
					out << idtable.table[lextable.table[i + 1].idxTI].id;
				out << std::endl;
			}
			else
			{
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR) {
					if (idtable.table[lextable.table[i + 1].idxTI].idtype != IT::IDTYPE::L)
						out << "\tmov\t\teax, " << '_' << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\t\t" << stackRet << std::endl;
					else
						out << "\tmov\t\teax, offset " << idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\t\t" << stackRet << std::endl;
				}
				else {
					if (idtable.table[lextable.table[i + 1].idxTI].idtype == IT::IDTYPE::L)
						out << "\tmov\t\teax, " << idtable.table[lextable.table[i + 1].idxTI].id
						<< "\n\tret\t\t" << stackRet << std::endl;
					else
						out << "\tmov\t\teax, " << '_' << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\t\t" << stackRet << std::endl;
				}
				stackRet = 0;
			}
			break;
		}
		case LEX_OUT: {
			if (lextable.table[i + 1].lexeme == LEX_ID) {
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::BZINT) {
					out << "\tpush\t\t" << '_' << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_outInt\n\n";
				}
				else {
					out << "\tpush\t\t" << '_' << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_out\n\n";
				}
			}
			else if (lextable.table[i + 1].lexeme == LEX_LITERAL) {
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::BZINT) {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_outInt\n\n";
				}
				else {
					out << "\tpush\t\toffset " << idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_out\n\n";
				}
			}
			break;
		}
		case LEX_EQUALS: {
			indOflex = i - 1;
			while (lextable.table[i].lexeme != LEX_SEMICOLON) {
				if (lextable.table[i].lexeme == LEX_ID) {
					if (idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F)
						if (!func)
							out << "\tpush\t\t" << '_' << idtable.table[lextable.table[i].idxTI].scope
							<< idtable.table[lextable.table[i].idxTI].id << "\n";
						else
							out << "\tpush\t\t" << '_' << idtable.table[lextable.table[i].idxTI].id << "\n";
					
				}
				if (lextable.table[i].lexeme == LEX_LITERAL) {
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::BZINT)
						out << "\tpush\t\t";
					else
						out << "\tpush\t\toffset ";
					out << idtable.table[lextable.table[i].idxTI].id << "\n";
				}
				if (lextable.table[i].lexeme == LEX_COMMERCIALAT)
				{
					out << "\tcall\t\t" << '_' << idtable.table[lextable.table[i].idxTI].id << "\n";
					out << "\tpush\t\teax\n";
				}
				if (lextable.table[i].lexeme == LEX_PLUS)
				{
					out << "\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tebx\n";
					out << "\tadd\t\teax, ebx\n";
					out << "\tpush\t\teax\n";
					out << "\n";
				}
				if (lextable.table[i].lexeme == LEX_MINUS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tsub\t\teax, ebx\n";
					out << "\tpush\t\teax\n";
					out << "\n";
				}
				if (lextable.table[i].lexeme == LEX_MORE)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tja\t\tMORE" << lextable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tjb\t\tLESS" << lextable.table[i].sn << "\n";
					out << "MORE" << lextable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "LESS" << lextable.table[i].sn << ":";
					out << "\n";
				}

				if (lextable.table[i].lexeme == LEX_LESS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjb\t\tLESS" << lextable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tja\t\tMORE" << lextable.table[i].sn << "\n";
					out << "LESS" << lextable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "MORE" << lextable.table[i].sn << ":";
					out << "\n";
				}

				if (lextable.table[i].lexeme == LEX_FULLEQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjne\t\tNOTEQUAL" << lextable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tje\t\tEQUAL" << lextable.table[i].sn << "\n";
					out << "EQUAL" << lextable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "NOTEQUAL" << lextable.table[i].sn << ":";
					out << "\n";
				}

				if (lextable.table[i].lexeme == LEX_NOTFULLEQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjne\t\tNOTEQUAL" << lextable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tje\t\tEQUAL" << lextable.table[i].sn << "\n";
					out << "NOTEQUAL" << lextable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "EQUAL" << lextable.table[i].sn << ":";
					out << "\n";
				}

				if (lextable.table[i].lexeme == LEX_MOREOREQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjae\t\tMOREOREQUAL" << lextable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tjnb\t\tLESS" << lextable.table[i].sn << "\n";
					out << "MOREOREQUAL" << lextable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "LESS" << lextable.table[i].sn << ":";
					out << "\n";
				}

				if (lextable.table[i].lexeme == LEX_LESSOREQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjbe\t\tLESSOREQUALS" << lextable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tjna\t\tMORE" << lextable.table[i].sn << "\n";
					out << "LESSOREQUALS" << lextable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "MORE" << lextable.table[i].sn << ":";
					out << "\n";
				}

				i++;
			}
			out << "\tpop\t\t\t" << '_' << idtable.table[lextable.table[indOflex].idxTI].scope
				<< idtable.table[lextable.table[indOflex].idxTI].id << "\n\n";
			break;
		}
		
		case LEX_IF: {
			flagelse = 0;
			operation = ' ';
			if(lextable.table[i + 2].lexeme != LEX_LITERAL)
				out << "\tpush\t\t" << '_' << idtable.table[lextable.table[indOflex].idxTI].scope << idtable.table[lextable.table[i + 2].idxTI].id << "\n";
			else
				out << "\tpush\t\t" << idtable.table[lextable.table[i + 2].idxTI].id << "\n";

			if (lextable.table[i + 4].lexeme != LEX_LITERAL)
				out << "\tpush\t\t" << '_' << idtable.table[lextable.table[indOflex].idxTI].scope << idtable.table[lextable.table[i + 4].idxTI].id << "\n";
			else
				out << "\tpush\t\t" << idtable.table[lextable.table[i + 4].idxTI].id << "\n";

			out << "\tpop\t\tebx\n";
			out << "\tpop\t\teax\n";
			out << "\tcmp\t\teax, ebx\n";
			Ifsn = lextable.table[i].sn;
			int j = i;
			while (lextable.table[j].lexeme != LEX_SQUARE_CLOSE)
				j++;
			if (lextable.table[j + 1].lexeme == LEX_ELSE)
				flagelse = 1;
			switch (lextable.table[i + 3].lexeme) {

			case LEX_FULLEQUALS:
			{
				out << "\tjne\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tje\t\tTRUE" << Ifsn << "\n";
					operation = LEX_FULLEQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_NOTFULLEQUALS:
			{
				out << "\tje\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjne\t\tTRUE" << Ifsn << "\n";
					operation = LEX_EQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_MORE:
			{
				out << "\tjna\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjnb\t\tTRUE" << Ifsn << "\n";
					operation = LEX_MORE;
					out << "TRUE" << Ifsn << ": " << "\n";

				}
				break;
			}

			case LEX_LESS:
			{	
				out << "\tjnb\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjna\t\tTRUE" << Ifsn << "\n";
					operation = LEX_LESS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_MOREOREQUALS:
			{
				out << "\tjb\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tja\t\tTRUE" << Ifsn << "\n";
					operation = LEX_MOREOREQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_LESSOREQUALS:
			{
				out << "\tja\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjb\t\tTRUE" << Ifsn << "\n";
					operation = LEX_LESSOREQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;


				
			}
			default:break;
			}
			break;
			
		}

		case LEX_SQUARE_CLOSE: {
			if (flagelse == 1 && lextable.table[i + 1].lexeme == LEX_ELSE) {
				out << "\tjmp\t\tIFOUT" << Ifsn << "\n";
				out << "FALSE" << Ifsn << ": " << "\n";
			}
			else if (flagelse == 0 && lextable.table[i + 1].lexeme != LEX_ELSE) {
				out << "FALSE" << Ifsn << ": " << "\n";
			}
			else if (flagelse == 1)
				out << "IFOUT" << Ifsn << ": " << "\n";
			break;
		}
		default:break;
		}
	}
	out << "end main\n";
}


