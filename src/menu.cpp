
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <array>
#include <algorithm>
#include <string>

using namespace geode::prelude;

namespace MaxCheat {
    void playClickSound();
}

namespace {

struct Feature {
    const char* name;
    const char* id;
    int category;
};

static constexpr std::array<Feature, 67> FEATURES = {{
    // GAMEPLAY — 15
    {"Noclip", "noclip", 0},
    {"Noclip Accuracy", "noclip-accuracy", 0},
    {"No Spikes", "no-spikes", 0},
    {"No Ground", "no-ground", 0},
    {"No Death", "no-death", 0},
    {"Instant Complete", "instant-complete", 0},
    {"Level Bypass", "level-bypass", 0},
    {"Practice Hack", "practice-hack", 0},
    {"Checkpoint Hack", "checkpoint-hack", 0},
    {"StartPos Switcher", "startpos-switcher", 0},
    {"Instant Respawn", "instant-respawn", 0},
    {"Auto Retry", "auto-retry", 0},
    {"Auto Practice", "auto-practice", 0},
    {"Safe Mode", "safe-mode", 0},
    {"Hitbox Viewer", "hitbox-viewer", 0},

    // PLAYER — 10
    {"Hide Player", "hide-player", 1},
    {"Hide Cube", "hide-cube", 1},
    {"Hide Trail", "hide-trail", 1},
    {"Hide Effects", "hide-effects", 1},
    {"No Glow", "no-glow", 1},
    {"No Particles", "no-particles", 1},
    {"No Death Effect", "no-death-effect", 1},
    {"No Respawn Effect", "no-respawn-effect", 1},
    {"Player Scale", "player-scale", 1},
    {"Player Color", "player-color", 1},

    // SPEED — 8
    {"Speedhack", "speedhack", 2},
    {"Slow Motion", "slow-motion", 2},
    {"Fast Motion", "fast-motion", 2},
    {"Custom Speed", "custom-speed", 2},
    {"Speed Slider", "speed-slider", 2},
    {"Frame Advance", "frame-advance", 2},
    {"Time Scale", "time-scale", 2},
    {"Freeze Game", "freeze-game", 2},

    // BOT & REPLAY — 10
    {"ReplayBot2", "replaybot2", 3},
    {"Auto Click", "auto-click", 3},
    {"Clickbot", "clickbot", 3},
    {"Record Inputs", "record-inputs", 3},
    {"Playback Inputs", "playback-inputs", 3},
    {"Save Replay", "save-replay", 3},
    {"Load Replay", "load-replay", 3},
    {"Replay Speed", "replay-speed", 3},
    {"Frame Step", "frame-step", 3},
    {"Auto Complete", "auto-complete", 3},

    // VISUALS — 10
    {"Show FPS", "show-fps", 4},
    {"Show CPS", "show-cps", 4},
    {"Show Hitboxes", "show-hitboxes", 4},
    {"Show Trajectory", "show-trajectory", 4},
    {"Show Icons", "show-icons", 4},
    {"Show Attempts", "show-attempts", 4},
    {"Show Progress", "show-progress", 4},
    {"RGB Menu", "rgb-menu", 4},
    {"Custom Menu Theme", "custom-menu-theme", 4},
    {"Transparent Menu", "transparent-menu", 4},

    // OTHER — 14
    {"Unlock Icons", "unlock-icons", 5},
    {"Unlock Colors", "unlock-colors", 5},
    {"Unlock Trails", "unlock-trails", 5},
    {"Unlock Death Effects", "unlock-death-effects", 5},
    {"No Mirror", "no-mirror", 5},
    {"No Wave Trail", "no-wave-trail", 5},
    {"No Camera Shake", "no-camera-shake", 5},
    {"No Blur", "no-blur", 5},
    {"No Particles Limit", "no-particles-limit", 5},
    {"Custom Music", "custom-music", 5},
    {"Custom Background", "custom-background", 5},
    {"Menu Position", "menu-position", 5},
    {"Save Settings", "save-settings", 5},
    {"Reset Settings", "reset-settings", 5}
}};

static constexpr const char* CATEGORIES[] = {
    "GAME",
    "PLAYER",
    "SPEED",
    "BOT",
    "VISUAL",
    "OTHER"
};

static std::array<bool, 67> enabledFeatures{};

class MaxCheatPanel : public CCLayerColor {
protected:
    int m_category = 0;
    CCMenu* m_featureMenu = nullptr;

