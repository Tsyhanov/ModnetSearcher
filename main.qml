import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import threadadm.config 1.0

Window {
    id: mainWindow
    visible: true
    width: 270
    minimumWidth: 270
    maximumWidth: 270
    height: 340
    minimumHeight: 340
    maximumHeight: 340
    color: "#c1bebe"
    title: "Modbus TCP device searcher"
    property real progress: 0.0
    Threadadm{
        id: threadadmconf
    }

    GroupBox {
        id: groupBox
        x: 6
        y: 8
        width: 259
        height: 218
        title: qsTr("Search settings")

        ComboBox {
            id: comboStart
            x: -12
            y: 59
            width: 120
            model: [1,10,20,30,40,50,60,70,80,90,100,
                   110,120,130,140,150,160,170,180,190,200,
                   210,220,230,240]
        }

        ComboBox {
            id: comboEnd
            x: 127
            y: 59
            width: 120
            model: [10,20,30,40,50,60,70,80,90,100,
                110,120,130,140,150,160,170,180,190,200,
                210,220,230,240,254]
        }

        Button {
            id: buttonStart
            x: -12
            y: 117
            width: 259
            height: 40
            text: qsTr("Start search")
            onClicked: {
//                searchconf.startSearch();
                progressBar.from = comboStart.displayText;
                progressBar.to = comboEnd.displayText;
            }
        }

        ProgressBar {
            id: progressBar
            x: -12
            y: 169
            width: 259
            height: 6
            hoverEnabled: false
            value: progress
            from: 0
            to: 1
        }

        Label {
            id: label
            x: -12
            y: -13
            text: qsTr("IP address")
        }

        Label {
            id: label2
            x: -12
            y: 45
            text: qsTr("From address")
        }

        Label {
            id: label3
            x: 127
            y: 45
            text: qsTr("To address")
        }

        TextInput {
            id: textIP
            x: -12
            y: 12
            width: 247
            height: 27
            text: qsTr("192.168.1.*")
            font.pixelSize: 20
        }
    }

    Button {
        id: buttonClose
        x: 6
        y: 292
        width: 259
        height: 40
        text: qsTr("Close")
        onClicked: {
            Qt.quit();
        }
    }

    TextArea {
        id: textArea
        x: 6
        y: 232
        width: 259
        height: 46
        text: qsTr("Log:")
    }
}
