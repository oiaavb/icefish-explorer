/* $Id: notificationmodel.h
 * IceFish Explorer is a free File Manager for Linux Desktops for managing
 * local files as well as files on cloud, Dropbox, Onedrive, Googledrive.
 * Additionally, it also serves as a multimedia explorer for your photos,
 * music, videos, documents and other files by providing built-in plugins
 * to open them.
 * © IceFish Community, 2019
 *
 * This file is part of IceFish Explorer.
 *
 * IceFish Explorer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * IceFish Explorer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with IceFish Explorer.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * The project is hosted here,
 * http://www.icefish.tech/index/explorer/0-5
*/

#ifndef NOTIFICATIONMODEL_H
#define NOTIFICATIONMODEL_H

#include <QObject>


enum class Error{
    StackLeak,
    FileAlreadyExist,
    PathDoesntExist,
    NoPermission,
    RemovalFailed,
    Unknown
};

class NotificationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Comment READ Comment NOTIFY CommentChanged)
    Q_PROPERTY(QString Header READ Header NOTIFY HeaderChanged)

public:
    explicit NotificationModel(QObject *parent = nullptr);

    QString Comment() const{ return comment;}
    QString Header() const{ return header;}

signals:
    void CommentChanged();
    void HeaderChanged();

    void showNotification();

public slots:
    void Notify(Error);

private:
    QString comment, header;
};

#endif // NOTIFICATIONMODEL_H
