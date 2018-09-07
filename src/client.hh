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
#include <QXmppCarbonManager.h>
#include <QXmppClient.h>
#include <QXmppDiscoveryManager.h>
#include <QXmppMamManager.h>
#include <QXmppMessage.h>
#include <QXmppTransferManager.h>
#include <QXmppVCardIq.h>

//#include "contactlistmodel.hh"
#include "contact.hh"

class Client : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> contactList READ contactList NOTIFY contactListChanged)

public:
    Client(QXmppConfiguration &configuration, QObject *parent = nullptr);

    QList<QObject *> contactList() const;

    void sendMessage(const QString &jid, const QString &message);

signals:
    void contactListChanged();

private:
    Contact &getContactRef(const QString &jid);
    void rebuildContactList();
    QString clientType() const;

    void onLogMessage(QXmppLogger::MessageType type, const QString &text) const;
    void onConnected();
    void onError(QXmppClient::Error error);

    void onMessageReceived(const QXmppMessage &message);
    void onRosterReceived();
    void onRosterPresenceChanged(const QString &bareJid, const QString &resource);
    void onRosterItemAdded(const QString &bareJid);
    void onRosterItemChanged(const QString &bareJid);
    void onRosterItemRemoved(const QString &bareJid);
    void onRosterSubscriptionReceived(const QString &bareJid);
    void onVCardReceived(const QXmppVCardIq &vcard);
    void onClientVCardReceived();
    void onDiscoveryInfoReceived(const QXmppDiscoveryIq &iq);
    void onDiscoveryItemsReceived(const QXmppDiscoveryIq &iq);
    void onArchiveMessageReceived(const QString &id, const QXmppMessage &message);
    void onArchiveResultsReceived(const QString &id, const QXmppResultSetReply &resultSetReply, bool complete);

    QXmppClient m_qxmppClient;
    QXmppCarbonManager *m_carbonManager;
    QXmppMamManager *m_mamManager;
    QXmppTransferManager *m_transferManager;
    QXmppDiscoveryManager *m_discoveryManager;

    bool m_mamAvailable;

    QMap<QString, QObject *> m_contactMap;
    QStringList m_serverEntities;
};

#endif // CLIENT_HH
