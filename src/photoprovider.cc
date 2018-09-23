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

#include "photoprovider.hh"

PhotoProvider *PhotoProvider::m_instance = nullptr;

PhotoProvider::PhotoProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

PhotoProvider *PhotoProvider::instance()
{
    if (!m_instance) {
        m_instance = new PhotoProvider;
    }
    return m_instance;
}

QString PhotoProvider::prefix()
{
    return QStringLiteral("photos");
}

QString PhotoProvider::imageUrl(QString &id)
{
    return QStringLiteral("image://") + prefix() + QStringLiteral("/") + id;
}


QImage PhotoProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    if (!m_images.contains(id)) {
        *size = QSize();
        return QImage();
    }

    QImage image = m_images[id];
    *size = image.size();
    if (requestedSize.isValid()) {
        return image.scaled(requestedSize);
    }
    return image;
}

void PhotoProvider::addImage(QString &id, QImage &image)
{
    m_images[id] = image;
}

void PhotoProvider::removeImage(QString &id)
{
    m_images.remove(id);
}
