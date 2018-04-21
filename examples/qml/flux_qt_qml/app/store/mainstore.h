#ifndef QML_MAIN_STORE_H
#define QML_MAIN_STORE_H

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

#include <flux_qt/action.h>
#include <flux_qt/store.h>

class MainStore final : public QObject, public flux_qt::Store
{
    Q_OBJECT

    Q_PROPERTY(bool showFileDialog READ getShowFileDialog NOTIFY showFileDialogChanged)
    Q_PROPERTY(QString selectedFilename READ getSelectedFilename NOTIFY selectedFilenameChanged)
    Q_PROPERTY(QString uploadStatus READ getUploadStatus NOTIFY uploadStatusChanged)

public:
    static MainStore& instance() {
        static MainStore self;
        return self;
    }

    void process(const QSharedPointer<flux_qt::Action>& action) Q_DECL_OVERRIDE;

    bool getShowFileDialog() const;
    QString getSelectedFilename() const;
    QString getUploadStatus() const;

signals:
    void showFileDialogChanged();
    void selectedFilenameChanged();
    void uploadStatusChanged();

private:
    MainStore();
    MainStore(const MainStore&) = delete;
    MainStore(MainStore&&) = delete;
    MainStore& operator=(const MainStore&) = delete;
    MainStore& operator=(MainStore&&) = delete;
    ~MainStore();

    void processShowFileDialogAction(const QSharedPointer<flux_qt::Action>& action);
    void processSelectFileAction(const QSharedPointer<flux_qt::Action>& action);
    void processUploadFtpStartedAction(const QSharedPointer<flux_qt::Action>& action);
    void processUploadFtpProcessAction(const QSharedPointer<flux_qt::Action>& action);
    void processUploadFtpFinishedAction(const QSharedPointer<flux_qt::Action>& action);

    class MainStoreImpl;
    QScopedPointer<MainStoreImpl> impl_;
};

#endif
