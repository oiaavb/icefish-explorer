/* $Id: rfilesystemmodel.h
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

#ifndef RFILESYSTEMMODEL_H
#define RFILESYSTEMMODEL_H

#include <QObject>
#include <QDir>
#include <QThread>
#include <QFile>
#include <QSettings>

#include "models/notification/notificationmodel.h"

#include "fileStructures/startpagehandler.h"

#include "models/cloudAccountViewer/dropboxviewer.h"
#include "models/cloudAccountViewer/onedriveviewer.h"
#include "models/cloudAccountViewer/googledriveviewer.h"

#include "multimediaProviders/photoViewer/rphotomodel.h"
#include "multimediaProviders/videoPlayer/rvideomodel.h"

class RFileSystemModel : public QObject
{
    Q_OBJECT
    /* allows accessing tabHeadersBar, having name of current opened directory
     * this list is also responsible for allowing switching to other tabs
     * connected with each tab to allow changing to new name when the current directory in tab changes
     */
    Q_PROPERTY(QList<QObject*> TabHeaderList READ TabHeaderList NOTIFY TabHeaderListChanged)


    Q_PROPERTY(StartPageHandler* StartPageHandle READ StartPageHandle NOTIFY StartPageHandleChanged)

    Q_PROPERTY(RPhotoModel* PhotoViewProvider READ PhotoViewProvider NOTIFY PhotoViewProviderChanged)

    Q_PROPERTY(RVideoModel* VideoViewProvider READ VideoViewProvider NOTIFY VideoViewProviderChanged)

    /* Provides error/warning data to NotificationPanel
     * connected with each tab via "Notfiy" slot in the NotificationModel class
     * "Notify" will also cause the N*Panel to show up in global view
     */
    Q_PROPERTY(NotificationModel* NModel READ NModel NOTIFY NModelChanged)

    // Provides access to currently mounted partitions list and info
    Q_PROPERTY(QList<QObject*> DiskDataList READ DiskDataList NOTIFY DiskDataListChanged)

    // Provides access to bookmark list, updates everytime the bookmark btn on SidePanel is clicked
    Q_PROPERTY(QList<QObject*> BookmarkDataList READ BookmarkDataList NOTIFY BookmarkDataListChanged)

    // Provides access to recently opened files and directories
    Q_PROPERTY(QList<QObject*> RecentsList READ RecentsList NOTIFY RecentsListChanged)
    // 5 mostly accessed Paths from RecentsList
    Q_PROPERTY(QList<QObject*> MostVisitedPlacesList READ MostVisitedPlacesList NOTIFY MostVisitedPlacesListChanged)

    Q_PROPERTY(QList<QObject*> TrashList READ TrashList NOTIFY TrashListChanged)

    /* Provides index position of AppTheme namely "Light, Dark, ..."
     * 'BackgroundColor' and 'IconColor' are associated with the current theme changed from settings
     * Defaults to Light theme if nothing is found, like started for the first time
     */
    Q_PROPERTY(int AppTheme READ AppTheme WRITE setAppTheme NOTIFY AppThemeChanged)
    Q_PROPERTY(QString BackgroundColor1 READ BackgroundColor1 WRITE setBackgroundColor1 NOTIFY BackgroundColor1Changed)
    Q_PROPERTY(QString BackgroundColor2 READ BackgroundColor2 WRITE setBackgroundColor2 NOTIFY BackgroundColor2Changed)
    Q_PROPERTY(QString IconColor1 READ IconColor1 WRITE setIconColor1 NOTIFY IconColor1Changed)
    Q_PROPERTY(QString IconColor2 READ IconColor2 WRITE setIconColor2 NOTIFY IconColor2Changed)
    Q_PROPERTY(QString HighlightColor READ HighlightColor WRITE setHighlightColor NOTIFY HighlightColorChanged)
    Q_PROPERTY(QString SelectedColor READ SelectedColor WRITE setSelectedColor NOTIFY SelectedColorChanged)
    Q_PROPERTY(bool IsPinPinned READ IsPinPinned WRITE setIsPinPinned NOTIFY IsPinPinnedChanged)
    /* While opening a new directory in any tab, first preference is given to these global properties and then the per directory settings are applied
     * 'Default(0)': Each directory will follow its own settings
     * 'Enabled(1)' AND 'Disabled(2)': Enforce these properties on each directory loading irrespective of the per directory values
     * Stored using qt provided QSettings class
     */
    Q_PROPERTY(int GlobalIsHiddenItemsShown READ GlobalIsHiddenItemsShown WRITE setGlobalIsHiddenItemsShown NOTIFY GlobalIsHiddenItemsShownChanged)
    Q_PROPERTY(int GlobalIsPreviewAvailable READ GlobalIsPreviewAvailable WRITE setGlobalIsPreviewAvailable NOTIFY GlobalIsPreviewAvailableChanged)
    Q_PROPERTY(int GlobalIconScale READ GlobalIconScale WRITE setGlobalIconScale NOTIFY GlobalIconScaleChanged)
    Q_PROPERTY(int GlobalAnimationDuration READ GlobalAnimationDuration WRITE setGlobalAnimationDuration NOTIFY GlobalAnimationDurationChanged)
    Q_PROPERTY(int GlobalFileFolderView READ GlobalFileFolderView WRITE setGlobalFileFolderView NOTIFY GlobalFileFolderViewChanged)

    Q_PROPERTY(DropboxViewer* DropboxViewerObj READ DropboxViewerObj NOTIFY DropboxViewerObjChanged)
    Q_PROPERTY(OneDriveViewer* OneDriveViewerObj READ OneDriveViewerObj NOTIFY OneDriveViewerObjChanged)
    Q_PROPERTY(GoogleDriveViewer* GoogleDriveViewerObj READ GoogleDriveViewerObj NOTIFY GoogleDriveViewerObjChanged)

