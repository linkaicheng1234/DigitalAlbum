#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "udisk.h"
#include <QFileInfoList>
#include <QListView>
#include <QFileSystemModel>
#include <QTranslator>
#include <QMessageBox>
#include <QTextEdit>
#include <QFileInfo>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QListWidget>
#include "viewitem.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static MainWindow* instance(QWidget *parent=0);
    ~MainWindow();

    void ReadPhotoSrc(QString path);
    void updateScrollWidget();
    void AreaAddItem(int num,ViewItem* item);
    QString workPath;
    QString srcPath;
    uDisk* m_uDisk;
    unsigned int fileTotalNum=0;
    QList<ViewItem*> itemList;
public slots:
    void uDiskCome(QString uDiskName);
    void uDiskRemove();
    void OpenClicked();
    void selectItem(ViewItem*);
private:
    MainWindow(QWidget *parent = 0);
    static MainWindow *pMainWindow;
    Ui::MainWindow *ui;
    QTranslator translator;
    QMessageBox* messBox;

    int row=0,col=0;
    QLabel* lbDiskName;
    QListWidgetItem *pItem;
    QListWidget* listWidget;
    QLabel* lbFileName;
    QLabel* lbFileSize;
    QLabel* lbFileType;
    QLabel* lbFileHeightWidth;
    QPushButton* btOpen;
    QFileInfoList srcInfoList;
    QStringList srcPathList;

    void initUI();
};

#endif // MAINWINDOW_H
