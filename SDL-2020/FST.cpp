#include "pch.h"
#include "FST.h"

FST::RELATION::RELATION(char c, short ns)
	: symbol(c), nnode(ns)
{ }

FST::NODE::NODE()
	: n_relation(0), relations(NULL)
{ }

FST::NODE::NODE(short n, RELATION rel, ...)
	: n_relation(n)
{
	RELATION* p = &rel;
	relations = DBG_NEW RELATION[n];

	for (short i = 0; i < n; ++i)
		relations[i] = p[i];
}

FST::FST::FST(short ns, NODE n, ...)
	: position(-1), nstates(ns)
{
	nodes = DBG_NEW NODE[ns];
	NODE* p = &n;

	for (int i = 0; i < ns; ++i)
		nodes[i] = p[i];

	rstates = DBG_NEW short[nstates];
	memset(rstates, 0xff, sizeof(short) * nstates);
	rstates[0] = 0;
}

FST::FST::~FST() {
	for (int i = 0; i < nstates; ++i) {
		delete nodes[i].relations;
		nodes[i].relations = nullptr;
	}

	delete[] nodes;
	nodes = nullptr;

	delete[] rstates;
	rstates = nullptr;
}

bool step(const char* string, FST::FST& fst, short*& rstates) {
	bool output = false;

	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; ++i)
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; ++j)
				if (fst.nodes[i].relations[j].symbol == string[fst.position]) {
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					output = true;
				}

	return output;
}

bool FST::execute(const char* string, FST& fst) {
	short* rstates = DBG_NEW short[fst.nstates];
	short lstring = (short)strlen(string);
	bool output = true;

	memset(rstates, 0xff, sizeof(short) * fst.nstates);

	for (short i = 0; i < lstring && output; ++i) {
		fst.position++;
		output = step(string, fst, rstates);
	}
	delete[] rstates;

	return output ? (fst.rstates[fst.nstates - 1] == lstring) : output;
}