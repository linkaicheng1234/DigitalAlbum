#ifndef UDISK_H
#define UDISK_H

#include <QWidget>
#include <windows.h>
#include <QAbstractNativeEventFilter>
#include <dbt.h>
class uDisk : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT
signals:
    void sigUDiskCome(QString uDiskName);
    void sigUDiskRemove();
protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
    char FirstDriveFromMask(ULONG unitmask);
};

#endif // UDISK_H
