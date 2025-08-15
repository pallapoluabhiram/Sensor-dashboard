#pragma once

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <random>

class SensorDataGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(double samplingRate READ samplingRate WRITE setSamplingRate NOTIFY samplingRateChanged)
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double pressure READ pressure NOTIFY pressureChanged)

public:
    explicit SensorDataGenerator(QObject *parent = nullptr);

    bool isRunning() const { return m_isRunning; }
    double samplingRate() const { return m_samplingRate; }
    void setSamplingRate(double rate);
    double temperature() const { return m_temperature; }
    double pressure() const { return m_pressure; }

    Q_INVOKABLE bool start();
    Q_INVOKABLE void stop();

signals:
    void runningChanged();
    void samplingRateChanged();
    void temperatureChanged();
    void pressureChanged();
    void dataReady(double temperature, double pressure, const QString &timestamp);

private slots:
    void generateData();

private:
    QTimer *m_timer;
    bool m_isRunning;
    double m_samplingRate; 
    double m_temperature;
    double m_pressure;
    
    
    std::random_device m_randomDevice;
    std::mt19937 m_generator;
    std::uniform_real_distribution<double> m_tempDistribution;
    std::uniform_real_distribution<double> m_pressureDistribution;
};
