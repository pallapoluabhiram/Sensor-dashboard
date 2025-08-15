#include "PlaybackController.h"
#include <QDebug>
#include <algorithm>
#include <numeric>

PlaybackController::PlaybackController(QObject *parent)
    : QObject(parent)
    , m_playbackTimer(new QTimer(this))
    , m_isPlaying(false)
    , m_isPaused(false)
    , m_currentIndex(0)
    , m_totalReadings(0)
    , m_playbackSpeed(1.0)
    , m_loopEnabled(false)
{
    connect(m_playbackTimer, &QTimer::timeout, this, &PlaybackController::nextDataPoint);
    m_playbackTimer->setInterval(1000); 
}

void PlaybackController::setPlaybackSpeed(double speed)
{
    if (speed <= 0) {
        speed = 0.1; 
    }
    if (speed > 10.0) {
        speed = 10.0; 
    }
    
    if (m_playbackSpeed != speed) {
        m_playbackSpeed = speed;
        int intervalMs = static_cast<int>(1000.0 / speed);
        m_playbackTimer->setInterval(intervalMs);
        emit playbackSpeedChanged();
    }
}

void PlaybackController::loadData(const QList<SensorReading> &readings)
{
    stop(); 
    
    m_readings = readings;
    m_totalReadings = readings.size();
    m_currentIndex = 0;
    
    emit totalReadingsChanged();
    emit currentIndexChanged();
    
    
    calculateStatistics();
    
    qDebug() << "Loaded" << m_totalReadings << "readings for playback";
}

void PlaybackController::play()
{
    if (m_readings.isEmpty()) {
        qDebug() << "No data loaded for playback";
        return;
    }
    
    if (m_currentIndex >= m_totalReadings) {
        m_currentIndex = 0;
        emit currentIndexChanged();
    }
    
    m_isPlaying = true;
    m_isPaused = false;
    m_playbackTimer->start();
    
    emit playingChanged();
    emit pausedChanged();
    
   
    updateCurrentData();
}

void PlaybackController::pause()
{
    if (!m_isPlaying) {
        return;
    }
    
    m_isPaused = !m_isPaused;
    
    if (m_isPaused) {
        m_playbackTimer->stop();
    } else {
        m_playbackTimer->start();
    }
    
    emit pausedChanged();
}

void PlaybackController::stop()
{
    m_playbackTimer->stop();
    m_isPlaying = false;
    m_isPaused = false;
    m_currentIndex = 0;
    
    emit playingChanged();
    emit pausedChanged();
    emit currentIndexChanged();
}

void PlaybackController::forward()
{
    int newIndex = findIndexByTimeOffset(m_currentIndex, 10); 
    seekToIndex(newIndex);
}

void PlaybackController::rewind()
{
    int newIndex = findIndexByTimeOffset(m_currentIndex, -10); 
    seekToIndex(newIndex);
}

void PlaybackController::seekToIndex(int index)
{
    if (index < 0) {
        index = 0;
    }
    if (index >= m_totalReadings) {
        index = m_totalReadings - 1;
    }
    
    m_currentIndex = index;
    emit currentIndexChanged();
    
    updateCurrentData();
}

void PlaybackController::nextDataPoint()
{
    if (m_currentIndex >= m_totalReadings) {
        if (m_loopEnabled) {
            m_currentIndex = 0;
            emit currentIndexChanged();
            updateCurrentData();
            return;
        } else {
            stop();
            emit playbackFinished();
            return;
        }
    }
    
    updateCurrentData();
    m_currentIndex++;
    emit currentIndexChanged();
}

void PlaybackController::updateCurrentData()
{
    if (m_currentIndex < 0 || m_currentIndex >= m_totalReadings) {
        return;
    }
    
    const SensorReading &reading = m_readings[m_currentIndex];
    emit dataPoint(reading.temperature, reading.pressure, 
                   reading.timestamp.toString(Qt::ISODate), reading.frameFilename);
    emit currentTimestampChanged();
}

