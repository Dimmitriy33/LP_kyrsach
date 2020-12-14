#include "pch.h"
#include "Error.h"

//   0 -  99 - системные ошибки
// 100 - 109 - ошибки параметров
// 110 - 119 - ошибки открытия и чтения файлов
// 120 - 129 - ошибки лексического анализатора
// 600 - 699 - ошибки синтаксического анализатора
// 700 - 800 - ошибки семантического анализатора
Error::ERROR errors[ERROR_MAX_ENTRY] = {
	ERROR_ENTRY(0, "Недопустимый код ошибки"),
	ERROR_ENTRY(1, "Системный сбой"),
	ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
	ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100, "Параметр -in должен быть задан"),
	ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104, "Превышена длина входного параметра"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
	ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
	ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
	ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY(120, "Превышено максимальное количество строк в таблице лексем"),
	ERROR_ENTRY(121, "Превышена максимальная емкость таблицы лексем"),
	ERROR_ENTRY(122, "Выход за пределы таблицы лексем"),
	ERROR_ENTRY(123, "Множественное объявление лексемы"),
	ERROR_ENTRY(124, "Идентификатор не объявлен"),
	ERROR_ENTRY(125, "Целочисленный литерал не может быть отрицательным"),
	ERROR_ENTRY(126, "Превышено максимальное количество строк в таблице идентификаторов"),
	ERROR_ENTRY(127, "Превышена максимальная емкость таблицы идентификаторов"),
	ERROR_ENTRY(128, "Выход за пределы таблицы идентификаторов"),
	ERROR_ENTRY(129, "Неопознанная лексема"),
	ERROR_ENTRY(130, "Отсутствует точка входа"),
	ERROR_ENTRY(131, "Несколько точек входа"),
	ERROR_ENTRY_NODEF(132),	ERROR_ENTRY_NODEF(133), ERROR_ENTRY_NODEF(134), ERROR_ENTRY_NODEF(135),
	ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138),	ERROR_ENTRY_NODEF(139),
	ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
	ERROR_ENTRY(600,"Неверная структура программы"),
	ERROR_ENTRY(601,"Ошибочный оператор"),
	ERROR_ENTRY(602,"Ошибка в выражении"),
	ERROR_ENTRY(603,"Ошибка в параметрах функции"),
	ERROR_ENTRY(604,"Ошибка в параметрах вызываемой функции"),
	ERROR_ENTRY(605, "Ошибка в подвыражении"),
	ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608),
	ERROR_ENTRY(609, "Неверный номер правила"),
	ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630),
	ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670),
	ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY(700, "Ошибка в возвращаемом значении"),
	ERROR_ENTRY(701, "Ошибка в параметрах функции"),
	ERROR_ENTRY(702, "Ошибка в параметрах функции библиотеки"),
	ERROR_ENTRY(703, "Ошибка в параметрах функции библиотеки (неверное кол-во аргументов)"),
	ERROR_ENTRY(704, "Ошибка в значении для вывода в консоль"),
	ERROR_ENTRY(705, "Несоответствие возвращаемого и присваемого типов данных"),
	ERROR_ENTRY(706, "Несоответсвие присваимаего типа данных"),
	ERROR_ENTRY(707, "Несоответствие типа функции и возвращаемого значения"),
	ERROR_ENTRY(708, "main должен возвращать числовое значение"),
	ERROR_ENTRY(709, "Использование имени переменной в качестве функции"),
	ERROR_ENTRY(710, "Ошибка в выражении цикла"),
	ERROR_ENTRY(711, "Ошибка в условии if"),
	ERROR_ENTRY(712, "Попытка присовоить отрицательное значение"),
	ERROR_ENTRY_NODEF(713),ERROR_ENTRY_NODEF(714),ERROR_ENTRY_NODEF(715),
	ERROR_ENTRY_NODEF(716),ERROR_ENTRY_NODEF(717),ERROR_ENTRY_NODEF(718),ERROR_ENTRY_NODEF(719),
	ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730), ERROR_ENTRY_NODEF10(740),
	ERROR_ENTRY_NODEF10(750), ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770), ERROR_ENTRY_NODEF10(780),
	ERROR_ENTRY_NODEF10(790),
	ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800)
};

Error::ERROR Error::geterror(int id) {
	ERROR e;

	e.id = (id < 0 || id >= ERROR_MAX_ENTRY) ? 0 : id;
	strcpy_s(e.message, errors[e.id].message);

	std::cout << "Смотри log.txt";
	return e;
}
Error::ERROR Error::geterrorin(int id, int line = -1, int col = -1) {
	ERROR e;

	e = geterror(id);
	e.inext.line = line;
	e.inext.col = col;

	std::cout << "Смотри log.txt";
	return e;
}

Error::ERROR Error::geterrors(int id, int line)
{
	ERROR e;

	e = geterror(id);
	e.inext.line = line;

	std::cout << "\n";

	std::cout << "Смотри log.txt";
	return e;
}