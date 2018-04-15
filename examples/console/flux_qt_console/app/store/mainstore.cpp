#include <QDebug>

#include <flux_qt/action.h>

#include <action/actiontypes.h>
#include <store/mainstore.h>

void MainStore::process(const QSharedPointer<flux_qt::Action>& action)
{
    switch (action->getType<ActionType>()) {

    case ActionType::UploadFtpStarted:
        qDebug().noquote() << "Start uploading" << action->getPayload<QString>();
        break;

    case ActionType::UploadFtpProcess:
        qDebug().noquote() << "Uploaded" << QString("%1%").arg(QString::number(action->getPayload<int>()));
        break;

    case ActionType::UploadFtpFinished:
        qDebug() << "File uploaded successfully";
        break;
    }
}
