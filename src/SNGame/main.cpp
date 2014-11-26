#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);

	view.setSource(QUrl("qrc:/qml/main.qml"));
	view.show();
	return app.exec();
}
