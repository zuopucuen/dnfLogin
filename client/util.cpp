#include "windows.h"
#include "TlHelp32.h"
#include <QString>
#include <QFile>
#include <QNetworkInterface>

static QString GetSysFolder ()
{
    TCHAR szPath[100] ={0};
    GetSystemDirectory( szPath, 100 ) ;
    return QString::fromWCharArray(szPath);
}

bool processExistsByName(LPCTSTR findProcessName)//根据进程名查找进程PID
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hSnapShot == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    PROCESSENTRY32 pe32;//声明进程入口对象
    pe32.dwSize = sizeof(PROCESSENTRY32);//填充进程入口对象大小
    Process32First(hSnapShot,&pe32);//遍历进程列表
    do{
        if(!lstrcmp(pe32.szExeFile, findProcessName))//查找指定进程名的PID
        {
            return true;
        }
    } while (Process32Next(hSnapShot,&pe32));
    CloseHandle(hSnapShot);
    return false;
}

QString getMacAddr()
{
    QString macAddr;
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

    foreach(QNetworkInterface interfaceItem, interfaceList)
    {
        if(interfaceItem.flags().testFlag(QNetworkInterface::IsUp)
                &&interfaceItem.flags().testFlag(QNetworkInterface::IsRunning)
                &&interfaceItem.flags().testFlag(QNetworkInterface::CanBroadcast)
                &&interfaceItem.flags().testFlag(QNetworkInterface::CanMulticast)
                &&!interfaceItem.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            QList<QNetworkAddressEntry> addressEntryList=interfaceItem.addressEntries();
            foreach(QNetworkAddressEntry addressEntryItem, addressEntryList)
            {
                if(addressEntryItem.ip().protocol()==QAbstractSocket::IPv4Protocol)
                {
                    macAddr = interfaceItem.hardwareAddress();
                }
            }
        }
    }

    return macAddr;
}

bool changeHostFile()
{
    QString hostPath = GetSysFolder();
    QString hostLine;
    bool hostIsChanged = false;

    hostPath.append("\\drivers\\etc\\hosts");

    QFile hostFile(hostPath);
    QTextStream hostStream(&hostFile);

    if(hostFile.open(QIODevice::ReadWrite| QIODevice::Text))
    {
        while(1){
            hostLine = hostStream.readLine();

            if(hostLine.isNull()){
                break;
            }

            hostLine = hostLine.simplified();

            if(hostLine.at(0) == '#'){
                continue;
            }

            if(hostLine.indexOf("103.37.162.118") != -1
                    && hostLine.indexOf("start.dnf.tw") != -1){
                hostIsChanged = true;
            }
        }

        if(!hostIsChanged){
            hostStream << "103.37.162.118 " << "start.dnf.tw";
        }

        hostFile.close();

        return true;
    }

    return false;
}
