
#include "calculator.h"


int main(int argc, char** argv) {
	QApplication app(argc, argv);

	Calculator calc;
	calc.setGeometry(200, 200, 400, 400);
	calc.show();

	return app.exec();


}
