#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QScreen>
#include <QDebug>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);

	QSize initialSize = view.screen()->size();
	view.rootContext()->setContextProperty("initialSize", initialSize);
	
	view.setSource(QUrl("qrc:qml/MainWindow.qml"));
	view.showFullScreen();

	return app.exec();
}
