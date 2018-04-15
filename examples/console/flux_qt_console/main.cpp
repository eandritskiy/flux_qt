#include <QCoreApplication>
#include <QString>

#include <flux_qt/action.h>
#include <flux_qt/dispatcher.h>
#include <action/actiontypes.h>
#include <middleware/ftpmiddleware.h>
#include <store/mainstore.h>

using namespace flux_qt;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dispatcher::instance().registerMiddleware(new FtpMiddleware);
    Dispatcher::instance().registerStore(new MainStore);

    Dispatcher::instance().dispatch(new Action(ActionType::UploadFtp, QString("ftp://example.com/example.zip")));

    return a.exec();
}
