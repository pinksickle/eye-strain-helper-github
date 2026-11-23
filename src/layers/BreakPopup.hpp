#pragma once
#include "../EyeStrainHelper.hpp"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/ui/Button.hpp"
#include "Geode/ui/Layout.hpp"
#include "Geode/ui/Popup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <fmt/format.h>

using namespace geode::prelude;
using namespace eyestrainhelper;

class BreakPopup : public geode::Popup {
    protected:
        CCLabelBMFont* countdownLabel = nullptr;

        std::string formattedTimeLeft() {
            long timeLeft = StateManager::get()->getTimeLeft();
            int64_t minutesLeft = timeLeft / 60;
            int64_t remainderSeconds = timeLeft % 60;
            if(remainderSeconds >= 10) {
                return fmt::format("{}:{}", minutesLeft, timeLeft % 60);
            } else {
                return fmt::format("{}:0{}", minutesLeft, timeLeft % 60);
            }
        }

        bool init() override { 
            auto stateManager = StateManager::get();
            if (!Popup::init(340.f, 210.f)) return false;

            this->setID("BreakPopup"_spr);
            this->setTitle("look at a point far in the distance");

            m_mainLayer->removeChildByID("background");
            m_mainLayer->removeChildByID("close-button");

            countdownLabel = CCLabelBMFont::create(formattedTimeLeft().c_str(), "bigFont.fnt");
            countdownLabel->setID("countdown"_spr);
            m_mainLayer->addChildAtPosition(countdownLabel, Anchor::Center);
            if(Settings::allowSkipping() && (Settings::maxSkips() > stateManager->getBreaksSinceSkip() || !Settings::limitSkipping())) {
                auto skipButtonSprite = ButtonSprite::create("Skip", "goldFont.fnt", "GE_button_05.png"_spr);
                auto skipButton = Button::createWithNode(skipButtonSprite,[this](Button* sender) {
                    StateManager::get()->skipBreak(); 
                    onClose(this);
                });
                skipButton->setID("skipButton"_spr);
                m_mainLayer->addChildAtPosition(skipButton, Anchor::Bottom);
            }

            if(Settings::limitSkipping()) {
                auto remainingSkipsLabel = CCLabelBMFont::create(fmt::format("Skipped {}/{} breaks in a row", stateManager->getBreaksSinceSkip(), Settings::maxSkips()).c_str(), "chatFont.fnt");
                remainingSkipsLabel->setID("remainingSkips"_spr);
                remainingSkipsLabel->m_obContentSize *= 0.9;
                m_mainLayer->addChildAtPosition(remainingSkipsLabel, Anchor::Bottom, CCPoint(0.0,35.0));
            }

            return true;
        }

    public:
        static BreakPopup* create() {
            auto ret = new BreakPopup();
            if(ret->init()) {
                ret->autorelease();
                return ret;
            }

            delete ret;
            return nullptr;
        }

        void update() {
            auto stateManager = StateManager::get();
            stateManager->updateBreak();
            if(stateManager->getBreakState() == BreakState::None) {
                onClose(this);
            } else if(countdownLabel != nullptr) {
                countdownLabel->setCString(formattedTimeLeft().c_str());
            }
        }

        void onClose(CCObject *) override {
            if(StateManager::get()->getBreakState() == BreakState::None) {
                removeMeAndCleanup();
                countdownLabel->autorelease();
                delete countdownLabel;
            }
        }
};