import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

    ApplicationWindow {
        id: root
        width: 1200
        height: 800
        visible: true
        title: "Camera Sensor Dashboard - Enhanced"

        property bool isRecording: false
        property bool isPlayback: false
    
    function resetAll() {
        isRecording = false
        isPlayback = false
        temperatureChart.clearData()
        pressureChart.clearData()
        console.log("All data and states reset successfully")
    }
    
    ErrorDialog {
        id: errorDialog
    }
    
    FileDialog {
        id: loadFileDialog
        title: "Load sensor data file"
        nameFilters: ["CSV files (*.csv)"]
        onAccepted: {
            console.log("Attempting to load file:", selectedFile)
            
            try {
                var filePath = selectedFile.toString().replace("file://", "")
                if (dataLogger.loadLogFile(filePath)) {
                    playbackController.loadData(dataLogger.getReadings())
                    imageProvider.setPlaybackMode(true)
                    isPlayback = true
                    console.log("Successfully loaded data file and entered playback mode")
                } else {
                    console.error("Failed to load data file:", filePath)
                }
            } catch (error) {
                errorDialog.showError("File Load Error", "Unexpected error while loading file: " + error.toString())
            }
        }
        
        onRejected: {
            console.log("File selection was cancelled")
        }
    }

    Connections {
        target: cameraCapture
        function onError(message) {
            errorDialog.showError("Camera Error", message)
            console.error("Camera Error:", message)
        }
    }
    
    Connections {
        target: dataLogger
        function onError(message) {
            errorDialog.showError("Data Logger Error", message)
            console.error("Data Logger Error:", message)
        }
    }
    
    Connections {
        target: loadFileDialog
        function onRejected() {
            console.log("File load dialog was cancelled")
        }
    }
    
    Connections {
        target: sensorGenerator
        function onSamplingRateChanged() {
            console.log("Sampling rate changed to:", sensorGenerator.samplingRate, "Hz")
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        ColumnLayout {
            Layout.preferredWidth: 400
            Layout.fillHeight: true
            spacing: 10

            CameraView {
                id: cameraView
                Layout.fillWidth: true
                Layout.preferredHeight: 280
                isPlaybackMode: isPlayback
            }

            ControlPanel {
                id: controlPanel
                Layout.fillWidth: true
                Layout.preferredHeight: 180
                
                onStartRecording: {
                    console.log("Start Acquisition clicked - starting camera, sensors, and data logging")
                    
                    var cameraStarted = cameraCapture.start()
                    var sensorStarted = sensorGenerator.start()
                    var loggerStarted = dataLogger.startLogging()
                    
                    console.log("Camera started:", cameraStarted)
                    console.log("Sensor started:", sensorStarted)
                    console.log("Logger started:", loggerStarted)
                    
                    if (sensorStarted && loggerStarted) {
                        isRecording = true
                        isPlayback = false
                        console.log("Recording started successfully - Sensor:", sensorStarted, "Logger:", loggerStarted, "Camera:", cameraStarted)
                        if (!cameraStarted) {
                            console.log("Note: Camera failed to start, but sensor logging is active")
                        }
                    } else {
                        console.log("Critical systems failed - Sensor:", sensorStarted, "Logger:", loggerStarted)
                        if (sensorStarted) sensorGenerator.stop()
                        if (loggerStarted) dataLogger.stopLogging()
                        if (cameraStarted) cameraCapture.stop()
                    }
                }
                
                onStopRecording: {
                    cameraCapture.stop()
                    sensorGenerator.stop()
                    dataLogger.stopLogging()
                    resetAll()
                }
                
                onLoadData: {
                    loadFileDialog.open()
                }
            }

            PlaybackControls {
                id: playbackControls
                Layout.fillWidth: true
                Layout.preferredHeight: 150
                visible: isPlayback
                
                Connections {
                    target: playbackController
                    function onPlaybackFinished() {
                        if (!playbackControls.loopEnabled) {
                            isPlayback = false
                        }
                    }
                }
            }
            
            Button {
                text: "Exit Playback Mode"
                Layout.fillWidth: true
                Layout.preferredHeight: 45
                visible: isPlayback
                
                background: Rectangle {
                    color: "#ff9800"
                    border.color: "#f57c00"
                    border.width: 1
                    radius: 5
                }
                
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: {
                    playbackController.stop()
                    imageProvider.setPlaybackMode(false)
                    isPlayback = false
                    temperatureChart.clearData()
                    pressureChart.clearData()
                    console.log("Exited playback mode, ready for live data")
                }
            }

            ScrollView {
                id: settingsScrollView
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: 200
                clip: true
                
                SettingsPanel {
                    id: settingsPanel
                    width: settingsScrollView.availableWidth
                    height: Math.max(settingsScrollView.availableHeight, implicitHeight)
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            Text {
                text: "Sensor Data"
                font.pointSize: 16
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
            }

            SensorChart {
                id: temperatureChart
                Layout.fillWidth: true
                Layout.preferredHeight: 300
                chartTitle: "Temperature (°C)"
                valueRange: [10, 40]
                lineColor: "#ff6b6b"
                
                property real lastTemperature: 20.0
                
                Connections {
                    target: sensorGenerator
                    function onDataReady(temperature, pressure, timestamp) {
                        if (!isPlayback) {
                            temperatureChart.lastTemperature = temperature
                            temperatureChart.addDataPoint(temperature)
                        }
                    }
                }
                
                Connections {
                    target: playbackController
                    function onDataPoint(temperature, pressure, timestamp, frameFile) {
                        if (isPlayback) {
                            temperatureChart.lastTemperature = temperature
                            temperatureChart.addDataPoint(temperature)
                        }
                    }
                }
            }

            SensorChart {
                id: pressureChart
                Layout.fillWidth: true
                Layout.preferredHeight: 300
                chartTitle: "Pressure (hPa)"
                valueRange: [980, 1040]
                lineColor: "#4ecdc4"
                
                property real lastPressure: 1013.25
                
                Connections {
                    target: sensorGenerator
                    function onDataReady(temperature, pressure, timestamp) {
                        if (!isPlayback) {
                            pressureChart.lastPressure = pressure
                            pressureChart.addDataPoint(pressure)
                        }
                    }
                }
                
                Connections {
                    target: playbackController
                    function onDataPoint(temperature, pressure, timestamp, frameFile) {
                        if (isPlayback) {
                            pressureChart.lastPressure = pressure
                            pressureChart.addDataPoint(pressure)
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                color: "#f0f0f0"
                border.color: "#cccccc"
                border.width: 1
                radius: 5

                RowLayout {
                    anchors.centerIn: parent
                    spacing: 40

                    Column {
                        Text {
                            text: "Temperature"
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: temperatureChart.lastTemperature.toFixed(1) + " °C"
                            font.pointSize: 14
                            color: "#ff6b6b"
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Column {
                        Text {
                            text: "Pressure"
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: pressureChart.lastPressure.toFixed(1) + " hPa"
                            font.pointSize: 14
                            color: "#4ecdc4"
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Column {
                        Text {
                            text: "Status"
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: {
                                if (isRecording) return "Recording"
                                if (isPlayback) return "Playback"
                                return "Stopped"
                            }
                            font.pointSize: 12
                            color: isRecording ? "#dc3545" : (isPlayback ? "#28a745" : "#6c757d")
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }
        }
    }
}
