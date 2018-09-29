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

import Qt.labs.platform 1.0 as Qp

Kirigami.ApplicationWindow {
    id: root

    property var visibleContact

    ContactList {
        id: contactList
    }

    Chat {
        id: chat
    }

    AccountList {
        id: accountList
    }

    About {
        id: about
    }

    pageStack.initialPage: [contactList, chat]

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Account settings…")
                onTriggered: { accountList.visible = true }
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Quit")
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                onTriggered: { about.visible = true }
            }
        }
    }

    Qp.SystemTrayIcon {
        id: systray
        visible: true
        iconSource: "qrc:/images/babilas.png"

        onActivated: {
            if (!root.visible) {
                root.show()
                root.raise()
                root.requestActivate()
            } else {
                root.hide()
            }
        }

        menu: Qp.Menu {
            visible: false
            Qp.MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }
}
