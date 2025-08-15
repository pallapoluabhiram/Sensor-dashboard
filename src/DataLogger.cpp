#include "DataLogger.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QApplication>

DataLogger::DataLogger(QObject *parent)
    : QObject(parent)
    , m_logFile(nullptr)
    , m_stream(nullptr)
    , m_isLogging(false)
    , m_frameTimer(new QTimer(this))
{
    m_dataDirectory = QApplication::applicationDirPath() + "/data";
    
    QDir dir;
    if (!dir.mkpath(m_dataDirectory)) {
        qDebug() << "Warning: Could not create data directory:" << m_dataDirectory;
    } else {
        QFileInfo dirInfo(m_dataDirectory);
        if (!dirInfo.isWritable()) {
            qDebug() << "Warning: Data directory is not writable:" << m_dataDirectory;
        }
    }
    
    m_frameTimer->setInterval(5000);
    m_frameTimer->setSingleShot(false);
}

DataLogger::~DataLogger()
{
    stopLogging();
}

bool DataLogger::startLogging()
{
    if (m_isLogging) {
        return true;
    }

    if (!createLogFile()) {
        emit error("Failed to create log file");
        return false;
    }

    m_isLogging = true;
    emit loggingChanged();
    
    qDebug() << "Started logging to:" << m_currentLogFile;
    return true;
}

void DataLogger::stopLogging()
{
    if (!m_isLogging) {
        return;
    }

    if (m_stream) {
        delete m_stream;
        m_stream = nullptr;
    }

    if (m_logFile) {
        m_logFile->close();
        delete m_logFile;
        m_logFile = nullptr;
    }

    m_isLogging = false;
    emit loggingChanged();
    
    qDebug() << "Stopped logging";
}

bool DataLogger::loadLogFile(const QString &filename)
{
    if (!QFile::exists(filename)) {
        emit error("File does not exist: " + filename);
        return false;
    }
    
    QFileInfo fileInfo(filename);
    if (!fileInfo.isReadable()) {
        emit error("File is not readable: " + filename + ". Please check file permissions.");
        return false;
    }
    
    if (fileInfo.size() == 0) {
        emit error("File is empty: " + filename);
        return false;
    }
    
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit error("Cannot open file: " + filename + ". Error: " + file.errorString());
        return false;
    }

    m_readings.clear();
    QTextStream in(&file);
    
    try {
        if (in.atEnd()) {
            file.close();
            emit error("File appears to be empty or corrupted: " + filename);
            return false;
        }
        
        QString header = in.readLine();
        if (!header.contains("Timestamp") || !header.contains("Temperature") || !header.contains("Pressure")) {
            emit error("Invalid file format. Expected CSV with Timestamp, Temperature, and Pressure columns: " + filename);
            file.close();
            return false;
        }
        
        int lineNumber = 1;
        int validReadings = 0;
        int invalidLines = 0;
        
        while (!in.atEnd()) {
            lineNumber++;
            QString line = in.readLine().trimmed();
            
            if (line.isEmpty()) continue;
            
            QStringList parts = line.split(',');
            
            if (parts.size() >= 3) {
                SensorReading reading;
                
                reading.timestamp = QDateTime::fromString(parts[0].trimmed(), Qt::ISODate);
                if (!reading.timestamp.isValid()) {
                    invalidLines++;
                    qDebug() << "Invalid timestamp on line" << lineNumber << ":" << parts[0];
                    continue;
                }
                
                bool tempOk;
                reading.temperature = parts[1].trimmed().toDouble(&tempOk);
                if (!tempOk) {
                    invalidLines++;
                    qDebug() << "Invalid temperature on line" << lineNumber << ":" << parts[1];
                    continue;
                }
                
                bool pressOk;
                reading.pressure = parts[2].trimmed().toDouble(&pressOk);
                if (!pressOk) {
                    invalidLines++;
                    qDebug() << "Invalid pressure on line" << lineNumber << ":" << parts[2];
                    continue;
                }
                
                if (parts.size() > 3) {
                    reading.frameFilename = parts[3].trimmed();
                }
                
                m_readings.append(reading);
                validReadings++;
            } else {
                invalidLines++;
                qDebug() << "Invalid line format on line" << lineNumber << ":" << line;
            }
        }
        
        file.close();
        
        if (validReadings == 0) {
            emit error("No valid data found in file: " + filename);
            return false;
        }
        
        if (invalidLines > 0) {
            qDebug() << "Warning: Skipped" << invalidLines << "invalid lines while loading" << filename;
        }
        
        emit dataLoaded();
        qDebug() << "Successfully loaded" << validReadings << "readings from" << filename;
        return true;
        
    } catch (const std::exception &e) {
        file.close();
        emit error("Error reading file " + filename + ": " + QString(e.what()));
        return false;
    } catch (...) {
        file.close();
        emit error("Unknown error occurred while reading file: " + filename);
        return false;
    }
}

QString DataLogger::getDataDirectory()
{
    return m_dataDirectory;
}

void DataLogger::logSensorData(double temperature, double pressure, const QString &timestamp)
{
    if (!m_isLogging || !m_stream) {
        return;
    }

    try {
        QString isoTimestamp = timestamp;
        if (!timestamp.contains('T')) {
            isoTimestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
        }
        
        QString frameFile = m_lastFrameFilename.isEmpty() ? "" : m_lastFrameFilename;
        *m_stream << isoTimestamp << "," << QString::number(temperature, 'f', 4) << "," 
                  << QString::number(pressure, 'f', 3) << "," << frameFile << "\n";
        
        if (m_stream->status() != QTextStream::Ok) {
            emit error("Error writing to log file. The disk may be full or the file may be locked.");
            return;
        }
        
        m_stream->flush();
        
        if (m_logFile && m_logFile->error() != QFile::NoError) {
            emit error("Log file error: " + m_logFile->errorString() + ". Logging may be incomplete.");
            return;
        }
        
        SensorReading reading;
        reading.timestamp = QDateTime::fromString(isoTimestamp, Qt::ISODate);
        reading.temperature = temperature;
        reading.pressure = pressure;
        reading.frameFilename = frameFile;
        m_readings.append(reading);
        
    } catch (const std::exception &e) {
        emit error("Error logging sensor data: " + QString(e.what()));
    } catch (...) {
        emit error("Unknown error occurred while logging sensor data");
    }
}

void DataLogger::logFrame(const QString &frameFilename)
{
    m_lastFrameFilename = frameFilename;
}

bool DataLogger::createLogFile()
{
    QDir dir(m_dataDirectory);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            emit error("Cannot create data directory: " + m_dataDirectory + ". Please check write permissions.");
            return false;
        }
    }
    
    QFileInfo dirInfo(m_dataDirectory);
    if (!dirInfo.isWritable()) {
        emit error("Data directory is not writable: " + m_dataDirectory + ". Please check folder permissions.");
        return false;
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString filename = m_dataDirectory + "/sensor_log_" + timestamp + ".csv";
    
    m_logFile = new QFile(filename);
    if (!m_logFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString errorMsg = QString("Cannot create log file: %1. Error: %2").arg(filename, m_logFile->errorString());
        emit error(errorMsg);
        delete m_logFile;
        m_logFile = nullptr;
        return false;
    }

    m_stream = new QTextStream(m_logFile);
    m_currentLogFile = filename;
    emit currentLogFileChanged();
    
    writeHeader();
    qDebug() << "Successfully created log file:" << filename;
    return true;
}

void DataLogger::writeHeader()
{
    if (m_stream) {
        *m_stream << "Timestamp,Temperature(C),Pressure(hPa),FrameFile\n";
        m_stream->flush();
    }
}
