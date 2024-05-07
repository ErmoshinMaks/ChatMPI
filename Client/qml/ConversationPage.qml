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
    }

    // ColumnLayout {
    //     anchors.fill: parent
    //     ListView {
    //         id: listView
    //         Layout.fillWidth: true
    //         Layout.fillHeight: true
    //         Layout.margins: pane.leftPadding + messageField.leftPadding
    //         displayMarginBeginning: 40
    //         displayMarginEnd: 40
    //         verticalLayoutDirection: ListView.BottomToTop
    //         spacing: 12
            
    //         model: SqlConversationModel {
    //             recipient: inConversationWith
    //         }

    //         delegate: Column {
    //             anchors.right: sentByMe ? listView.contentItem.right : undefined
    //             spacing: 6

    //             readonly property bool sentByMe: model.recipient !== "Me"

    //             Row {
    //                 id: messageRow
    //                 spacing: 6
    //                 anchors.right: sentByMe ? parent.right : undefined

    //                 Image {
    //                     id: avatar
    //                     // source: !sentByMe ? "images/" + model.author.replace(" ", "_") + ".png" : ""
    //                     source: "qrc:/data/img/icon.png"
    //                 }

    //                 Rectangle {
    //                     width: Math.min(messageText.implicitWidth + 24,
    //                         listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
    //                     height: messageText.implicitHeight + 24
    //                     color: sentByMe ? "lightgrey" : "steelblue"

    //                     Label {
    //                         id: messageText
    //                         text: model.message
    //                         color: sentByMe ? "black" : "white"
    //                         anchors.fill: parent
    //                         anchors.margins: 12
    //                         wrapMode: Label.Wrap
    //                     }
    //                 }
    //             }

    //             Label {
    //                 id: timestampText
    //                 text: Qt.formatDateTime(model.timestamp, "d MMM hh:mm")
    //                 color: "lightgrey"
    //                 anchors.right: sentByMe ? parent.right : undefined
    //             }
    //         }

    //         ScrollBar.vertical: ScrollBar {}
    //     }

    //     // ListView {
    //     //     id: listView
    //     //     Layout.fillWidth: true
    //     //     Layout.fillHeight: true
    //     //     Layout.margins: pane.leftPadding + messageField.leftPadding
    //     //     displayMarginBeginning: 40
    //     //     displayMarginEnd: 40
    //     //     verticalLayoutDirection: ListView.BottomToTop
    //     //     spacing: 12
    //     //     model: 11
    //     //     delegate: Row {
    //     //         readonly property bool sentByMe: index % 2 == 0

    //     //         anchors.right: sentByMe ? listView.contentItem.right : undefined
    //     //         spacing: 6

    //     //         Rectangle {
    //     //             id: avatar
    //     //             width: height
    //     //             height: parent.height
    //     //             color: "grey"
    //     //             visible: !sentByMe
    //     //         }

    //     //         Rectangle {
    //     //             width: 80
    //     //             height: 40
    //     //             color: sentByMe ? "lightgrey" : "steelblue"

    //     //             Label {
    //     //                 anchors.centerIn: parent
    //     //                 text: index
    //     //                 color: sentByMe ? "black" : "white"
    //     //             }
    //     //         }
    //     //     }

    //     //     ScrollBar.vertical: ScrollBar {}
    //     // }

    //     Pane {
    //         id: pane
    //         Layout.fillWidth: true
    //         Layout.fillHeight: false

    //         RowLayout {
    //             width: parent.width

    //             TextArea {
    //                 id: messageField
    //                 Layout.fillWidth: true
    //                 placeholderText: qsTr("Compose message")
    //                 wrapMode: TextArea.Wrap
    //             }

    //             // Button {
    //             //     id: sendButton
    //             //     text: qsTr("Send")
    //             //     enabled: messageField.length > 0
    //             //     Layout.fillWidth: false
    //             // }
    //             Button {
    //                 id: sendButton
    //                 text: qsTr("Send")
    //                 enabled: messageField.length > 0
    //                 Layout.fillWidth: false
    //                 onClicked: {
    //                     listView.model.sendMessage(inConversationWith, messageField.text);
    //                     messageField.text = "";
    //                 }
    //             }
    //         }
    //     }

    // }  
} 