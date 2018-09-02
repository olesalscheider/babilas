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

struct Message {
    QDateTime stamp;
    QString from;
    QString to;
    QString body;
};

class Conversation : public QAbstractListModel {
    Q_OBJECT

public:
    enum ContactRoles {
        BodyRole = Qt::UserRole + 1,
    };

    Conversation(QObject *parent = nullptr) : QAbstractListModel(parent) {
    }

    int rowCount(const QModelIndex & = QModelIndex()) const {
        return m_messages.count();
    }

    QVariant data(const QModelIndex &index, int role) const {
        switch (role) {
        case BodyRole:
            return m_messages[index.row()].body;
        default:
            qCCritical(DebugCategories::general) << "Unknown conversation role " << role;
            return QVariant();
        }
    }

    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[BodyRole] = "body";
        return roles;
    }

    void addMessage(const QXmppMessage &qxmppMessage)
    {
        if (!qxmppMessage.body().isEmpty()) {
            qxmppMessage.body();
            Message message;
            message.body = qxmppMessage.body();
            message.stamp = qxmppMessage.stamp();
            message.from = qxmppMessage.from();
            message.to = qxmppMessage.to();

            beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count());
            m_messages.append(message);
            endInsertRows();
        }
    }

private:
    QList<Message> m_messages;
};

#endif // CONVERSATION_HH
