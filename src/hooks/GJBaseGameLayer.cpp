#include "../EyeStrainHelper.hpp"
#include "../layers/BreakPopup.hpp"
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;
using namespace eyestrainhelper;

class $modify(ESHBaseGameLayer, GJBaseGameLayer) {
    struct Fields {
        BreakPopup* breakPopup = nullptr;
    };

    void update(float dt) {
        auto stateManager = StateManager::get();
        if(stateManager->getBreakState() == BreakState::Active) {
            if(m_fields->breakPopup != nullptr) {
                m_fields->breakPopup->update();
            }
        } else {
            GJBaseGameLayer::update(dt);
        }
    }
};