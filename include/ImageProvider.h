#pragma once

#include <QQuickImageProvider>
#include <QImage>
#include <QMutex>
#include <QString>
#include <QObject>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();
    
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    
    void updateImage(const QImage &image);
    void updatePlaybackImage(const QString &frameFilename);
    void setPlaybackMode(bool enabled);

private:
    QImage m_currentImage;
    QImage m_playbackImage;
    QMutex m_mutex;
    bool m_playbackMode;
    QString m_lastFrameFile;
};
