#pragma once
#define ID_MAXSIZE		30
#define SCOPE_MAXSIZE	30
#define TI_MAXSIZE		4096
#define TI_INT_DEFAULT	0x00000000
#define TI_STR_DEFAULT	0x00
#define TI_NULLIDX		((int)0xffffffff)
#define TI_STR_MAXSIZE	255

namespace IT {
	enum class IDDATATYPE { BZINT = 1, STR };
	enum class IDTYPE { V = 1, F, P, L };

	struct Entry {
		int idxfirstLE;
		char scope[SCOPE_MAXSIZE];
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union {
			int vint;
			struct {
				char len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
		} value;
		Entry() = default;
		Entry(int idxfirstLE, const char* scope, const char* id, IDTYPE idtype, int value);
		Entry(int idxfirstLE, const char* scope, const char* id, IDTYPE idtype, const char* value);
		Entry(int idxfirstLE, const char* scope, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
	};

	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
		std::string showIdTable(int startIndex = 0, int endIndex = 0);
	};
	IdTable Create(int size);
	void Add(IdTable& idtable, const Entry& entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, const char scope[SCOPE_MAXSIZE], const char id[ID_MAXSIZE]);
	int IsLiteral(IdTable& idtable, const char literal[TI_STR_MAXSIZE]);
	int IsLiteral(IdTable& idtable, int literal);
	void Delete(IdTable& idtable);

}