#pragma once
#include<QtWidgets>

struct Display {
	Display() =default;

	QString exprStrDispl;
	QString numStrDispl;
	QLineEdit* exprDispl=nullptr;
	QLineEdit* numDispl=nullptr;
};