import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.5

import chatlib 1.0

Page {
    id: root

    property string inConversationWith

    header: ToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        Label {
            text: qsTr("Contacts")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    // ListView {
    //     id: listView
    //     anchors.fill: parent
    //     topMargin: 48
    //     leftMargin: 48
    //     bottomMargin: 48
    //     rightMargin: 48
    //     spacing: 20
    //     model: SqlContactModel {}
    //     delegate: ItemDelegate {
    //         text: model.display
    //         width: listView.width - listView.leftMargin - listView.rightMargin
    //         height: 32
    //         leftPadding: 32 

    //         // Image {
    //         //     id: avatar
    //         //     // source: "qrc:/data/img/icon.png"
    //         // }
    //         onClicked: root.StackView.view.push("qrc:/ConversationPage.qml", { inConversationWith: model.display })
    //     }
    // }

}

