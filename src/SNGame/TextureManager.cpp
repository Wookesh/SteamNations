#include "TextureManager.hpp"
#include <QPixmap>
#include <QSGTexture>
#include <QQuickWindow>
#include <QTextStream>
#include <QDir>
#include <QDebug>

const QStringList &TextureManager::elementsToLoad()
{
	static QStringList elementsToLoad_({
		"hex", "unit"
	});
	return elementsToLoad_;
}



TextureManager::TextureManager(QObject *parent): QObject(parent), loaded_(false)
{
}

TextureManager::~TextureManager()
{
	qDeleteAll(textures_);
}

void TextureManager::loadTextures(QQuickWindow *window)
{
	if (window == nullptr)
		return;
	
	qDeleteAll(textures_);
	textures_.clear();
	
	QStringList textureList;
	for (const QString &group : elementsToLoad()) {
		for (const QString &name: QDir(":" + group).entryList()) {
			QPixmap *pixmap = new QPixmap(":///" + group + "/" + name.trimmed());
			if (pixmap->isNull()) {
				emit textureNotFound(name);
				return;
			}
			textures_[name] = window->createTextureFromImage(pixmap->toImage());
		}
	}
	loaded_ = true;
	emit texturesLoaded();
}

bool TextureManager::isLoaded() const
{
	return loaded_;
}


QSGTexture *TextureManager::texture(const QString &name) const
{
	if (textures_.contains(name))
		return textures_[name];
	qDebug() << "[ERROR] Didn't found texture :" << name;
	return nullptr;
}
