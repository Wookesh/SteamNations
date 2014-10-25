#include <QApplication>
#include "FantasyCIV.hpp"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	FantasyCIV *fantasyciv = new FantasyCIV();
	fantasyciv->showFullScreen();
	return app.exec();
}