    void rebuildFeatures() {
        if (m_featureMenu) {
            m_featureMenu->removeFromParentAndCleanup(true);
            m_featureMenu = nullptr;
        }

        m_featureMenu = CCMenu::create();
        m_featureMenu->setPosition(CCPointZero);
        this->addChild(m_featureMenu, 5);

        auto win = CCDirector::get()->getWinSize();
        int row = 0;

        for (int i = 0; i < 67; i++) {
            if (FEATURES[i].category != m_category)
                continue;

            std::string text = std::string(FEATURES[i].name)
                + (enabledFeatures[i] ? "  [ON]" : "  [OFF]");

            auto label = CCLabelBMFont::create(
                text.c_str(),
                "bigFont.fnt"
            );

            if (!label) continue;

            label->setScale(0.55f);

            auto item = CCMenuItemLabel::create(
                label,
                this,
                menu_selector(MaxCheatPanel::onFeature)
            );

            if (!item) continue;

            item->setTag(i);
            item->setPosition(
                win.width / 2,
                win.height / 2 + 125 - row * 23
            );

            m_featureMenu->addChild(item);
            row++;
        }
    }

public:
    static MaxCheatPanel* create() {
        auto ret = new MaxCheatPanel();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() override {
        auto win = CCDirector::get()->getWinSize();

        if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 175)))
            return false;

        this->setContentSize(win);

        // Main panel
        float panelWidth = std::min(560.0f, win.width - 30.0f);
        float panelHeight = std::min(560.0f, win.height - 30.0f);

        auto background = CCLayerColor::create(
            ccc4(25, 29, 42, 250)
        );

        background->setContentSize(
            CCSize(panelWidth, panelHeight)
        );

        background->setPosition(
            (win.width - panelWidth) / 2,
            (win.height - panelHeight) / 2
        );

        this->addChild(background, 1);

        // Title
        auto title = CCLabelBMFont::create(
            "MAX CHEAT PRO",
            "bigFont.fnt"
        );

        title->setScale(0.85f);
        title->setPosition(
            win.width / 2,
            win.height / 2 + 225
        );

        this->addChild(title, 3);

        // Close button
        auto closeLabel = CCLabelBMFont::create(
            "X",
            "bigFont.fnt"
        );

        auto closeButton = CCMenuItemLabel::create(
            closeLabel,
            this,
            menu_selector(MaxCheatPanel::onClose)
        );

        auto closeMenu = CCMenu::create(closeButton, nullptr);
        closeMenu->setPosition(
            win.width / 2 + panelWidth / 2 - 30,
            win.height / 2 + panelHeight / 2 - 30
        );

        this->addChild(closeMenu, 10);

        // Category buttons
        auto categoryMenu = CCMenu::create();
        categoryMenu->setPosition(CCPointZero);
        this->addChild(categoryMenu, 5);

        float startX = win.width / 2 - 150;

        for (int i = 0; i < 6; i++) {
            auto label = CCLabelBMFont::create(
                CATEGORIES[i],
                "bigFont.fnt"
            );

            label->setScale(0.42f);

            auto button = CCMenuItemLabel::create(
                label,
                this,
                menu_selector(MaxCheatPanel::onCategory)
            );

            button->setTag(i);
            button->setPosition(
                startX + i * 60,
                win.height / 2 + 175
            );

            categoryMenu->addChild(button);
        }

        rebuildFeatures();

        return true;
    }

    void onCategory(CCObject* sender) {
        MaxCheat::playClickSound();

        auto item = static_cast<CCMenuItemLabel*>(sender);
        m_category = item->getTag();

        rebuildFeatures();
    }

    void onFeature(CCObject* sender) {
        MaxCheat::playClickSound();

        auto item = static_cast<CCMenuItemLabel*>(sender);
        int index = item->getTag();

        if (index < 0 || index >= 67)
            return;

        enabledFeatures[index] = !enabledFeatures[index];

        rebuildFeatures();
    }

    void onClose(CCObject*) {
        MaxCheat::playClickSound();
        this->removeFromParentAndCleanup(true);
    }
};

class $modify(MaxCheatFloatingButton, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto win = CCDirector::get()->getWinSize();

        auto label = CCLabelBMFont::create(
            "MAX",
            "bigFont.fnt"
        );

        label->setScale(0.65f);

        auto button = CCMenuItemLabel::create(
            label,
            this,
            menu_selector(MaxCheatFloatingButton::openMaxMenu)
        );

        auto menu = CCMenu::create(button, nullptr);
        menu->setPosition(CCPointZero);

        button->setPosition(
            win.width - 45,
            win.height - 65
        );

        this->addChild(menu, 100);

        return true;
    }

    void openMaxMenu(CCObject*) {
        MaxCheat::playClickSound();

        auto scene = CCDirector::get()->getRunningScene();

        if (!scene)
            return;

        auto panel = MaxCheatPanel::create();

        if (panel)
            scene->addChild(panel, 9999);
    }
};

}
