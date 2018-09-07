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

#include "account.hh"

#include "constants.hh"

#include <QSettings>

Account::Account(QUuid uuid, QObject *parent) : QObject(parent), m_uuid(uuid), m_deleteAccount(false)
{
    m_uuidString = m_uuid.toString().replace("{", "").replace("}", "");

    /* Try to load settings */
    QSettings settings(Constants::organizationName, Constants::applicationName);
    auto groupName = QStringLiteral("accounts/") + m_uuidString;
    auto defaultResource = Constants::applicationName + QLatin1String("-") + m_uuidString;

    settings.beginGroup(groupName);
    m_configuration.setJid(settings.value(QLatin1String("jid")).toString());
    m_configuration.setPassword(settings.value(QLatin1String("password")).toString());
    m_configuration.setResource(settings.value(QLatin1String("resource"), defaultResource).toString());
    settings.endGroup();

    m_client = new Client(m_configuration, this);
}

Account::~Account()
{
    /* Store the settings */
    QSettings settings(Constants::organizationName, Constants::applicationName);
    auto groupName = QStringLiteral("accounts/") + m_uuidString;
    settings.beginGroup(groupName);
    if (m_deleteAccount) {
        settings.remove("");
    } else {
        settings.setValue(QLatin1String("jid"), m_configuration.jidBare());
        settings.setValue(QLatin1String("password"), m_configuration.password());
        settings.setValue(QLatin1String("resource"), m_configuration.resource());
    }
    settings.endGroup();
}

void Account::deleteAccount()
{
    m_deleteAccount = true;
}

QString Account::jid() const
{
    return m_configuration.jidBare();
}

void Account::setJid(QString jid)
{
    m_configuration.setJid(jid);
    emit jidChanged();
}

QString Account::password() const
{
    return m_configuration.password();
}

void Account::setPassword(QString password)
{
    m_configuration.setPassword(password);
    emit passwordChanged();
}

QString Account::resource() const
{
    return m_configuration.resource();
}

void Account::setResource(QString resource)
{
    m_configuration.setResource(resource);
    emit resourceChanged();
}

QObject *Account::client() const
{
    return m_client;
}