int PlaybackController::findIndexByTimeOffset(int currentIndex, int secondsOffset)
{
    if (m_readings.isEmpty() || currentIndex < 0 || currentIndex >= m_totalReadings) {
        return currentIndex;
    }
    
    QDateTime currentTime = m_readings[currentIndex].timestamp;
    QDateTime targetTime = currentTime.addSecs(secondsOffset);
    
    
    int bestIndex = currentIndex;
    qint64 bestDiff = qAbs(currentTime.secsTo(targetTime));
    
    for (int i = 0; i < m_totalReadings; ++i) {
        qint64 diff = qAbs(m_readings[i].timestamp.secsTo(targetTime));
        if (diff < bestDiff) {
            bestDiff = diff;
            bestIndex = i;
        }
    }
    
    return bestIndex;
}

void PlaybackController::setLoopEnabled(bool enabled)
{
    if (m_loopEnabled != enabled) {
        m_loopEnabled = enabled;
        emit loopEnabledChanged();
    }
}

QDateTime PlaybackController::currentTimestamp() const
{
    if (m_currentIndex >= 0 && m_currentIndex < m_totalReadings) {
        return m_readings[m_currentIndex].timestamp;
    }
    return QDateTime();
}

void PlaybackController::seekToTimestamp(const QDateTime &timestamp)
{
    int index = findIndexByTimestamp(timestamp);
    seekToIndex(index);
}

int PlaybackController::findIndexByTimestamp(const QDateTime &timestamp)
{
    if (m_readings.isEmpty()) {
        return 0;
    }
    
    int bestIndex = 0;
    qint64 bestDiff = qAbs(m_readings[0].timestamp.msecsTo(timestamp));
    
    for (int i = 1; i < m_totalReadings; ++i) {
        qint64 diff = qAbs(m_readings[i].timestamp.msecsTo(timestamp));
        if (diff < bestDiff) {
            bestDiff = diff;
            bestIndex = i;
        }
    }
    
    return bestIndex;
}

QList<SensorReading> PlaybackController::getReadingsInRange(const QDateTime &start, const QDateTime &end)
{
    QList<SensorReading> result;
    
    for (const SensorReading &reading : m_readings) {
        if (reading.timestamp >= start && reading.timestamp <= end) {
            result.append(reading);
        }
    }
    
    return result;
}

void PlaybackController::calculateStatistics()
{
    if (m_readings.isEmpty()) {
        m_statistics.clear();
        emit statisticsChanged();
        return;
    }
    
    
    QList<double> temperatures, pressures;
    for (const SensorReading &reading : m_readings) {
        temperatures.append(reading.temperature);
        pressures.append(reading.pressure);
    }
    
    
    std::sort(temperatures.begin(), temperatures.end());
    double tempMin = temperatures.first();
    double tempMax = temperatures.last();
    double tempSum = std::accumulate(temperatures.begin(), temperatures.end(), 0.0);
    double tempMean = tempSum / temperatures.size();
    double tempMedian = (temperatures.size() % 2 == 0) ? 
        (temperatures[temperatures.size()/2 - 1] + temperatures[temperatures.size()/2]) / 2.0 :
        temperatures[temperatures.size()/2];
    
    std::sort(pressures.begin(), pressures.end());
    double pressureMin = pressures.first();
    double pressureMax = pressures.last();
    double pressureSum = std::accumulate(pressures.begin(), pressures.end(), 0.0);
    double pressureMean = pressureSum / pressures.size();
    double pressureMedian = (pressures.size() % 2 == 0) ? 
        (pressures[pressures.size()/2 - 1] + pressures[pressures.size()/2]) / 2.0 :
        pressures[pressures.size()/2];
    
    QDateTime startTime = m_readings.first().timestamp;
    QDateTime endTime = m_readings.last().timestamp;
    qint64 duration = startTime.msecsTo(endTime) / 1000; 
    
    m_statistics["temperatureMin"] = tempMin;
    m_statistics["temperatureMax"] = tempMax;
    m_statistics["temperatureMean"] = tempMean;
    m_statistics["temperatureMedian"] = tempMedian;
    m_statistics["pressureMin"] = pressureMin;
    m_statistics["pressureMax"] = pressureMax;
    m_statistics["pressureMean"] = pressureMean;
    m_statistics["pressureMedian"] = pressureMedian;
    m_statistics["startTime"] = startTime;
    m_statistics["endTime"] = endTime;
    m_statistics["durationSeconds"] = duration;
    m_statistics["totalReadings"] = m_totalReadings;
    
    emit statisticsChanged();
}

QVariantMap PlaybackController::getStatistics() const
{
    return m_statistics;
}
