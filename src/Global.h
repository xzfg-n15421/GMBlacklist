#pragma once
#include <GMLIB/Files/JsonConfig.h>
#include <GMLIB/Files/JsonFile.h>
#include <GMLIB/Files/JsonLanguage.h>
#include <ll/api/Logger.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/command/DynamicCommand.h>
#include <ll/api/memory/Hook.h>
#include <ll/api/service/Bedrock.h>
#include <mc/certificates/Certificate.h>
#include <mc/certificates/ExtendedCertificate.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/network/packet/LoginPacket.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/Level.h>
#include <sstream>

#define PLUGIN_NAME "GMBlacklist"

extern ll::Logger logger;
extern int        commandPermissionLevel;

extern GMLIB::Files::JsonConfig* Config;

extern nlohmann::json mBanList;
extern nlohmann::json mBanIpList;
extern nlohmann::json mUserCache;

extern std::string tr(std::string key, std::vector<std::string> data = {});
extern std::string getExpiredTime(int offsetMinutes = 0);

extern void initConfigFile();
extern void initDataFile();

extern void RegisterCommands();
extern void checkBanTimeTask();

extern bool banPlayer(std::string& name, std::string& opSource, int time, std::string& reason);
extern bool banIP(std::string& ip, std::string& opSource, int time, std::string& reason);
extern bool banOnlinePlayer(Player* pl, std::string& opSource, int time, std::string& reason);
extern bool unbanPlayer(std::string& name);
extern bool unbanIP(std::string& ip);

extern void showBanPlayersList(CommandOutput& output);
extern void showBanIpsList(CommandOutput& output);

extern void unloadPlugin();