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

RowLayout {
    Layout.fillHeight: false
    Image {
        source: root.visibleContact.photo
        Layout.preferredWidth: 4 * Kirigami.Units.gridUnit
        Layout.preferredHeight: 4 * Kirigami.Units.gridUnit
        fillMode: Image.PreserveAspectFit
    }
    ColumnLayout {
        Label {
            text: root.visibleContact.name
        }
        Label {
            text: "<" + root.visibleContact.jid + ">"
        }
    }
}
