import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "#f8f8f8"
    border.color: "#cccccc"
    border.width: 1
    radius: 5

    signal startRecording()
    signal stopRecording()
    signal loadData()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 10

        Text {
            text: "Control Panel"
            font.bold: true
            font.pointSize: 14
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                id: startButton
                text: "Start Acquisition"
                enabled: !cameraCapture.isRunning && !sensorGenerator.isRunning
                Layout.fillWidth: true
                
                background: Rectangle {
                    color: startButton.enabled ? "#4CAF50" : "#cccccc"
                    radius: 5
                    border.color: startButton.enabled ? "#45a049" : "#999999"
                    border.width: 1
                }
                
                contentItem: Text {
                    text: startButton.text
                    color: "white"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                onClicked: root.startRecording()
            }

            Button {
                id: stopButton
                text: "Stop Acquisition"
                enabled: cameraCapture.isRunning || sensorGenerator.isRunning
                Layout.fillWidth: true
                
                background: Rectangle {
                    color: stopButton.enabled ? "#f44336" : "#cccccc"
                    radius: 5
                    border.color: stopButton.enabled ? "#da190b" : "#999999"
                    border.width: 1
                }
                
                contentItem: Text {
                    text: stopButton.text
                    color: "white"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                onClicked: root.stopRecording()
            }
        }

        Button {
            text: "Load Recorded Data"
            Layout.fillWidth: true
            enabled: !cameraCapture.isRunning && !sensorGenerator.isRunning
            
            background: Rectangle {
                color: parent.enabled ? "#2196F3" : "#cccccc"
                radius: 5
                border.color: parent.enabled ? "#0b7dda" : "#999999"
                border.width: 1
            }
            
            contentItem: Text {
                text: parent.text
                color: "white"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: root.loadData()
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#ffffff"
            border.color: "#cccccc"
            border.width: 1
            radius: 5

            Column {
                anchors.centerIn: parent
                spacing: 12

                Text {
                    text: "System Status"
                    font.bold: true
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: 14
                        height: 14
                        radius: 7
                        color: cameraCapture.isRunning ? "#4CAF50" : "#cccccc"
                    }
                    Text {
                        text: "Camera"
                        font.pointSize: 11
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: 14
                        height: 14
                        radius: 7
                        color: sensorGenerator.isRunning ? "#4CAF50" : "#cccccc"
                    }
                    Text {
                        text: "Sensors"
                        font.pointSize: 11
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }
}
