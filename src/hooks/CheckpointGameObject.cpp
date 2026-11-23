#include "../EyeStrainHelper.hpp"
#include "Geode/modify/Modify.hpp"
#include <Geode/binding/CheckpointGameObject.hpp>
#include <Geode/modify/CheckpointGameObject.hpp>

using namespace geode::prelude;
using namespace eyestrainhelper;

class $modify(CheckpointGameObject) {
    
    void triggerObject(GJBaseGameLayer* layer, int uniqueID, std::vector<int> const* remapKeys) {
        CheckpointGameObject::triggerObject(layer, uniqueID, remapKeys);
        auto stateManager = StateManager::get();
        #ifdef BREAK_EVERY_CHECKPOINT
        if(Settings::breakAtCheckpoints()) {
            stateManager->startBreak(BreakLocation::Gameplay);
        }
        #else
        if(stateManager->getBreakState() == BreakState::Armed && Settings::breakAtCheckpoints()) {
            stateManager->startBreak(BreakLocation::Gameplay);
        }
        #endif
    }
};