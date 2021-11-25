import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.private 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World from QML")

    background: Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:///background.jpg"
    }

    WidgetContainer {
        id: container
        objectName: "myWidget"
        anchors.fill: parent
        anchors.margins: 50
    }
}
