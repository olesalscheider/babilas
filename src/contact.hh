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

#ifndef CONTACT_HH
#define CONTACT_HH

#include <QObject>
#include <QString>
#include <QImage>

#include "conversation.hh"

class Client;

class Contact : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString jid READ jid)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QImage photo READ photo NOTIFY photoChanged)
    Q_PROPERTY(Conversation * conversation READ conversation)

public:
    Contact(const QString &jid, Client *parent);
    QString jid() const;

    QString name() const;
    void setName(const QString &name);

    QImage photo() const;
    void photoFromData(const QByteArray &data);

    Conversation * conversation() const;
    Q_INVOKABLE void sendMessage(const QString &message);

signals:
    void jidChanged();
    void nameChanged();
    void photoChanged();

private:
    Client *m_client;
    Conversation *m_conversation;
    QString m_jid;
    QString m_name;
    QImage m_photo;
};

#endif // CONTACT_HH
