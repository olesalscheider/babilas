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
import QtQuick.XmlListModel 2.0

GridView {
    XmlListModel {
        id: emojimodel
        source: "emojis.xml"
        query: "/collection/category/emojis/emoji"

        XmlRole { name: "character"; query: "character/string()" }
        XmlRole { name: "description"; query: "desc/string()" }
    }

    model: emojimodel
    delegate: Button {
        text: character //"<font size='6'>" + modelData + "</font>"
        hoverEnabled: true
        ToolTip.text: description
        ToolTip.visible: hovered
    }
}
