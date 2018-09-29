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

Item {
    id: accountDetails

    property int accountIdx: -1

    ColumnLayout {
        TextField {
            placeholderText: qsTr("Jabber ID (user@server.end)")
            text: accountIdx < 0 ? "" : accountmanager.accounts[accountIdx].jid
            onEditingFinished: { accountmanager.accounts[accountIdx].jid = text; }
        }

        TextField {
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
            text: accountIdx < 0 ? "" : accountmanager.accounts[accountIdx].password
            onEditingFinished: { accountmanager.accounts[accountIdx].password = text; }
        }

        TextField {
            placeholderText: qsTr("Resource")
            text: accountIdx < 0 ? "" : accountmanager.accounts[accountIdx].resource
            onEditingFinished: { accountmanager.accounts[accountIdx].resource = text; }
        }

        Button {
            text: qsTr("Delete account")
            onClicked: {
                accountDetails.visible = false;
                var deleteIdx = accountIdx
                accountIdx = -1;
                accountmanager.deleteAccount(deleteIdx);
            }
        }

        Button {
            text: qsTr("Back…")
            onClicked: {
                accountDetails.parent.pop()
            }
        }
    }

}
