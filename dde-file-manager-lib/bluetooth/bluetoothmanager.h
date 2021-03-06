/*
 * Copyright (C) 2020 ~ 2020 Deepin Technology Co., Ltd.
 *
 * Author:     zhangsheng <zhangsheng@uniontech.com>
 *
 * Maintainer: zhangsheng <zhangsheng@uniontech.com>
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

#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>

#include "dfmglobal.h"

class BluetoothModel;
class BluetoothDevice;
class BluetoothAdapter;
class BluetoothManagerPrivate;

/**
 * @brief This is singleton class.
 * you should `#include "app/define.h"` and `"bluetooth/bluetoothmanager.h"`,
 * then use the macro `bluetoothManager` call method
 */
class BluetoothManager : public QObject
{
    Q_OBJECT

public:
    static BluetoothManager *instance();

    /**
     * @brief 返回数据模型
     * @return
     */
    BluetoothModel *model();


public Q_SLOTS:
    /**
     * @brief 异步接口：调用刷新蓝牙模块，初始化数据
     */
    void refresh();

    /**
     * @brief 打开控制中心的‘蓝牙’界面
     */
    void showBluetoothSettings();

    /**
     * @brief 向设备发送文件
     * @param device 设备对象
     * @param filePath 文件路径
     * @return 返回一个 sessionPath，用于对传输进行取消，返回空说明调用dbus接口时发生了错误
     */
    QString sendFiles(const BluetoothDevice &device, const QStringList &filePath);

    /**
     * @brief 向设备发送文件
     * @param id 设备对象中的id
     * @param filePath 文件路径
     * @return 返回一个 sessionPath，用于对传输进行取消，返回空说明调用dbus接口时发生了错误
     */
    QString sendFiles(const QString &id, const QStringList &filePath);

    /**
     * @brief cancleTransfer 取消某个传输会话
     * @param sessionPath
     * @return
     */
    bool cancelTransfer(const QString &sessionPath);

    bool canSendBluetoothRequest();

Q_SIGNALS:

    /**
     * @brief transferProcessUpdated    当前传输会话进度更新
     * @param sessionPath   用来标识当前传输进程的会话id
     * @param total         当前传输列表的总bytes
     * @param transferred   当前已传输的 bytes
     * @param currFileIndex 当前传输文件的序号
     */
    void transferProgressUpdated(const QString &sessionPath, qulonglong total, qulonglong transferred, int currFileIndex);

    /**
     * @brief transferCancledByRemote
     * @param sessionPath
     */
    void transferCancledByRemote(const QString &sessionPath);

    void fileTransferFinished(const QString &sessionPath, const QString &filePath);
    void transferFailed(const QString &sessionPath, const QString &filePath, const QString &errMsg);

private:
    explicit BluetoothManager(QObject *parent = nullptr);
    BluetoothManager(const BluetoothManager &) = delete;
    BluetoothManager &operator = (const BluetoothManager &) = delete;

    QSharedPointer<BluetoothManagerPrivate> d_ptr;

    Q_DECLARE_PRIVATE(BluetoothManager)
};

#endif // BLUETOOTHMANAGER_H
