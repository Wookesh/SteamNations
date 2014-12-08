#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include "Board.hpp"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	qmlRegisterType<Board>("SN", 1, 0, "Board");
	
	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);

	view.setSource(QUrl("qrc:/qml/main.qml"));
	view.showFullScreen();
	return app.exec();
}
