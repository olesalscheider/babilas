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

#include "client.hh"

#include <QApplication>
#include <QDBusInterface>
#include <QUuid>
#include <QXmppVersionManager.h>
#include <QXmppRosterManager.h>
#include <QXmppVCardManager.h>
#include <QXmppUtils.h>

#include "constants.hh"
#include "conversation.hh"

Client::Client(QXmppConfiguration &configuration, QObject *parent)
    : QObject(parent), m_mamAvailable(false)
{
    m_qxmppClient.versionManager().setClientName(qAppName());
    m_qxmppClient.versionManager().setClientVersion(babilas_VERSION_STRING);
    m_qxmppClient.versionManager().setClientOs(QSysInfo::prettyProductName());

    QXmppLogger *logger = new QXmppLogger();
    logger->setLoggingType(QXmppLogger::SignalLogging);
    logger->setMessageTypes(QXmppLogger::AnyMessage);
    connect(logger, &QXmppLogger::message, this, &Client::onLogMessage);
    m_qxmppClient.setLogger(logger);

    connect(&m_qxmppClient, &QXmppClient::connected, this, &Client::onConnected);
    connect(&m_qxmppClient, &QXmppClient::error, this, &Client::onError);
    connect(&m_qxmppClient, &QXmppClient::messageReceived, this, &Client::onMessageReceived);

    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::rosterReceived, this, &Client::onRosterReceived);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::presenceChanged, this, &Client::onRosterPresenceChanged);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::itemAdded, this, &Client::onRosterItemAdded);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::itemChanged, this, &Client::onRosterItemChanged);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::itemRemoved, this, &Client::onRosterItemRemoved);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::subscriptionReceived, this, &Client::onRosterSubscriptionReceived);

    connect(&m_qxmppClient.vCardManager(), &QXmppVCardManager::vCardReceived, this, &Client::onVCardReceived);
    connect(&m_qxmppClient.vCardManager(), &QXmppVCardManager::clientVCardReceived, this, &Client::onClientVCardReceived);

    m_carbonManager = new QXmppCarbonManager;
    m_qxmppClient.addExtension(m_carbonManager);
    connect(m_carbonManager, &QXmppCarbonManager::messageReceived, this, &Client::onMessageReceived);
    connect(m_carbonManager, &QXmppCarbonManager::messageSent, this, &Client::onMessageReceived);

    m_mamManager = new QXmppMamManager;
    m_qxmppClient.addExtension(m_mamManager);
    connect(m_mamManager, &QXmppMamManager::archivedMessageReceived, this, &Client::onArchiveMessageReceived);
    connect(m_mamManager, &QXmppMamManager::resultsRecieved, this, &Client::onArchiveResultsReceived);

    m_discoveryManager = m_qxmppClient.findExtension<QXmppDiscoveryManager>();
    m_discoveryManager->setClientType(clientType());
    connect(m_discoveryManager, &QXmppDiscoveryManager::infoReceived, this, &Client::onDiscoveryInfoReceived);
    connect(m_discoveryManager, &QXmppDiscoveryManager::itemsReceived, this, &Client::onDiscoveryItemsReceived);

    m_transferManager = new QXmppTransferManager;
    m_qxmppClient.addExtension(m_transferManager);
    // TODO connect signals etc.

    m_qxmppClient.connectToServer(configuration);
}

Contact& Client::getContactRef(const QString &jid)
{
    auto bareJid = QXmppUtils::jidToBareJid(jid);
    if (!m_contactMap.contains(bareJid)) {
        m_contactMap.insert(bareJid, new Contact(bareJid, this));
        emit contactListChanged();
    }
    return *static_cast<Contact *>(m_contactMap[bareJid]);
}

QList<QObject *> Client::contactList() const
{
    return m_contactMap.values();
}