public:
    explicit RFileSystemModel(QObject *parent = nullptr);

    //void setupDbus();

    //Q_SCRIPTABLE void ShowFolders(const QStringList& uriList, const QString& startUpId);
    //Q_SCRIPTABLE void ShowItems(const QStringList& uriList, const QString& startUpId);


    /* Handles Tab Creation/ Navigation/ Deletion stuffs
     * can be invoked from any part of QML code
     */
    //as the name suggest
    Q_INVOKABLE void createNewTab(QString Path = QDir::homePath());

    Q_INVOKABLE int doesTabExist(QString key);
    //returns pointer to lastly added new Tab and QML code links that pointer with the newly created TabUI handler
    Q_INVOKABLE QObject* getTabData();
    //NOT USED YET
    Q_INVOKABLE QObject* getTabData(int index);
    //NOT USED YET
    Q_INVOKABLE void updateCurrentDirectoryOnCurrentView(QString stdName, int activeIndex);
    //as the name suggest
    Q_INVOKABLE void deleteTab(int index);


    //following all the methods are just C++ wrappers to properties declared above using Q_Property

    QList<QObject*> TabHeaderList() const{ return tabHeaderList;}

    StartPageHandler* StartPageHandle() const{ return sph;}

    RPhotoModel* PhotoViewProvider() const{ return rvp;}

    RVideoModel* VideoViewProvider() const{ return vvp;}

    NotificationModel* NModel() const{ return nm;}

    QList<QObject*> DiskDataList() const{ return diskDataList;}

    QList<QObject*> BookmarkDataList() const{ return bookmarkDataList;}

    QList<QObject*> RecentsList() const{ return recentsList;}
    QList<QObject*> MostVisitedPlacesList() const{ return mostVisitedPlacesList;}

    QList<QObject*> TrashList() const{ return trashList;}

    int AppTheme() const;
    void setAppTheme(const int AppTheme);

    QString BackgroundColor1() const;
    void setBackgroundColor1(const QString &BackgroundColor1);

    QString BackgroundColor2() const;
    void setBackgroundColor2(const QString &BackgroundColor2);

    QString IconColor1() const;
    void setIconColor1(const QString &IconColor1);

    QString IconColor2() const;
    void setIconColor2(const QString &IconColor2);

    QString HighlightColor() const;
    void setHighlightColor(const QString &HighlightColor);

    QString SelectedColor() const;
    void setSelectedColor(const QString &SelectedColor);

    bool IsPinPinned() const;
    void setIsPinPinned(const bool IsPinPinned);

    int GlobalIsHiddenItemsShown() const;
    void setGlobalIsHiddenItemsShown(const int GlobalIsHiddenItemsShown);

    int GlobalIsPreviewAvailable() const;
    void setGlobalIsPreviewAvailable(const int GlobalIsPreviewAvailable);

    int GlobalIconScale() const;
    void setGlobalIconScale(const int GlobalIconScale);

    int GlobalAnimationDuration() const;
    void setGlobalAnimationDuration(const int GlobalAnimationDuration);

    int GlobalFileFolderView() const;
    void setGlobalFileFolderView(const int &GlobalFileFolderView);

    DropboxViewer* DropboxViewerObj() const{ return dropboxViewer;}
    OneDriveViewer* OneDriveViewerObj() const{ return oneDriveViewerObj;}
    GoogleDriveViewer* GoogleDriveViewerObj() const{ return googleDriveViewerObj;}

