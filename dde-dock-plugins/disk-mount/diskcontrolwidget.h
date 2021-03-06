/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *               2016 ~ 2018 dragondjf
 *
 * Author:     dragondjf<dingjiangfeng@deepin.com>
 *
 * Maintainer: dragondjf<dingjiangfeng@deepin.com>
 *             zccrs<zhangjide@deepin.com>
 *             Tangtong<tangtong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DISKCONTROLWIDGET_H
#define DISKCONTROLWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <dfmglobal.h>
#include <dgiomount.h>

class DDiskManager;
DFM_BEGIN_NAMESPACE
class DFMSettings;
class DFMVfsManager;
DFM_END_NAMESPACE

class DGioVolumeManager;
class DiskControlWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit DiskControlWidget(QWidget *parent = nullptr);
    ~DiskControlWidget() override;
    void initConnect();

    DDiskManager*  startMonitor();
    void doStartupAutoMount();
    void unmountAll();

    const QList<QExplicitlySharedDataPointer<DGioMount> > getVfsMountList();
    static void NotifyMsg(QString msg);
    static void NotifyMsg(QString title, QString msg);

signals:
    void diskCountChanged(const int count) const;

private slots:
    void onDiskListChanged();
    void onDriveDisconnected();
    void onMountAdded();
    void onMountRemoved(const QString &blockDevicePath, const QByteArray &mountPoint);
    void onVolumeAdded();
    void onVolumeRemoved();
    void onVfsMountChanged(QExplicitlySharedDataPointer<DGioMount> mount);
    void onBlockDeviceAdded(const QString &path);

private:
    QVBoxLayout *m_centralLayout;
    QWidget *m_centralWidget;
    bool m_isInLiveSystem = false; // 当处于 liveSys 的时候禁用自动挂载（以前的逻辑）
    bool m_autoMountEnable = false; // 配置项中的自动挂载
    bool m_autoMountAndOpenEnable = false; // 配置项中的挂载并打开

    DDiskManager *m_diskManager;

    QScopedPointer<DGioVolumeManager> m_vfsManager;
};

#endif // DISKCONTROLWIDGET_H
