#include "SensorDataGenerator.h"
#include <QDebug>

SensorDataGenerator::SensorDataGenerator(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
    , m_isRunning(false)
    , m_samplingRate(1.0) 
    , m_temperature(20.0)
    , m_pressure(1013.25)
    , m_generator(m_randomDevice())
    , m_tempDistribution(15.0, 35.0)    
    , m_pressureDistribution(990.0, 1030.0) 
{
    connect(m_timer, &QTimer::timeout, this, &SensorDataGenerator::generateData);
    setSamplingRate(m_samplingRate); 
}

void SensorDataGenerator::setSamplingRate(double rate)
{
    if (rate <= 0) {
        rate = 1.0; 
    }
    
    if (m_samplingRate != rate) {
        m_samplingRate = rate;
        int intervalMs = static_cast<int>(1000.0 / rate);
        m_timer->setInterval(intervalMs);
        emit samplingRateChanged();
    }
}

bool SensorDataGenerator::start()
{
    if (!m_isRunning) {
        m_isRunning = true;
       
        int intervalMs = static_cast<int>(1000.0 / m_samplingRate);
        m_timer->setInterval(intervalMs);
        m_timer->start();
        emit runningChanged();
        
        qDebug() << "Starting sensor data generation at" << m_samplingRate << "Hz (interval:" << intervalMs << "ms)";
        
        generateData();
        
        return true;
    }
    return true;
}

void SensorDataGenerator::stop()
{
    if (m_isRunning) {
        m_timer->stop();
        m_isRunning = false;
        emit runningChanged();
    }
}

void SensorDataGenerator::generateData()
{
    m_temperature = m_tempDistribution(m_generator);
    m_pressure = m_pressureDistribution(m_generator);
    
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    emit temperatureChanged();
    emit pressureChanged();
    emit dataReady(m_temperature, m_pressure, timestamp);
}
