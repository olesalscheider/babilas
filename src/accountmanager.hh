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

#ifndef ACCOUNTMANAGER_HH
#define ACCOUNTMANAGER_HH

#include "account.hh"

#include <QList>
#include <QSettings>

class AccountManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> accounts READ accounts NOTIFY accountsChanged)

public:
    AccountManager(QObject *parent = nullptr);

    QList<QObject *> accounts() const;

    Q_INVOKABLE void newAccount();
    Q_INVOKABLE void deleteAccount(int idx);

signals:
    void accountsChanged();

private:
    QList<QObject *> m_accountList;
};

#endif // ACCOUNTMANAGER_HH
