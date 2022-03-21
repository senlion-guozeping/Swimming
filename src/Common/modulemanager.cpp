#include "modulemanager.h"

#include "src/Excel/player.h"
#include "src/Common/basictool.h"
#include "src/Common/message.h"
#include "src/Algorithm/kmeans.h"
#include "src/Algorithm/statistics.h"

#include "src/Settings/TableSetting.h"
#include "src/Settings/WindowSetting.h"

ModuleManager::ModuleManager() {}

void ModuleManager::initModuleInstance()
{//实现单例模式
    auto player = Player::getInstance();
    auto basictool = BasicTool::getInstance();
    auto statistics = Statistics::getInstance();
    auto errMessage = ErrMessage::getInstance();
    auto warnMessage = WarnMessage::getInstance();
    auto infoMessage = InfoMessage::getInstance();
    auto questionMessage = QuestionMessage::getInstance();
    auto tableSetting = TableSetting::getInstance();
    auto windowSetting = WindowSetting::getInstance();
}
