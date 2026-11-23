#include "../EyeStrainHelper.hpp"
#include "Geode/loader/Log.hpp"
#include "Geode/modify/Modify.hpp"
#include "Geode/ui/Notification.hpp"
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/binding/GJBaseGameLayer.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;
using namespace eyestrainhelper;

class $modify(PlayerObject) {
    void playerDestroyed(bool noEffects) {
        if(isVanillaPlayer()) {
            auto stateManager = eyestrainhelper::StateManager::get();
            #ifdef BREAK_EVERY_ATTEMPT
            stateManager->startBreak(BreakLocation::Gameplay);
            #else
            if(stateManager->getBreakState() == BreakState::Armed) {
                stateManager->startBreak(BreakLocation::Gameplay);
            }
            #endif
        }
        PlayerObject::playerDestroyed(noEffects);
    }

    void update(float dt) {
        if(isVanillaPlayer()) {
                auto stateManager = eyestrainhelper::StateManager::get();
                if(stateManager->getBreakState() == BreakState::None && stateManager->getTimeSinceBreak() >= Settings::timeBetweenBreaks()*60) {
                if(PlayLayer::get()->m_level->m_autoLevel && Settings::breakDuringAutos()) {
                    stateManager->startBreak(BreakLocation::Gameplay);
                } else {
                    stateManager->armBreak();
                }
            
            }
        }
        PlayerObject::update(dt);
    }
    
};