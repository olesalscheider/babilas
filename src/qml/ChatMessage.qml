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
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import org.kde.kirigami 2.4 as Kirigami

Item {
    property string messageBody
    property string messageFrom
    property date messageStamp
    property bool messageOutgoing

    width: parent.width
    height: outerLayout.implicitHeight
    RowLayout {
        id: outerLayout
        anchors.fill: parent

        Item {
            Layout.preferredWidth: outgoing ? 3 * Kirigami.Units.largeSpacing : 0
        }
        Rectangle {
            color: outgoing ? "#ddddff" : "#ddffdd"
            Layout.fillWidth: true
            Layout.minimumWidth: innerLayout.implicitWidth + 0.5 * Kirigami.Units.gridUnit
            Layout.preferredHeight: innerLayout.implicitHeight + 0.5 * Kirigami.Units.gridUnit
            radius: 0.5 * Kirigami.Units.gridUnit
            ColumnLayout {
                id: innerLayout
                anchors.fill: parent
                anchors.margins: 0.25 * Kirigami.Units.gridUnit
                RowLayout {
                    Text {
                        text: messageFrom
                        font.pointSize: Kirigami.Units.fontMetrics.font.pointSize * 0.8
                        color: "#444444"
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    Text {
                        text: "✔✔⏳"
                        font.pointSize: Kirigami.Units.fontMetrics.font.pointSize * 0.8
                    }
                    Text {
                        text: stamp.toLocaleTimeString()
                        font.pointSize: Kirigami.Units.fontMetrics.font.pointSize * 0.8
                        color: "#444444"
                    }
                }
                Text {
                    text: messageBody
                }
            }
        }
        Item {
            Layout.preferredWidth: outgoing ? 0 : 3 * Kirigami.Units.largeSpacing
        }
    }
}
