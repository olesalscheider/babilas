/*
 * Copyright 2018, Niels Ole Salscheider
 *
 * This file is part of Babilas.
 *
 * Babilas is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Babilas is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Babilas. If not, see <https://www.gnu.org/licenses/>.
 */

import QtQuick 2.10
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.3

Item {
    Layout.fillWidth: true
    Layout.preferredHeight: Math.max(buttons.Layout.preferredHeight, textArea.Layout.preferredHeight) + 2 * contentLayout.spacing
    Layout.minimumHeight: Math.max(buttons.Layout.preferredHeight, textArea.Layout.preferredHeight) + 2 * contentLayout.spacing

    RowLayout {
        id: contentLayout
        anchors.fill: parent

        TextArea {
            id: textArea

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: contentHeight

            placeholderText: qsTr("Enter text…")
            wrapMode: TextEdit.Wrap

            Keys.onPressed: {
                if (event.key === Qt.Key_Return) {
                    if (!(event.modifiers & Qt.ShiftModifier)) {
                        sendButton.clicked()
                        event.accepted = true;
                    }
                }
            }
        }

        Item {
            id: buttons

            Layout.fillHeight: true
            Layout.preferredWidth: childrenRect.width
            Layout.minimumWidth: childrenRect.width
            Layout.preferredHeight: childrenRect.height
            Layout.minimumHeight: childrenRect.height

            ColumnLayout {
                Item {
                    // spacer item
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                Button {
                    text: qsTr("Emoji 😀")
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    onClicked: popup.open()
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    onClicked: {
                        root.visibleContact.sendMessage(textArea.text)
                        textArea.text = ""
                    }
                }
            }
        }
    }


    Popup {
        id: popup
        parent: contentLayout
        x: textArea.x
        y: textArea.y - 2 * textArea.height
        width: textArea.width
        height: 3 * textArea.height
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    }
}
