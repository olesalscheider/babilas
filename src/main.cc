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

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "constants.hh"
#include "accountmanager.hh"
#include "photoprovider.hh"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setApplicationName(Constants::applicationName);
    app.setDesktopFileName(Constants::applicationName);
    app.setApplicationVersion(babilas_VERSION_STRING);
    app.setWindowIcon(QIcon(":/images/babilas.png"));

    AccountManager accountmanager;
    QQmlApplicationEngine engine;
    engine.addImageProvider(PhotoProvider::prefix(), PhotoProvider::instance());
    auto context = engine.rootContext();
    context->setContextProperty("accountmanager", &accountmanager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
