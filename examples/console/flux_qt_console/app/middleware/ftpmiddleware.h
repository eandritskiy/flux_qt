#ifndef CONSOLE_FTP_MIDDLEWARE_H
#define CONSOLE_FTP_MIDDLEWARE_H

#include <QSharedPointer>
#include <QScopedPointer>

#include <flux_qt/action.h>
#include <flux_qt/middleware.h>

class FtpMiddleware final : public flux_qt::Middleware
{
public:
    FtpMiddleware();
    ~FtpMiddleware();

    QSharedPointer<flux_qt::Action> process(const QSharedPointer<flux_qt::Action>& action) override;

private:
    FtpMiddleware(const FtpMiddleware&) = delete;
    FtpMiddleware(FtpMiddleware&&) = delete;
    FtpMiddleware& operator=(const FtpMiddleware&) = delete;
    FtpMiddleware& operator=(FtpMiddleware&&) = delete;

    class FtpMiddlewareImpl;
    QScopedPointer<FtpMiddlewareImpl> impl_;
};

#endif
