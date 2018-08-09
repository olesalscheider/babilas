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

#include "accountmanager.hh"

#include "constants.hh"

#include <QUuid>

AccountManager::AccountManager(QObject *parent)
    : QObject(parent)
{
    m_contactListModel = new ContactListModel(this);

    QSettings settings(Constants::organizationName, Constants::applicationName);
    settings.beginGroup(QLatin1String("accounts"));
    for (auto &accountName : settings.childGroups()) {
        m_accountList.push_back(new Account(QUuid::fromString(accountName), this));
    }
    settings.endGroup();
    emit accountsChanged();
}

QList<QObject *> AccountManager::accounts() const
{
    return m_accountList;
}

QObject * AccountManager::contacts() const
{
    return m_contactListModel;
}

void AccountManager::newAccount()
{
    m_accountList.push_back(new Account(QUuid::createUuid(), this));
    emit accountsChanged();
}

void AccountManager::deleteAccount(int idx)
{
    static_cast<Account *>(m_accountList[idx])->deleteAccount();
    m_accountList.removeAt(idx);
    emit accountsChanged();
}
