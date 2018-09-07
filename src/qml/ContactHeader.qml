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

import org.kde.kirigami 2.4 as Kirigami

Item {
    width: parent.width
    height: 50 //childRect.contentHeight
    RowLayout {
        height: 50 //childRect.contentHeight
        Image {
            //image: root.visibleContact.photo
            width: 64
            height: 64
            fillMode: Image.PreserveAspectFit
        }
        Text {
            text: root.visibleContact.name
        }
        Text {
            text: "(" + root.visibleContact.jid + ")"
        }
    }
}
