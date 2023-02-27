#pragma once
#include<string>
#include <iterator>
#include <stack>
#include<QtWidgets>



class PolishNotateParser {
public:
	PolishNotateParser(QString s) : parseStr(s) {};

	QString parse_expr();
	QString calculate_expr();

private:
	int getPriority(const QString& s);

	QString parseStr;
};
