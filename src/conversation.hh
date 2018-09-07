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

#ifndef CONVERSATION_HH
#define CONVERSATION_HH

#include <QAbstractItemModel>
#include <QXmppMessage.h>

#include "constants.hh"

struct Message
{
    QDateTime stamp;
    QString from;
    QString to;
    QString body;
};

class Contact;

class Conversation : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ConversationRoles
    {
        BodyRole = Qt::UserRole + 1,
        StampRole,
        OutgoingRole,
        FromJidRole
    };

    Conversation(Contact *contact);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void addMessage(const QXmppMessage &qxmppMessage);

private:
    QList<Message> m_messages;
    Contact *m_contact;
};

#endif // CONVERSATION_HH
