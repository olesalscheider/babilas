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
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1

Item {
    property string messageBody
    property string messageFrom
    property date messageStamp
    property bool messageOutgoing

    height: childrenRect.height + 10
    width: parent.width

    Rectangle {
        color: outgoing ? "#ddddff" : "#ddffdd"
        width: parent.width - 50
        height: childrenRect.height
        anchors.left: outgoing ? null : parent.left
        anchors.right: outgoing ? parent.right : null
        anchors.top: parent.top
        anchors.margins: 10
        radius: 5
        ColumnLayout {
            anchors.centerIn: parent
            width: parent.width - 10
            RowLayout {
                width: parent.width
                Text {
                    text: messageFrom
                    font.pointSize: 8
                    color: "#444444"
                }
                Item {
                    Layout.fillWidth: true
                }
                Text {
                    text: "✔✔⏳"
                    font.pointSize: 8
                }
                Text {
                    text: stamp.toLocaleTimeString()
                    font.pointSize: 8
                    color: "#444444"
                }
            }
            Text {
                text: messageBody
            }
        }
    }
}
