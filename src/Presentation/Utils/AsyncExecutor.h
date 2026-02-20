#ifndef ASYNCEXECUTOR_H
#define ASYNCEXECUTOR_H

#include <functional>

#include <QFutureWatcher>
#include <QObject>
#include <QtConcurrent/QtConcurrentRun>

namespace Sea {
namespace Presentation {

class AsyncExecutor : public QObject
{
    Q_OBJECT
public:
    explicit AsyncExecutor(QObject *parent = nullptr);

    template<typename T>
    void exec(std::function<T()> func, std::function<void(const T &)> resultHandler)
    {
        auto *watcher = new QFutureWatcher<T>();

        connect(watcher, &QFutureWatcher<T>::finished, this, [watcher, resultHandler]() {
            resultHandler(watcher->result());
            watcher->deleteLater();
        });

        auto future = QtConcurrent::run(func);
        watcher->setFuture(future);
    }

    template<typename T>
    void exec(std::function<void()> func)
    {
        auto *watcher = new QFutureWatcher<T>();

        connect(watcher, &QFutureWatcher<T>::finished, this, [watcher]() {
            watcher->deleteLater();
        });

        auto future = QtConcurrent::run(func);
        watcher->setFuture(future);
    }
};

} // namespace Presentation
} // namespace Sea

#endif // ASYNCEXECUTOR_H
