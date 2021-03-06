/* $Id: googledrive.cpp
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

#include "googledrive.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "../../models/fileFolder/filefoldermodel.h"

GoogleDrive::GoogleDrive(RAbstractDirectoryModel *parent)
    :RAbstractDirectoryModel (parent){
    authorize();
}

void GoogleDrive::authorize(){
    oauth2 = new QOAuth2AuthorizationCodeFlow(this);
    oauth2->setClientIdentifier("597675045346-va3odvu1lcl3pavj9ofarct4rq1grgne.apps.googleusercontent.com");
    oauth2->setClientIdentifierSharedKey("_ekr0D7RVYScr2WYgAqAAj5i");
    oauth2->setAuthorizationUrl(QUrl("https://www.GoogleDrive.com/oauth2/authorize"));
    oauth2->setAccessTokenUrl(QUrl("https://api.GoogleDriveapi.com/oauth2/token"));
    connect(oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    auto replyHandler = new QOAuthHttpServerReplyHandler(2377, this);
    oauth2->setReplyHandler(replyHandler);
    connect(oauth2, &QOAuth2AuthorizationCodeFlow::granted, this, &GoogleDrive::isGranted);
    oauth2->grant();
}

void GoogleDrive::isGranted(){
    qDebug() << oauth2->token();
    updateCurrentDirectory("");
}

void GoogleDrive::updateCurrentDirectory(QString newDirectoryToSwitchTo){
    fileFolderList.clear();
    QVariantMap parameters;
    parameters.insert("path", newDirectoryToSwitchTo);
    //parameters.insert("recursive", false);
    parameters.insert("include_deleted", false);
    parameters.insert("include_has_explicit_shared_members", false);
    parameters.insert("include_mounted_folders", true);

    QUrl query("https://api.GoogleDriveapi.com/2/files/list_folder");

    oauth2->setContentType(QAbstractOAuth::ContentType::Json);
    connect(oauth2, &QOAuth2AuthorizationCodeFlow::finished, this, &GoogleDrive::receiveDirectoryInfo);
    oauth2->post(query, parameters);
}

void GoogleDrive::receiveDirectoryInfo(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonArr = jsonDoc.object()["entries"].toArray();

        foreach (const QJsonValue &anotherValue, jsonArr) {
            QJsonObject obj = anotherValue.toObject();

            FileFolderModel *newModel = new FileFolderModel();
            newModel->setDisplayName(obj["name"].toString());
            newModel->setPath(obj["path_display"].toString());
            newModel->setDate_Time_Modified(obj["client_modified"].toString());
            //newModel->setFileSize(obj["size"].toDouble());
            fileFolderList.append(newModel);
        }
        emit FileFolderListChanged();
        emit FileFolderListCountChanged();

        qDebug() << jsonArr;
    }
}

void GoogleDrive::updateAddressBoxShortcutMenuList(QString jumpAddress){

}

void GoogleDrive::setAddressBoxData(QString changedAddress){

}

void GoogleDrive::setWildSearchKey(const QString &WildSearchKey){

}

void GoogleDrive::navigateBackward(){

}

void GoogleDrive::navigateForward(){

}

void GoogleDrive::reloadCurrentDirectory(){

}

void GoogleDrive::deleteFile(int index){

}

bool GoogleDrive::createNewFolder(QString folderName){

}

bool GoogleDrive::createNewFile(QString fileName, QString fileType){

}

void GoogleDrive::performAction(QString filePath, QString action, QString optionalParam){

}

void GoogleDrive::copyOrCutItems(int type, QString filePath){

}
