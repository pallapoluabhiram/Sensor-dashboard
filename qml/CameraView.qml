import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    color: "#000000"
    border.color: "#cccccc"
    border.width: 2
    radius: 5

    property alias imageSource: cameraImage.source
    property bool isPlaybackMode: false

    Image {
        id: cameraImage
        anchors.fill: parent
        anchors.margins: 2
        fillMode: Image.PreserveAspectFit
        source: "image://camera/current"
        cache: false
        
        Timer {
            id: liveRefreshTimer
            interval: 33
            running: cameraCapture.isRunning && !root.isPlaybackMode
            repeat: true
            onTriggered: {
                var timestamp = Date.now()
                cameraImage.source = "image://camera/current?" + timestamp
            }
        }
        
        // Add connections to refresh image during playback
        Connections {
            target: playbackController
            function onDataPoint(temperature, pressure, timestamp, frameFile) {
                if (root.isPlaybackMode) {
                    // Force image refresh by changing source
                    var refreshTimestamp = Date.now()
                    cameraImage.source = "image://camera/current?" + refreshTimestamp
                }
            }
        }
        
        Text {
            anchors.centerIn: parent
            text: "No Camera Feed"
            color: "#888888"
            font.pointSize: 14
            visible: cameraImage.status !== Image.Ready
        }
    }

    Rectangle {
        id: recordingIndicator
        width: 20
        height: 20
        radius: 10
        color: "#ff0000"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        visible: cameraCapture.isRunning

        SequentialAnimation on opacity {
            running: recordingIndicator.visible
            loops: Animation.Infinite
            PropertyAnimation { to: 0.3; duration: 500 }
            PropertyAnimation { to: 1.0; duration: 500 }
        }
    }

    Text {
        anchors.top: recordingIndicator.bottom
        anchors.right: parent.right
        anchors.margins: 10
        text: "REC"
        color: "#ff0000"
        font.bold: true
        font.pointSize: 10
        visible: cameraCapture.isRunning
    }
}
