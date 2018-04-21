#ifndef QML_ACTION_PROVIDER_H
#define QML_ACTION_PROVIDER_H

#include <QObject>
#include <QString>

class ActionProvider final : public QObject
{
    Q_OBJECT

public:
    static ActionProvider& instance() {
        static ActionProvider self;
        return self;
    }

    Q_INVOKABLE void showFileDialog(bool show);
    Q_INVOKABLE void selectFile(const QString& filename);
    Q_INVOKABLE void uploadFtp(const QString& filename);

private:
    ActionProvider() = default;
    ActionProvider(const ActionProvider&) = delete;
    ActionProvider(ActionProvider&&) = delete;
    ActionProvider& operator=(const ActionProvider&) = delete;
    ActionProvider& operator=(ActionProvider&&) = delete;
    ~ActionProvider() = default;
};

#endif
