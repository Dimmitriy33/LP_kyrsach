#include "pch.h"
#include "In.h"
#include "Error.h"
#include "IT.h"

In::IN In::getin(wchar_t infile[], wchar_t outfile[]) {
	std::ifstream inputFile(infile, std::ifstream::ate);
	std::ofstream outputFile(outfile);
	size_t fileSize = (size_t)inputFile.tellg();
	IN input;
	int writingPosition = 0;

	if (!inputFile.is_open())
		throw ERROR_THROW(110);

	if (!outputFile.is_open())
		throw ERROR_THROW(110);

	inputFile.seekg(std::ios::beg);

	input.text = DBG_NEW unsigned char[fileSize + 1488];

	for (int column = 0, readChar = 0; readChar != EOF;) {
		readChar = inputFile.get();
		input.size++;

		if (input.code[readChar] == IN::Q) {
			do {
				input.text[writingPosition] = readChar;
				writingPosition++;
				column++;
				readChar = inputFile.get();
				input.size++;
			} while (input.code[readChar] != IN::Q && column < TI_STR_MAXSIZE);
		}

		if (input.code[readChar] == IN::O) {
			if (input.code[input.text[writingPosition - 1]] == IN::S) {
				writingPosition--;
				input.ignor++;
			}
		}

		if (readChar == IN_CODE_ENDL || readChar == EOF) {
			input.lines++;
			if (input.text[writingPosition - 1] != IN_CODE_ENDL) {
				input.text[writingPosition] = IN_CODE_DELIM;
				writingPosition++;
				if (readChar != EOF) {
					input.text[writingPosition] = IN_CODE_ENDL;
					writingPosition++;
				}
				column = 0;
			}
			else {
				input.ignor++;
			}
			continue;
		}
		else if (input.code[readChar] == IN::S) {
			if (input.code[input.text[writingPosition - 1]] != IN::S && input.code[input.text[writingPosition - 1]] != IN::O) {
				input.text[writingPosition] = readChar;
				writingPosition++;
			}
			else {
				input.ignor++;
			}
		}
		else if (input.code[readChar] == IN::F) {
			throw ERROR_THROW_IN(111, input.lines, column);
		}
		else if (input.code[readChar] == IN::I) {
			input.ignor++;
		}
		else if (input.code[readChar] == IN::T || input.code[readChar] == IN::O || input.code[readChar] == IN::Q) {
			input.text[writingPosition] = readChar;
			writingPosition++;
		}
		else {
			input.text[writingPosition] = input.code[readChar];
			writingPosition++;
		}
		column++;
	}
	input.text[writingPosition] = '\0';
	input.size--;
	inputFile.close();
	outputFile << input.text;
	outputFile.close();
	return input;
}

In::IN::IN()
	:size(0), lines(0), ignor(0), text(nullptr), code IN_CODE_TABLE
{	}

In::IN::IN(const IN& other)
	: size(other.size), lines(other.lines), ignor(other.ignor), code IN_CODE_TABLE
{
	text = DBG_NEW unsigned char[strlen((const char*)other.text) + 1];
	std::copy(other.text, other.text + strlen((const char*)other.text) + 1, text);
}

In::IN::~IN() {
	delete[] text;
	text = nullptr;
}