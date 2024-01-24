#include "Language.h"
#include "Global.h"

GMLIB::Files::JsonConfig* Config = nullptr;
nlohmann::json            Language;

void initConfigFile() {
    Config = new GMLIB::Files::JsonConfig("./plugins/GMBlacklist/config/config.json", defaultConfig);
    Config->initConfig();
    std::string langPath = "./plugins/GMBlacklist/language/{language}.json";
    std::string language = Config->getValue<std::string>({"language"}, "zh_CN");
    ll::utils::string_utils::replaceAll(langPath, "{language}", language);
    Language = GMLIB::Files::JsonLanguage::initLanguage(langPath, defaultLanguage);
    initDataFile();
}

std::string tr(std::string key, std::vector<std::string> data) {
    return GMLIB::Files::JsonLanguage::translate(Language, key, data);
}
