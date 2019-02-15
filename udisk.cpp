#include "udisk.h"
#include "uDisk.h"
#include <QApplication>
#include <QDebug>
//uDisk::uDisk()
//{

//}

char uDisk::FirstDriveFromMask(ULONG unitmask)
{
    char i;
    for (i = 0; i < 26; ++i) {
        if (unitmask & 0x1) {
            break;
        }
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}
bool uDisk::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType == WM_DEVICECHANGE) {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME) {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags ==0) {
                    QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    emit sigUDiskCome(USBDisk);
                }
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME) {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags == 0) {
                    emit sigUDiskRemove();
                }
            }
            break;
        case DBT_DEVNODES_CHANGED:
            break;
        default:
            break;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}
