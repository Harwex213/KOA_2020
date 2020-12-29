#pragma once
#include "LT.h"
#define GRAPH_UINT LEX_UINT, string, 5, \
FST::NODE(1, FST::RELATION('u', 1)), \
FST::NODE(1, FST::RELATION('i', 2)), \
FST::NODE(1, FST::RELATION('n', 3)), \
FST::NODE(1, FST::RELATION('t', 4)), \
FST::NODE()

#define GRAPH_STRING LEX_STRING, string, 7, \
FST::NODE(1, FST::RELATION('s', 1)), \
FST::NODE(1, FST::RELATION('t', 2)), \
FST::NODE(1, FST::RELATION('r', 3)), \
FST::NODE(1, FST::RELATION('i', 4)), \
FST::NODE(1, FST::RELATION('n', 5)), \
FST::NODE(1, FST::RELATION('g', 6)), \
FST::NODE()

#define GRAPH_BOOL LEX_BOOL, string, 5, \
FST::NODE(1, FST::RELATION('b', 1)), \
FST::NODE(1, FST::RELATION('o', 2)), \
FST::NODE(1, FST::RELATION('o', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE()

#define GRAPH_INCLUDE LEX_INCLUDE, string, 9, \
FST::NODE(1, FST::RELATION('#', 1)), \
FST::NODE(1, FST::RELATION('i', 2)), \
FST::NODE(1, FST::RELATION('n', 3)), \
FST::NODE(1, FST::RELATION('c', 4)), \
FST::NODE(1, FST::RELATION('l', 5)), \
FST::NODE(1, FST::RELATION('u', 6)), \
FST::NODE(1, FST::RELATION('d', 7)), \
FST::NODE(1, FST::RELATION('e', 8)), \
FST::NODE()

#define GRAPH_PROTOTYPE LEX_PROTOTYPE, string, 10, \
FST::NODE(1, FST::RELATION('p', 1)), \
FST::NODE(1, FST::RELATION('r', 2)), \
FST::NODE(1, FST::RELATION('o', 3)), \
FST::NODE(1, FST::RELATION('t', 4)), \
FST::NODE(1, FST::RELATION('o', 5)), \
FST::NODE(1, FST::RELATION('t', 6)), \
FST::NODE(1, FST::RELATION('y', 7)), \
FST::NODE(1, FST::RELATION('p', 8)), \
FST::NODE(1, FST::RELATION('e', 9)), \
FST::NODE()

#define GRAPH_FUNCTION LEX_FUNCTION, string, 9, \
FST::NODE(1, FST::RELATION('f', 1)), \
FST::NODE(1, FST::RELATION('u', 2)), \
FST::NODE(1, FST::RELATION('n', 3)), \
FST::NODE(1, FST::RELATION('c', 4)), \
FST::NODE(1, FST::RELATION('t', 5)), \
FST::NODE(1, FST::RELATION('i', 6)), \
FST::NODE(1, FST::RELATION('o', 7)), \
FST::NODE(1, FST::RELATION('n', 8)), \
FST::NODE()

#define GRAPH_IF LEX_IF, string, 3, \
FST::NODE(1, FST::RELATION('i', 1)), \
FST::NODE(1, FST::RELATION('f', 2)), \
FST::NODE()

#define GRAPH_ELSE LEX_ELSE, string, 5, \
FST::NODE(1, FST::RELATION('e', 1)), \
FST::NODE(1, FST::RELATION('l', 2)), \
FST::NODE(1, FST::RELATION('s', 3)), \
FST::NODE(1, FST::RELATION('e', 4)), \
FST::NODE()

#define GRAPH_WHILE LEX_WHILE, string, 6, \
FST::NODE(1, FST::RELATION('w', 1)), \
FST::NODE(1, FST::RELATION('h', 2)), \
FST::NODE(1, FST::RELATION('i', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE(1, FST::RELATION('e', 5)), \
FST::NODE()

#define GRAPH_MAIN LEX_MAIN, string, 5, \
FST::NODE(1, FST::RELATION('m', 1)), \
FST::NODE(1, FST::RELATION('a', 2)), \
FST::NODE(1, FST::RELATION('i', 3)), \
FST::NODE(1, FST::RELATION('n', 4)), \
FST::NODE()

#define GRAPH_RETURN LEX_RETURN, string, 7, \
FST::NODE(1, FST::RELATION('r', 1)), \
FST::NODE(1, FST::RELATION('e', 2)), \
FST::NODE(1, FST::RELATION('t', 3)), \
FST::NODE(1, FST::RELATION('u', 4)), \
FST::NODE(1, FST::RELATION('r', 5)), \
FST::NODE(1, FST::RELATION('n', 6)), \
FST::NODE()

#define GRAPH_PARENTHESES_LEFT LEX_PARENTHESES_LEFT, string, 2, \
FST::NODE(1, FST::RELATION('(', 1)), \
FST::NODE()


#define GRAPH_PARENTHESES_RIGHT LEX_PARENTHESES_RIGHT, string, 2, \
FST::NODE(1, FST::RELATION(')', 1)), \
FST::NODE()


#define GRAPH_BRACKETS_LEFT LEX_BRACKETS_LEFT, string, 2, \
FST::NODE(1, FST::RELATION('[', 1)), \
FST::NODE()


#define GRAPH_BRACKETS_RIGHT LEX_BRACKETS_RIGHT, string, 2, \
FST::NODE(1, FST::RELATION(']', 1)), \
FST::NODE()


#define GRAPH_BRACES_LEFT LEX_BRACES_LEFT, string, 2, \
FST::NODE(1, FST::RELATION('{', 1)), \
FST::NODE()


#define GRAPH_BRACES_RIGHT LEX_BRACES_RIGHT, string, 2, \
FST::NODE(1, FST::RELATION('}', 1)), \
FST::NODE()


#define GRAPH_PLUS LEX_PLUS, string, 2, \
FST::NODE(1, FST::RELATION('+', 1)), \
FST::NODE()


#define GRAPH_MINUS LEX_MINUS, string, 2, \
FST::NODE(1, FST::RELATION('-', 1)), \
FST::NODE()


#define GRAPH_MULTIPLY LEX_MULTIPLY, string, 2, \
FST::NODE(1, FST::RELATION('*', 1)), \
FST::NODE()


#define GRAPH_DIVISION LEX_DIVISION, string, 2, \
FST::NODE(1, FST::RELATION('/', 1)), \
FST::NODE()


#define GRAPH_EQUALLY LEX_EQUALLY, string, 3, \
FST::NODE(1, FST::RELATION('=', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_NON_EQUALLY LEX_NON_EQUALLY, string, 3, \
FST::NODE(1, FST::RELATION('!', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_MORE LEX_MORE, string, 2, \
FST::NODE(1, FST::RELATION('>', 1)), \
FST::NODE()


#define GRAPH_LESS LEX_LESS, string, 2, \
FST::NODE(1, FST::RELATION('<', 1)), \
FST::NODE()


#define GRAPH_MORE_OR_EQUAL LEX_MORE_OR_EQUAL, string, 3, \
FST::NODE(1, FST::RELATION('>', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_LESS_OR_EQUAL LEX_LESS_OR_EQUAL, string, 3, \
FST::NODE(1, FST::RELATION('<', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_OR LEX_OR, string, 2, \
FST::NODE(1, FST::RELATION('|', 1)), \
FST::NODE()


#define GRAPH_AND LEX_AND, string, 2, \
FST::NODE(1, FST::RELATION('&', 1)), \
FST::NODE()


#define GRAPH_INVERSION LEX_INVERSION, string, 2, \
FST::NODE(1, FST::RELATION('~', 1)), \
FST::NODE()


#define GRAPH_ASSIGNMENT LEX_ASSIGNMENT, string, 2, \
FST::NODE(1, FST::RELATION('=', 1)), \
FST::NODE()


#define GRAPH_COMMA LEX_COMMA, string, 2, \
FST::NODE(1, FST::RELATION(',', 1)), \
FST::NODE()


#define GRAPH_SEMICOLON LEX_SEMICOLON, string, 2, \
FST::NODE(1, FST::RELATION(';', 1)), \
FST::NODE()


#define GRAPH_IDENTIFICATOR LEX_IDENTIFICATOR, string, 2, \
FST::NODE(52, \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
	FST::RELATION('A', 1), \
	FST::RELATION('B', 1), \
	FST::RELATION('C', 1), \
	FST::RELATION('D', 1), \
	FST::RELATION('E', 1), \
	FST::RELATION('F', 1), \
	FST::RELATION('G', 1), \
	FST::RELATION('H', 1), \
	FST::RELATION('I', 1), \
	FST::RELATION('J', 1), \
	FST::RELATION('K', 1), \
	FST::RELATION('L', 1), \
	FST::RELATION('M', 1), \
	FST::RELATION('N', 1), \
	FST::RELATION('O', 1), \
	FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), \
	FST::RELATION('R', 1), \
	FST::RELATION('S', 1), \
	FST::RELATION('T', 1), \
	FST::RELATION('U', 1), \
	FST::RELATION('V', 1), \
	FST::RELATION('W', 1), \
	FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), \
	FST::RELATION('Z', 1)), \
FST::NODE(63, \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
	FST::RELATION('A', 1), \
	FST::RELATION('B', 1), \
	FST::RELATION('C', 1), \
	FST::RELATION('D', 1), \
	FST::RELATION('E', 1), \
	FST::RELATION('F', 1), \
	FST::RELATION('G', 1), \
	FST::RELATION('H', 1), \
	FST::RELATION('I', 1), \
	FST::RELATION('J', 1), \
	FST::RELATION('K', 1), \
	FST::RELATION('L', 1), \
	FST::RELATION('M', 1), \
	FST::RELATION('N', 1), \
	FST::RELATION('O', 1), \
	FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), \
	FST::RELATION('R', 1), \
	FST::RELATION('S', 1), \
	FST::RELATION('T', 1), \
	FST::RELATION('U', 1), \
	FST::RELATION('V', 1), \
	FST::RELATION('W', 1), \
	FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), \
	FST::RELATION('Z', 1), \
	FST::RELATION('_', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1))

#define GRAPH_LITERAL_INT_DEC LEX_LITERAL, string, 1, \
FST::NODE(10, \
	FST::RELATION('1', 0), \
	FST::RELATION('2', 0), \
	FST::RELATION('3', 0), \
	FST::RELATION('4', 0), \
	FST::RELATION('5', 0), \
	FST::RELATION('6', 0), \
	FST::RELATION('7', 0), \
	FST::RELATION('8', 0), \
	FST::RELATION('9', 0), \
	FST::RELATION('0', 0))

#define GRAPH_LITERAL_INT_OCT LEX_LITERAL, string, 2, \
FST::NODE(9, \
	FST::RELATION('1', 0), \
	FST::RELATION('2', 0), \
	FST::RELATION('3', 0), \
	FST::RELATION('4', 0), \
	FST::RELATION('5', 0), \
	FST::RELATION('6', 0), \
	FST::RELATION('7', 0), \
	FST::RELATION('0', 0), \
	FST::RELATION('e', 1)), \
FST::NODE()

#define GRAPH_LITERAL_STRING LEX_LITERAL, string, 3, \
FST::NODE(1, FST::RELATION('\"', 1)), \
FST::NODE(160, \
	FST::RELATION(' ', 1), \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
	FST::RELATION('A', 1), \
	FST::RELATION('B', 1), \
	FST::RELATION('C', 1), \
	FST::RELATION('D', 1), \
	FST::RELATION('E', 1), \
	FST::RELATION('F', 1), \
	FST::RELATION('G', 1), \
	FST::RELATION('H', 1), \
	FST::RELATION('I', 1), \
	FST::RELATION('J', 1), \
	FST::RELATION('K', 1), \
	FST::RELATION('L', 1), \
	FST::RELATION('M', 1), \
	FST::RELATION('N', 1), \
	FST::RELATION('O', 1), \
	FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), \
	FST::RELATION('R', 1), \
	FST::RELATION('S', 1), \
	FST::RELATION('T', 1), \
	FST::RELATION('U', 1), \
	FST::RELATION('V', 1), \
	FST::RELATION('W', 1), \
	FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), \
	FST::RELATION('Z', 1), \
	FST::RELATION('0', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1), \
	FST::RELATION('à', 1), \
	FST::RELATION('á', 1), \
	FST::RELATION('â', 1), \
	FST::RELATION('ã', 1), \
	FST::RELATION('ä', 1), \
	FST::RELATION('å', 1), \
	FST::RELATION('¸', 1), \
	FST::RELATION('æ', 1), \
	FST::RELATION('ç', 1), \
	FST::RELATION('è', 1), \
	FST::RELATION('é', 1), \
	FST::RELATION('ê', 1), \
	FST::RELATION('ë', 1), \
	FST::RELATION('ì', 1), \
	FST::RELATION('í', 1), \
	FST::RELATION('î', 1), \
	FST::RELATION('ï', 1), \
	FST::RELATION('ð', 1), \
	FST::RELATION('ñ', 1), \
	FST::RELATION('ò', 1), \
	FST::RELATION('ó', 1), \
	FST::RELATION('ô', 1), \
	FST::RELATION('õ', 1), \
	FST::RELATION('ö', 1), \
	FST::RELATION('÷', 1), \
	FST::RELATION('ø', 1), \
	FST::RELATION('ù', 1), \
	FST::RELATION('ü', 1), \
	FST::RELATION('ú', 1), \
	FST::RELATION('û', 1), \
	FST::RELATION('ý', 1), \
	FST::RELATION('þ', 1), \
	FST::RELATION('ÿ', 1), \
	FST::RELATION('À', 1), \
	FST::RELATION('Á', 1), \
	FST::RELATION('Â', 1), \
	FST::RELATION('Ã', 1), \
	FST::RELATION('Ä', 1), \
	FST::RELATION('Å', 1), \
	FST::RELATION('¨', 1), \
	FST::RELATION('Æ', 1), \
	FST::RELATION('Ç', 1), \
	FST::RELATION('È', 1), \
	FST::RELATION('É', 1), \
	FST::RELATION('Ê', 1), \
	FST::RELATION('Ë', 1), \
	FST::RELATION('Ì', 1), \
	FST::RELATION('Í', 1), \
	FST::RELATION('Î', 1), \
	FST::RELATION('Ï', 1), \
	FST::RELATION('Ð', 1), \
	FST::RELATION('Ñ', 1), \
	FST::RELATION('Ò', 1), \
	FST::RELATION('Ó', 1), \
	FST::RELATION('Ô', 1), \
	FST::RELATION('Õ', 1), \
	FST::RELATION('Ö', 1), \
	FST::RELATION('×', 1), \
	FST::RELATION('Ø', 1), \
	FST::RELATION('Ù', 1), \
	FST::RELATION('Ü', 1), \
	FST::RELATION('Ú', 1), \
	FST::RELATION('Û', 1), \
	FST::RELATION('Ý', 1), \
	FST::RELATION('Þ', 1), \
	FST::RELATION('ß', 1), \
	FST::RELATION('=', 1), \
	FST::RELATION('+', 1), \
	FST::RELATION('-', 1), \
	FST::RELATION('*', 1), \
	FST::RELATION('/', 1), \
	FST::RELATION('(', 1), \
	FST::RELATION(')', 1), \
	FST::RELATION('{', 1), \
	FST::RELATION('}', 1), \
	FST::RELATION('[', 1), \
	FST::RELATION(']', 1), \
	FST::RELATION(';', 1), \
	FST::RELATION(',', 1), \
	FST::RELATION('?', 1), \
	FST::RELATION('!', 1), \
	FST::RELATION('#', 1), \
	FST::RELATION('\'', 1), \
	FST::RELATION('`', 1), \
	FST::RELATION('^', 1), \
	FST::RELATION('@', 1), \
	FST::RELATION('_', 1), \
	FST::RELATION('\\', 1), \
	FST::RELATION('%', 1), \
	FST::RELATION('¹', 1), \
	FST::RELATION('&', 1), \
	FST::RELATION('~', 1), \
	FST::RELATION('|', 1), \
	FST::RELATION('?', 1), \
	FST::RELATION('.', 1), \
	FST::RELATION(':', 1), \
	FST::RELATION('\"', 2)), \
FST::NODE()

#define GRAPH_TRUE LEX_LITERAL, string, 5, \
FST::NODE(1, FST::RELATION('t', 1)), \
FST::NODE(1, FST::RELATION('r', 2)), \
FST::NODE(1, FST::RELATION('u', 3)), \
FST::NODE(1, FST::RELATION('e', 4)), \
FST::NODE()

#define GRAPH_FALSE LEX_LITERAL, string, 6, \
FST::NODE(1, FST::RELATION('f', 1)), \
FST::NODE(1, FST::RELATION('a', 2)), \
FST::NODE(1, FST::RELATION('l', 3)), \
FST::NODE(1, FST::RELATION('s', 4)), \
FST::NODE(1, FST::RELATION('e', 5)), \
FST::NODE()

#define GRAPHS_AMOUNT						39
#define GRAPH_UINT_INDEX					0
#define GRAPH_STRING_INDEX					1
#define GRAPH_BOOL_INDEX					2
#define GRAPH_TRUE_LITERAL_INDEX			3
#define GRAPH_FALSE_LITERAL_INDEX			4
#define GRAPH_PLUS_INDEX					GRAPHS_AMOUNT - 17
#define GRAPH_MINUS_INDEX					GRAPHS_AMOUNT - 16
#define GRAPH_MULTYPLY_INDEX				GRAPHS_AMOUNT - 15
#define GRAPH_DIVISION_INDEX				GRAPHS_AMOUNT - 14
#define GRAPH_EQUALLY_INDEX					GRAPHS_AMOUNT - 13
#define GRAPH_NON_EQUALLY_INDEX				GRAPHS_AMOUNT - 12
#define GRAPH_MORE_INDEX					GRAPHS_AMOUNT - 11
#define GRAPH_LESS_INDEX					GRAPHS_AMOUNT - 10
#define GRAPH_MORE_OR_EQUAL_INDEX			GRAPHS_AMOUNT - 9
#define GRAPH_LESS_OR_EQUAL_INDEX			GRAPHS_AMOUNT - 8
#define GRAPH_OR_INDEX						GRAPHS_AMOUNT - 7
#define GRAPH_AND_INDEX						GRAPHS_AMOUNT - 6
#define GRAPH_INVERSION_INDEX				GRAPHS_AMOUNT - 5
#define GRAPH_INT_DEC_LITERAL_INDEX			GRAPHS_AMOUNT - 3
#define GRAPH_INT_OCT_LITERAL_INDEX			GRAPHS_AMOUNT - 2
#define GRAPH_STRING_LITERAL_INDEX			GRAPHS_AMOUNT - 1

#define GRAPHS_INITILIZATION \
FST::FST(GRAPH_UINT), \
FST::FST(GRAPH_STRING), \
FST::FST(GRAPH_BOOL), \
FST::FST(GRAPH_TRUE), \
FST::FST(GRAPH_FALSE), \
FST::FST(GRAPH_PROTOTYPE), \
FST::FST(GRAPH_INCLUDE), \
FST::FST(GRAPH_FUNCTION), \
FST::FST(GRAPH_IF), \
FST::FST(GRAPH_ELSE), \
FST::FST(GRAPH_WHILE), \
FST::FST(GRAPH_MAIN), \
FST::FST(GRAPH_RETURN), \
FST::FST(GRAPH_PARENTHESES_LEFT), \
FST::FST(GRAPH_PARENTHESES_RIGHT), \
FST::FST(GRAPH_BRACKETS_LEFT), \
FST::FST(GRAPH_BRACKETS_RIGHT), \
FST::FST(GRAPH_BRACES_LEFT), \
FST::FST(GRAPH_BRACES_RIGHT), \
FST::FST(GRAPH_ASSIGNMENT), \
FST::FST(GRAPH_COMMA), \
FST::FST(GRAPH_SEMICOLON), \
FST::FST(GRAPH_PLUS), \
FST::FST(GRAPH_MINUS), \
FST::FST(GRAPH_MULTIPLY), \
FST::FST(GRAPH_DIVISION), \
FST::FST(GRAPH_EQUALLY), \
FST::FST(GRAPH_NON_EQUALLY), \
FST::FST(GRAPH_MORE), \
FST::FST(GRAPH_LESS), \
FST::FST(GRAPH_MORE_OR_EQUAL), \
FST::FST(GRAPH_LESS_OR_EQUAL), \
FST::FST(GRAPH_OR), \
FST::FST(GRAPH_AND), \
FST::FST(GRAPH_INVERSION), \
FST::FST(GRAPH_IDENTIFICATOR), \
FST::FST(GRAPH_LITERAL_INT_DEC), \
FST::FST(GRAPH_LITERAL_INT_OCT), \
FST::FST(GRAPH_LITERAL_STRING)

namespace Graphs
{
	struct GRAPHS
	{
		char* string = NULL;
		std::vector<FST::FST*> tests[256];

		GRAPHS()
		{
			FST::FST* fstArray = new FST::FST[GRAPHS_AMOUNT] { GRAPHS_INITILIZATION };
			fstArray[GRAPH_UINT_INDEX].idDataType = IT::UINT;
			fstArray[GRAPH_STRING_INDEX].idDataType = IT::STRING;
			fstArray[GRAPH_BOOL_INDEX].idDataType = IT::BOOL;
			fstArray[GRAPH_TRUE_LITERAL_INDEX].idDataType = IT::BOOL;
			fstArray[GRAPH_FALSE_LITERAL_INDEX].idDataType = IT::BOOL;
			fstArray[GRAPH_INT_DEC_LITERAL_INDEX].idDataType = IT::UINT;
			fstArray[GRAPH_INT_OCT_LITERAL_INDEX].idDataType = IT::UINT;
			fstArray[GRAPH_STRING_LITERAL_INDEX].idDataType = IT::STRING;
			fstArray[GRAPH_PLUS_INDEX].operationType = LT::PLUS;
			fstArray[GRAPH_MINUS_INDEX].operationType = LT::MINUS;
			fstArray[GRAPH_MULTYPLY_INDEX].operationType = LT::MULTIPLY;
			fstArray[GRAPH_DIVISION_INDEX].operationType = LT::DIVISION;
			fstArray[GRAPH_EQUALLY_INDEX].operationType = LT::EQUALLY;
			fstArray[GRAPH_NON_EQUALLY_INDEX].operationType = LT::NON_EQUALLY;
			fstArray[GRAPH_MORE_INDEX].operationType = LT::MORE;
			fstArray[GRAPH_LESS_INDEX].operationType = LT::LESS;
			fstArray[GRAPH_MORE_OR_EQUAL_INDEX].operationType = LT::MORE_OR_EQUAL;
			fstArray[GRAPH_LESS_OR_EQUAL_INDEX].operationType = LT::LESS_OR_EQUAL;
			fstArray[GRAPH_OR_INDEX].operationType = LT::OR;
			fstArray[GRAPH_AND_INDEX].operationType = LT::AND;
			fstArray[GRAPH_INVERSION_INDEX].operationType = LT::INVERSION;

			for (int i = 0; i < GRAPHS_AMOUNT; i++)
			{
				for (int j = 0; j < fstArray[i].nodes[0].n_relation; j++)
				{
					unsigned char tempSymbol = static_cast<unsigned char>(fstArray[i].nodes[0].relations[j].symbol);
					tests[tempSymbol].push_back(&fstArray[i]);
				}
			}
		};
	};
}