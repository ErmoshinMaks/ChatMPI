import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.5

import chatlib 1.0

Page {
    id: root


    header: ToolBar {
        height: 50
        background: Rectangle {
            anchors.fill: parent
            color: "#6D9886"
        }
        Label {
            text: qsTr("Login")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
        ToolButton {
            text: qsTr("Log button")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.push("qrc:/ContactPage.qml")
            // onClicked: root.StackView.view.pop()
        }
    }



    Rectangle {
        id: rect
        signal sendMessage()    // определяем сигнал
        anchors.fill: parent
        Column{
            anchors.fill: parent
            Button {
                id:sendButton
                text: "Send"
                onClicked: rect.sendMessage()
            }
            Text{
                id: content
            }
        }
        onSendMessage: {    // определяем обработчик сигнала sendMessage()
            content.text += "SendMessage Signal Received\n"
        }
    }

    

}

