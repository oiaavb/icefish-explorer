/* $Id: operation.cpp
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

#include "operation.h"

Operation::Operation(){}

QString Operation::getTimeRequired(qint64 timeInNanoSec){

    int timeInSeconds = static_cast<int>(timeInNanoSec/1000000000);
    if(timeInSeconds < 60)
        return QString::number(timeInSeconds) + " Seconds";
    else if(timeInSeconds < 60*60){
        int minute = timeInSeconds/60;
        int second = timeInSeconds%60;
        return QString::number(minute) + " Minutes and " + QString::number(second) + " Seconds";
    }
    else if(timeInSeconds < 60*60*24){
        int hour = timeInSeconds/3600;
        timeInSeconds = timeInSeconds%3600;
        int minute = timeInSeconds/60;
        int second = timeInSeconds%60;
        return QString::number(hour) + " Hours, " + QString::number(minute) + " Minutes and " + QString::number(second) + " Seconds";
    }
    else if(timeInSeconds < 60*60*24*7){
        int day = timeInSeconds/(3600*24);
        timeInSeconds = timeInSeconds%(3600*24);
        int hour = timeInSeconds/3600;
        timeInSeconds = timeInSeconds%3600;
        int minute = timeInSeconds/60;
        int second = timeInSeconds%60;
        return QString::number(day) + " Days, " + QString::number(hour) + " Hours, " + QString::number(minute) + " Minutes and " + QString::number(second) + " Seconds";
    }
    else if(timeInSeconds < 60*60*24*30){
        int week = timeInSeconds/(3600*24*7);
        timeInSeconds = timeInSeconds%(3600*24*7);
        int day = timeInSeconds/(3600*24);
        timeInSeconds = timeInSeconds%(3600*24);
        int hour = timeInSeconds/3600;
        timeInSeconds = timeInSeconds%3600;
        int minute = timeInSeconds/60;
        int second = timeInSeconds%60;
        return QString::number(week) + " Weeks, " + QString::number(day) + " Days, " + QString::number(hour) + " Hours, " + QString::number(minute) + " Minutes and " + QString::number(second) + " Seconds";
    }
    else if(timeInSeconds < 60*60*24*30*12){
        int month = timeInSeconds/(3600*24*30);
        timeInSeconds = timeInSeconds%(3600*24*30);
        int day = timeInSeconds/(3600*24);
        timeInSeconds = timeInSeconds%(3600*24);
        int hour = timeInSeconds/3600;
        timeInSeconds = timeInSeconds%3600;
        int minute = timeInSeconds/60;
        int second = timeInSeconds%60;
        return QString::number(month) + " Months, " + QString::number(day) + " Days, " + QString::number(hour) + " Hours, " + QString::number(minute) + " Minutes and " + QString::number(second) + " Seconds";
    }
    else if(timeInSeconds > 60*60*24*30*12){
        int year = timeInSeconds/(3600*24*30*12);
        timeInSeconds = timeInSeconds%(3600*24*30);
        int month = timeInSeconds/(3600*24*30);
        timeInSeconds = timeInSeconds%(3600*24*30);
        int day = timeInSeconds/(3600*24);
        timeInSeconds = timeInSeconds%(3600*24);
        int hour = timeInSeconds/3600;
        timeInSeconds = timeInSeconds%3600;
        int minute = timeInSeconds/60;
        int second = timeInSeconds%60;
        return QString::number(year) + " Years, " + QString::number(month) + " Months, " + QString::number(day) + " Days, " + QString::number(hour) + " Hours, " + QString::number(minute) + " Minutes and " + QString::number(second) + " Seconds";
    }
    else
        return "Unkown time";
}


qint64 Operation::getTheOverallFileSize(QFileInfo file){
    if(file.exists()){
        qint64 finalSize = 0;
        if(file.isFile()){
            fileCount++;
            finalSize += file.size();
        }
        else if(file.isDir()){
            dirCount++;
            QDir dir(file.absoluteFilePath());
            QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
            foreach (QFileInfo anotherFile, fileList) {
                qint64 whetherDirNotExist = getTheOverallFileSize(anotherFile);
                if(whetherDirNotExist >= 0)
                    finalSize += whetherDirNotExist;
            }
            finalSize += 4096;
        }
        else
            finalSize = 0;
        return finalSize;
    }
    else
        return -1;
}

QString Operation::getFormattedFileSize(qint64 fileSize){
    if(fileSize < 1024)
        return QString::number(fileSize, 'f', 2) + " Bytes";
    else if(fileSize < 1024*1024)
        return QString::number(fileSize/1024, 'f', 2) + " KBytes";
    else if(fileSize < 1024*1024*1024)
        return QString::number(fileSize/(1024*1024), 'f', 2) + " MBytes";
    else if(fileSize > 1024*1024*1024)
        return QString::number(fileSize/(1024*1024*1024), 'f', 2) + " GBytes";
    else
        return " Unknown";
}


void Operation::saveTransferStates(QString opType){
    QFile file(QDir::homePath() + "/.config/" + QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + "-operations.conf");

    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    if(file.open(QIODevice::Append)){
        QTextStream stream(&file);
        stream << "{OpType: " + opType;
        stream << ";Origin: ";
        foreach(QUrl url, fileList)
            stream << url.path() + ",";

        stream << ";Destinition: " + destinitionPath;
        stream << ";FinishedAt: " + QDateTime::currentDateTime().toString("dd/MM/yy hh:mm");
        stream << ";ElapsedTime: " + QString::number(static_cast<int>(elaspedTime.nsecsElapsed()/1000000000));
        stream << ";}\n";
        file.close();
    }
}
