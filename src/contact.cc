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

#include <QUuid>

#include "contact.hh"
#include "client.hh"
#include "photoprovider.hh"

Contact::Contact(const QString &jid, Client *parent) : QObject(parent), m_client(parent), m_jid(jid)
{
    m_conversation = new Conversation(this);
    m_name = m_jid;
}

QString Contact::jid() const
{
    return m_jid;
}

QString Contact::name() const
{
    return m_name;
}

void Contact::setName(const QString &name)
{
    if (m_name.isEmpty()) {
        m_name = m_jid;
    } else {
        m_name = name;
    }
    emit nameChanged();
}

QString Contact::photo() const
{
    if (m_photo.isEmpty()) {
        return QStringLiteral("qrc:/images/default_contact_photo.png");
    }
    return m_photo;
}

void Contact::photoFromData(const QByteArray &data)
{
    if (!m_photo.isEmpty()) {
        PhotoProvider::instance()->removeImage(m_photo);
    }
    QImage photo;
    if (!photo.loadFromData(data)) {
        m_photo = QString();
    } else {
        QString newId = QUuid::createUuid().toString().replace("{", "").replace("}", "");
        m_photo = PhotoProvider::imageUrl(newId);;
        PhotoProvider::instance()->addImage(newId, photo);
    }
    emit photoChanged();
}

void Contact::sendMessage(const QString &message)
{
    m_client->sendMessage(m_jid, message);

    // TODO: We have to take resource locking (xep-0296) into account here!
}

Conversation *Contact::conversation() const
{
    return m_conversation;
}
