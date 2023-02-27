#include "operations.h"



void Dot::oper(Display& displ, const QString& clickBtn) {
	if (displ.numStrDispl.back() == 'c') {
		displ.numStrDispl.chop(1);
	}
	if (std::count_if(displ.numStrDispl.begin(), displ.numStrDispl.end(),
	[](QChar i) {return i.isDigit(); }) > 15) {

	}
	else if (displ.numStrDispl.back().isDigit() &&
		std::find(displ.numStrDispl.begin(), displ.numStrDispl.end(), '.') == displ.numStrDispl.end()) {
		displ.numStrDispl += '.';
		
	}
	else if (displ.numStrDispl == "0s") {
		displ.numStrDispl = "0.";
		
	}
	displ.numDispl->setText(displ.numStrDispl);
}


void Digit::oper(Display& displ, const QString& clickBtn) {

	if (displ.numStrDispl.back() == 's') {
		displ.numStrDispl.clear();
		displ.exprStrDispl.clear();
		displ.numStrDispl += clickBtn;
	}
	else if (displ.numStrDispl.back() == 'c') {
		displ.numStrDispl.clear();
		displ.numStrDispl += clickBtn;
	}
	else if (displ.numStrDispl.size() == 1 && displ.numStrDispl[0] == '0') {
		displ.numStrDispl.clear();
		displ.numStrDispl += clickBtn;
	}
	else if (std::count_if(displ.numStrDispl.begin(), displ.numStrDispl.end(),
		[](QChar i) {return i.isDigit(); }) > 15) {

	}
	else {
		displ.numStrDispl += clickBtn;
	}

	displ.numDispl->setText(displ.numStrDispl);

}


void Arithmetic::oper(Display& displ, const QString& clickBtn) {


	if (displ.numStrDispl.back()=='s') {
		displ.exprStrDispl.clear();
		displ.numStrDispl.chop(1);
	}
	else if (displ.numStrDispl.back() == 'c') {
		displ.numStrDispl.chop(1);
	}


	if (!displ.exprStrDispl.isEmpty() && displ.exprStrDispl.back() == ')') {
		displ.exprStrDispl += clickBtn;
	}
	else {
		if (displ.numStrDispl[0] == '-') { displ.exprStrDispl += '(' + displ.numStrDispl +')'; }
		else { displ.exprStrDispl += displ.numStrDispl; }
		displ.exprStrDispl += clickBtn;
	}

	displ.numDispl->setText(displ.numStrDispl);
	displ.exprDispl->setText(displ.exprStrDispl);
	displ.numStrDispl += 'c';

}

void LeftBracket::oper(Display& displ, const QString& clickBtn) {
	if (displ.exprStrDispl.isEmpty()) {
		
	}
	else if (displ.exprStrDispl.back() == ')') {
		displ.exprStrDispl += '*';
		displ.numStrDispl += 'c';
	}
	else if (displ.numStrDispl.back()=='s') {
		displ.exprStrDispl.clear();
		displ.numStrDispl.chop(1);
		displ.numStrDispl += 'c';
	}
	displ.exprStrDispl += clickBtn;
	displ.exprDispl->setText(displ.exprStrDispl);
}


void RightBracket::oper(Display& displ, const QString& clickBtn) {
	if (displ.exprStrDispl.back() == ')' &&
		std::count(displ.exprStrDispl.begin(), displ.exprStrDispl.end(), '(') >
		std::count(displ.exprStrDispl.begin(), displ.exprStrDispl.end(), ')')) {

		displ.exprStrDispl += clickBtn;
	}
	else if (displ.exprStrDispl.back() != '(' &&
		std::count(displ.exprStrDispl.begin(), displ.exprStrDispl.end(), '(') >
		std::count(displ.exprStrDispl.begin(), displ.exprStrDispl.end(), ')')) {

		if (displ.numStrDispl.back() == 'c') displ.numStrDispl.chop(1);
		displ.exprStrDispl += displ.numStrDispl;
		displ.exprStrDispl += clickBtn;
	}
	else if (displ.exprStrDispl.back() == '('){

		if (displ.numStrDispl.back() == 'c') displ.numStrDispl.chop(1);
		displ.exprStrDispl += displ.numStrDispl + clickBtn;
	}
	displ.exprDispl->setText(displ.exprStrDispl);
}


void CE::oper(Display& displ, const QString& clickBtn) {
	displ.exprStrDispl = "";
	displ.numStrDispl = "0s";
	displ.numDispl->setText("0");
	displ.exprDispl->setText("");
}


void Remove::oper(Display& displ, const QString& clickBtn) {
	displ.numStrDispl.chop(1);
}


void Equally::oper(Display& displ, const QString& clickBtn){

	if (displ.numStrDispl.back() == 'c') { displ.numStrDispl.chop(1); }
	else if (displ.numStrDispl.back() == 's') {
		displ.numStrDispl.chop(1);
		displ.exprStrDispl.clear();
	}

	if (!displ.exprStrDispl.isEmpty() && displ.exprStrDispl.back() == ')') {}
	else if (displ.numStrDispl[0] == '-') {
		displ.exprStrDispl += '(' + displ.numStrDispl + ')';
	}
	else displ.exprStrDispl += displ.numStrDispl;

	while (std::count(displ.exprStrDispl.begin(), displ.exprStrDispl.end(), '(') >
		std::count(displ.exprStrDispl.begin(), displ.exprStrDispl.end(), ')')) {

		displ.exprStrDispl += ')';
	}


	displ.numStrDispl = calculate(displ.exprStrDispl);
	displ.exprStrDispl += "=";

	if (displ.numStrDispl == "inf" || displ.numStrDispl == "-inf" ||
		displ.numStrDispl == "nan") { 
		displ.numDispl->setText("Error");
		displ.numStrDispl="0";
	}
	else { displ.numDispl->setText(displ.numStrDispl); }
	displ.exprDispl->setText(displ.exprStrDispl);
	displ.numStrDispl += 's';
		
}


QString Equally::calculate(const QString& parseStr)
{
	PolishNotateParser pst(parseStr);
	return pst.calculate_expr();
}


void UnMinus::oper(Display& displ, const QString& clickBtn) {


	if (displ.numStrDispl[0].isDigit()) {

		displ.numStrDispl.insert(0, "-");

		if (!displ.numStrDispl.back().isDigit()) {
			QChar lastC = displ.numStrDispl.back();
			displ.numStrDispl.chop(1);
			displ.numDispl->setText(displ.numStrDispl);
			displ.numStrDispl += lastC;
		}
		else displ.numDispl->setText(displ.numStrDispl);
	}
	else {
		displ.numStrDispl.remove(0, 1);
		if (!displ.numStrDispl.back().isDigit()) {
			QChar lastC = displ.numStrDispl.back();
			displ.numStrDispl.chop(1);
			displ.numDispl->setText(displ.numStrDispl);
			displ.numStrDispl += lastC;
		}
		else displ.numDispl->setText(displ.numStrDispl);
	}
	
}