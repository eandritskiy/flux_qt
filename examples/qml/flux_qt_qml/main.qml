import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.3

import Flux 1.0

Window {
    id: root

    visible: true

    width: 640
    height: 480

    maximumWidth: width
    maximumHeight: height

    Item {
        visible: !MainStore.uploadStatus

        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }

        width: textField.width + button.width + button.anchors.leftMargin
        height: textField.height

        TextField {
            id: textField

            readOnly: true
            selectByMouse: true

            placeholderText: "Select a file to upload"
            text: MainStore.selectedFilename
        }

        Button {
            id: button

            anchors {
                verticalCenter: textField.verticalCenter
                left: textField.right
                leftMargin: 10
            }

            text: MainStore.selectedFilename ? "Upload" : "Select"

            onPressed: MainStore.selectedFilename ? ActionProvider.uploadFtp(MainStore.selectedFilename) :
                                                    ActionProvider.showFileDialog(true)

        }
    }

    Text {
        id: uploadStatus

        visible: MainStore.uploadStatus

        anchors {
            centerIn: parent
        }

        text: MainStore.uploadStatus
    }

    Component {
        id: fileDialogComponent

        FileDialog {
            id: fileDialog

            visible: true

            title: "Please select a file"
            folder: shortcuts.home

            onAccepted: {
                ActionProvider.selectFile(fileDialog.fileUrls);
            }

            onRejected: {
                ActionProvider.showFileDialog(false);
            }
        }
    }

    Loader {
        id: fileDialogLoader

        sourceComponent: MainStore.showFileDialog ? fileDialogComponent : undefined
    }
}
