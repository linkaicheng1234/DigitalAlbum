#include "viewitem.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
ViewItem::ViewItem(QFrame *parent):QFrame(parent)
{
    this->resize(100,80);
    this->setMaximumSize(100,80);

    //不能设置边框颜色
    //this->setFrameShape(QFrame::Box);

    //setStyleSheet这种边框设置父控件会影响子控件
    //this->setStyleSheet ("background-image:url(:/images/common/border.png);");

    labelPic = new QLabel;
    labelName = new QLabel;
    labelPic->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    labelName->setAlignment(Qt::AlignHCenter);

    QVBoxLayout* VLayout = new QVBoxLayout;
    VLayout->addWidget(labelPic);
    VLayout->addWidget(labelName);
    this->setLayout(VLayout);
    this->setObjectName("viewitem");
    this->setFocusPolicy(Qt::ClickFocus);
    instance = this;
}

void ViewItem::setName(QString name)
{
    labelName->setText(name);
}

void ViewItem::initParams(QString name,QString filePath)
{
    this->filePath = filePath;
    this->fileName = name;
    labelName->setText(name);
    labelName->setToolTip(name);
    QPixmap pixmap(filePath);
    QPixmap fitpixmap=pixmap.scaled(186, 46, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    labelPic->setPixmap(fitpixmap);
}

QString ViewItem::getName()
{
    return fileName;
}

QString ViewItem::getFilePath()
{
    return filePath;
}

void ViewItem::mousePressEvent(QMouseEvent *event)
{    
    this->setStyleSheet("QWidget#viewitem{border:2px solid blue;}");
    emit select(instance);
}

void ViewItem::focusOutEvent(QFocusEvent *e)
{
    this->setStyleSheet("QWidget#viewitem{border:2px solid transparent;}");
}

//void ViewItem::leaveEvent(QEvent  *event)
//{
//    qDebug()<<"out";
//    this->setStyleSheet("QWidget#viewitem{border:2px solid transparent;}");
//}

