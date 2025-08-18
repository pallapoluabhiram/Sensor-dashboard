#include "ImageProvider.h"
#include <QMutexLocker>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <QFileInfo>

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
    , m_playbackMode(false)
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(requestedSize)
    
    QMutexLocker locker(&m_mutex);
    
    QImage imageToReturn;
    
    if (m_playbackMode && !m_playbackImage.isNull()) {
        imageToReturn = m_playbackImage;
        if (size) {
            *size = m_playbackImage.size();
        }
        qDebug() << "ImageProvider::requestImage - serving playback image, size:" << m_playbackImage.size();
    } else {
        imageToReturn = m_currentImage;
        if (size) {
            *size = m_currentImage.size();
        }
        qDebug() << "ImageProvider::requestImage - serving live image, size:" << m_currentImage.size() << "null:" << m_currentImage.isNull();
    }
    
    return imageToReturn;
}

void ImageProvider::updateImage(const QImage &image)
{
    QMutexLocker locker(&m_mutex);
    if (!image.isNull() && !image.size().isEmpty()) {
        m_currentImage = image.copy();
        qDebug() << "ImageProvider::updateImage - Updated with image size:" << image.size();
    } else {
        qDebug() << "ImageProvider::updateImage - Received invalid image, null:" << image.isNull() << "size:" << image.size();
    }
}

void ImageProvider::updatePlaybackImage(const QString &frameFilename)
{
    QMutexLocker locker(&m_mutex);
    
    if (frameFilename == m_lastFrameFile && !m_playbackImage.isNull()) {
        return;
    }
    
    if (frameFilename.isEmpty()) {
        qDebug() << "ImageProvider::updatePlaybackImage - Empty frame filename";
        return;
    }
    
    QString fullPath;
    if (QFileInfo(frameFilename).isAbsolute()) {
        fullPath = frameFilename;
    } else {
        QString dataDir = QApplication::applicationDirPath() + "/data";
        fullPath = dataDir + "/" + frameFilename;
        
        if (!QFileInfo(fullPath).exists()) {
            QFileInfo info(frameFilename);
            fullPath = dataDir + "/" + info.fileName();
        }
    }
    
    QImage loadedImage(fullPath);
    if (!loadedImage.isNull()) {
        m_playbackImage = loadedImage.copy();
        m_lastFrameFile = frameFilename;
        qDebug() << "ImageProvider::updatePlaybackImage - Loaded frame:" << fullPath << "size:" << loadedImage.size();
    } else {
        qDebug() << "ImageProvider::updatePlaybackImage - Failed to load frame:" << fullPath;
        m_playbackImage = QImage(640, 480, QImage::Format_RGB888);
        m_playbackImage.fill(QColor(50, 50, 50));
    }
}

void ImageProvider::setPlaybackMode(bool enabled)
{
    QMutexLocker locker(&m_mutex);
    if (m_playbackMode != enabled) {
        m_playbackMode = enabled;
        if (!enabled) {
            m_playbackImage = QImage();
            m_lastFrameFile.clear();
        }
        qDebug() << "ImageProvider::setPlaybackMode -" << (enabled ? "enabled" : "disabled") << "playback mode";
    }
}
