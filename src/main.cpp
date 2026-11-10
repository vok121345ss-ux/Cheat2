
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MaxCheatMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        log::info("MAX CHEAT PRO loaded!");

        // Floating button and menu will be initialized here.
        return true;
    }
};
