#pragma once
#include "display.h"
#include "parser.h" 




class Operation{
public:

	virtual void oper(Display& displ, const QString& clickBtn) {};
	virtual ~Operation() {}

};


class Dot : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};


class Digit : public Operation {
public:	
	void oper(Display& displ, const QString& clickBtn) override;

};


class Arithmetic : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};


class LeftBracket : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};


class RightBracket : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};


class CE : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};


class Remove : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};


class Equally : public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

private: 
	QString calculate(const QString& clickBtn);
};


class UnMinus :public Operation {
public:
	void oper(Display& displ, const QString& clickBtn) override;

};