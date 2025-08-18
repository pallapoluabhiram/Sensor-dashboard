import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    modal: true
    anchors.centerIn: parent
    width: 400
    height: 200
    
    property string errorTitle: ""
    property string errorMessage: ""

    function showError(title, message) {
        errorTitle = title
        errorMessage = message
        open()
    }

    title: errorTitle

    background: Rectangle {
        color: "#ffffff"
        border.color: "#ff6b6b"
        border.width: 2
        radius: 8
    }

    header: Rectangle {
        height: 50
        color: "#ff6b6b"
        radius: 8

        Text {
            anchors.centerIn: parent
            text: root.errorTitle
            color: "white"
            font.bold: true
            font.pointSize: 14
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            color: "#fff5f5"
            border.color: "#fed7d7"
            border.width: 1
            radius: 5

            Row {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 15
                spacing: 10

                Text {
                    text: "⚠️"
                    font.pointSize: 24
                }

                Text {
                    text: "Error"
                    font.bold: true
                    font.pointSize: 16
                    color: "#c53030"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            TextArea {
                text: root.errorMessage
                wrapMode: TextArea.Wrap
                readOnly: true
                selectByMouse: true
                color: "#333333"
                
                background: Rectangle {
                    color: "#f8f8f8"
                    border.color: "#e0e0e0"
                    border.width: 1
                    radius: 3
                }
            }
        }
    }

    standardButtons: Dialog.Ok

    onAccepted: {
        close()
    }
}
