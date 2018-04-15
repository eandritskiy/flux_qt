#ifndef CONSOLE_MAIN_STORE_H
#define CONSOLE_MAIN_STORE_H

#include <QSharedPointer>

#include <flux_qt/action.h>
#include <flux_qt/store.h>

class MainStore final : public flux_qt::Store
{
public:
    MainStore() = default;
    MainStore(const MainStore&) = default;
    MainStore(MainStore&&) = default;
    MainStore& operator=(const MainStore&) = default;
    MainStore& operator=(MainStore&&) = default;
    ~MainStore() = default;

    void process(const QSharedPointer<flux_qt::Action>& action) Q_DECL_OVERRIDE;
};

#endif
