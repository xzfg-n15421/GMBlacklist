#include "Language.h"
#include "Global.h"

GMLIB::Files::JsonConfig* Config = nullptr;
nlohmann::json            Language;
int                       commandPermissionLevel = 4;

void initConfigFile() {
    Config = new GMLIB::Files::JsonConfig("./plugins/GMBlacklist/config/config.json", defaultConfig);
    Config->initConfig();
    std::string langPath = "./plugins/GMBlacklist/language/{language}.json";
    std::string language = Config->getValue<std::string>({"language"}, "zh_CN");
    ll::utils::string_utils::replaceAll(langPath, "{language}", language);
    Language               = GMLIB::Files::JsonLanguage::initLanguage(langPath, defaultLanguage);
    commandPermissionLevel = Config->getValue<int>({"CommandPermissionLevel"}, 4);
    if (commandPermissionLevel < 0 || commandPermissionLevel > 4) {
        Config->setValue<int>({"CommandPermissionLevel"}, 4);
        logger.error(tr("permission.error.invalidLevel"));
    }
    if (commandPermissionLevel == 0) {
        logger.warn(tr("permission.warning.dangerousLevel"));
    }
    initDataFile();
}

std::string tr(std::string key, std::vector<std::string> data) {
    return GMLIB::Files::JsonLanguage::translate(Language, key, data);
}
