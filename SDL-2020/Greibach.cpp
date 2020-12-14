#include "pch.h"
#include "Greibach.h"
#define GRB_ERROR_SERIES 600

namespace GRB {
#pragma region Rules
	const Greibach greibach(NS('S'), TS('$'), //  Структура программы
		6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0,
			7,
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(7, TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),

			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, // возможные конструкции в функциях
			26,
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),

			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(6, TS('p'), TS('i'), TS('('), NS('W'), TS(')'), TS(';')),

			Rule::Chain(7, TS('p'), TS('c'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('p'), TS('c'), TS('('), NS('W'), TS(')'), TS(';')),

			Rule::Chain(7, TS('p'), TS('x'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('p'), TS('x'), TS('('), NS('W'), TS(')'), TS(';')),

			Rule::Chain(7, TS('d'), TS('f'), TS('x'), TS('('), NS('F'), TS(')'), TS(';') ),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('x'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('x'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),

			Rule::Chain(7, TS('d'), TS('f'), TS('c'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('c'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('c'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),

			Rule::Chain(8, TS('I'), TS('('), NS('E'), TS(')'), TS('['), NS('N'), TS(']'), NS('N')),
			Rule::Chain(12, TS('I'), TS('('), NS('E'), TS(')'), TS('['), NS('N'), TS(']'), TS('E'), TS('['), NS('N'), TS(']'), NS('N'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, // выражения
			10,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('x'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('c'), TS('('), NS('W'), TS(')'))

		),
		Rule(NS('M'), GRB_ERROR_SERIES + 3, // знакин
			40,
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(4, TS('+'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('+'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(4, TS('-'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('-'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(4, TS('*'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('*'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(4, TS('/'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('/'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M')),
			Rule::Chain(2, TS('$'), NS('E')),
			Rule::Chain(4, TS('$'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('$'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('$'), NS('E'), NS('M')),
			Rule::Chain(2, TS('%'), NS('E')),
			Rule::Chain(4, TS('%'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('%'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('%'), NS('E'), NS('M')),
			Rule::Chain(2, TS('<'), NS('E')),
			Rule::Chain(4, TS('<'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('<'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('<'), NS('E'), NS('M')),
			Rule::Chain(2, TS('>'), NS('E')),
			Rule::Chain(4, TS('>'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('>'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('>'), NS('E'), NS('M')),
			Rule::Chain(2, TS('^'), NS('E')),
			Rule::Chain(4, TS('^'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('^'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('^'), NS('E'), NS('M')),
			Rule::Chain(2, TS('&'), NS('E')),
			Rule::Chain(4, TS('&'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('&'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('&'), NS('E'), NS('M'))

		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5, // принимаемые параметры функции
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		)
	);
#pragma endregion

	Rule::Chain::Chain()
		: size(0), nt(nullptr)
	{	}

	Rule::Chain::Chain(short size, GRBALPHABET s, ...)
		: size(size)
	{
		nt = DBG_NEW GRBALPHABET[size];
		int* p = (int*)&s;

		for (short i = 0; i < size; ++i) {
			nt[i] = (GRBALPHABET)p[i];
		}
	}

	Rule::Rule()
		:nn(0x00), iderror(0), size(0), chains(nullptr)
	{	}

	Rule::Rule(GRBALPHABET nn, int iderror, short size, Chain c, ...)
		: nn(nn), iderror(iderror), size(size)
	{
		chains = DBG_NEW Chain[size];
		Chain* p = &c;
		for (int i = 0; i < size; ++i) {
			chains[i] = p[i];
		}
	}

	Greibach::Greibach()
		: size(0), startN(0), stbottomT(0), rules(nullptr)
	{	}

	Greibach::Greibach(GRBALPHABET startN, GRBALPHABET stbottomT, short size, Rule r, ...)
		: startN(startN), stbottomT(stbottomT), size(size)
	{
		rules = DBG_NEW Rule[size];
		const Rule* p = &r;
		for (int i = 0; i < size; ++i) {
			rules[i] = p[i];
		}
	}

	std::string Rule::Chain::getCChain() {
		std::string chain;

		for (int i = 0; i < size; ++i) {
			chain.push_back(Chain::alphabet_to_char(nt[i]));
		}

		return chain;
	}

	std::string Rule::getCRule(short nchain) {
		std::string ruleChain(1, Chain::alphabet_to_char(nn));
		ruleChain += "->";
		ruleChain += chains[nchain].getCChain();

		return ruleChain;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& chain, short n) {
		short output = -1;

		while (n < size && chains[n].nt[0] != t)
			++n;

		output = (n < size) ? n : -1;
		if (output >= 0) {
			chain = chains[output];
		}

		return output;
	}

	short Greibach::getRule(GRBALPHABET nn, Rule& rule) {
		short output = -1;
		short i = 0;

		while (i < size && rules[i].nn != nn)
			i++;

		if (i < size) {
			output = i;
			rule = rules[output];
		}

		return output;
	}

	Rule Greibach::getRule(short n) {
		if (n > size) {
			throw ERROR_THROW(609);
		}

		return rules[n];
	}

	const Greibach& getGreibach() {
		return greibach;
	}
}