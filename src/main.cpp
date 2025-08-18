#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QDir>

#include "CameraCapture.h"
#include "SensorDataGenerator.h"
#include "DataLogger.h"
#include "PlaybackController.h"
#include "ImageProvider.h"
#include "ImageProviderWrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Camera Sensor Dashboard");
    app.setApplicationVersion("1.0.0");

    qmlRegisterType<CameraCapture>("CameraSensorDashboard", 1, 0, "CameraCapture");
    qmlRegisterType<SensorDataGenerator>("CameraSensorDashboard", 1, 0, "SensorDataGenerator");
    qmlRegisterType<DataLogger>("CameraSensorDashboard", 1, 0, "DataLogger");
    qmlRegisterType<PlaybackController>("CameraSensorDashboard", 1, 0, "PlaybackController");

    CameraCapture cameraCapture;
    SensorDataGenerator sensorGenerator;
    DataLogger dataLogger;
    PlaybackController playbackController;
    ImageProvider *imageProvider = new ImageProvider();
    ImageProviderWrapper *imageProviderWrapper = new ImageProviderWrapper(imageProvider);

    QObject::connect(&cameraCapture, &CameraCapture::frameReady,
                     [imageProvider](const QImage &image) {
                         imageProvider->updateImage(image);
                     });

    QObject::connect(&cameraCapture, &CameraCapture::frameSaved,
                     &dataLogger, &DataLogger::logFrame);

    QObject::connect(&sensorGenerator, &SensorDataGenerator::dataReady,
                     &dataLogger, &DataLogger::logSensorData);

    QObject::connect(&dataLogger, &DataLogger::dataLoaded, [&dataLogger, &playbackController]() {
        playbackController.loadData(dataLogger.getReadings());
    });
    
    QObject::connect(&playbackController, &PlaybackController::dataPoint,
                     [imageProvider](double temperature, double pressure, const QString &timestamp, const QString &frameFile) {
                         Q_UNUSED(temperature)
                         Q_UNUSED(pressure)
                         Q_UNUSED(timestamp)
                         if (!frameFile.isEmpty()) {
                             imageProvider->updatePlaybackImage(frameFile);
                         }
                     });

    QQmlApplicationEngine engine;
    
    engine.addImageProvider("camera", imageProvider);
    
    engine.rootContext()->setContextProperty("cameraCapture", &cameraCapture);
    engine.rootContext()->setContextProperty("sensorGenerator", &sensorGenerator);
    engine.rootContext()->setContextProperty("dataLogger", &dataLogger);
    engine.rootContext()->setContextProperty("playbackController", &playbackController);
    engine.rootContext()->setContextProperty("imageProvider", imageProviderWrapper);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);

    return app.exec();
}
