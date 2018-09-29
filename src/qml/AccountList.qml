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

import org.kde.kirigami 2.4 as Kirigami


Dialog {
    title: qsTr("Account settings")
    standardButtons: Dialog.Close
    modal: true
    visible: accountmanager.accounts.length === 0
    width: 0.75 * parent.width
    height: 0.75 * parent.height
    x: 0.125 * parent.width
    y: 0.125 * parent.height


    StackView {
        id: stackview
        width: parent.width
        height: parent.height

        initialItem: mainPage

        AccountDetails {
            id: accountdetails
            visible: false
        }

        Item {
            id: mainPage
            ScrollView {
                anchors.fill: parent
                ListView {
                    anchors.fill: parent
                    model: accountmanager.accounts
                    delegate: Kirigami.BasicListItem {
                        label: modelData.jid
                        reserveSpaceForIcon: false
                        onClicked: {
                            stackview.push(accountdetails)
                            accountdetails.accountIdx = index
                            accountdetails.visible = true
                        }
                    }
                    footer: Kirigami.BasicListItem {
                        label: qsTr("New account…")
                        reserveSpaceForIcon: false
                        onClicked: {
                            accountmanager.newAccount()
                            stackview.push(accountdetails)
                            accountdetails.accountIdx = accountmanager.accounts.length - 1
                            accountdetails.visible = true
                        }
                    }
                }
            }
        }
    }
}
