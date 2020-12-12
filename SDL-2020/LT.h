#pragma once
#define LT_MAXSIZE				4096
#define LT_TI_NULLIDX			((int)0xffffffff)
#define LEX_BZINT				'n'
#define LEX_STR					's'
#define LEX_DATATYPE			't'
#define LEX_ID					'i'
#define LEX_BZINT_LITERAL		'1'
#define LEX_STR_LITERAL			'2'
#define LEX_LITERAL				'l'
#define LEX_FUNCTION			'f'
#define LEX_DECLARE				'd'
#define LEX_COMPARE				'x'
#define LEX_STRLEN				'c'
#define LEX_IF					'I'
#define LEX_ELSE				'E'
#define LEX_ECHO				'y'
#define LEX_RETURN				'r'
#define LEX_OUT					'p'
#define LEX_MAIN				'm'
#define LEX_SEMICOLON			';'
#define LEX_COMMA				','
#define LEX_LEFTBRACE			'{'
#define LEX_BRACELET			'}'
#define LEX_LEFTHESIS			'('
#define LEX_RIGHTHESIS			')'
#define LEX_PLUS				'+'
#define LEX_MINUS				'-'
#define LEX_STAR				'*'
#define LEX_DIRSLASH			'/'
#define LEX_EQUALS				'='
#define LEX_MORE				'>'
#define LEX_LESS				'<'
#define LEX_LESSOREQUALS		'$'
#define LEX_MOREOREQUALS		'%'
#define LEX_FULLEQUALS			'^'
#define LEX_NOTFULLEQUALS		'&'
#define LEX_COMMERCIALAT		'@'
#define LEX_SQUARE_OPEN			'['
#define LEX_SQUARE_CLOSE		']'



namespace LT {
	struct Entry {
		char lexeme;
		int sn;
		int idxTI;
	};

	struct LexTable {
		int maxsize;
		int size;
		Entry* table;
		std::string showLexTable(int startIndex = 0, int endIndex = 0);
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);

}