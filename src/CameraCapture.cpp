#include "CameraCapture.h"
#include <QDebug>
#include <QImage>
#include <QApplication>
#include <QStandardPaths>
#include <QThread>

CameraCapture::CameraCapture(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
    , m_frameSaveTimer(new QTimer(this))
    , m_isRunning(false)
    , m_resolution(640, 480)
{
    m_timer->setInterval(33);
    connect(m_timer, &QTimer::timeout, this, &CameraCapture::captureFrame);
    m_frameSaveTimer->setInterval(5000);
    m_frameSaveTimer->setSingleShot(false);
    connect(m_frameSaveTimer, &QTimer::timeout, this, &CameraCapture::saveCurrentFrame);
    m_dataDirectory = QApplication::applicationDirPath() + "/data";
    QDir().mkpath(m_dataDirectory);
}

CameraCapture::~CameraCapture()
{
    stop();
}

void CameraCapture::setResolution(const QSize &resolution)
{
    if (m_resolution != resolution) {
        m_resolution = resolution;
        if (m_capture.isOpened()) {
            m_capture.set(cv::CAP_PROP_FRAME_WIDTH, resolution.width());
            m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, resolution.height());
        }
        emit resolutionChanged();
    }
}

bool CameraCapture::start()
{
    if (m_isRunning) {
        return true;
    }

    if (!openCamera()) {
        emit error("Camera is not available. Please check if a camera is connected and not being used by another application. The system will continue with placeholder frames.");
        qDebug() << "Camera failed to open, will generate placeholder frames";
    }

    m_isRunning = true;
    m_timer->start();
    m_frameSaveTimer->start(); 
    emit runningChanged();
    return true;
}

void CameraCapture::stop()
{
    if (!m_isRunning) {
        return;
    }

    m_timer->stop();
    m_frameSaveTimer->stop(); 
    closeCamera();
    m_isRunning = false;
    emit runningChanged();
}

bool CameraCapture::saveFrame(const QString &filename)
{
    if (!m_currentFrame.empty()) {
        return cv::imwrite(filename.toStdString(), m_currentFrame);
    }
    return false;
}

void CameraCapture::captureFrame()
{
    if (!m_capture.isOpened()) {
        return;
    }

    try {
        cv::Mat frame;
        if (m_capture.read(frame) && !frame.empty()) {
            m_currentFrame = frame.clone();
            QImage qimg = matToQImage(frame);
            emit frameReady(qimg);
        } else {
            static int failureCount = 0;
            failureCount++;
            if (failureCount > 10) {
                emit error("Camera disconnected or cannot read frames. Please check camera connection.");
                closeCamera();
                failureCount = 0;
            }
        }
    } catch (const cv::Exception &e) {
        emit error("Camera capture error: " + QString(e.what()));
        closeCamera();
    } catch (const std::exception &e) {
        emit error("Camera error: " + QString(e.what()));
        closeCamera();
    } catch (...) {
        emit error("Unknown camera error occurred during frame capture");
        closeCamera();
    }
}

bool CameraCapture::openCamera()
{
    try {
        qDebug() << "Attempting to open camera device...";
        
        m_capture.open(0, cv::CAP_V4L2);
        if (!m_capture.isOpened()) {
            qDebug() << "Failed to open camera device 0 with V4L2, trying default backend...";
            m_capture.open(0);
            if (!m_capture.isOpened()) {
                qDebug() << "Failed to open camera device 0";
                return false;
            }
        }
        
        qDebug() << "Camera opened, configuring settings...";
        
        m_capture.set(cv::CAP_PROP_FRAME_WIDTH, m_resolution.width());
        m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_resolution.height());
        m_capture.set(cv::CAP_PROP_BUFFERSIZE, 1);
        m_capture.set(cv::CAP_PROP_FPS, 30);
        
        QThread::msleep(500);
        
        cv::Mat testFrame;
        int retries = 5;
        bool frameRead = false;
        
        for (int i = 0; i < retries; i++) {
            if (m_capture.read(testFrame) && !testFrame.empty()) {
                qDebug() << "Successfully read test frame on attempt" << (i + 1);
                frameRead = true;
                break;
            }
            qDebug() << "Test frame read attempt" << (i + 1) << "failed, retrying...";
            QThread::msleep(200);
        }
        
        if (!frameRead) {
            qDebug() << "Camera opened but cannot read frames after" << retries << "attempts";
            m_capture.release();
            return false;
        }
        
        qDebug() << "Camera successfully opened and configured";
        qDebug() << "Frame size:" << testFrame.cols << "x" << testFrame.rows;
        qDebug() << "Frame type:" << testFrame.type();
        
        return true;
    } catch (const cv::Exception &e) {
        qDebug() << "OpenCV exception:" << e.what();
        return false;
    } catch (const std::exception &e) {
        qDebug() << "Standard exception in openCamera:" << e.what();
        return false;
    } catch (...) {
        qDebug() << "Unknown exception in openCamera";
        return false;
    }
}

void CameraCapture::closeCamera()
{
    if (m_capture.isOpened()) {
        m_capture.release();
    }
}

void CameraCapture::saveCurrentFrame()
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString filename = m_dataDirectory + "/frame_" + timestamp + ".jpg";
    
    QDir dir(m_dataDirectory);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            emit error("Cannot create data directory: " + m_dataDirectory + ". Please check write permissions.");
            return;
        }
    }
    
    try {
        if (!m_currentFrame.empty()) {
            if (cv::imwrite(filename.toStdString(), m_currentFrame)) {
                emit frameSaved(filename);
                qDebug() << "Saved camera frame:" << filename;
            } else {
                emit error("Failed to save camera frame to: " + filename + ". Please check disk space and write permissions.");
            }
        } else {
            cv::Mat placeholderFrame = cv::Mat::zeros(m_resolution.height(), m_resolution.width(), CV_8UC3);
            
            std::string timestampText = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
            cv::putText(placeholderFrame, "No Camera Available", cv::Point(50, m_resolution.height()/2 - 40), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
            cv::putText(placeholderFrame, timestampText, cv::Point(50, m_resolution.height()/2 + 20), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(200, 200, 200), 1);
            
            if (cv::imwrite(filename.toStdString(), placeholderFrame)) {
                emit frameSaved(filename);
                qDebug() << "Saved placeholder frame:" << filename;
            } else {
                emit error("Failed to save placeholder frame to: " + filename + ". Please check disk space and write permissions.");
            }
        }
    } catch (const cv::Exception &e) {
        emit error("OpenCV error while saving frame: " + QString(e.what()));
    } catch (const std::exception &e) {
        emit error("Error while saving frame: " + QString(e.what()));
    } catch (...) {
        emit error("Unknown error occurred while saving frame to: " + filename);
    }
}

QImage CameraCapture::matToQImage(const cv::Mat &mat)
{
    switch (mat.type()) {
    case CV_8UC4: {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.rgbSwapped();
    }
    case CV_8UC3: {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    case CV_8UC1: {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        return image;
    }
    default:
        break;
    }

    return QImage();
}
