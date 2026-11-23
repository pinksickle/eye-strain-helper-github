#pragma once

using namespace geode::prelude;

class Settings {
    public:
        static int64_t shortBreakDuration() { return geode::getMod()->getSettingValue<int64_t>("shortBreakDuration"); }
        static int64_t longBreakDuration() { return geode::getMod()->getSettingValue<int64_t>("longBreakDuration"); }
        static float timeBetweenBreaks() { return geode::getMod()->getSettingValue<float>("timeBetweenBreaks"); }
        static bool breakAtCheckpoints() { return geode::getMod()->getSettingValue<bool>("breakAtCheckpoints"); }
        static bool breakDuringAutos() { return geode::getMod()->getSettingValue<bool>("breakDuringAutos"); }
        static bool allowSkipping() { return geode::getMod()->getSettingValue<bool>("allowSkipping"); }
        static bool limitSkipping() { return geode::getMod()->getSettingValue<bool>("limitSkipping"); }
        static int64_t maxSkips() { return geode::getMod()->getSettingValue<int64_t>("maxSkips"); }
        static bool pauseAfterBreak() { return geode::getMod()->getSettingValue<bool>("pauseAfterBreak"); }
};