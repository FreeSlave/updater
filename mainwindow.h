#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "downloadtimecalculator.h"

#include <QMainWindow>
#include <QRegularExpression>
#include <QSettings>
#include <QNetworkConfigurationManager>
#include <QThread>

#include <memory>

namespace Ui {
class MainWindow;
}

class DownloadWorker;
class NewsFetcher;
class CurrentVersionFetcher;
class QLabel;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread thread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setDownloadSpeed(int speed);
    void setUploadSpeed(int speed);
    void setTotalSize(int size);
    void setCompletedSize(int size);
    void onDownloadEvent(int event);
    void toggleDownload(void);
    void onCurrentVersion(QString version);
    bool close(void);

private slots:
    void startUpdate(void);
    void openSettings(void);
    void onNewsLoaded(QStringList news);
    void startGame(void);

private:
    QString sizeToString(int size);
    QString timeToString(int time);
    void stopAria(void);

    Ui::MainWindow *ui;
    DownloadWorker *worker;
    DownloadTimeCalculator downloadTime;
    QSettings settings;
    std::unique_ptr<QLabel> textBrowser;
    std::unique_ptr<NewsFetcher> newsFetcher;
    std::unique_ptr<CurrentVersionFetcher> currentVersionFetcher;
    int totalSize;
    bool paused;
    QRegularExpression commandRegex;
    QNetworkConfigurationManager networkManager;
    QString currentVersion;
};

#endif // MAINWINDOW_H
