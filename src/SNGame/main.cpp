#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QTimer>
#include "GameBoard.hpp"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	qmlRegisterType<GameBoard>("SN", 1, 0, "Board");
	QQuickView view;
	QTimer timer;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);


	view.setSource(QUrl("qrc:/qml/main.qml"));
	view.show();
	return app.exec();
}