public slots:

    // A Threaded slot called everytime a new place is bookmarked, only does the job of calling actual Threaded BookmarkKeeper class
    void writeBookmarkAsync(QString filePath, bool addOrRemove);

    // Called everytime the BookmarkBtn on SidePanel is clicked, will refresh all the bookmarks stored
    void updateStoredBookmarkList();

    // Called everytime the RecentsBtn is clicked on SidePanel to refresh the recents list
    // Currently removal from list is not implemented
    void prepareRecentsList();
    void prepareMostVisitedPlacesList();

    void prepareTrashList(QString nameFilter = "");

signals:
    void cppTabListChanged(const QString stdName = "");
    void qmlTabChanged(const QString stdName = "");

    void NModelChanged();

    // Signals to notify BookmarkKeeper Thread to add or remove the currently bookmarked place
    void addBookmark(QString);
    void removeBookmark(QString);

    // Following all are just Notifiers to make QML code aware of the changes in C++ code
    void TabHeaderListChanged();
    void StartPageHandleChanged();
    void PhotoViewProviderChanged();
    void VideoViewProviderChanged();
    void DiskDataListChanged();
    void BookmarkDataListChanged();
    void RecentsListChanged();
    void MostVisitedPlacesListChanged();
    void TrashListChanged();

    void AppThemeChanged();
    void BackgroundColor1Changed();
    void BackgroundColor2Changed();
    void IconColor1Changed();
    void IconColor2Changed();
    void HighlightColorChanged();
    void SelectedColorChanged();
    void IsPinPinnedChanged();

    void GlobalIsHiddenItemsShownChanged();
    void GlobalIsPreviewAvailableChanged();
    void GlobalIconScaleChanged();
    void GlobalAnimationDurationChanged();
    void GlobalFileFolderViewChanged();
    void DropboxViewerObjChanged();
    void OneDriveViewerObjChanged();
    void GoogleDriveViewerObjChanged();

    // Linked with Each TabModel to allow async writing of recent events
    void writeHistoryThreaded(QString fileAccessed);

private:
    // Called once when the application starts to retrieve currently attached partitions
    // ONLY Linux implementation is present, comment it out if compiling on Windows
    void GetAttachedDiskList();

    QList<QObject*> tabHeaderList;
    QList<QObject*> tabDataList;

    QList<QObject*> diskDataList;

    QThread bookmarkKeeperThread;
    QList<QObject*> bookmarkDataList;

    QThread historyKeeperThread;
    QList<QObject*> recentsList;
    QList<QObject*> mostVisitedPlacesList;

    QList<QObject*> trashList;

    NotificationModel *nm;

    QString backgroundColor1;
    QString backgroundColor2;
    QString iconColor1;
    QString iconColor2;
    QString highlightColor;
    QString selectedColor;
    int animationDuration;
    bool isPinPinned;

    void checkCloudDriveSyncStatus();
    OneDriveViewer* oneDriveViewerObj;
    GoogleDriveViewer* googleDriveViewerObj;
    DropboxViewer *dropboxViewer;

    StartPageHandler *sph;
    RPhotoModel *rvp;
    RVideoModel *vvp;

    // Global Settings handler object
    QSettings settings;
};

#endif // RFILESYSTEMMODEL_H
