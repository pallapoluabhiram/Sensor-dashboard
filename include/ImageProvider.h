#pragma once

#include <QQuickImageProvider>
#include <QImage>
#include <QMutex>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();
    
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    
    void updateImage(const QImage &image);

private:
    QImage m_currentImage;
    QMutex m_mutex;
};
