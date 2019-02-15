#ifndef SRCPREVIEW_H
#define SRCPREVIEW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <udisk.h>
#include <QFileInfoList>
enum EffectType
{
    NONE = 0,
    RANDOM,
    LEFTTORIGHT,
    RIGHTTOLEFT,
    TOPTOBOTTOM,
    BOTTOMTOTOP,
    MIDTOSIDE,
    SIDETOMID
};
class SrcPreview : public QWidget
{
    Q_OBJECT
public:
    explicit SrcPreview(QWidget *parent = nullptr);
    void init();
    void DisplayPhotoAndInfo(QString srcPathName);
    void DisplayPhoto(QImage* img);
    void initUI();
    void initParam();
    QString currentFilePath;
    EffectType currentEffect;
    unsigned int fileTotalNum = 0;
    unsigned int currentDisplayNum = 0;
    QImage* currentImage = NULL;

    QString srcPath;
    QStringList srcPathList;
signals:

public slots:
    void JumpPhotoClicked();
    void EffectChanged(int effecttype);
    void TranClicked();
private:
    QLabel* board;
    QLabel* lbFileName;
    QComboBox* cbEffect;
    QPushButton* btLeftTrans;
    QPushButton* btRightTrans;
    QPushButton* btNext;
    QPushButton* btPre;
};

#endif // SRCPREVIEW_H
