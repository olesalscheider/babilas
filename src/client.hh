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

#ifndef CLIENT_HH
#define CLIENT_HH

#include <memory>

#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>
#include <QXmppVCardIq.h>

#include "contactlistmodel.hh"

class Client : public QObject {
    Q_OBJECT

    Q_PROPERTY(QObject * contactList READ contactList NOTIFY contactListChanged)

public:
    Client(QXmppConfiguration &configuration, QObject *parent = nullptr);

    QObject * contactList() const;

    void sendMessage(QString &jid, QString &message);

signals:
    void contactListChanged();

private:
    void onLogMessage(QXmppLogger::MessageType type, const QString &text) const;

    void onMessageReceived(const QXmppMessage &message);
    void onRosterReceived();
    void onRosterPresenceChanged(const QString &bareJid, const QString &resource);
    void onRosterItemAdded(const QString &bareJid);
    void onRosterItemChanged(const QString &bareJid);
    void onRosterItemRemoved(const QString &bareJid);
    void onRosterSubscriptionReceived(const QString &bareJid);
    void onVCardReceived(const QXmppVCardIq &vcard);

    QXmppClient m_qxmppClient;

    ContactListModel *m_contactList;
};

#endif // CLIENT_HH
