#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
#include <QDir>
#include <QFileSystemModel>
#include <QScrollArea>
#include <QGroupBox>
#include "srcpreview.h"
MainWindow* MainWindow::pMainWindow = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,480);

    workPath = qApp->applicationDirPath();
    workPath += "/";
//    QString sheetPath = workPath + "style.qss";
//    QFile file(sheetPath);
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());
    file.close();

//    srcPath = workPath + "srcphoto/";
    //background
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/BG.png")));
    qApp->setPalette(palette);

    initUI();

    m_uDisk = new uDisk;
    qApp->installNativeEventFilter(m_uDisk);
    connect(m_uDisk, SIGNAL(sigUDiskCome(QString)), this,SLOT(uDiskCome(QString)));
    connect(m_uDisk, SIGNAL(sigUDiskRemove()), this,SLOT(uDiskRemove()));

    srcPath = workPath+"srcphoto";
    ReadPhotoSrc(srcPath);
    updateScrollWidget();
}

MainWindow *MainWindow::instance(QWidget *parent)
{
    if(!pMainWindow)
        pMainWindow = new MainWindow(parent);
    return pMainWindow;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadPhotoSrc(QString path)
{
    QDir* srcDir = new QDir(path);
    if(!srcDir->exists())
    {
        return ;
    }

    srcInfoList = srcDir->entryInfoList();
    foreach (QFileInfo srcInfo,srcInfoList)
    {
        if(srcInfo.fileName() == "." || srcInfo.fileName() == "..")
        {
            srcInfoList.removeOne(srcInfo);
            continue;
        }
        srcPathList<<srcInfo.absoluteFilePath();
        fileTotalNum++;
    }
}

/*load photo item*/
void MainWindow::updateScrollWidget()
{
    ViewItem* item;
    int num = 0;
    foreach (QFileInfo srcInfo,srcInfoList)
    {
        item = new ViewItem;
        qDebug()<<srcInfo.fileName() <<srcInfo.filePath();
        item->initParams(srcInfo.fileName(),srcInfo.filePath());
        AreaAddItem(num++,item);
        connect(item,SIGNAL(select(ViewItem*)),this,SLOT(selectItem(ViewItem*)));
    }
}

/* show photo item*/
void MainWindow::AreaAddItem(int nIndex,ViewItem *item)
{
     pItem = new QListWidgetItem;
     pItem->setSizeHint(QSize(100,80));
     listWidget->insertItem(nIndex, pItem);
     listWidget->setItemWidget(pItem,item);
     itemList<<item;
}

/*detect UDisk*/
void MainWindow::uDiskCome(QString uDiskName)
{
    lbDiskName->setText(uDiskName);
    srcPath = uDiskName;
    if(srcPath.isEmpty())
        return ;
    srcPath = uDiskName+":/srcphoto";
    qDebug()<<srcPath;
//    ReadPhotoSrc(srcPath);
//    updateScrollWidget();
}

/*remove UDisk*/
void MainWindow::uDiskRemove()
{
    lbDiskName->clear();
    itemList.clear();

//    QGridLayout* scrollLayout = qobject_cast<QGridLayout*> (scrollWidget->layout());
//    while ((child = scrollLayout->takeAt(0)) != 0)
//    {
//        //setParent为NULL，防止删除之后界面不消失
//        if(child->widget())
//        {
//            child->widget()->setParent(NULL);
//        }
//        delete child;
//    }
    QMessageBox::information(NULL, "Warnning", "remove UDisk", QMessageBox::Yes, QMessageBox::Yes);
}

void MainWindow::OpenClicked()
{
//    if(lbDiskName->text().isEmpty())
//        return ;
    SrcPreview* e = new SrcPreview;
    e->srcPath = srcPath;
    e->srcPathList = srcPathList;
    e->fileTotalNum = fileTotalNum;
    e->init();
    e->show();
}

void MainWindow::selectItem(ViewItem* item)
{
    QFileInfo* fileInfo = new QFileInfo(item->getFilePath());
    QImage* info = new QImage(item->getFilePath());
    lbFileName->setText(tr("name: ")+item->getName());
    lbFileSize->setText(tr("size: ")+QString::number(fileInfo->size()/1024.0,'f',1)+" KB");
    lbFileType->setText(tr("type: ")+fileInfo->suffix());
    lbFileHeightWidth->setText(tr("resolution: ")+QString::number(info->height())+"*"+QString::number(info->width()));
    this->statusBar()->showMessage(item->getFilePath());
    srcPath = item->getFilePath();
}

void MainWindow::initUI()
{
    QSize btSize(100,20);

    lbDiskName = new QLabel;
    lbDiskName->setMaximumSize(btSize);
    lbDiskName->setMinimumSize(btSize);

    listWidget = new QListWidget;
    listWidget->setMovement(QListView::Static);
    listWidget->setViewMode(QListView::IconMode);
    QVBoxLayout* midLay = new QVBoxLayout;
    midLay->addWidget(lbDiskName);
    midLay->addWidget(listWidget);



    lbFileName = new QLabel;
//    lbFileName->setMaximumSize(btSize);
//    lbFileName->setMinimumSize(btSize);
    lbFileSize = new QLabel;
    lbFileType = new QLabel;
    lbFileHeightWidth = new QLabel;
    btOpen = new QPushButton;
    btOpen->setText(tr("open"));
    QVBoxLayout* gbLayout = new QVBoxLayout;
    gbLayout->addWidget(lbFileName);
    gbLayout->addWidget(lbFileSize);
    gbLayout->addWidget(lbFileType);
    gbLayout->addWidget(lbFileHeightWidth);
    QGroupBox* gbFileInfo = new QGroupBox(tr("file info"));
    gbFileInfo->setMinimumSize(200, 150);
    gbFileInfo->setMaximumSize(200, 300);
    gbFileInfo->setLayout(gbLayout);
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(gbFileInfo);
    rightLayout->addWidget(btOpen);

    QHBoxLayout* centLay = new QHBoxLayout;
    centLay->addLayout(midLay);
    centLay->addLayout(rightLayout);
    QWidget* centWidget = new QWidget;
    centWidget->setLayout(centLay);
    setCentralWidget(centWidget);

    connect(btOpen,SIGNAL(clicked()),this,SLOT(OpenClicked()));
}

