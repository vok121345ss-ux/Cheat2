
#include <Geode/Geode.hpp>
#include <array>
#include <string_view>

using namespace geode::prelude;

namespace MaxCheat {

struct Feature {
    std::string_view name;
    bool enabled = false;
};

std::array<Feature, 67> features = {{
    {"Noclip"},
    {"Noclip Accuracy"},
    {"No Spikes"},
    {"No Ground"},
    {"No Death"},
    {"Instant Complete"},
    {"Level Bypass"},
    {"Practice Hack"},
    {"Checkpoint Hack"},
    {"StartPos Switcher"},
    {"Instant Respawn"},
    {"Auto Retry"},
    {"Auto Practice"},
    {"Safe Mode"},
    {"Hitbox Viewer"},

    {"Hide Player"},
    {"Hide Cube"},
    {"Hide Trail"},
    {"Hide Effects"},
    {"No Glow"},
    {"No Particles"},
    {"No Death Effect"},
    {"No Respawn Effect"},
    {"Player Scale"},
    {"Player Color"},

    {"Speedhack"},
    {"Slow Motion"},
    {"Fast Motion"},
    {"Custom Speed"},
    {"Speed Slider"},
    {"Frame Advance"},
    {"Time Scale"},
    {"Freeze Game"},

    {"ReplayBot2"},
    {"Auto Click"},
    {"Clickbot"},
    {"Record Inputs"},
    {"Playback Inputs"},
    {"Save Replay"},
    {"Load Replay"},
    {"Replay Speed"},
    {"Frame Step"},
    {"Auto Complete"},

    {"Show FPS"},
    {"Show CPS"},
    {"Show Hitboxes"},
    {"Show Trajectory"},
    {"Show Icons"},
    {"Show Attempts"},
    {"Show Progress"},
    {"RGB Menu"},
    {"Custom Menu Theme"},
    {"Transparent Menu"},

    {"Unlock Icons"},
    {"Unlock Colors"},
    {"Unlock Trails"},
    {"Unlock Death Effects"},
    {"No Mirror"},
    {"No Wave Trail"},
    {"No Camera Shake"},
    {"No Blur"},
    {"No Particles Limit"},
    {"Custom Music"},
    {"Custom Background"},
    {"Menu Position"},
    {"Save Settings"},
    {"Reset Settings"}
}};

bool isEnabled(size_t index) {
    return index < features.size() && features[index].enabled;
}

void setEnabled(size_t index, bool enabled) {
    if (index < features.size()) {
        features[index].enabled = enabled;
    }
}

}
