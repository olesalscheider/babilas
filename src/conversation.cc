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

#include "conversation.hh"

#include <QXmppUtils.h>

#include "contact.hh"

Conversation::Conversation(Contact *contact)
    : QAbstractListModel(contact), m_contact(contact)
{
}

int Conversation::rowCount(const QModelIndex &) const
{
    return m_messages.count();
}

QVariant Conversation::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case BodyRole:
        return m_messages[index.row()].body;
    case StampRole:
        return m_messages[index.row()].stamp;
    case OutgoingRole:
        return m_contact->jid() == m_messages[index.row()].to;
    case FromJidRole:
        return QXmppUtils::jidToBareJid(m_messages[index.row()].from);
    default:
        qCCritical(DebugCategories::general) << "Unknown conversation role " << role;
        return QVariant();
    }
}

QHash<int, QByteArray> Conversation::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BodyRole] = "body";
    roles[StampRole] = "stamp";
    roles[OutgoingRole] = "outgoing";
    roles[FromJidRole] = "fromJid";
    return roles;
}

void Conversation::addMessage(const QXmppMessage &qxmppMessage)
{
    if (!qxmppMessage.body().isEmpty()) {
        qxmppMessage.body();
        Message message;
        message.body = qxmppMessage.body();
        message.stamp = qxmppMessage.stamp();
        if (!message.stamp.isValid()) {
            message.stamp = QDateTime::currentDateTime();
        }
        message.from = qxmppMessage.from();
        message.to = qxmppMessage.to();

        beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count());
        m_messages.append(message);
        endInsertRows();
    }
}
