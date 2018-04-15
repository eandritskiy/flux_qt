#ifndef CONSOLE_FTP_SERVICE_WORKER_H
#define CONSOLE_FTP_SERVICE_WORKER_H

#include <QThread>

class FtpServiceWorkerThread final : public QThread
{
public:
    FtpServiceWorkerThread() = default;
    virtual ~FtpServiceWorkerThread() = default;

private:
    FtpServiceWorkerThread(const FtpServiceWorkerThread&) = delete;
    FtpServiceWorkerThread(FtpServiceWorkerThread&&) = delete;
    FtpServiceWorkerThread& operator=(const FtpServiceWorkerThread&) = delete;
    FtpServiceWorkerThread& operator=(FtpServiceWorkerThread&&) = delete;

    void run() override;
};

class FtpServiceWorker final : public QObject
{
    Q_OBJECT

public:
    FtpServiceWorker() = default;
    ~FtpServiceWorker() = default;

public slots:
    void onUploadFtp(const QString& filename);

private:
    FtpServiceWorker(const FtpServiceWorker&) = delete;
    FtpServiceWorker(FtpServiceWorker&&) = delete;
    FtpServiceWorker& operator=(const FtpServiceWorker&) = delete;
    FtpServiceWorker& operator=(FtpServiceWorker&&) = delete;
};

#endif
