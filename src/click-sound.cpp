
#include <Geode/Geode.hpp>
#include <Geode/fmod/fmod.hpp>
#include <algorithm>
#include <string>

using namespace geode::prelude;

namespace MaxCheat {

namespace {
    FMOD::Sound* clickSound = nullptr;
    std::string loadedPath;

    void unloadSound() {
        if (clickSound) {
            clickSound->release();
            clickSound = nullptr;
        }
        loadedPath.clear();
    }
}

// Загружает выбранный пользователем MP3
void loadClickSound() {
    auto path = Mod::get()->getSettingValue<
        std::filesystem::path
    >("custom-click");

    if (path.empty()) {
        unloadSound();
        return;
    }

    auto filePath =
        geode::utils::string::pathToString(path);

    if (filePath == loadedPath && clickSound)
        return;

    unloadSound();

    auto engine = FMODAudioEngine::sharedEngine();

    if (!engine || !engine->m_system) {
        log::error("FMOD system unavailable");
        return;
    }

    FMOD_RESULT result = engine->m_system->createSound(
        filePath.c_str(),
        FMOD_DEFAULT,
        nullptr,
        &clickSound
    );

    if (result != FMOD_OK) {
        clickSound = nullptr;
        log::error("Failed to load MP3: {}", filePath);
        return;
    }

    loadedPath = filePath;
    log::info("Custom click sound loaded!");
}

// Воспроизведение клика
void playClickSound() {
    if (!Mod::get()->getSettingValue<bool>("click-sound"))
        return;

    loadClickSound();

    if (!clickSound)
        return;

    auto engine = FMODAudioEngine::sharedEngine();

    if (!engine || !engine->m_system)
        return;

    FMOD::Channel* channel = nullptr;

    auto result = engine->m_system->playSound(
        clickSound,
        nullptr,
        false,
        &channel
    );

    if (result != FMOD_OK || !channel)
        return;

    auto volume = Mod::get()->getSettingValue<int64_t>(
        "click-volume"
    );

    float normalizedVolume = std::clamp(
        static_cast<float>(volume) / 100.0f,
        0.0f,
        0.8f
    );

    channel->setVolume(normalizedVolume);
}

// Для кнопки предварительного прослушивания
void previewClickSound() {
    playClickSound();
}

}
