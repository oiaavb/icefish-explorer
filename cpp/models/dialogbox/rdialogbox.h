#ifndef RDIALOGBOX_H
#define RDIALOGBOX_H

#include <QObject>
#include <QDir>
#include <QSettings>

class RDialogBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(QString fileURL READ fileURL WRITE setFileURL NOTIFY fileURLChanged)
    Q_PROPERTY(QString homePath READ homePath NOTIFY homePathChanged)
    Q_PROPERTY(QList<QObject*> DirectoryList READ DirectoryList NOTIFY DirectoryListChanged)

    Q_PROPERTY(bool backNavBtnEnabled READ backNavBtnEnabled NOTIFY backNavBtnEnabledChanged)
    Q_PROPERTY(bool forNavBtnEnabled READ forNavBtnEnabled NOTIFY forNavBtnEnabledChanged)

    Q_PROPERTY(QString BackgroundColor READ BackgroundColor NOTIFY BackgroundColorChanged)
    Q_PROPERTY(QString IconColor READ IconColor NOTIFY IconColorChanged)
    Q_PROPERTY(QString HighlightColor READ HighlightColor NOTIFY HighlightColorChanged)
    Q_PROPERTY(int AnimationDuration READ AnimationDuration NOTIFY AnimationDurationChanged)

public:
    explicit RDialogBox(QObject *parent = nullptr);

    QString header() const{ return t_header;}
    void setHeader(const QString &Header){ t_header = Header;}

    QString currentPath() const{ return t_currentPath;}
    void setCurrentPath(const QString &currentPath){ t_currentPath = currentPath;}

    QString fileURL() const{ return t_fileURL;}
    void setFileURL(const QString &FileURL){ t_fileURL = FileURL;}

    QString homePath() const{ return QDir::homePath();}

    QList<QObject*> DirectoryList() const{ return directoryList;}

    bool backNavBtnEnabled() const{ return t_backNavBtnEnabled;}
    bool forNavBtnEnabled() const{ return t_forNavBtnEnabled;}


    QString BackgroundColor() const{ return settings.value("global/backgroundColor").toString();}
    QString IconColor() const{ return settings.value("global/iconColor").toString();}
    QString HighlightColor() const{ return settings.value("global/highlightColor").toString();}
    int AnimationDuration() const{ return settings.value("global/animationDuration").toInt();}

public slots:
    void updateDirectory(QString Path);
    void navigateBackward();
    void navigateForward();

signals:
    void headerChanged();
    void currentPathChanged();
    void fileURLChanged();
    void homePathChanged();
    void DirectoryListChanged();

    void backNavBtnEnabledChanged();
    void forNavBtnEnabledChanged();

    void BackgroundColorChanged();
    void IconColorChanged();
    void HighlightColorChanged();
    void AnimationDurationChanged();

private:
    bool WithFile;
    QString t_header;
    QString t_currentPath;
    QString t_fileURL;
    QList<QObject*> directoryList;

    //used for tracking navigation
    QList<QObject*> navigationHistoryInfoList;
    int pointerToCurrentDirectoryInNavigationHistoryInfoList;
    bool t_backNavBtnEnabled;
    bool t_forNavBtnEnabled;

    QSettings settings;
};

#endif // RDIALOGBOX_H