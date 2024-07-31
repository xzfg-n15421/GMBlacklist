#include "Entry.h"
#include "Global.h"
#include "Language.h"

ll::Logger logger(PLUGIN_NAME);

namespace GMBlacklist {

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() { return true; }

bool Entry::enable() {
    mConfig.emplace();
    if (!ll::config::loadConfig(*mConfig, getSelf().getConfigDir() / u8"config.json")) {
        ll::config::saveConfig(*mConfig, getSelf().getConfigDir() / u8"config.json");
    }
    auto& commandPermissionLevel = getConfig().CommandPermissionLevel;
    if (commandPermissionLevel < 0 || commandPermissionLevel > 4) {
        commandPermissionLevel = 4;
        logger.error(tr("permission.error.invalidLevel"));
    }
    if (commandPermissionLevel == 0) {
        logger.warn(tr("permission.warning.dangerousLevel"));
    }
    initDataFile();
    mI18n.emplace(getSelf().getLangDir(), mConfig->language);
    mI18n->updateOrCreateLanguage("en_US", en_US);
    mI18n->updateOrCreateLanguage("zh_CN", zh_CN);
    mI18n->loadAllLanguages();
    mI18n->chooseLanguage(mConfig->language); // maybe
    checkBanTimeTask();
    RegisterCommands();
    listenEvent();
    logger.info("GMBlacklist Loaded!");
    logger.info("Author: Tsubasa6848");
    logger.info("Repository: https://github.com/GroupMountain/GMBlacklist");
    return true;
}

bool Entry::disable() { return true; }

Config& Entry::getConfig() { return mConfig.value(); }

JsonI18n& Entry::getI18n() { return mI18n.value(); }

} // namespace GMBlacklist

LL_REGISTER_MOD(GMBlacklist::Entry, GMBlacklist::Entry::getInstance());

std::string tr(std::string const& key, std::vector<std::string> const& data) {
    return GMBlacklist::Entry::getInstance()->getI18n().get(key, data);
}