QString Client::clientType() const
{
    /* Try to set the device type. For now, we will try to query the hostnamed
     * dbus interface and assume "pc" if that fails. It would be great if
     * QSysInfo would provide this functionality. */
    QString clientType = QLatin1String("pc");
    QDBusInterface hostnameInterface(QStringLiteral("org.freedesktop.hostname1"),
                                     QStringLiteral("/org/freedesktop/hostname1"),
                                     QStringLiteral("org.freedesktop.hostname1"),
                                     QDBusConnection::systemBus());
    QVariant chassisReply = hostnameInterface.property("Chassis");
    if (chassisReply.isValid()) {
        auto chassisType = chassisReply.toString();
        /* This is the best mapping that I can think of... */
        if (chassisType == QLatin1String("tablet")) {
            clientType = QStringLiteral("handheld");
        } else if (chassisType == QLatin1String("handset")) {
            clientType = QStringLiteral("phone");
        }
    }

    return clientType;
}

void Client::onConnected()
{
    //TODO use m_qxmppClient->clientPresence();
    m_qxmppClient->clientPresence();
    m_qxmppClient.vCardManager().requestClientVCard();

    auto serverDomain = m_qxmppClient.configuration().domain();
    m_discoveryManager->requestInfo(serverDomain);
    m_serverEntities.clear();
    m_serverEntities.push_back(serverDomain);
    m_discoveryManager->requestItems(serverDomain);
}

void Client::onError(QXmppClient::Error error)
{
    //TODO
    if (error == QXmppClient::SocketError || error == QXmppClient::KeepAliveError) {
        //TODO
    } else if (error == QXmppClient::XmppStreamError) {
        QXmppStanza::Error::Condition xmppStreamError = m_qxmppClient.xmppStreamError();
        if (xmppStreamError == QXmppStanza::Error::NotAuthorized) {
            //TODO
        } else {
            //TODO
        }
    } else {
        qCCritical(DebugCategories::general) << "Unknown qxmpp error";
    }
}

void Client::onDiscoveryInfoReceived(const QXmppDiscoveryIq &iq)
{
    for (auto &identity : iq.identities()) {
#if 0
        if (identity.category() == QLatin1String("client")) {
            m_contactsFeatures[iq.from()] = iq.features();
            m_clientTypes[iq.from()] = identity.type();
        } else 
#endif
        if (identity.category() == QLatin1String("proxy")) {
            if (identity.type() == QLatin1String("bytestreams") && m_serverEntities.contains(iq.from())) {
                qCDebug(DebugCategories::general) << "Found proxy with JID" << iq.from();
                m_transferManager->setProxy(iq.from());
            }
        }
    }

    bool carbonFeaturesAvailable = true;
    for (auto &carbonFeature : m_carbonManager->discoveryFeatures()) {
        if (!iq.features().contains(carbonFeature)) {
            carbonFeaturesAvailable = false;
            break;
        }
    }
    if (carbonFeaturesAvailable) {
        m_carbonManager->setCarbonsEnabled(true);
    }

    bool mamFeaturesAvailable = true;
    for (auto &mamFeature : m_mamManager->discoveryFeatures()) {
        if (!iq.features().contains(mamFeature)) {
            mamFeaturesAvailable = false;
            break;
        }
    }
    m_mamAvailable = mamFeaturesAvailable;
}

void Client::onDiscoveryItemsReceived(const QXmppDiscoveryIq &iq)
{
    for (auto &item : iq.items()) {
        if (m_serverEntities.contains(iq.from())) {
            m_serverEntities.push_back(item.jid());
            m_discoveryManager->requestInfo(item.jid(), item.node());
        }
    }
}

void Client::onLogMessage(QXmppLogger::MessageType type, const QString &text) const
{
    switch(type) {
    case QXmppLogger::ReceivedMessage:
    case QXmppLogger::SentMessage:
        qCDebug(DebugCategories::qxmppStanza) << text;
        break;
    case QXmppLogger::InformationMessage:
        qCInfo(DebugCategories::qxmppGeneric) << text;
        break;
    case QXmppLogger::WarningMessage:
        qCCritical(DebugCategories::qxmppGeneric) << text;
        break;
    default:
        qCDebug(DebugCategories::qxmppGeneric) << text;
    }
}

