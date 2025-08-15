#include "ImageProvider.h"
#include <QMutexLocker>
#include <QDebug>

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(requestedSize)
    
    QMutexLocker locker(&m_mutex);
    
    if (size) {
        *size = m_currentImage.size();
    }
    
    qDebug() << "ImageProvider::requestImage called, image size:" << m_currentImage.size() << "null:" << m_currentImage.isNull();
    
    return m_currentImage;
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
