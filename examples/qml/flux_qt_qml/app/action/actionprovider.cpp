#include <flux_qt/action.h>
#include <flux_qt/dispatcher.h>

#include <action/actionprovider.h>
#include <action/actiontypes.h>

void ActionProvider::showFileDialog(bool show)
{
    flux_qt::Dispatcher::instance().dispatch(new flux_qt::Action(ActionType::ShowFileDialog, show));
}

void ActionProvider::selectFile(const QString &filename)
{
    flux_qt::Dispatcher::instance().dispatch(new flux_qt::Action(ActionType::SelectFile, filename));
}

void ActionProvider::uploadFtp(const QString &filename)
{
    flux_qt::Dispatcher::instance().dispatch(new flux_qt::Action(ActionType::UploadFtp, filename));
}
