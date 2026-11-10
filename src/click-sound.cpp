
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace MaxCheat {

static bool clickSoundEnabled = true;

void playClickSound() {
    if (!clickSoundEnabled) {
        return;
    }

    FMODAudioEngine::sharedEngine()->playEffect("click.ogg");
}

void setClickSound(bool enabled) {
    clickSoundEnabled = enabled;
}

bool isClickSoundEnabled() {
    return clickSoundEnabled;
}

}
