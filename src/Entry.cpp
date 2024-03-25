#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace GMBlacklist {

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() {
    initConfigFile();
    checkBanTimeTask();
    return true;
}

bool Entry::enable() {
    RegisterCommands();
    listenEvent();
    logger.info("GMBlacklist Loaded!");
    logger.info("Author: Tsubasa6848");
    logger.info("Repository: https://github.com/GroupMountain/GMBlacklist");
    return true;
}

bool Entry::disable() { return true; }

} // namespace GMBlacklist

LL_REGISTER_PLUGIN(GMBlacklist::Entry, GMBlacklist::Entry::getInstance());