#include "filesrever.h"

FileSrever::FileSrever(QObject *parent)
    : QTcpServer{parent}
{
}

void FileSrever::incomingConnection(qintptr socketDescriptor)
{
    // 将描述符发射
    emit this->newDescriptor(socketDescriptor);
}
