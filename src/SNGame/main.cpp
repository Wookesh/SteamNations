#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QFontDatabase>
#include <QScreen>
#include <QQmlContext>
#include <QDebug>
#include "GameBoard.hpp"


int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	
	QSize initialSize = view.screen()->size();
	
	qmlRegisterType<GameBoard>("SN", 1, 0, "Board");
	view.rootContext()->setContextProperty("initialSize", initialSize);
	
	QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);

	view.setSource(QUrl("qrc:/qml/main.qml"));
	
	view.showFullScreen();
	return app.exec();
}
