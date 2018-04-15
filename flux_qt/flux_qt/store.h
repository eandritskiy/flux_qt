#ifndef FLUX_QT_STORE_H
#define FLUX_QT_STORE_H

#include <QSharedPointer>

namespace flux_qt 
{
class Action;

class Store
{
public:
    virtual ~Store() = default;

    virtual void process(const QSharedPointer<Action>& action) = 0;

protected:
    Store() = default;
    Store(const Store&) = default;
    Store(Store&&) = default;
    Store& operator=(const Store&) = default;
    Store& operator=(Store&&) = default;
};

}

#endif
