#include "Geode/cocos/CCDirector.h"
#include "../EyeStrainHelper.hpp"
#include <Geode/Enums.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/binding/GameLevelManager.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include <Geode/binding/PlayLayer.hpp>

using namespace geode::prelude;

#ifdef INSTANT_DEBUG_LEVEL
class $modify(MenuLayer) {
    void onPlay(CCObject* sender) {
        auto levelManager = GameLevelManager::sharedState();
        auto debugLevel = levelManager->getSavedLevel(INSTANT_DEBUG_LEVEL_ID);
        debugLevel->m_difficulty = GJDifficulty::Auto;
        auto playLayer = PlayLayer::scene(debugLevel, false);
        auto ccDirector = CCDirector::sharedDirector();
        ccDirector->replaceScene(playLayer);
    }
};
#endif