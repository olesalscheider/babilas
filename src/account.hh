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

#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <QObject>
#include <QUuid>

#include <QXmppConfiguration.h>

#include "client.hh"

class Account : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString jid READ jid WRITE setJid NOTIFY jidChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString resource READ resource WRITE setResource NOTIFY resourceChanged)
    Q_PROPERTY(QObject * client READ client NOTIFY clientChanged)

public:
    Account(QUuid uuid, QObject *parent = nullptr);
    ~Account();

    void deleteAccount();

    QString jid() const;
    void setJid(QString jid);

    QString password() const;
    void setPassword(QString password);

    QString resource() const;
    void setResource(QString resource);

    QObject * client() const;

signals:
    void jidChanged();
    void passwordChanged();
    void resourceChanged();
    void clientChanged();

private:
    QUuid m_uuid;
    QString m_uuidString;
    QXmppConfiguration m_configuration;
    Client* m_client;
    bool m_deleteAccount;
};

#endif // ACCOUNT_HH
