#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include <QObject>
#include <QHash>
#include <QStringList>

class QQuickWindow;
class QSGTexture;

class TextureManager : public QObject {
Q_OBJECT
public:
	TextureManager(QObject *parent = nullptr);
	virtual ~TextureManager();
	
	QSGTexture *texture(const QString &name) const;
	bool isLoaded() const;
private:
	bool loaded_;
	
	QHash<QString, QSGTexture *> textures_;
	static const QStringList &elementsToLoad();
public slots:
	void loadTextures(QQuickWindow *window);
signals:
	void texturesLoaded();
	void textureNotFound(const QString &textureName);
};

#endif