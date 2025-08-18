#pragma once

#include <QObject>
#include <QTimer>
#include <QSize>
#include <QImage>
#include <QDir>
#include <QDateTime>
#include <opencv2/opencv.hpp>

class CameraCapture : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(QSize resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)

public:
    explicit CameraCapture(QObject *parent = nullptr);
    ~CameraCapture();

    bool isRunning() const { return m_isRunning; }
    QSize resolution() const { return m_resolution; }
    void setResolution(const QSize &resolution);

    Q_INVOKABLE bool start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE bool saveFrame(const QString &filename);

signals:
    void frameReady(const QImage &frame);
    void runningChanged();
    void resolutionChanged();
    void error(const QString &message);
    void frameSaved(const QString &filename);

private slots:
    void captureFrame();
    void saveCurrentFrame();

private:
    bool openCamera();
    void closeCamera();
    QImage matToQImage(const cv::Mat &mat);

    cv::VideoCapture m_capture;
    QTimer *m_timer;
    QTimer *m_frameSaveTimer;
    bool m_isRunning;
    QSize m_resolution;
    cv::Mat m_currentFrame;
    QString m_dataDirectory;
};
