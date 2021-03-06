/* $Id: diskinfomodel.cpp
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

#include "diskinfomodel.h"

DiskInfoModel::DiskInfoModel(QObject *parent)
    :QObject(parent){}

DiskInfoModel::DiskInfoModel(const QString &DisplayName,const QString &DevName, const QString &MountPoint,const QString &FileSystem, QObject *parent)
    :QObject(parent), m_DisplayName(DisplayName), m_DevName(DevName), m_MountPoint(MountPoint), m_FileSystem(FileSystem)
    {}

void DiskInfoModel::GenerateExtras(){

    //QString temp = m_TotalVolumeSize.left(m_TotalVolumeSize.size() - 6);
    //double total = temp.toDouble();
    //temp = m_UsedVolumeSize.left(m_UsedVolumeSize.size() - 6);
    //double used = temp.toDouble();

    if(totalVolumeSize != 0.0){
        double ratio = 1 - usedVolumeSize/totalVolumeSize;
        if(ratio == 0.0){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/100.png";
        }
        else if(ratio<=0.05){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/95.png";
        }
        else if(ratio<=0.1){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/90.png";
        }
        else if(ratio<=0.15){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/85.png";
        }
        else if(ratio<=0.2){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/80.png";
        }
        else if(ratio<=0.25){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/75.png";
        }
        else if(ratio<=0.3){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/70.png";
        }
        else if(ratio<=0.35){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/65.png";
        }
        else if(ratio<=0.4){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/60.png";
        }
        else if(ratio<=0.45){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/55.png";
        }
        else if(ratio<=0.5){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/50.png";
        }
        else if(ratio<=0.55){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/45.png";
        }
        else if(ratio<=0.6){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/40.png";
        }
        else if(ratio<=0.65){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/35.png";
        }
        else if(ratio<=0.7){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/30.png";
        }
        else if(ratio<=0.75){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/25.png";
        }
        else if(ratio<=0.8){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/20.png";
        }
        else if(ratio<=0.85){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/15.png";
        }
        else if(ratio<=0.9){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/10.png";
        }
        else if(ratio<=0.95){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/05.png";
        }
        else if(ratio>0.95){
            t_icon = "/DiskView/Assets/Resources/DiskViewAssets/00.png";
        }
    }
    else{
        t_icon = "/DiskView/Assets/Resources/DiskViewAssets/00.png";
    }

    emit IconPathChanged();

    if(usedVolumeSize < 1024)
        diskUsageAnalysis = QString::number(usedVolumeSize, 'f', 1) + " MB ";
    else if(usedVolumeSize < 1048576)
        diskUsageAnalysis = QString::number((usedVolumeSize)/1024, 'f', 1) + " GB ";

    diskUsageAnalysis += "free of ";

    if(totalVolumeSize < 1024)
        diskUsageAnalysis += QString::number(totalVolumeSize, 'f', 1) + " MB";
    else if(totalVolumeSize < 1048576)
        diskUsageAnalysis += QString::number(totalVolumeSize/1024, 'f', 1) + " GB";
}
