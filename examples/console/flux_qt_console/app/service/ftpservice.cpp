#include <QSharedPointer>

#include <flux_qt/action.h>
#include <flux_qt/dispatcher.h>

#include <action/actiontypes.h>
#include <service/ftpservice.h>
#include <service/ftpserviceworker.h>

class FtpService::FtpServiceImpl final
{
public:
    FtpServiceImpl() = default;
    FtpServiceImpl(const FtpServiceImpl&) = delete;
    FtpServiceImpl(FtpServiceImpl&&) = delete;
    FtpServiceImpl& operator=(const FtpServiceImpl&) = delete;
    FtpServiceImpl& operator=(FtpServiceImpl&&) = delete;
    ~FtpServiceImpl() = default;

    QSharedPointer<FtpServiceWorkerThread> thread_;
};

FtpService::FtpService()
    : impl_(new FtpServiceImpl)
{
    impl_->thread_ = QSharedPointer<FtpServiceWorkerThread>(new FtpServiceWorkerThread);

    FtpServiceWorker *worker = new FtpServiceWorker();
    worker->moveToThread(impl_->thread_.data());

    QObject::connect(impl_->thread_.data(), &QThread::finished, worker, &FtpServiceWorker::deleteLater);
    QObject::connect(this, &FtpService::uploadFtp, worker, &FtpServiceWorker::onUploadFtp, Qt::QueuedConnection);

    impl_->thread_->start(QThread::Priority::LowPriority);
}

FtpService::~FtpService()
{
    impl_->thread_->quit();
    impl_->thread_->wait();
}

void FtpService::onUploadFtp(const QString &filename)
{
    emit uploadFtp(filename);
}
