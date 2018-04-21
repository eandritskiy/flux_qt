#include <QDebug>

#include <flux_qt/action.h>

#include <action/actiontypes.h>
#include <store/mainstore.h>

class MainStore::MainStoreImpl final
{
public:
    MainStoreImpl() = default;
    MainStoreImpl(const MainStoreImpl&) = delete;
    MainStoreImpl(MainStoreImpl&&) = delete;
    MainStoreImpl& operator=(const MainStoreImpl&) = delete;
    MainStoreImpl& operator=(MainStoreImpl&&) = delete;
    ~MainStoreImpl() = default;

    bool showFileDialog_;
    QString selectedFilename_;
    QString uploadStatus_;
};

MainStore::MainStore()
    : impl_(new MainStoreImpl)
{
    impl_->showFileDialog_ = false;
}

MainStore::~MainStore()
{
}

bool MainStore::getShowFileDialog() const
{
    return impl_->showFileDialog_;
}

QString MainStore::getSelectedFilename() const
{
    return impl_->selectedFilename_;
}

QString MainStore::getUploadStatus() const
{
    return impl_->uploadStatus_;
}

void MainStore::process(const QSharedPointer<flux_qt::Action>& action)
{
    switch (action->getType<ActionType>()) {

    case ActionType::ShowFileDialog:
        processShowFileDialogAction(action);
        break;

    case ActionType::SelectFile:
        processSelectFileAction(action);
        break;

    case ActionType::UploadFtpStarted:
        processUploadFtpStartedAction(action);
        break;

    case ActionType::UploadFtpProcess:
        processUploadFtpProcessAction(action);
        break;

    case ActionType::UploadFtpFinished:
        processUploadFtpFinishedAction(action);
        break;
    }
}

void MainStore::processShowFileDialogAction(const QSharedPointer<flux_qt::Action> &action)
{
    impl_->showFileDialog_ = action->getPayload<bool>();
    emit showFileDialogChanged();
}

void MainStore::processSelectFileAction(const QSharedPointer<flux_qt::Action> &action)
{
    impl_->selectedFilename_ = action->getPayload<QString>();
    emit selectedFilenameChanged();
}

void MainStore::processUploadFtpStartedAction(const QSharedPointer<flux_qt::Action> &action)
{
    Q_UNUSED(action)
    impl_->uploadStatus_ = QStringLiteral("Start uploading...");
    emit uploadStatusChanged();
}

void MainStore::processUploadFtpProcessAction(const QSharedPointer<flux_qt::Action> &action)
{
    impl_->uploadStatus_ = QString("Uploaded %1%").arg(action->getPayload<QString>());
    emit uploadStatusChanged();
}

void MainStore::processUploadFtpFinishedAction(const QSharedPointer<flux_qt::Action> &action)
{
    Q_UNUSED(action)
    impl_->uploadStatus_ = QStringLiteral("Uploading finished");
    emit uploadStatusChanged();
}
