#pragma once

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QDateTime>
#include <QStandardPaths>

struct SensorReading {
    QDateTime timestamp;
    double temperature;
    double pressure;
    QString frameFilename;
};

Q_DECLARE_METATYPE(SensorReading)

class DataLogger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLogging READ isLogging NOTIFY loggingChanged)
    Q_PROPERTY(QString currentLogFile READ currentLogFile NOTIFY currentLogFileChanged)

public:
    explicit DataLogger(QObject *parent = nullptr);
    ~DataLogger();

    bool isLogging() const { return m_isLogging; }
    QString currentLogFile() const { return m_currentLogFile; }

    Q_INVOKABLE bool startLogging();
    Q_INVOKABLE void stopLogging();
    Q_INVOKABLE bool loadLogFile(const QString &filename);
    Q_INVOKABLE QString getDataDirectory();
    Q_INVOKABLE QList<SensorReading> getReadings() const { return m_readings; }

    void logSensorData(double temperature, double pressure, const QString &timestamp);
    void logFrame(const QString &frameFilename);

signals:
    void loggingChanged();
    void currentLogFileChanged();
    void dataLoaded();
    void error(const QString &message);

private:
    bool createLogFile();
    void writeHeader();

    QFile *m_logFile;
    QTextStream *m_stream;
    bool m_isLogging;
    QString m_currentLogFile;
    QTimer *m_frameTimer;
    QString m_lastFrameFilename;
    QList<SensorReading> m_readings;
    QString m_dataDirectory;
};
