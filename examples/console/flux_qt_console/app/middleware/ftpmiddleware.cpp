#include <QString>

#include <action/actiontypes.h>
#include <middleware/ftpmiddleware.h>
#include <service/ftpservice.h>

class FtpMiddleware::FtpMiddlewareImpl final
{
public:
    FtpMiddlewareImpl()
        : service_(new FtpService)
    {
    }

    FtpMiddlewareImpl(const FtpMiddlewareImpl&) = delete;
    FtpMiddlewareImpl(FtpMiddlewareImpl&&) = delete;
    FtpMiddlewareImpl& operator=(const FtpMiddlewareImpl&) = delete;
    FtpMiddlewareImpl& operator=(FtpMiddlewareImpl&&) = delete;
    ~FtpMiddlewareImpl() = default;

    QScopedPointer<FtpService> service_;
};

FtpMiddleware::FtpMiddleware()
    : impl_(new FtpMiddlewareImpl)
{
}

FtpMiddleware::~FtpMiddleware()
{
}

QSharedPointer<flux_qt::Action> FtpMiddleware::process(const QSharedPointer<flux_qt::Action>& action)
{
    switch (action->getType<ActionType>()) {

    case ActionType::UploadFtp:
        impl_->service_->onUploadFtp(action->getPayload<QString>());
        return QSharedPointer<flux_qt::Action>(new flux_qt::Action(ActionType::UploadFtpStarted, action->getPayload<QString>()));
    }

    return action;
}