void Client::onMessageReceived(const QXmppMessage &message)
{
    /* Send receipt and markers */
    if (message.isReceiptRequested() || message.isMarkable()) {
        QXmppMessage outMessage;
        if (message.isMarkable()) {
            outMessage.setMarker(QXmppMessage::Received);
            outMessage.setMarkerId(message.id());
        }
        if (message.isReceiptRequested()) { 
            outMessage.setReceiptId(message.receiptId());
        }
        outMessage.setStamp(QDateTime::currentDateTimeUtc());
        outMessage.setId(QUuid::createUuid().toString().replace("{", "").replace("}", ""));
        outMessage.setTo(message.from());
        outMessage.setFrom(m_qxmppClient.configuration().jid());
        outMessage.setThread(message.thread());
        m_qxmppClient.sendPacket(outMessage);
    }

    // TODO: Handle markers for displayed Messages (XEP-0333) and all incoming markers and receipts

    auto &contact = getContactRef(message.from());
    static_cast<Conversation *>(contact.conversation())->addMessage(message);
}

void Client::sendMessage(const QString &jid, const QString &message)
{
    QXmppMessage outMessage;
    outMessage.setStamp(QDateTime::currentDateTimeUtc());
    outMessage.setId(QUuid::createUuid().toString().replace("{", "").replace("}", ""));
    outMessage.setTo(jid);
    outMessage.setFrom(m_qxmppClient.configuration().jid());
    // outMessage.setReceiptRequested(true); // TODO only request this if the other party supports it
    // outMessage.setMarkable(true); // TODO only request this if the other party supports it
    outMessage.setBody(message);
    m_qxmppClient.sendPacket(outMessage);

    auto &contact = getContactRef(jid);
    static_cast<Conversation *>(contact.conversation())->addMessage(outMessage);
}

void Client::onRosterReceived()
{
    for (auto jid : m_qxmppClient.rosterManager().getRosterBareJids()) {
        getContactRef(jid);
        auto rosterEntry = m_qxmppClient.rosterManager().getRosterEntry(jid);
        auto contactPresences = m_qxmppClient.rosterManager().getAllPresencesForBareJid(jid);
        m_qxmppClient.vCardManager().requestVCard(jid);
        //TODO
    }
}

void Client::onVCardReceived(const QXmppVCardIq &vcard)
{
    auto jid = QXmppUtils::jidToBareJid(vcard.from());
    auto &contact = getContactRef(jid);
    contact.photoFromData(vcard.photo());
}

void Client::onClientVCardReceived()
{
    //TODO
}

void Client::onRosterPresenceChanged(const QString &bareJid, const QString &resource)
{
    //TODO
}

void Client::onRosterItemAdded(const QString &bareJid)
{
    getContactRef(bareJid);
    auto rosterEntry = m_qxmppClient.rosterManager().getRosterEntry(bareJid);
    //TODO
}

void Client::onRosterItemChanged(const QString &bareJid)
{
    getContactRef(bareJid);
    auto rosterEntry = m_qxmppClient.rosterManager().getRosterEntry(bareJid);
    //TODO
}

void Client::onRosterItemRemoved(const QString &bareJid)
{
    //TODO
}

void Client::onRosterSubscriptionReceived(const QString &bareJid)
{
    //TODO
}

void Client::onArchiveMessageReceived(const QString &id, const QXmppMessage &message)
{
    // TODO: Implement MAM v2 and stanza-id in QXMPP
    // TODO: Try to associate by stanza-id, then by MAM ID, then by time + content
    // onMessageReceived(message);
}

void Client::onArchiveResultsReceived(const QString &id, const QXmppResultSetReply &resultSetReply, bool complete)
{
    QXmppResultSetQuery query;
    query.setAfter(resultSetReply.last());
    if (!complete) {
        // TODO Take the first parameters from running request list using the id
        m_mamManager->retrieveArchivedMessages(QString(), QString(), QStringLiteral("test@salscheider-online.de"), QDateTime(), QDateTime(), query);
    } else {
        // TODO remove request from running request list
    }
}

// TODO: File transfer and VoIP
