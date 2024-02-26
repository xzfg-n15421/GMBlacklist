#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace GMBlacklist {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace GMBlacklist
