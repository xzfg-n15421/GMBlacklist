#include "Plugin.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace plugin {

Plugin::Plugin(ll::plugin::NativePlugin& self) : mSelf(self) {
    // Code for loading the plugin goes here.
    initConfigFile();
    checkBanTimeTask();
}

bool Plugin::enable() {
    // Code for enabling the plugin goes here.
    RegisterCommands();
    logger.info("GMBlacklist Loaded!");
    logger.info("Author: Tsubasa6848");
    logger.info("Repository: https://github.com/GroupMountain/GMBlacklist");
    return true;
}

bool Plugin::disable() {
    // Code for disabling the plugin goes here.
    unloadPlugin();
    logger.info("GMBlacklist Unloaded!");
    return true;
}

} // namespace plugin