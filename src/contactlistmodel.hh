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

class ContactListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum ContactRoles {
        JidRole = Qt::UserRole + 1,
    };

    ContactListModel(QObject *parent = nullptr) : QAbstractListModel(parent) { }
    int rowCount(const QModelIndex &parent = QModelIndex()) const { return 3; }
    QVariant data(const QModelIndex &index, int role) const { return QString("mark@test.de"); }

    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[JidRole] = "jid";
        return roles;
    }
};

#endif // CONTACTLISTMODEL_HH
