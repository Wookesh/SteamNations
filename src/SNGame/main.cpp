#include <QGuiApplication>
#include <QQuickView>
#include <QDebug>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:qml/MainWindow.qml"));
	view.show();

	return app.exec();
}
