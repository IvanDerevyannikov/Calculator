#pragma once

#include <algorithm>
#include <memory>

#include "display.h"
#include "operations.h"
#include "parser.h"


class Calculator:public QWidget
{
	Q_OBJECT

public:
	Calculator(QWidget* parent = 0);

protected:
	void keyPressEvent(QKeyEvent* e) override ;
	void resizeEvent(QResizeEvent* event) override;

private:

	QMultiHash<QPushButton*, std::shared_ptr<Operation>> calcBtns;
	Display displ;
	QScrollBar* exprScroll;

public slots:
	void display();
	
};

