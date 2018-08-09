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

#include "constants.hh"

#include <QApplication>
#include <QXmppVersionManager.h>
#include <QXmppRosterManager.h>

Client::Client(QXmppConfiguration &configuration, QObject *parent) : QObject(parent)
{
    m_qxmppClient.versionManager().setClientName(qAppName());
    m_qxmppClient.versionManager().setClientVersion(babilas_VERSION_STRING);
    m_qxmppClient.versionManager().setClientOs(QSysInfo::prettyProductName());

    QXmppLogger *logger = new QXmppLogger();
    logger->setLoggingType(QXmppLogger::SignalLogging);
    logger->setMessageTypes(QXmppLogger::AnyMessage);
    connect(logger, &QXmppLogger::message, this, &Client::onLogMessage);
    m_qxmppClient.setLogger(logger);

    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::rosterReceived, this, &Client::onRosterReceived);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::presenceChanged, this, &Client::onRosterPresenceChanged);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::itemAdded, this, &Client::onRosterItemAdded);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::itemChanged, this, &Client::onRosterItemChanged);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::itemRemoved, this, &Client::onRosterItemRemoved);
    connect(&m_qxmppClient.rosterManager(), &QXmppRosterManager::subscriptionReceived, this, &Client::onRosterSubscriptionReceived);

    m_qxmppClient.connectToServer(configuration);
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

void Client::onRosterReceived()
{
    qCWarning(DebugCategories::general) << "Got roster!";
    for (auto jid : m_qxmppClient.rosterManager().getRosterBareJids()) {
        auto rosterEntry = m_qxmppClient.rosterManager().getRosterEntry(jid);
        auto contactPresences = m_qxmppClient.rosterManager().getAllPresencesForBareJid(jid);
    }
}

void Client::onRosterPresenceChanged(const QString &bareJid, const QString &resource)
{
}

void Client::onRosterItemAdded(const QString &bareJid)
{
}

void Client::onRosterItemChanged(const QString &bareJid)
{
}

void Client::onRosterItemRemoved(const QString &bareJid)
{
}

void Client::onRosterSubscriptionReceived(const QString &bareJid)
{
}
