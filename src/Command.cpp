#include "Global.h"
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/command/DynamicCommand.h>

void RegBanCmd(CommandRegistry& registry) {
    auto command =
        DynamicCommand::createCommand(registry, "ban", tr("command.ban.desc"), CommandPermissionLevel::Owner);
    command->mandatory("player", DynamicCommand::ParameterType::String);
    command->optional("minutes", DynamicCommand::ParameterType::Int);
    command->optional("reason", DynamicCommand::ParameterType::String);
    command->addOverload({"player", "minutes", "reason"});
    command->addOverload({"player", "reason"});
    command->setCallback([](DynamicCommand const&                                    command,
                            CommandOrigin const&                                     origin,
                            CommandOutput&                                           output,
                            std::unordered_map<std::string, DynamicCommand::Result>& result) {
        std::string source = "Console";
        int         time   = -1;
        std::string reason = tr("disconnect.defaultReason");
        auto        type   = origin.getOriginType();
        if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
            if (type == CommandOriginType::Player) {
                auto pl = (Player*)origin.getEntity();
                source  = pl->getRealName();
            }
            if (result["minutes"].isSet) {
                time = result["minutes"].get<int>();
                if (time < 1) {
                    return output.error(tr("command.error.invalidTime"));
                }
            }
            if (result["reason"].isSet) {
                reason = result["reason"].get<std::string>();
                if (reason.empty()) {
                    reason = tr("disconnect.defaultReason");
                }
            }
            auto name = result["player"].get<std::string>();
            auto pl   = ll::service::getLevel()->getPlayer(name);
            bool res  = false;
            if (pl) {
                res = banOnlinePlayer(pl, source, time, reason);
            } else {
                res = banPlayer(name, source, time, reason);
            }
            if (res) {
                std::string endTime = time < 0 ? tr("disconnect.forever") : getExpiredTime(time);
                return output.success(tr("command.ban.success", {name, endTime}));
            }
            return output.error(tr("command.ban.isBanned", {name}));
        }
        return output.error(tr("command.error.invalidCommandOrigin"));
    });
    DynamicCommand::setup(registry, std::move(command));
}

void RegUnbanCmd(CommandRegistry& registry) {
    auto command =
        DynamicCommand::createCommand(registry, "unban", tr("command.unban.desc"), CommandPermissionLevel::Owner);
    command->mandatory("player", DynamicCommand::ParameterType::String);
    command->addOverload({"player"});
    command->setCallback([](DynamicCommand const&                                    command,
                            CommandOrigin const&                                     origin,
                            CommandOutput&                                           output,
                            std::unordered_map<std::string, DynamicCommand::Result>& result) {
        auto type = origin.getOriginType();
        if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
            auto name = result["player"].get<std::string>();
            auto res  = unbanPlayer(name);
            if (res) {
                return output.success(tr("command.unban.success", {name}));
            }
            return output.error(tr("command.unban.notBanned", {name}));
        }
        return output.error(tr("command.error.invalidCommandOrigin"));
    });
    DynamicCommand::setup(registry, std::move(command));
}

void RegBanIpCmd(CommandRegistry& registry) {
    auto command =
        DynamicCommand::createCommand(registry, "banip", tr("command.ban.desc"), CommandPermissionLevel::Owner);
    command->setAlias("ban-ip");
    command->mandatory("ip", DynamicCommand::ParameterType::String);
    command->optional("minutes", DynamicCommand::ParameterType::Int);
    command->optional("reason", DynamicCommand::ParameterType::String);
    command->addOverload({"ip", "minutes", "reason"});
    command->addOverload({"ip", "reason"});
    command->setCallback([](DynamicCommand const&                                    command,
                            CommandOrigin const&                                     origin,
                            CommandOutput&                                           output,
                            std::unordered_map<std::string, DynamicCommand::Result>& result) {
        std::string source = "Console";
        int         time   = -1;
        std::string reason = tr("disconnect.defaultReason");
        auto        type   = origin.getOriginType();
        if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
            if (type == CommandOriginType::Player) {
                auto pl = (Player*)origin.getEntity();
                source  = pl->getRealName();
            }
            if (result["minutes"].isSet) {
                time = result["minutes"].get<int>();
                if (time < 1) {
                    return output.error(tr("command.error.invalidTime"));
                }
            }
            if (result["reason"].isSet) {
                reason = result["reason"].get<std::string>();
                if (reason.empty()) {
                    reason = tr("disconnect.defaultReason");
                }
            }
            auto ip  = result["ip"].get<std::string>();
            auto res = banIP(ip, source, time, reason);
            if (res) {
                std::string endTime = time < 0 ? tr("disconnect.forever") : getExpiredTime(time);
                return output.success(tr("command.banip.success", {ip, endTime}));
            }
            return output.error(tr("command.banip.isBanned", {ip}));
        }
        return output.error(tr("command.error.invalidCommandOrigin"));
    });
    DynamicCommand::setup(registry, std::move(command));
}

void RegUnbanipCmd(CommandRegistry& registry) {
    auto command =
        DynamicCommand::createCommand(registry, "unbanip", tr("command.unban.desc"), CommandPermissionLevel::Owner);
    command->mandatory("ip", DynamicCommand::ParameterType::String);
    command->addOverload({"ip"});
    command->setCallback([](DynamicCommand const&                                    command,
                            CommandOrigin const&                                     origin,
                            CommandOutput&                                           output,
                            std::unordered_map<std::string, DynamicCommand::Result>& result) {
        auto type = origin.getOriginType();
        if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
            auto ip  = result["ip"].get<std::string>();
            auto res = unbanIP(ip);
            if (res) {
                return output.success(tr("command.unbanip.success", {ip}));
            }
            return output.error(tr("command.unbanip.notBanned", {ip}));
        }
        return output.error(tr("command.error.invalidCommandOrigin"));
    });
    DynamicCommand::setup(registry, std::move(command));
}

void RegisterCommands() {
    auto registry = ll::service::getCommandRegistry();
    RegBanCmd(registry);
    RegUnbanCmd(registry);
    RegBanIpCmd(registry);
    RegUnbanipCmd(registry);
}