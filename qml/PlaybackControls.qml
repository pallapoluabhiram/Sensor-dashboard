import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "#f0f8ff"
    border.color: "#4682b4"
    border.width: 1
    radius: 5

    property bool loopEnabled: false
    property int stepSize: 1
    property bool showAdvancedControls: false
    property var bookmarks: []

    function addBookmark() {
        var bookmark = {
            index: playbackController.currentIndex,
            name: "Bookmark " + (bookmarks.length + 1),
            timestamp: new Date().toLocaleTimeString()
        }
        bookmarks.push(bookmark)
        bookmarksRepeater.model = bookmarks
    }

    function removeBookmark(index) {
        bookmarks.splice(index, 1)
        bookmarksRepeater.model = bookmarks
    }

    function jumpToBookmark(bookmarkIndex) {
        if (bookmarkIndex >= 0 && bookmarkIndex < bookmarks.length) {
            playbackController.seekToIndex(bookmarks[bookmarkIndex].index)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        RowLayout {
            Layout.fillWidth: true
            
            Text {
                text: "Playback Controls"
                font.bold: true
                font.pointSize: 12
                Layout.fillWidth: true
            }
            
            Button {
                text: showAdvancedControls ? "◀" : "▶"
                ToolTip.text: showAdvancedControls ? "Hide Advanced" : "Show Advanced"
                ToolTip.visible: hovered
                Layout.preferredWidth: 25
                onClicked: showAdvancedControls = !showAdvancedControls
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 6

            Button {
                text: "⏮⏮"
                ToolTip.text: "Jump to Start"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                onClicked: playbackController.seekToIndex(0)
            }

            Button {
                text: "⏮"
                ToolTip.text: "Rewind 10s"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                onClicked: playbackController.rewind()
            }

            Button {
                text: "◀"
                ToolTip.text: "Step Backward"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                enabled: playbackController.currentIndex > 0
                onClicked: {
                    var newIndex = Math.max(0, playbackController.currentIndex - stepSize)
                    playbackController.seekToIndex(newIndex)
                }
            }

            Button {
                text: playbackController.isPlaying ? "⏸" : "▶"
                ToolTip.text: playbackController.isPlaying ? "Pause" : "Play"
                ToolTip.visible: hovered
                Layout.preferredWidth: 45
                enabled: playbackController.totalReadings > 0
                highlighted: true
                onClicked: {
                    if (playbackController.isPlaying) {
                        playbackController.pause()
                    } else {
                        playbackController.play()
                    }
                }
            }

            Button {
                text: "▶"
                ToolTip.text: "Step Forward"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                enabled: playbackController.currentIndex < playbackController.totalReadings - 1
                onClicked: {
                    var newIndex = Math.min(playbackController.totalReadings - 1, playbackController.currentIndex + stepSize)
                    playbackController.seekToIndex(newIndex)
                }
            }

            Button {
                text: "⏹"
                ToolTip.text: "Stop"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                onClicked: playbackController.stop()
            }

            Button {
                text: "⏭"
                ToolTip.text: "Forward 10s"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                onClicked: playbackController.forward()
            }

            Button {
                text: "⏭⏭"
                ToolTip.text: "Jump to End"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                onClicked: playbackController.seekToIndex(playbackController.totalReadings - 1)
            }

            Button {
                text: loopEnabled ? "🔁" : "↪"
                ToolTip.text: loopEnabled ? "Loop Enabled" : "Enable Loop"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                checkable: true
                checked: loopEnabled
                onToggled: loopEnabled = checked
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                text: "Speed:"
                font.pointSize: 10
            }

            SpinBox {
                from: 1
                to: 100
                stepSize: 1
                value: playbackController.playbackSpeed * 10
                Layout.preferredWidth: 80
                
                property int decimals: 1
                property real realValue: value / 10.0

                validator: DoubleValidator {
                    bottom: Math.min(0.1, 10.0)
                    top: Math.max(0.1, 10.0)
                }

                textFromValue: function(value, locale) {
                    return (value / 10.0).toFixed(decimals) + "x"
                }

                valueFromText: function(text, locale) {
                    return Math.round(parseFloat(text) * 10)
                }

                onRealValueChanged: {
                    playbackController.playbackSpeed = realValue
                }
            }

            Button {
                text: "🔖"
                ToolTip.text: "Add Bookmark"
                ToolTip.visible: hovered
                Layout.preferredWidth: 35
                onClicked: addBookmark()
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 5

            Text {
                text: playbackController.currentIndex.toString()
                font.pointSize: 9
                Layout.preferredWidth: 30
            }

            Slider {
                Layout.fillWidth: true
                from: 0
                to: Math.max(1, playbackController.totalReadings - 1)
                value: playbackController.currentIndex
                stepSize: 1
                
                onMoved: {
                    playbackController.seekToIndex(Math.round(value))
                }

                background: Rectangle {
                    x: parent.leftPadding
                    y: parent.topPadding + parent.availableHeight / 2 - height / 2
                    implicitWidth: 200
                    implicitHeight: 4
                    width: parent.availableWidth
                    height: implicitHeight
                    radius: 2
                    color: "#bdbebf"

                    Rectangle {
                        width: parent.parent.visualPosition * parent.width
                        height: parent.height
                        color: "#4682b4"
                        radius: 2
                    }
                }

                handle: Rectangle {
                    x: parent.leftPadding + parent.visualPosition * (parent.availableWidth - width)
                    y: parent.topPadding + parent.availableHeight / 2 - height / 2
                    implicitWidth: 16
                    implicitHeight: 16
                    radius: 8
                    color: "#ffffff"
                    border.color: "#4682b4"
                    border.width: 2
                }
            }

            Text {
                text: playbackController.totalReadings.toString()
                font.pointSize: 9
                Layout.preferredWidth: 30
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            visible: showAdvancedControls
            spacing: 6
            
            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#cccccc"
            }
            
            RowLayout {
                Layout.fillWidth: true
                
                Text {
                    text: "Step Size:"
                    font.pointSize: 9
                }
                
                SpinBox {
                    from: 1
                    to: 100
                    value: stepSize
                    Layout.preferredWidth: 70
                    onValueChanged: stepSize = value
                }
                
                Item { Layout.fillWidth: true }
                
                Button {
                    text: "📷"
                    ToolTip.text: "Export Current View"
                    ToolTip.visible: hovered
                    Layout.preferredWidth: 30
                }
            }
            
            Text {
                text: "Bookmarks (" + bookmarks.length + "):"
                font.pointSize: 9
                font.bold: true
            }
            
            ScrollView {
                Layout.fillWidth: true
                Layout.preferredHeight: Math.min(60, bookmarks.length * 25)
                clip: true
                visible: bookmarks.length > 0
                
                ListView {
                    id: bookmarksRepeater
                    model: bookmarks
                    
                    delegate: Rectangle {
                        width: ListView.view.width
                        height: 22
                        color: index % 2 === 0 ? "#f8f9fa" : "#ffffff"
                        
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 2
                            spacing: 5
                            
                            Text {
                                text: modelData.name
                                font.pointSize: 8
                                Layout.fillWidth: true
                                elide: Text.ElideRight
                            }
                            
                            Text {
                                text: "#" + modelData.index
                                font.pointSize: 8
                                color: "#666666"
                                Layout.preferredWidth: 30
                            }
                            
                            Button {
                                text: "Go"
                                Layout.preferredWidth: 25
                                Layout.preferredHeight: 18
                                font.pointSize: 7
                                onClicked: jumpToBookmark(index)
                            }
                            
                            Button {
                                text: "×"
                                Layout.preferredWidth: 18
                                Layout.preferredHeight: 18
                                font.pointSize: 8
                                onClicked: removeBookmark(index)
                            }
                        }
                    }
                }
            }
        }

        Text {
            text: {
                if (playbackController.totalReadings === 0) {
                    return "No data loaded"
                } else if (playbackController.isPlaying) {
                    var statusText = "Playing... (" + playbackController.currentIndex + "/" + playbackController.totalReadings + ")"
                    if (loopEnabled) statusText += " 🔁"
                    return statusText
                } else {
                    return "Ready (" + playbackController.totalReadings + " data points loaded)"
                }
            }
            font.pointSize: 9
            color: "#666666"
            Layout.alignment: Qt.AlignHCenter
        }
        
        Connections {
            target: playbackController
            function onPlaybackFinished() {
                if (loopEnabled && playbackController.totalReadings > 0) {
                    playbackController.seekToIndex(0)
                    playbackController.play()
                }
            }
        }
    }
}
