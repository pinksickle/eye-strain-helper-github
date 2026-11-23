#pragma once

#include "utils/Singleton.hpp"
#include <cstdint>
#include <Geode/Geode.hpp>
#include "Settings.hpp"

//#define ESH_DEBUG_MODE

#ifdef ESH_DEBUG_MODE
    //#define INSTANT_DEBUG_LEVEL
    #ifdef INSTANT_DEBUG_LEVEL
        #define INSTANT_DEBUG_LEVEL_ID 152764593
    #endif
    //#define BREAK_EVERY_ATTEMPT
    #define BREAK_EVERY_CHECKPOINT
#endif

namespace eyestrainhelper {

enum BreakState {
    None = 0,
    Armed = 1,
    Active = 2
};

enum BreakLocation {
    Gameplay = 0,
    Editor = 1
};

class StateManager : public Singleton<StateManager> {
    protected:
        int8_t breakState = BreakState::None;
        long calcNow();
        long lastBreakTimestamp = calcNow();
        long breakStartTime = -1;
        BreakLocation breakLocation;
        int64_t skipsSinceBreak = 0;
        int64_t breaksThisSession = 0;
    public:
        int8_t getBreakState() const { return breakState; }
        void armBreak() { breakState = BreakState::Armed; }
        long getTimeSinceBreak() { return calcNow()-lastBreakTimestamp; }
        void startBreak(BreakLocation location);
        void updateBreak();
        void endBreak();
        void skipBreak();
        long getTimeLeft() { return Settings::shortBreakDuration()-(calcNow()-breakStartTime); }
        int64_t getSessionBreaks() const { return breaksThisSession; }
        int64_t getBreaksSinceSkip() const { return skipsSinceBreak; }
    };
}