import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "#fafafa"
    border.color: "#cccccc"
    border.width: 1
    radius: 5

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15

        Text {
            text: "Settings"
            font.bold: true
            font.pointSize: 14
            Layout.alignment: Qt.AlignHCenter
        }

        GroupBox {
            title: "Camera Settings"
            Layout.fillWidth: true
            
            background: Rectangle {
                color: "#ffffff"
                border.color: "#dddddd"
                border.width: 1
                radius: 3
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    Layout.fillWidth: true

                    Text {
                        text: "Resolution:"
                        Layout.preferredWidth: 80
                    }

                    ComboBox {
                        id: resolutionCombo
                        Layout.fillWidth: true
                        model: ["640x480", "1280x720", "1920x1080"]
                        currentIndex: 0
                        
                        onActivated: {
                            var resolution = currentText.split('x')
                            if (resolution.length === 2) {
                                cameraCapture.resolution = Qt.size(parseInt(resolution[0]), parseInt(resolution[1]))
                            }
                        }
                    }
                }
            }
        }

        GroupBox {
            title: "Sensor Settings"
            Layout.fillWidth: true
            
            background: Rectangle {
                color: "#ffffff"
                border.color: "#dddddd"
                border.width: 1
                radius: 3
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    Layout.fillWidth: true

                    Text {
                        text: "Sampling Rate:"
                        Layout.preferredWidth: 100
                    }

                    ComboBox {
                        id: samplingRateCombo
                        Layout.fillWidth: true
                        model: ["0.5 Hz", "1.0 Hz", "5.0 Hz"]
                        currentIndex: 1
                        
                        onActivated: {
                            var rateText = currentText.split(' ')[0]
                            var rate = parseFloat(rateText)
                            sensorGenerator.samplingRate = rate
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "#f8f8f8"
                    border.color: "#e0e0e0"
                    border.width: 1
                    radius: 3

                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 20

                        Column {
                            Text {
                                text: "Temperature"
                                font.pointSize: 9
                                color: "#666666"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text {
                                text: sensorGenerator.temperature.toFixed(1) + "°C"
                                font.bold: true
                                color: "#ff6b6b"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }

                        Column {
                            Text {
                                text: "Pressure"
                                font.pointSize: 9
                                color: "#666666"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text {
                                text: sensorGenerator.pressure.toFixed(1) + "hPa"
                                font.bold: true
                                color: "#4ecdc4"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }
        }

        GroupBox {
            title: "Data Storage"
            Layout.fillWidth: true
            
            background: Rectangle {
                color: "#ffffff"
                border.color: "#dddddd"
                border.width: 1
                radius: 3
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                Text {
                    text: "Data Directory:"
                    font.pointSize: 10
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 40
                    color: "#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    radius: 3

                    Text {
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 8
                        text: dataLogger.getDataDirectory()
                        font.pointSize: 9
                        color: "#333333"
                        elide: Text.ElideMiddle
                        width: parent.width - 16
                    }
                }

                Button {
                    text: "Open Data Folder"
                    Layout.alignment: Qt.AlignHCenter
                    
                    background: Rectangle {
                        color: "#e3f2fd"
                        border.color: "#2196f3"
                        border.width: 1
                        radius: 3
                    }

                    onClicked: {
                    }
                }
            }
        }

        GroupBox {
            title: "About"
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            
            background: Rectangle {
                color: "#ffffff"
                border.color: "#dddddd"
                border.width: 1
                radius: 3
            }

            Column {
                anchors.centerIn: parent
                spacing: 8

                Text {
                    text: "Camera Sensor Dashboard"
                    font.bold: true
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: "Version 1.0.0"
                    font.pointSize: 10
                    color: "#666666"
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: "Built with Qt6 & OpenCV"
                    font.pointSize: 9
                    color: "#888888"
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: "Generates random sensor data\nfor temperature and pressure"
                    font.pointSize: 9
                    color: "#888888"
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
