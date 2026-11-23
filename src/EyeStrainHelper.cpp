#include "EyeStrainHelper.hpp"
#include "layers/BreakPopup.hpp"
#include "hooks/GJBaseGameLayer.cpp"
#include <Geode/binding/GJBaseGameLayer.hpp>
#include <Geode/binding/PlayLayer.hpp>

using namespace eyestrainhelper;

long StateManager::calcNow() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void StateManager::updateBreak() {
    if(getTimeLeft() <= 0) {
        StateManager::endBreak();
        StateManager::skipsSinceBreak = 0;
    }
}

void StateManager::startBreak(BreakLocation location) {
    breakStartTime = StateManager::calcNow();
    auto breakPopup = BreakPopup::create();
    breakPopup->show();
    StateManager::breakLocation = location;
    if(location == BreakLocation::Gameplay) {
        static_cast<ESHBaseGameLayer*>(GJBaseGameLayer::get())->m_fields->breakPopup = breakPopup;
        // PlayLayer::get()->pauseAudio();
    } else {
        // TODO: Implement editor breaks!
    }

    StateManager::breaksThisSession++;
    StateManager::breakState = BreakState::Active;
}

void StateManager::endBreak() {
    StateManager::lastBreakTimestamp = StateManager::calcNow();
    StateManager::breakState = BreakState::None;
    if(StateManager::breakLocation == BreakLocation::Gameplay) {
        PlayLayer::get()->resumeAudio();
        FMODAudioEngine::sharedEngine()->playEffectAsync("break_over.ogg"_spr);
        if(Settings::pauseAfterBreak()) {
            PlayLayer::get()->pauseGame(false);
        }
    }
}

void StateManager::skipBreak() {
    StateManager::skipsSinceBreak++;
    StateManager::endBreak();
}