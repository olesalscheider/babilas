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
import QtQuick.XmlListModel 2.4
import org.kde.kirigami 2.4 as Kirigami

ColumnLayout {
    anchors.fill: parent

    XmlListModel {
        id: categorymodel
        source: "emojis.xml"
        query: "/collection/category"

        XmlRole { name: "categoryname"; query: "name/string()" }
        //XmlRole { name: "categoryemoji"; query: "emoji/string()" }
    }

    XmlListModel {
        id: emojimodel
        source: "emojis.xml"
        query: "/collection/category[" + (bar.currentIndex + 1) + "]/emojis/emoji"

        XmlRole { name: "character"; query: "character/string()" }
        XmlRole { name: "description"; query: "desc/string()" }
    }

//     XmlListModel {
//         id: searchmodel
//         source: "emojis.xml"
//         query: "/collection/category/emojis/emoji"
//         XmlRole { name: "character"; query: "character[contains(text(), \"" +  + "\")]"
//     }

    TabBar {
        id: bar
        Layout.fillWidth: true

        Repeater {
            model: categorymodel
            delegate: TabButton {
                text: categoryname //categoryemoji
                hoverEnabled: true
                ToolTip.text: categoryname
                ToolTip.visible: hovered
            }
        }
    }

    GridView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        cellWidth: Kirigami.Units.fontMetrics.height * 2
        cellHeight: Kirigami.Units.fontMetrics.height * 2

        model: emojimodel
        delegate: Button {
            text: "e " + character //"<font size='6'>" + modelData + "</font>"
            flat: true
            hoverEnabled: true
            ToolTip.text: description
            ToolTip.visible: hovered
        }
    }

    
}
