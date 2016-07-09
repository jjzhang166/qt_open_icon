#include "procedure.h"

Procedure::Procedure(const QString &_socketname, const QString &_proName, \
                     const QStringList &_arguments):
    socketName(_socketname),
    proName(_proName),
    arguments(_arguments),
    client(NULL),
    proIcon(NULL)
{
    process = new QProcess;
    server = new QLocalServer();
}

/**
 * @brief 把所有虚函数初始化放到这个里边
 * @return
 */
void Procedure::init()
{
    //初始化图标
    proIcon = createIcon();
    connect(proIcon, SIGNAL(btnReleased()), this, SLOT(startProSlot()));
}


BaseButton *Procedure::createIcon()
{
    qDebug()<<"Procedure createIcon";
    BaseButton *iconBtn = new BaseButton(MuiFont(), MuiFont::ICON_WEINXIN, 100, 100);
    return iconBtn;
}

void Procedure::startProSlot()
{
    if(process->isOpen()){
        qDebug()<<proName<<" has run";
        sendCmd(10);
    }else{
        bool startRet = (startSocketServer() && startProcedure());
        if(startRet){
            emit startResult(true);
        }else{
            emit startResult(false);
        }
    }
}

bool Procedure::startSocketServer()
{
    //初始化服务端
#ifdef Q_OS_LINUX
    //linux下有些特殊，详情参考listen函数帮助文档
    QFile file("/tmp/image");
    if(file.exists()){
        file.remove();
    }
#elif defined Q_OS_WIN
#elif defined Q_OS_MAC
#endif

    if (!server->listen(socketName)) {
        qDebug()<<"server listen err";
        return false;
    }else{
        qDebug()<<socketName<<" is listening";
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(connectionSlot()));
    return true;
}


/**
 * @brief 启动进程
 * @return 成功返回true，失败返回false
 */
bool Procedure::startProcedure()
{
    process->start(proName, arguments);
    if (!process->waitForStarted())
    {
        qDebug()<<proName<<" process start err";
        return false;
    }else{
        qDebug()<<proName<<" process start success";
        return true;
    }
}

void Procedure::connectionSlot()
{
    client = server->nextPendingConnection();
    qDebug()<<"connect to "<<client->serverName();
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
}


bool Procedure::sendCmd(int cmd)
{
    if(client != NULL){
        QString cmdStr = cmdStr.number(cmd);
        QByteArray cmdStream;
        QDataStream out(&cmdStream, QIODevice::WriteOnly);
        out << cmdStr.toLatin1().data();

        if(client->write(cmdStream) == -1){
            return false;
        }else{
            return true;
        }
    }else{
        qDebug()<<socketName<<" client is null";
        return false;
    }
}



