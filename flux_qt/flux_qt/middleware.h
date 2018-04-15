#ifndef FLUX_QT_MIDDLEWARE_H
#define FLUX_QT_MIDDLEWARE_H

#include <QSharedPointer>

namespace flux_qt
{
class Action;

class Middleware
{
public:
    virtual ~Middleware() = default;

    virtual QSharedPointer<Action> process(const QSharedPointer<Action>& action) = 0;

protected:
    Middleware() = default;
    Middleware(const Middleware&) = default;
    Middleware(Middleware&&) = default;
    Middleware& operator=(const Middleware&) = default;
    Middleware& operator=(Middleware&&) = default;
};

}

#endif
