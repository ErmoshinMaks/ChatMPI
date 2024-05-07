import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.5


ApplicationWindow {
    id: window
    width: 540
    height: 940
    visible: true

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: LogPage {}
    }
}

