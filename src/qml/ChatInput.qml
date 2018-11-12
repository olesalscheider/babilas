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

import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import org.kde.kirigami 2.4 as Kirigami

RowLayout {
    Layout.fillHeight: false

    TextArea {
        id: textArea
        Layout.fillWidth: true
        Layout.minimumHeight: buttons.height

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

        Layout.alignment: Qt.AlignBottom
        width: childrenRect.width
        height: childrenRect.height

        ColumnLayout {
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

    Popup {
        id: popup
        x: textArea.x
        y: textArea.y - 2 * textArea.height
        width: textArea.width
        height: 3 * textArea.height
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        EmojiChooser { }
    }
}
