
#include "pch.h"
#include "Error.h"
#include "FST.h"
#include "Greibach.h"
#include "In.h"
#include "IT.h"
#include "Lexer.h"
#include "Log.h"
#include "LT.h"
#include "MFST.h"
#include "Parm.h"
#include "SA.h"
#include "PolishNotation.h"
#include "CG.h"


int _tmain(int argc, _TCHAR* argv[]) {
	setlocale(LC_ALL, "rus");

	Log::LOG log = Log::INITLOG;

	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", "\n", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);

		LA::Scan(lextable, idtable, in, parm, log);

		#define LEXEM
		#define IDENT
		#define SYNTAX 
		#define SEMANT 
		#define POLISH
		#define	GENERATION

		#ifdef SYNTAX

		MFST_TRACE_START
			MFST::Mfst mfst(lextable, GRB::getGreibach());
		mfst.start(*log.stream);
		#endif // SYNTAX


		#ifdef SEMANT
		SA::SemanticAnalyzer SAnalyzer = SA::SemanticAnalyzer(lextable, idtable);
		SAnalyzer.Start(log);
		#endif // SEMANT


		#ifdef POLISH
		PN::PolishNotation(lextable, idtable);
		#endif // POLISH

		#ifdef LEXEM

		std::cout << "/ ==============############    Таблица лексем   ############==================== */\n";
		std::cout << lextable.showLexTable();

		#endif // LEXEM

		#ifdef IDENT

		std::cout << "\n/ =============############    Таблица идентификаторов   ############=================== */\n";
		std::cout << idtable.showIdTable();

		#endif // IDENT

		#ifdef GENERATION
		CG::Generator CodeBuilder = CG::Generator(lextable, idtable, parm.out);
		CodeBuilder.Start(log);
		#endif // GENERATION


		LT::Delete(lextable);
		IT::Delete(idtable);
		Log::Close(log);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}

#ifdef _DEBUG
	int hasMemoryLeaks = _CrtDumpMemoryLeaks();
#else
	system("pause");
#endif // _DEBUG
	return 0;
}