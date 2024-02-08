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
    auto requireLibVersion = SemVersion(0, 7, 2, "", "");
    if (GMLIB::Version::checkLibVersionMatch(requireLibVersion)) {
        RegisterCommands();
        listenEvent();
        logger.info("GMBlacklist Loaded!");
        logger.info("Author: Tsubasa6848");
        logger.info("Repository: https://github.com/GroupMountain/GMBlacklist");
        return true;
    } else {
        logger.error("GMLIB Version is outdated! Please update your GMLIB!");
        logger.error(
            "Current GMLIB Version {}, Required Lowest GMLIB Version {}",
            GMLIB::Version::getLibVersionString(),
            requireLibVersion.asString()
        );
        return false;
    }
}

bool Plugin::disable() {
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace plugin