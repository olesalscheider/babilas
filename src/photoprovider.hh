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

#ifndef PHOTOPROVIDER_HH
#define PHOTOPROVIDER_HH

#include <QQuickImageProvider>
#include <memory>

class PhotoProvider : public QQuickImageProvider
{
public:
    static PhotoProvider *instance();
    static QString prefix();
    static QString imageUrl(QString &id);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    void addImage(QString &id, QImage &image);
    void removeImage(QString &id);

private:
    PhotoProvider();

    static PhotoProvider *m_instance;
    QMap<QString, QImage> m_images;
};

#endif // PHOTOPROVIDER_HH
