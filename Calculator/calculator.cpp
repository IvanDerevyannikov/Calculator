#include "calculator.h"




Calculator::Calculator(QWidget* parent):QWidget(parent)
{
	this->setStyleSheet("QLineEdit {border: 2px solid gray; "
		"border-radius: 20px;"
		"background: rgba(0, 0, 0, 0);"
		"selection - background - color: darkgray;}"
		"QPushButton {border: 2px solid gray; "
		"border-radius: 20px;"
		"background: rgba(0, 0, 0, 0);"
		"selection - background - color: darkgray;}"
		"QScrollBar::horizontal{background-color: rgba(0, 0, 0,0);}"
		"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {background: none;}");

	QGridLayout* calcLayout = new QGridLayout(this);

	displ.exprStrDispl = "";
	displ.numStrDispl = "0s";

	displ.exprDispl = new QLineEdit(this);
	displ.exprDispl->setMinimumSize(400, 50);
	displ.exprDispl->setAlignment(Qt::AlignRight);
	displ.exprDispl->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	displ.exprDispl->setFocusPolicy(Qt::NoFocus);
	QFont font = displ.exprDispl->font();
	font.setPixelSize(14);
	displ.exprDispl->setFont(font);
	displ.exprDispl->setReadOnly(true);
	displ.exprDispl->setFrame(false);

	exprScroll = new QScrollBar(Qt::Horizontal, displ.exprDispl);
	exprScroll->move(30, 5);
	exprScroll->resize(displ.exprDispl->size().width()-60, 15);
	exprScroll->hide();

	connect(exprScroll, &QScrollBar::valueChanged, displ.exprDispl, &QLineEdit::setCursorPosition);
	connect(displ.exprDispl, &QLineEdit::cursorPositionChanged, exprScroll, [&]() {
		QFont exFont = displ.exprDispl->font();
		QFontMetrics fm(exFont);
		int width = fm.horizontalAdvance(displ.exprStrDispl);
		width >= displ.exprDispl->width() ? exprScroll->show() : exprScroll->hide();
		exprScroll->setMaximum(displ.exprDispl->text().length());
		exprScroll->setSingleStep(1);
		}
	);


	displ.numDispl = new QLineEdit(this);
	displ.numDispl->setMinimumSize(150, 100);
	displ.numDispl->setAlignment(Qt::AlignRight);
	displ.numDispl->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	displ.numDispl->setFocusPolicy(Qt::NoFocus);
	displ.numDispl->setFont(font);
	displ.numDispl->setText("0");


	calcLayout->addWidget(displ.exprDispl, 0, 0, 1, 4);
	calcLayout->addWidget(displ.numDispl, 1, 0, 1, 4);


	QString butnName[5][4] = {	{"(",")","C","+/-"},
								{"7","8","9","*"},
								{"4","5","6","/"},
								{"1","2","3","+"},
								{"0",".","=", "-"} };


	QVector<QVector<std::shared_ptr<Operation>>> operation = { 
		{std::make_shared<LeftBracket>(),std::make_shared<RightBracket>(),
		std::make_shared<CE>(),std::make_shared<UnMinus>() },
		{std::make_shared<Digit>(),std::make_shared<Digit>(),
		std::make_shared<Digit>(), std::make_shared<Arithmetic>() },
		{std::make_shared<Digit>(),std::make_shared<Digit>(),
		std::make_shared<Digit>(), std::make_shared<Arithmetic>() },
		{std::make_shared<Digit>(),std::make_shared<Digit>(),
		std::make_shared<Digit>(), std::make_shared<Arithmetic>() },
		{std::make_shared<Digit>(),std::make_shared<Dot>(),
		std::make_shared<Equally>(), std::make_shared<Arithmetic>() } };


	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			QPushButton* butn = new QPushButton(butnName[i][j],this);
			butn->setObjectName(butnName[i][j]);
			butn->setMinimumSize(50, 50);
			butn->setFocusPolicy(Qt::NoFocus);
			butn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
			calcBtns[butn] = operation[i][j];
			calcLayout->addWidget(butn, i + 2, j);
			connect(butn, SIGNAL(clicked()), SLOT(display()));
		}
	}

	calcLayout->setRowStretch(0, 3);
	calcLayout->setRowStretch(1, 5);
	calcLayout->setRowStretch(2, 3);
	calcLayout->setRowStretch(3, 3);
	calcLayout->setRowStretch(4, 3);
	calcLayout->setRowStretch(5, 3);
	calcLayout->setRowStretch(6, 3);

	setLayout(calcLayout);

}



void Calculator::keyPressEvent(QKeyEvent* e)
{
	QPushButton* pressButn = this->findChild<QPushButton*>
		(QKeySequence(e->key()).toString());

	if(pressButn) pressButn->clicked(true);
	
	if (e->text() == "\b") {

		if (!displ.numStrDispl.isEmpty() &&
			(displ.numStrDispl.back().isDigit()|| displ.numStrDispl.back()=='.')) {
			displ.numStrDispl.chop(1);
			if (displ.numStrDispl.isEmpty()) {
				displ.numStrDispl = "0s";
				displ.numDispl->setText("0");
			}
			else displ.numDispl->setText(displ.numStrDispl);
		}
	}

}


void Calculator::resizeEvent(QResizeEvent* event)
{
	exprScroll->resize(displ.exprDispl->size().width() - 60, 15);

	if (this->height()/20>displ.numDispl->font().pixelSize()||
		this->height() / 20 < displ.numDispl->font().pixelSize()) {
		QFont font = displ.numDispl->font();
		font.setPixelSize(this->height() / 20);
		displ.numDispl->setFont(font);
	}

	auto btn = calcBtns.begin().key();
	if (this->height() / 35 > btn->font().pixelSize() ||
		this->height() / 35 < btn->font().pixelSize()) {
		QFont font = btn->font();
		font.setPixelSize(this->height() / 35);
		for (auto it = calcBtns.begin(),end = calcBtns.end(); it!=end; ++it) {
			it.key()->setFont(font);
		}
	}

}



void Calculator::display() {

	QPushButton* clickButn = dynamic_cast<QPushButton*>(sender());
	calcBtns[clickButn]->oper(displ, clickButn->text());

}