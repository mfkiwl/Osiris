#pragma once

#include "VirtualMethod.h"

namespace csgo::pod { struct SoundEmitter; }

class SoundEmitter : public VirtualCallableFromPOD<SoundEmitter, csgo::pod::SoundEmitter> {
public:
    VIRTUAL_METHOD2(const char*, getSoundName, 46, (int index), (index))
};
