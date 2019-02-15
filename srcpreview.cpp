#include "srcpreview.h"
#include <QLayout>
#include <QDebug>
#include <QDir>
#include "mainwindow.h"
SrcPreview::SrcPreview(QWidget *parent) : QWidget(parent)
{

}

void SrcPreview::init()
{
    qDebug()<<srcPath;
    initUI();
    initParam();
    DisplayPhotoAndInfo(currentFilePath);
}

void SrcPreview::DisplayPhotoAndInfo(QString srcPathName)
{
    QImage* srcImg = new QImage;
    if(!srcImg->load(srcPathName))
    {
        return;
    }
    DisplayPhoto(srcImg);

    currentDisplayNum = srcPathList.indexOf(srcPathName) + 1;
    qDebug()<<currentDisplayNum;
    QString name = srcPathName.split("/").at(srcPathName.split("/").count()-1);
    //name = name+"("+currentDisplayNum+"/"+fileTotalNum+")";
    lbFileName->setText(name);
    lbFileName->setToolTip(srcPathName);
}

void SrcPreview::DisplayPhoto(QImage *img)
{
    if(img->isNull())
        return ;
    QImage* scaledimg = new QImage;

    int Owidth=img->width(),Oheight=img->height();
    int Fwidth,Fheight;       //缩放后的图片大小
    int Mul;            //记录图片与label大小的比例，用于缩放图片
    if(Owidth/600>=Oheight/350)
        Mul=Owidth/600;
    else
        Mul=Oheight/350;
    if(0 != Mul)
    {
        Fwidth=Owidth/Mul;
        Fheight=Oheight/Mul;
    }
    else
    {
        Fwidth=Owidth;
        Fheight=Oheight;
    }
    *scaledimg=img->scaled(Fwidth,Fheight,Qt::KeepAspectRatio);
    currentImage = scaledimg;
    qDebug()<<currentImage->size();
    board->setPixmap(QPixmap::fromImage(*currentImage));
}

void SrcPreview::initUI()
{
    QSize btSize(100,20);
    cbEffect = new QComboBox;
    cbEffect->setMaximumSize(btSize);
    cbEffect->setMinimumSize(btSize);
    QStringList effectList;
    effectList<<"NONE"<<"RANDOM"<<"LEFTTORIGHT"<<"RIGHTTOLEFT"<<"TOPTOBOTTOM"<<"BOTTOMTOTOP"<<"MIDTOSIDE"<<"SIDETOMID";
    //effectList<<tr("NONE")<<tr("RANDOM")<<tr("LEFTTORIGHT") <<tr("RIGHTTOLEFT")<<tr("TOPTOBOTTOM")<<tr("BOTTOMTOTOP")<<tr("MIDTOSIDE"<<tr("SIDETOMID"));
    foreach (QString effectInfo, effectList) {
        cbEffect->addItem(effectInfo);
    }

    lbFileName = new QLabel;
    lbFileName->setMaximumSize(btSize);
    lbFileName->setMinimumSize(btSize);
    board = new QLabel;
    board->setMaximumSize(QSize(600,440));
    board->setMinimumSize(QSize(600,440));
    //board->setGeometry(100,50,600,350);

    btLeftTrans = new QPushButton;
    btLeftTrans->setText(tr("left trans"));
    btRightTrans = new QPushButton;
    btRightTrans->setText(tr("right trans"));
    QHBoxLayout* tranLay = new QHBoxLayout;
    tranLay->addWidget(btLeftTrans);
    tranLay->addWidget(btRightTrans);
    btNext = new QPushButton;
    btNext->setText(tr("next"));
    btPre = new QPushButton;
    btPre->setText(tr("prev"));

    QVBoxLayout* leftLay = new QVBoxLayout;
    //leftLay->addWidget(cbEffect);
    QVBoxLayout* midLay = new QVBoxLayout;
    midLay->addWidget(lbFileName);
    midLay->addWidget(board);
    QVBoxLayout* rightLay = new QVBoxLayout;
    rightLay->addWidget(cbEffect);
    rightLay->addLayout(tranLay);
    rightLay->addWidget(btNext);
    rightLay->addWidget(btPre);

    QHBoxLayout* centLay = new QHBoxLayout;
    centLay->addLayout(leftLay);
    centLay->addLayout(midLay);
    centLay->addLayout(rightLay);

    setLayout(centLay);

    connect(cbEffect,SIGNAL(currentIndexChanged(int)),this,SLOT(EffectChanged(int)));
    connect(btNext,SIGNAL(clicked()),this,SLOT(JumpPhotoClicked()));
    connect(btPre,SIGNAL(clicked()),this,SLOT(JumpPhotoClicked()));
    connect(btLeftTrans,SIGNAL(clicked()),this,SLOT(TranClicked()));
    connect(btRightTrans,SIGNAL(clicked()),this,SLOT(TranClicked()));

}

void SrcPreview::initParam()
{
    currentEffect = NONE;
    currentFilePath = srcPath;//srcPathList.at(0);
    currentDisplayNum = srcPathList.indexOf(currentFilePath) + 1;
    qDebug()<<currentDisplayNum<<"ss";
}

void SrcPreview::JumpPhotoClicked()
{
    QPushButton* bt = qobject_cast<QPushButton*>(sender());
    int index = currentDisplayNum-1;
    if(bt == btNext)
    {
        index++;
        if(index >= srcPathList.size())
        {
            DisplayPhotoAndInfo(srcPathList.at(0));
            return ;
        }
    }
    else if(bt == btPre)
    {
        index--;
        if(index < 0)
        {
            DisplayPhotoAndInfo(srcPathList.at(srcPathList.size()-1));
            return ;
        }
    }
    currentFilePath = srcPathList.at(index);
    DisplayPhotoAndInfo(currentFilePath);
}

void SrcPreview::EffectChanged(int effecttype)
{
    currentEffect = (EffectType)effecttype;
}

void SrcPreview::TranClicked()
{
    QPushButton* bt = qobject_cast<QPushButton*>(sender());
    if(!currentImage)
        return ;
    if(bt == btLeftTrans)
    {
        QMatrix matrix;
        matrix.rotate(-90);
        *currentImage = currentImage->transformed(matrix);
        DisplayPhoto(currentImage);
    }
    else if(bt == btRightTrans)
    {
        QMatrix matrix;
        matrix.rotate(90);
        *currentImage = currentImage->transformed(matrix);
        DisplayPhoto(currentImage);
    }
}
