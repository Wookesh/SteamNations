#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QFontDatabase>
#include <QScreen>
#include <QQmlContext>
#include <QDebug>

#include "GameBoard.hpp"
#include "SNCore/Console.hpp"
#include "SNCore/GameManager.hpp"
#include "InfoBox.hpp"
#include "SNCore/Bonuses/Bonuses.hpp"

QObject *getGM(QQmlEngine *engine, QJSEngine *jEngine) 
{
	Q_UNUSED(engine)
	Q_UNUSED(jEngine)
	
	return GameManager::get();
}

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	
	QSize initialSize = view.screen()->size();
	if (initialSize.width() < initialSize.height())
		initialSize.transpose();
	
	GameManager::init();
	
	qmlRegisterType<GameBoard>("SN", 1, 0, "Board");
	qmlRegisterType<Console>("SN", 1, 0, "SNConsole");
	qmlRegisterType<InfoBox>("SN", 1, 0, "InfoBox");
	qmlRegisterType<BonusManager>("SN", 1, 0, "BonusManager");
	qmlRegisterSingletonType<GameManager>("SNGM", 1, 0, "gm", getGM);
	view.rootContext()->setContextProperty("initialSize", initialSize);
	
	QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);

	view.setSource(QUrl("qrc:/qml/main.qml"));
	
	//view.showFullScreen();
	view.showMaximized();
	return app.exec();
}

