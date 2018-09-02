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

import Qt.labs.platform 1.0 as Qp

ApplicationWindow {
    id: root
    visible: true

    property var visibleContact

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

    AccountList {
        id: accountList
    }

    About {
        id: about
    }

    width: mainLayout.implicitWidth
    height: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout
        anchors.fill: parent

        ContactList {
            id: contactList
            visible: true
            Layout.preferredWidth: 300
            Layout.fillHeight: true
        }

        ColumnLayout {
            Chat {
                id: chat
                visible: true
                Layout.preferredWidth: 500
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            ChatInput {
                visible: true
            }
        }
    }

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
                onTriggered: {about.visible = true }
            }
        }
    }
}
