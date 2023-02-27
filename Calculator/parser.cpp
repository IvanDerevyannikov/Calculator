#include "parser.h"


int PolishNotateParser::getPriority(const QString& s) {
	if (s == "sum") return 1;
	if (s == "sub") return 1;
	if (s == "mul") return 2;
	if (s == "der") return 2;
	if (s == "neg") return 3;

	return 0;
}



QString PolishNotateParser::parse_expr() {
	QString polStr;
	QStack<QString> operations;
	auto token = parseStr.begin();
	const char signs[6] = { '+','-','*','/','(',')' };
	auto isArithmetic = [&signs](QChar sng)->bool {
		for (auto i : signs) {
			if (sng == i) return true;
		}
		return false;
	};

	auto add_to_stack = [&operations, &polStr, this](const QString str) {
		if (operations.empty() || operations.top() == "(") {
			operations.push(str);
		}
		else {
			while (!operations.empty() && getPriority(str) <= getPriority(operations.top()) &&
				operations.top() != "(") {
				polStr += operations.top();
				polStr += ' ';
				operations.pop();
			}
			operations.push(str);
		}
	};

	while (token < parseStr.end()) {

		if ((*token).isDigit()) {
			while (token<parseStr.end()&&((*token).isDigit() || (*token)=='.')) {
				polStr.push_back(*token++);
			}
			polStr.push_back(' ');
		}

		else if (isArithmetic(*token) == true) {

			if (*token == '-') {
				if (*(token-1)=='(') {
					operations.push("neg");
				}
				else {
					add_to_stack("sub");
					}
			}
			
			else if (*token == '+') {
				add_to_stack("sum");
			}

			else if (*token == '*') {
				add_to_stack("mul");
			}

			else if (*token == '/') {
				add_to_stack("der");
			}

			else if (*token == '(') {
				operations.push("(");
			}

			else if (*token == ')') {
				while (operations.top() != "(") {
					polStr += operations.top();
					polStr += ' ';
					operations.pop();
				}
				operations.pop();
			}

			++token;
		}
	}

	while (!operations.empty()) {
		polStr += operations.top();
		polStr += ' ';
		operations.pop();
	}

	return polStr;
}

QString PolishNotateParser::calculate_expr()
{
	QStack<double> numsstack;
	QString num;
	QString finalValue;
	QString oper;
	QString parseStr = parse_expr();
	auto token = parseStr.begin();


	while (token < parseStr.end()) {
		if ((*token).isDigit()) {

			while (token < parseStr.end() && ((*token).isDigit() || (*token) == '.')) {
				num += *token++;
			}
			++token;
			numsstack.push(num.toDouble());
			num.clear();
			continue;
		}

		else {

			for (size_t i = 0; i < 3; ++i) {
				oper += *token++;
			}
			++token;

			if (oper == "neg") {
				double val = numsstack.top();
				numsstack.pop();
				numsstack.push(-val);
			}

			else if (oper == "sub") {
				double val1 = numsstack.top();
				numsstack.pop();
				double val2 = numsstack.top();
				numsstack.pop();
				numsstack.push(val2 - val1);
			}

			else if (oper == "sum") {
				double val1 = numsstack.top();
				numsstack.pop();
				double val2 = numsstack.top();
				numsstack.pop();
				numsstack.push(val2 + val1);
			}

			else if (oper == "mul") {
				double val1 = numsstack.top();
				numsstack.pop();
				double val2 = numsstack.top();
				numsstack.pop();
				numsstack.push(val2 * val1);
			}

			else if (oper == "der") {
				double val1 = numsstack.top();
				numsstack.pop();
				double val2 = numsstack.top();
				numsstack.pop();
				numsstack.push(val2 / val1);
			}
			oper.clear();
		}
	}

	finalValue = QString::number(numsstack.top(), 'f',15);
	finalValue.remove(QRegularExpression("0+$"));
	finalValue.remove(QRegularExpression("\\.$"));
	return finalValue;
}