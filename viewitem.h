#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QEvent>
class ViewItem: public QFrame
{
    Q_OBJECT
public:
    ViewItem(QFrame *parent = 0);
    void setName(QString name);
    void initParams(QString name,QString filePath);
    QString getName();
    QString getFilePath();
    ViewItem* instance;
signals:
    void select(ViewItem* item);
private slots:
protected:
    void mousePressEvent(QMouseEvent *event);
   // void leaveEvent(QEvent  *event);
    void focusOutEvent(QFocusEvent *e);
private:
    QLabel* labelPic;
    QLabel* labelName;
    QString filePath;
    QString fileName;
};

#endif // VIEWITEM_H
