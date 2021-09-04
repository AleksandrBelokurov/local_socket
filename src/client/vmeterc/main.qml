import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Client 4 testing virtual V meter")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: page1
            width: 600
            height: 400

            header: Label {
                text: qsTr("Control")
                font.pixelSize: Qt.application.font.pixelSize * 2
                padding: 10
            }
            Button {
                id: buttonConnect
                x: 5
                y: 5
                text: qsTr("Connect")
                onClicked: qmlSignalConnect("Try connect")
            }
            Label {
                id: labelConnectStatus
                objectName: "lConnectStatus"
                anchors.left: buttonConnect.right
                anchors.verticalCenter: buttonConnect.verticalCenter
                anchors.leftMargin: 15
                font.pixelSize: Qt.application.font.pixelSize * 1.5
                text: qsTr("connect status")
            }
            Button {
                id: buttonDisconnect
                anchors.left: labelConnectStatus.right
                anchors.verticalCenter: labelConnectStatus.verticalCenter
                anchors.leftMargin: 15
                text: qsTr("Disconnect")
                onClicked: qmlSignalDisconnect("Try disconnect")
            }
            ComboBox {
                id: cbCommand
                currentIndex: -1
                model: ListModel {
                    id: cbCommItems
                    ListElement { text: "get_status"}
                    ListElement { text: "set_range"}
                    ListElement { text: "start_measure"}
                    ListElement { text: "stop_measure"}
                    ListElement { text: "get_result"}
                }
                width: 200
                anchors.top: buttonConnect.bottom
                anchors.left: buttonConnect.left
                anchors.topMargin: 15
                displayText: "choose command"
                onActivated: {
//                    console.debug(cbCommItems.get(currentIndex).text)
                    textSendCommand.text = cbCommItems.get(currentIndex).text + ", "
                    cbChannel.enabled = true
                    cbRange.enabled = false
                }
            }
            ComboBox {
                id: cbChannel
                currentIndex: -1
                enabled: false
                model: ListModel {
                    id: cbChannItems
                    ListElement { text: "channel0"}
                    ListElement { text: "channel1"}
                    ListElement { text: "channel2"}
                    ListElement { text: "channel3"}
                }
                width: 200
                anchors.left: cbCommand.right
                anchors.verticalCenter: cbCommand.verticalCenter
                anchors.leftMargin: 15
                displayText: "choose channel"
                onActivated: {
                    if (textSendCommand.text === "set_range, ") cbRange.enabled = true
                    textSendCommand.text = textSendCommand.text
                            + cbChannItems.get(currentIndex).text + ", "
                    cbChannel.enabled = false
                }
            }
            ComboBox {
                id: cbRange
                currentIndex: -1
                enabled: false
                model: ListModel {
                    id: cbRangeItems
                    ListElement { text: "range0"}
                    ListElement { text: "range1"}
                    ListElement { text: "range2"}
                    ListElement { text: "range3"}
                }
                width: 200
                anchors.left: cbChannel.right
                anchors.verticalCenter: cbChannel.verticalCenter
                anchors.leftMargin: 15
                displayText: "choose range"
                onActivated: {
                    textSendCommand.text = textSendCommand.text
                            + cbRangeItems.get(currentIndex).text + ", "
                    cbRange.enabled = false
                }
            }
            Rectangle {
                id: recSndCmd
                border.width: 1
                border.color: "black"
                height: parent.height * 0.08
                width: parent.width * 0.97
                anchors.centerIn: parent
                TextInput
                {
                    id: textSendCommand
                    objectName: "SendCommand"
                    anchors.fill: parent
                    anchors.margins: 3
                    font.pixelSize: parent.height * 0.6
                    text: "command would be here"
                }
            }
            Text
            {
                anchors.bottom: recSndCmd.top
                anchors.left: recSndCmd.left
                anchors.bottomMargin: 10
                font.pixelSize: Qt.application.font.pixelSize * 1.5
                text: 'outgoing command:'
            }

            Button {
                id: buttonSend
                anchors.top: recSndCmd.bottom
                anchors.left: recSndCmd.left
                anchors.topMargin: 10
                text: qsTr("Send")
                onClicked: qmlSignalSend(textSendCommand.text)
            }
            Rectangle {
                id: recResponse
                border.width: 1
                border.color: "black"
                height: parent.height * 0.4
                anchors.left: buttonSend.right
                anchors.leftMargin: 10
                anchors.top: buttonSend.top
                anchors.right: recSndCmd.right
                TextArea {
                    id: textResponse
                    objectName: "tResponse"
                    wrapMode: Text.WordWrap
                    anchors.fill: parent
                    anchors.margins: 3
                    font.pixelSize: Qt.application.font.pixelSize * 1.5
                    text: qsTr("server response would be here")
                }
            }
        }

        Page {
            id: page2
            width: 600
            height: 400

            header: Label {
                text: qsTr("Settings")
                font.pixelSize: Qt.application.font.pixelSize * 2
                padding: 10
            }

            Rectangle {
                id: recSockPath
                border.width: 1
                border.color: "black"
                height: parent.height * 0.085
                width: parent.width * 0.7
                anchors.centerIn: parent
                TextInput
                {
                    id: textInputSocketPath
                    objectName: "SocketPath"
                    anchors.fill: parent
                    anchors.margins: 4
                    font.pixelSize: parent.height * 0.6
                    text: qsTr("/tmp/relay_socket")
                }
            }
            Text
            {
                anchors.bottom: recSockPath.top
                anchors.left: recSockPath.left
                anchors.bottomMargin: 10
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                text: 'UNIX domain socket path:'
            }
        }
    }

    signal qmlSignalConnect(msg: string)
    signal qmlSignalDisconnect(msg: string)
    signal qmlSignalSend(msg: string)



    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Control")
        }
        TabButton {
            text: qsTr("Settings")
        }
    }
}
