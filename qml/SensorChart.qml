import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    color: "#ffffff"
    border.color: "#cccccc"
    border.width: 1
    radius: 5

    property string chartTitle: "Sensor Data"
    property var valueRange: [0, 100]
    property color lineColor: "#0066cc"
    property int maxDataPoints: 50
    property var dataPoints: []

    function addDataPoint(value) {
        dataPoints.push(value)
        if (dataPoints.length > maxDataPoints) {
            dataPoints.shift()
        }
        canvas.requestPaint()
    }

    function clearData() {
        dataPoints = []
        canvas.requestPaint()
    }

    Text {
        id: titleText
        text: root.chartTitle
        font.bold: true
        font.pointSize: 12
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 10
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        anchors.topMargin: titleText.height + 20
        anchors.margins: 20

        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            if (root.dataPoints.length === 0) {
                return
            }

            ctx.strokeStyle = "#eeeeee"
            ctx.lineWidth = 1

            for (var i = 0; i <= 5; i++) {
                var y = i * height / 5
                ctx.beginPath()
                ctx.moveTo(0, y)
                ctx.lineTo(width, y)
                ctx.stroke()
            }

            for (var j = 0; j < 10; j++) {
                var x = j * width / 9
                ctx.beginPath()
                ctx.moveTo(x, 0)
                ctx.lineTo(x, height)
                ctx.stroke()
            }

            if (root.dataPoints.length > 1) {
                ctx.strokeStyle = root.lineColor
                ctx.lineWidth = 2
                ctx.beginPath()

                var minVal = root.valueRange[0]
                var maxVal = root.valueRange[1]
                var valRange = maxVal - minVal

                for (var k = 0; k < root.dataPoints.length; k++) {
                    var xPos = (k / (root.maxDataPoints - 1)) * width
                    var normalizedValue = (root.dataPoints[k] - minVal) / valRange
                    var yPos = height - (normalizedValue * height)

                    if (k === 0) {
                        ctx.moveTo(xPos, yPos)
                    } else {
                        ctx.lineTo(xPos, yPos)
                    }
                }

                ctx.stroke()

                ctx.fillStyle = root.lineColor
                for (var l = 0; l < root.dataPoints.length; l++) {
                    var xPos2 = (l / (root.maxDataPoints - 1)) * width
                    var normalizedValue2 = (root.dataPoints[l] - minVal) / valRange
                    var yPos2 = height - (normalizedValue2 * height)

                    ctx.beginPath()
                    ctx.arc(xPos2, yPos2, 3, 0, 2 * Math.PI)
                    ctx.fill()
                }
            }
        }
    }

    Column {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 5
        spacing: canvas.height / 5 - 10

        Repeater {
            model: 6
            Text {
                text: (root.valueRange[1] - (index * (root.valueRange[1] - root.valueRange[0]) / 5)).toFixed(1)
                font.pointSize: 8
                color: "#666666"
            }
        }
    }

    Rectangle {
        width: 80
        height: 30
        color: "#f8f8f8"
        border.color: root.lineColor
        border.width: 1
        radius: 3
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        Text {
            anchors.centerIn: parent
            text: root.dataPoints.length > 0 ? root.dataPoints[root.dataPoints.length - 1].toFixed(1) : "---"
            font.bold: true
            font.pointSize: 10
            color: root.lineColor
        }
    }
}
