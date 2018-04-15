#include <QString>
#include <QThread>

#include <flux_qt/action.h>
#include <flux_qt/dispatcher.h>

#include <action/actiontypes.h>
#include <service/ftpserviceworker.h>

void FtpServiceWorkerThread::run()
{
    exec();
}

void FtpServiceWorker::onUploadFtp(const QString &filename)
{
    Q_UNUSED(filename)
    QThread::msleep(2000);

    int percentDone = 0;
    for (int i = 0; i < 10; ++i) {
        percentDone += 10;
        flux_qt::Dispatcher::instance().dispatch(new flux_qt::Action(ActionType::UploadFtpProcess, percentDone));

        QThread::msleep(1000);
    }

    flux_qt::Dispatcher::instance().dispatch(new flux_qt::Action(ActionType::UploadFtpFinished));
}
