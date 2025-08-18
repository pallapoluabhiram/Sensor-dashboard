#pragma once

#include <QObject>
#include <QTimer>
#include "DataLogger.h"

class PlaybackController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY playingChanged)
    Q_PROPERTY(bool isPaused READ isPaused NOTIFY pausedChanged)
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(int totalReadings READ totalReadings NOTIFY totalReadingsChanged)
    Q_PROPERTY(double playbackSpeed READ playbackSpeed WRITE setPlaybackSpeed NOTIFY playbackSpeedChanged)
    Q_PROPERTY(bool loopEnabled READ loopEnabled WRITE setLoopEnabled NOTIFY loopEnabledChanged)
    Q_PROPERTY(QDateTime currentTimestamp READ currentTimestamp NOTIFY currentTimestampChanged)

public:
    explicit PlaybackController(QObject *parent = nullptr);

    bool isPlaying() const { return m_isPlaying; }
    bool isPaused() const { return m_isPaused; }
    int currentIndex() const { return m_currentIndex; }
    int totalReadings() const { return m_totalReadings; }
    double playbackSpeed() const { return m_playbackSpeed; }
    void setPlaybackSpeed(double speed);
    bool loopEnabled() const { return m_loopEnabled; }
    void setLoopEnabled(bool enabled);
    QDateTime currentTimestamp() const;

    Q_INVOKABLE void loadData(const QList<SensorReading> &readings);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void forward(); 
    Q_INVOKABLE void rewind();  
    Q_INVOKABLE void seekToIndex(int index);
    Q_INVOKABLE void seekToTimestamp(const QDateTime &timestamp);
    Q_INVOKABLE QList<SensorReading> getReadingsInRange(const QDateTime &start, const QDateTime &end);
    Q_INVOKABLE QVariantMap getStatistics() const;

signals:
    void playingChanged();
    void pausedChanged();
    void currentIndexChanged();
    void totalReadingsChanged();
    void playbackSpeedChanged();
    void loopEnabledChanged();
    void currentTimestampChanged();
    void dataPoint(double temperature, double pressure, const QString &timestamp, const QString &frameFilename);
    void playbackFinished();
    void statisticsChanged();

private slots:
    void nextDataPoint();

private:
    void updateCurrentData();
    int findIndexByTimeOffset(int currentIndex, int secondsOffset);
    void calculateStatistics();
    int findIndexByTimestamp(const QDateTime &timestamp);

    QList<SensorReading> m_readings;
    QTimer *m_playbackTimer;
    bool m_isPlaying;
    bool m_isPaused;
    int m_currentIndex;
    int m_totalReadings;
    double m_playbackSpeed;
    bool m_loopEnabled;
    QVariantMap m_statistics;
};
