#include "../EyeStrainHelper.hpp"
#include "Geode/modify/Modify.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;
using namespace eyestrainhelper;

class $modify(PlayLayer) {
    void onExit() {
        auto stateManager = StateManager::get();
        if(stateManager->getBreakState() == BreakState::Active) {
            stateManager->endBreak();
        }
        PlayLayer::onExit();
    }

    void resetLevel() {
        auto stateManager = StateManager::get();
        if(stateManager->getBreakState() == BreakState::Armed) {
            stateManager->startBreak(BreakLocation::Gameplay);
        }
        PlayLayer::resetLevel();
    }

    void resetLevelFromStart() {
        auto stateManager = StateManager::get();
        if(stateManager->getBreakState() == BreakState::Armed) {
            stateManager->startBreak(BreakLocation::Gameplay);
        }
        PlayLayer::resetLevelFromStart();
    }

    void pauseGame(bool unfocused) {
        auto stateManager = StateManager::get();
        if(stateManager->getBreakState() != BreakState::Active) {
            PlayLayer::pauseGame(unfocused);
        }
    }
};