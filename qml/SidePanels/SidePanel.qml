/* $Id: SidePanel.qml
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

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import "../CustomComponents"

Popup {
    id: sidePanel
    property bool isExpanded: false
    property bool isPined: rFileSystem.IsPinPinned
    property int normalizedWidth: 35
    property int widthWhenExpanded: 200

    padding: 0
    width: parent.width
    height: parent.height - 1
    closePolicy: Popup.NoAutoClose
    //clip: true

    background: Rectangle{
        opacity: 0.5
        color: Qt.darker(rFileSystem.BackgroundColor2)
    }

    ButtonGroup{id: radioGroup}

    Rectangle{
        id: sidePanelParentRect
        width: parent.width
        height: parent.height
        color: "transparent"

        Column{
            id: sidePanelParentLayout
            anchors.fill: parent
            anchors.leftMargin: 10
            //anchors.rightMargin: 1
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            spacing: 2
            clip: true

            Rectangle{
                id: controlBar
                width: parent.width
                height: normalizedWidth
                color: "transparent"

                RImageButton{
                    id: hamburgerBtn
                    width: normalizedWidth
                    height: normalizedWidth
                    icon.source: "/local/assets/menu.svg"
                    icon.color: rFileSystem.IconColor1
                    onClicked: (!isPined && isExpanded) ? reverseExpandMenu() : expandMenu()
                }

                RImageButton{
                    id: pinBtn
                    width: normalizedWidth*0.5
                    height: width
                    visible: isExpanded
                    anchors.right: parent.right
                    icon.source: isPined ? "/local/assets/pin.png" : "/local/assets/unpin.svg"
                    icon.color: rFileSystem.IconColor1
                    onClicked: rFileSystem.IsPinPinned = !isPined
                }
            }

            ScrollView{
                id: sidePanelParentFlickable
                width: parent.width
                height: parent.height - controlBar.height
                //contentWidth: sidePanelChildLayout.width
                //contentHeight: sidePanelChildLayout.height
                ScrollBar.horizontal: ScrollBar{
                    policy: ScrollBar.AlwaysOff
                }

                ScrollBar.vertical: ScrollBar{
                    policy: ScrollBar.AsNeeded
                }

                clip: true

                Column{
                    id: sidePanelChildLayout
                    width: sidePanelParentRect.width
                    height: (rFileSystem.DiskDataListCount + 14)*(normalizedWidth + 2)
                    spacing: 2

                    RImageExpandingButton{
                        id: homeBar
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-home"
                        text: "Home"
                        onClicked: updateCurrentDirectory("home")
                        ButtonGroup.group: radioGroup
                        checked: true
                    }

                    RImageExpandingButton{
                        id: documentsBar
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-documents"
                        text: "Documents"
                        onClicked: updateCurrentDirectory("Documents")
                        ButtonGroup.group: radioGroup
                    }

                    RImageExpandingButton{
                        id: downloadsBar
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-downloads"
                        text: "Downloads"
                        onClicked: updateCurrentDirectory("Downloads")
                        ButtonGroup.group: radioGroup
                    }

                    RImageExpandingButton{
                        id: musicBar
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-music"
                        text: "Musics"
                        onClicked: updateCurrentDirectory("Music")
                    }

                    RImageExpandingButton{
                        id: videoBar
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-video"
                        text: "Videos"
                        onClicked: updateCurrentDirectory("Videos")
                        ButtonGroup.group: radioGroup
                    }

                    RImageExpandingButton{
                        id: pictureBar
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-pictures"
                        text: "Pictures"
                        onClicked: updateCurrentDirectory("Pictures")
                        ButtonGroup.group: radioGroup
                    }

                    RImageExpandingButton{
                        id: dropboxBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/dropbox"
                        text: "Dropbox"
                        onClicked: {
                            var index = rFileSystem.doesTabExist("Dropbox")
                            if(index === -1)
                                rFileSystem.createNewTab("cloud://dropbox")
                            else{
                                tabHeader.currentIndex = index
                                mainTabControl.currentIndex = index
                            }
                        }
                        ButtonGroup.group: radioGroup
                    }

                    RImageExpandingButton{
                        id: onedriveBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/skydrive"//"/local/assets/onedrive.svg"
                        text: "OneDrive"
                        onClicked: rFileSystem.createNewTab("cloud://onedrive")
                        ButtonGroup.group: radioGroup
                    }

                    RImageExpandingButton{
                        id: gdriveBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/google-drive"//"/local/assets/google-drive.svg"
                        text: "Google Drive"
                        onClicked: rFileSystem.createNewTab("cloud://google-drive")
                        ButtonGroup.group: radioGroup
                    }

                    Rectangle{
                        //id: separator
                        color: rFileSystem.BackgroundColor2
                        opacity: 0.1
                        height: 1
                        width: parent.width
                    }

                    ListView{
                        id: diskListView
                        width: parent.width
                        height: count*normalizedWidth
                        spacing: 2
                        clip: true
                        interactive: false
                        model: rFileSystem.DiskDataList

                        delegate: Rectangle{
                            id: diskListViewDelegate
                            width: parent.width
                            height: normalizedWidth
                            color: "transparent"

                            RProgressBar {
                                id: progress
                                opacity: 0.4
                                width: parent.width - 2
                                height: parent.height
                                visible: (width - height > 1)
                                value: 1 - model.modelData.UsedVolumeSize/model.modelData.TotalVolumeSize
                                from: 0
                                to: 1
                            }
                            RImageExpandingButton{
                                width: parent.width
                                height: normalizedWidth
                                icon.source: "image://xdg/drive-harddisk"
                                text: "<b>" + model.modelData.DisplayName + "</b> (" + model.modelData.DevName + ")"
                                onClicked: {
                                    updateCurrentDirectory(model.modelData.MountPoint)
                                    mainTabControl.forceActiveFocus()
                                }
                                ButtonGroup.group: radioGroup
                            }
                        }
                    }

                    Rectangle{
                        //id: separator
                        color: rFileSystem.BackgroundColor2
                        opacity: 0.1
                        height: 1
                        width: parent.width
                    }

                    RImageExpandingButton{
                        id: bookmarksBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-favorites"
                        text: "Bookmarks"
                        hoverText: "Your Bookmarks"
                        checked: bookmarkPanel.isOpened

                        BookmarkPanel{
                            id: bookmarkPanel
                            x: sidePanel.width
                            widthWhenExpanded: sidePanel.width*1.5
                            contentHeight: mainWindow.height - 35
                        }
                        onClicked: {
                            bookmarkPanel.isOpened ? bookmarkPanel.close() : bookmarkPanel.open()
                            bookmarkPanel.isOpened = !bookmarkPanel.isOpened
                        }
                    }
                    RImageExpandingButton{
                        id: recentsBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/folder-activities"
                        text: "Recents"
                        hoverText: "Your Recently Visited Places"
                        checked: recentsPanel.isOpened

                        RecentsPanel{
                            id: recentsPanel
                            x: sidePanel.width
                            widthWhenExpanded: sidePanel.width*1.5
                            contentHeight: mainWindow.height - 35
                        }
                        onClicked: {
                            recentsPanel.isOpened ? recentsPanel.close() : recentsPanel.open()
                            recentsPanel.isOpened = !recentsPanel.isOpened
                        }
                    }
                    RImageExpandingButton{
                        id: trashBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/user-trash"
                        text: "Trash"
                        checked: trashPanel.isOpened

                        TrashPanel{
                            id: trashPanel
                            x: sidePanel.width
                            widthWhenExpanded: sidePanel.width*1.5
                            contentHeight: mainWindow.height - 35
                        }

                        onClicked: {
                            trashPanel.isOpened ? trashPanel.close() : trashPanel.open()
                            trashPanel.isOpened = !trashPanel.isOpened
                        }
                    }

                    Rectangle{
                        //id: separator
                        color: rFileSystem.BackgroundColor2
                        opacity: 0.1
                        height: 1
                        width: parent.width
                    }

                    RImageExpandingButton{
                        id: processBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/cs-startup-programs"//"/local/assets/process.svg"
                        //icon.color: rFileSystem.IconColor1
                        text: "Processes"
                        hoverText: "File Operations you perform"
                        checked: indicatorPanel.isOpened

                        IndicatorPanel{
                            id: indicatorPanel
                            x: sidePanel.width
                            widthWhenExpanded: sidePanel.width*1.5
                            contentHeight: mainWindow.height - 35
                        }
                        onClicked: {
                            indicatorPanel.isOpened ? indicatorPanel.close() : indicatorPanel.open()
                            indicatorPanel.isOpened = !indicatorPanel.isOpened
                        }
                    }

                    RImageExpandingButton{
                        id: settingsBtn
                        width: parent.width
                        height: normalizedWidth
                        icon.source: "image://xdg/applications-system"//"/local/assets/settings.svg"
                        //icon.color: rFileSystem.IconColor1
                        text: "Global Settings"
                        hoverText: "Customize your File Manager"
                        checked: settingsPanel.isOpened

                        SettingsPanel{
                            id: settingsPanel
                            x: sidePanel.width
                            widthWhenExpanded: sidePanel.width*1.5//mainWindow.width*0.35
                            contentHeight: mainWindow.height - 35
                        }
                        onClicked: {
                            settingsPanel.isOpened ? settingsPanel.close() : settingsPanel.open()
                            settingsPanel.isOpened = !settingsPanel.isOpened
                        }
                    }
                }
            }
        }

        Rectangle{
            id: separator
            color: rFileSystem.BackgroundColor2
            opacity: 0.1
            height: parent.height
            width: 1
            anchors.right: parent.right
        }
    }

    PropertyAnimation{
        id: expandAnimation
        target: sidePanel
        property: "width"
        to: widthWhenExpanded
        duration: rFileSystem.GlobalAnimationDuration
    }

    PropertyAnimation{
        id: reverseExpandAnimation
        target: sidePanel
        property: "width"
        to: normalizedWidth + 10
        duration: rFileSystem.GlobalAnimationDuration
    }

    Component.onCompleted: sidePanel.open()

    function expandMenu(){
        if(!isExpanded){
            isExpanded = true
            expandAnimation.start()
        }
        if(isPined)
            sideBar.width = widthWhenExpanded
    }

    function reverseExpandMenu(){
        if(isExpanded){
            isExpanded = false
            reverseExpandAnimation.start()
            sideBar.width = normalizedWidth + 10
        }
    }

    function updateCurrentDirectory(Path){
        var currentItem = tabHeader.currentItem
        console.log(currentItem.qtModelIndex)
        rFileSystem.updateCurrentDirectoryOnCurrentView(Path, currentItem.qtModelIndex)
        if(!isPined)
            reverseExpandMenu()
    }


    onIsPinedChanged: {
        widthWhenExpanded = 200
        isPined ? expandMenu() : reverseExpandMenu()
    }
}
