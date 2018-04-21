#ifndef FLUX_QT_DISPATCHER_H
#define FLUX_QT_DISPATCHER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>

#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QQueue>
#include <QtGlobal>
#include <QSharedPointer>
#include <QVector>

#include "middleware.h"
#include "store.h"

namespace flux_qt
{
class Action;

class Dispatcher final : public QObject
{
    Q_OBJECT

public:
    static Dispatcher& instance() {
        static Dispatcher self;
        return self;
    }

    template <class... Args>
    void registerMiddleware(Args&&... args)
    {
        middlewares_.push_back(QSharedPointer<Middleware>(std::forward<Args>(args)...));
    }

    template <class... Args>
    void registerStore(Args&&... args)
    {
        stores_.push_back(QSharedPointer<Store>(std::forward<Args>(args)...));
    }

    template <class... Args>
    void dispatch(Args&&... args)
    {
        QMutexLocker locker(&mutex_);
        actions_.enqueue(QSharedPointer<Action>(std::forward<Args>(args)...));

        emit newActionAdded();
    }

signals:
    void newActionAdded();

private:
    Dispatcher()
    {
        QObject::connect(this, &Dispatcher::newActionAdded, this, [this]() {
            this->onNewActionAdded();
        }, Qt::QueuedConnection);
    }

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher(Dispatcher&&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;
    Dispatcher& operator=(Dispatcher&&) = delete;
    ~Dispatcher() = default;

    void onNewActionAdded()
    {
        mutex_.lock();

        while (!actions_.empty()) {
            auto action = actions_.dequeue();

            mutex_.unlock();

            for (const auto& middleware : middlewares_) {
                action = middleware->process(action);
            }

            for (const auto& store : stores_) {
                store->process(action);
            }

            mutex_.lock();
        }

        mutex_.unlock();
    }

    QVector<QSharedPointer<Middleware> > middlewares_;
    QVector<QSharedPointer<Store> > stores_;

    QQueue<QSharedPointer<Action> > actions_;
    QMutex mutex_;
};

}

#endif

