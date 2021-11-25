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
    flags: Qt.WA_TranslucentBackground

    background: Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:///background.jpg"
    }
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            Rectangle {
                border.color: "red"
                border.width: 1
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                width: 50
                height: 50
                color: "green"
            }
            Item {
                Layout.fillWidth: true
            }
            Rectangle {
                border.color: "red"
                border.width: 1
                Layout.alignment: Qt.AlignTop | Qt.AlignRight
                width: 50
                height: 50
                color: "green"
            }
        }
        ColumnLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 50
            Layout.rightMargin: 50
            spacing: 10

            Rectangle {
                border.color: "red"
                border.width: 1
                Layout.fillWidth: true
                height: 10
                color: "red"
            }

            WidgetContainer {
                id: container
                objectName: "myWidget"
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Rectangle {
                border.color: "red"
                border.width: 1
                Layout.fillWidth: true
                height: 10
                color: "red"
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Rectangle {
                border.color: "red"
                border.width: 1
                Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
                width: 50
                height: 50
                color: "green"
            }
            Item {
                Layout.fillWidth: true
            }
            Rectangle {
                border.color: "red"
                border.width: 1
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                width: 50
                height: 50
                color: "green"
            }
        }
    }
}
