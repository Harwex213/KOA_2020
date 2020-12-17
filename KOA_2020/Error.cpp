#include "stdafx.h"

namespace Error
{
	// серии ошибок: 0-99 - системные ошибки
	//				 100-109 - ошибки параметров
	//				 110-119 - ошибки открытия и чтения файлов
	//				 120-XXX - ошибки определения лексем
	ERROR errors[ERROR_MAX_ENTRY+1] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),

		ERROR_ENTRY_NODEF(2),		ERROR_ENTRY_NODEF(3),		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),		ERROR_ENTRY_NODEF(6),		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),		ERROR_ENTRY_NODEF(9),		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),	ERROR_ENTRY_NODEF10(30),	ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),	ERROR_ENTRY_NODEF10(60),	ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),	ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "Параметр -in должен быть задан"),

		ERROR_ENTRY_NODEF(101),		ERROR_ENTRY_NODEF(102),		ERROR_ENTRY_NODEF(103),

		ERROR_ENTRY(104, "Превышена длина входного параметра"),

		ERROR_ENTRY_NODEF(105),		ERROR_ENTRY_NODEF(106),		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),		ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Файл, переданный как -in:, пуст"),
		ERROR_ENTRY(114, "Ошибка при создании файла генерации кода"),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),		ERROR_ENTRY_NODEF(117),		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Ошибка при лексическом анализе: Неправильная лексика ключевого слова"),
		ERROR_ENTRY_NODEF(121),
		ERROR_ENTRY_NODEF(122),
		ERROR_ENTRY_NODEF(123),
		ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY_NODEF(126),
		ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY(140, "Ошибка в подключении библиотек или Неверная структура программы"),
		ERROR_ENTRY(141, "Неверная структура программы"),
		ERROR_ENTRY(142, "Ошибочная инструкция"),
		ERROR_ENTRY(143, "Ошибочное выражение"),
		ERROR_ENTRY(144, "Ошибка в параметрах функции"),
		ERROR_ENTRY(145, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(146),
		ERROR_ENTRY_NODEF(147),
		ERROR_ENTRY_NODEF(148),
		ERROR_ENTRY_NODEF(149),
		ERROR_ENTRY_NODEF10(150),	ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),	ERROR_ENTRY_NODEF10(180),	ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),	ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY(400, "Идентификатор должен быть объявлен до его использования"), //done
		ERROR_ENTRY(401, "Переобъявление идентификатора"), //done
		ERROR_ENTRY(402, "Объявление идентификатора вне функции"), //done
		ERROR_ENTRY(403, "Выход за диапазон допустимых целочисленных значений"), //done
		ERROR_ENTRY(404, "Выход за диапазон допустимого строкового значения"), //done
		ERROR_ENTRY(405, "В программе может быть только одна точка входа (main)"), //done
		ERROR_ENTRY(406, "Отсутствует точка входа в программу (main)"), //done
		ERROR_ENTRY(407, "Лишняя лексема окончания блока"), //done
		ERROR_ENTRY(408, "Неверный параметр возвращаемого типа"), //
		ERROR_ENTRY(409, "Превышено максимальное количество параметров функции (не больше 8)"), //done
		ERROR_ENTRY(410, "Несоответствие типов формальных и фактических параметров при вызове функции"), //
		ERROR_ENTRY(411, "Несоответствие количества формальных и фактических параметров при вызове функци"), //
		ERROR_ENTRY(412, "Невозможно преобразовать тип правостороннего операнда к типу левостороннего"), //
		ERROR_ENTRY(413, "Использован запрещенный оператор с данными операндами."), //
		ERROR_ENTRY(414, "Прототип функции не найден для текущих библиотек."), // done
		ERROR_ENTRY(415, "Идентификатор функции совпадает с идентификатором библиотечной функции"), //done
		ERROR_ENTRY(416, "Подключена неизвестная библиотека"), //
		ERROR_ENTRY_NODEF(419),
		ERROR_ENTRY_NODEF10(420),
		ERROR_ENTRY_NODEF10(430),
		ERROR_ENTRY_NODEF10(440),
		ERROR_ENTRY_NODEF10(450),
		ERROR_ENTRY_NODEF10(460),
		ERROR_ENTRY_NODEF10(470),
		ERROR_ENTRY_NODEF10(480),
		ERROR_ENTRY_NODEF10(490),
		ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF(600),
		ERROR_ENTRY_NODEF(601),
		ERROR_ENTRY_NODEF(602),
		ERROR_ENTRY_NODEF(603),
		ERROR_ENTRY_NODEF(604),
		ERROR_ENTRY_NODEF(605),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609), 
		ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),
		ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),	ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (0 < id < ERROR_MAX_ENTRY)
			return errors[id];
		else
			return errors[0];
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (0 < id < ERROR_MAX_ENTRY)
		{
			errors[id].inext.line = line;
			errors[id].inext.col = col;
			return errors[id];
		}
		else
			return errors[0];
	}
}