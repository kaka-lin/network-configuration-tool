import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    anchors.fill: parent

    GridLayout {
        id: grid
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30

        columns: 4
        rowSpacing: 12
        columnSpacing: 12

        // row 1
        Label {
            text: "Current Ip"

            Layout.row: 0
            Layout.column: 0
        }

        TextField {
            id: ipText
            Layout.preferredWidth: 300

            readOnly: true

            Layout.row: 0
            Layout.column: 1
        }

        Button {
            text: "Read"

            Layout.row: 0
            Layout.column: 2

            onClicked: {
                //
            }
        }

        // row 2
        Label {
            text: "Parameters"

            Layout.row: 1
            Layout.column: 0
        }

        TextField {
            id: currentTimeText
            Layout.preferredWidth: 300

            selectByMouse: true

            Layout.row: 1
            Layout.column: 1
        }

        Button {
            text: "Write"

            Layout.row: 1
            Layout.column: 2

            onClicked: {
                //
            }
        }
    }


    Connections {
        target: mainApp

        onPrepareMsg: {
            ipText.text = message;
        }
    }
}
