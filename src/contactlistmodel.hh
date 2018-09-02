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

#ifndef CONTACTLISTMODEL_HH
#define CONTACTLISTMODEL_HH

#include <QAbstractItemModel>
#include <QImage>

#include "constants.hh"

class ContactListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum ContactRoles {
        JidRole = Qt::UserRole + 1,
        NameRole,
        PhotoRole,
        ConversationRole,
    };

    struct Contact {
        Contact() {
            photo.load(":/images/default_contact_photo.png");
        }
        QString jid;
        QString name;
        QStringList resources;
        QImage photo;
    };

    ContactListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {
        m_conversations.append("Hihihi");
    }

    int rowCount(const QModelIndex & = QModelIndex()) const {
        return m_jids.count();
    }

    QVariant data(const QModelIndex &index, int role) const {
        auto jid = m_jids[index.row()];
        switch (role) {
        case JidRole:
            return jid;
        case NameRole:
            return m_contactDetails[jid].name;
        case PhotoRole:
            return m_contactDetails[jid].photo;
        case ConversationRole:
            return m_conversations;
        default:
            qCCritical(DebugCategories::general) << "Unknown contact role " << role;
            return QVariant();
        }
    }

    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[JidRole] = "jid";
        roles[NameRole] = "name";
        roles[PhotoRole] = "photo";
        roles[ConversationRole] = "conversation";
        return roles;
    }

    void ensureJid(const QString &jid) {
        if (!m_jids.contains(jid)) {
            beginInsertRows(QModelIndex(), m_jids.count(), m_jids.count());
            m_jids.append(jid);
            m_contactDetails[jid].jid = jid;
            m_contactDetails[jid].name = jid;
            endInsertRows();
        }
    }

    void setName(const QString &jid, const QString &name) {
        m_contactDetails[jid].name = name;
        QModelIndex idx = createIndex(m_jids.indexOf(jid), 0);
        emit dataChanged(idx, idx);
    }

    void setPhoto(const QString &jid, const QByteArray &data) {
        if (!m_contactDetails[jid].photo.loadFromData(data)) {
             m_contactDetails[jid].photo.load(":/images/default_contact_photo.png");
        }
        QModelIndex idx = createIndex(m_jids.indexOf(jid), 0);
        emit dataChanged(idx, idx);
    }

private:
    QMap<QString, Contact> m_contactDetails;
    QStringList m_jids;
    QStringList m_conversations;
};

#endif // CONTACTLISTMODEL_HH
