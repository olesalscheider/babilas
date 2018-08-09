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

Dialog {
    title: qsTr("About Babilas")
    standardButtons: Dialog.Close
    modal: true

    width: 0.75 * parent.width
    height: 0.75 * parent.height
    x: 0.125 * parent.width
    y: 0.125 * parent.height

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        spacing: 10

        Image {
            source: "qrc:/images/babilas.png"
        }

        ColumnLayout {
            spacing: 2

            Text {
                text: qsTr("Babilas is an XMPP client.")
            }

            Text {
                text: qsTr("Homepage: <a href=\"https://www.babilas.org\">https://www.babilas.org</a>")
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }
}
