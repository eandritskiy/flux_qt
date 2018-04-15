#ifndef CONSOLE_FTP_SERVICE_H
#define CONSOLE_FTP_SERVICE_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

class FtpService final : public QObject
{
    Q_OBJECT

public:
    FtpService();
    ~FtpService();

    void onUploadFtp(const QString& filename);

signals:
    void uploadFtp(const QString& filename);

private:
    FtpService(const FtpService&) = delete;
    FtpService(FtpService&&) = delete;
    FtpService& operator=(const FtpService&) = delete;
    FtpService& operator=(FtpService&&) = delete;

    class FtpServiceImpl;
    QScopedPointer<FtpServiceImpl> impl_;
};

#endif
