#include <QApplication>
#include "SteamNations.hpp"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	SteamNations *steamNations = new SteamNations();
	steamNations->showFullScreen();
	return app.exec();
}

