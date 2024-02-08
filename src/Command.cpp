#include "Global.h"

struct BanParam1 {
    std::string                        name;
    ll::command::Optional<int>         time;
    ll::command::Optional<std::string> reason;
};

struct BanParam2 {
    std::string                        name;
    ll::command::Optional<std::string> reason;
};

void RegBanCmd() {
    auto& cmd = ll::command::CommandRegistrar::getInstance()
                    .getOrCreateCommand("ban", tr("command.ban.desc"), (CommandPermissionLevel)commandPermissionLevel);
    cmd.overload<BanParam1>()
        .required("name")
        .optional("time")
        .optional("reason")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, BanParam1 const& param) {
            std::string source = "Console";
            int         time   = -1;
            std::string reason = tr("disconnect.defaultReason");
            auto        type   = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                if (type == CommandOriginType::Player) {
                    auto pl = (Player*)origin.getEntity();
                    source  = pl->getRealName();
                }
                if (param.time.has_value()) {
                    time = param.time;
                    if (time < 1) {
                        return output.error(tr("command.error.invalidTime"));
                    }
                }
                if (param.reason.has_value()) {
                    reason = param.reason;
                    if (reason.empty()) {
                        reason = tr("disconnect.defaultReason");
                    }
                }
                auto name = param.name;
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
        }>();
    cmd.overload<BanParam2>()
        .required("name")
        .optional("reason")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, BanParam2 const& param) {
            std::string source = "Console";
            int         time   = -1;
            std::string reason = tr("disconnect.defaultReason");
            auto        type   = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                if (type == CommandOriginType::Player) {
                    auto pl = (Player*)origin.getEntity();
                    source  = pl->getRealName();
                }
                if (param.reason.has_value()) {
                    reason = param.reason;
                    if (reason.empty()) {
                        reason = tr("disconnect.defaultReason");
                    }
                }
                auto name = param.name;
                auto pl   = ll::service::getLevel()->getPlayer(name);
                bool res  = false;
                if (pl) {
                    res = banOnlinePlayer(pl, source, time, reason);
                } else {
                    res = banPlayer(name, source, time, reason);
                }
                if (res) {
                    std::string endTime = tr("disconnect.forever");
                    return output.success(tr("command.ban.success", {name, endTime}));
                }
                return output.error(tr("command.ban.isBanned", {name}));
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
}

struct UnbanParam {
    std::string name;
};

void RegUnbanCmd() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "unban",
        tr("command.unban.desc"),
        (CommandPermissionLevel)commandPermissionLevel
    );
    cmd.overload<UnbanParam>()
        .required("name")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, UnbanParam const& param) {
            auto type = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                auto name = param.name;
                auto res  = unbanPlayer(name);
                if (res) {
                    return output.success(tr("command.unban.success", {name}));
                }
                return output.error(tr("command.unban.notBanned", {name}));
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
}

struct BanIpParam1 {
    std::string                        ip;
    ll::command::Optional<int>         time;
    ll::command::Optional<std::string> reason;
};

struct BanIpParam2 {
    std::string                        ip;
    ll::command::Optional<std::string> reason;
};

void RegBanIpCmd() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "banip",
        tr("command.banip.desc"),
        (CommandPermissionLevel)commandPermissionLevel
    );
    cmd.overload<BanIpParam1>()
        .required("ip")
        .optional("time")
        .optional("reason")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, BanIpParam1 const& param) {
            std::string source = "Console";
            int         time   = -1;
            std::string reason = tr("disconnect.defaultReason");
            auto        type   = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                if (type == CommandOriginType::Player) {
                    auto pl = (Player*)origin.getEntity();
                    source  = pl->getRealName();
                }
                if (param.time.has_value()) {
                    time = param.time;
                    if (time < 1) {
                        return output.error(tr("command.error.invalidTime"));
                    }
                }
                if (param.reason.has_value()) {
                    reason = param.reason;
                    if (reason.empty()) {
                        reason = tr("disconnect.defaultReason");
                    }
                }
                auto ip  = param.ip;
                auto res = banIP(ip, source, time, reason);
                if (res) {
                    std::string endTime = time < 0 ? tr("disconnect.forever") : getExpiredTime(time);
                    return output.success(tr("command.banip.success", {ip, endTime}));
                }
                return output.error(tr("command.banip.isBanned", {ip}));
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
    cmd.overload<BanIpParam2>()
        .required("ip")
        .optional("reason")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, BanIpParam2 const& param) {
            std::string source = "Console";
            int         time   = -1;
            std::string reason = tr("disconnect.defaultReason");
            auto        type   = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                if (type == CommandOriginType::Player) {
                    auto pl = (Player*)origin.getEntity();
                    source  = pl->getRealName();
                }
                if (param.reason.has_value()) {
                    reason = param.reason;
                    if (reason.empty()) {
                        reason = tr("disconnect.defaultReason");
                    }
                }
                auto ip  = param.ip;
                auto res = banIP(ip, source, time, reason);
                if (res) {
                    std::string endTime = tr("disconnect.forever");
                    return output.success(tr("command.banip.success", {ip, endTime}));
                }
                return output.error(tr("command.banip.isBanned", {ip}));
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
}

struct UnbanIpParam {
    std::string ip;
};

void RegUnbanipCmd() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "unbanip",
        tr("command.unbanip.desc"),
        (CommandPermissionLevel)commandPermissionLevel
    );
    cmd.overload<UnbanIpParam>()
        .required("ip")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, UnbanIpParam const& param) {
            auto type = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                auto ip  = param.ip;
                auto res = unbanIP(ip);
                if (res) {
                    return output.success(tr("command.unbanip.success", {ip}));
                }
                return output.error(tr("command.unbanip.notBanned", {ip}));
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
}

struct BanListParam {
    enum class Mode { players, ips };
    ll::command::SoftEnum<Mode> mode;
};

void RegBanlistCmd() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "banlist",
        tr("command.banlist.desc"),
        (CommandPermissionLevel)commandPermissionLevel
    );
    cmd.overload<BanListParam>()
        .optional("mode")
        .execute<[](CommandOrigin const& origin, CommandOutput& output, BanListParam const& param) {
            auto type = origin.getOriginType();
            if (type == CommandOriginType::DedicatedServer || type == CommandOriginType::Player) {
                if (param.mode == "ips") {
                    return showBanIpsList(output);
                }
                return showBanPlayersList(output);
            }
            return output.error(tr("command.error.invalidCommandOrigin"));
        }>();
}

void RegisterCommands() {
    RegBanCmd();
    RegUnbanCmd();
    RegBanIpCmd();
    RegUnbanipCmd();
    RegBanlistCmd();
}