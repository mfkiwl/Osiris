#pragma once

#include <cstddef>
#include <string_view>

#include "Material.h"
#include "VirtualMethod.h"

enum class OverrideType {
    Normal = 0,
    BuildShadows,
    DepthWrite,
    CustomMaterial, // weapon skins
    SsaoDepthWrite
};

namespace csgo::pod
{
    struct StudioRender {
        PAD(WIN32_LINUX(592, 600))
        csgo::pod::Material* materialOverride;
        PAD(WIN32_LINUX(12, 24))
        OverrideType overrideType;
    };
}

class StudioRender : public VirtualCallableFromPOD<StudioRender, csgo::pod::StudioRender> {
public:
    VIRTUAL_METHOD2(void, forcedMaterialOverride, 33, (csgo::pod::Material* material, OverrideType type = OverrideType::Normal, int index = -1), (material, type, index))

    bool isForcedMaterialOverride() const noexcept
    {
        if (!getPOD()->materialOverride)
            return getPOD()->overrideType == OverrideType::DepthWrite || getPOD()->overrideType == OverrideType::SsaoDepthWrite; // see CStudioRenderContext::IsForcedMaterialOverride
        return std::string_view{ Material::from(getInvoker(), getPOD()->materialOverride).getName() }.starts_with("dev/glow");
    }
};
