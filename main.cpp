#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Zmienna przechowująca stan naszego Noclipa (włączony/wyłączony)
bool g_noclipEnabled = false;

// 1. DOWIĄZANIE DO MENU GŁÓWNEGO - Dodajemy przycisk
class $modify(MyNewMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Tworzymy przycisk w menu
        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"),
            this,
            menu_selector(MyNewMenu::onOpenModMenu)
        );

        auto menu = this->getChildByID("right-side-menu");
        if (menu) {
            menu->addChild(button);
            menu->updateLayout();
        }

        return true;
    }

    // Co robi przycisk po kliknięciu: przełącza Noclip i pokazuje komunikat
    void onOpenModMenu(CCObject*) {
        g_noclipEnabled = !g_noclipEnabled;

        std::string message = g_noclipEnabled ? "Noclip: WLACZONY!" : "Noclip: WYLACZONY!";
        FLAlertLayer::create("MOJE NOWE MOD MENU", message.c_ptr(), "OK")->show();
    }
};

// 2. LOGIKA GRY - Noclip
class $modify(MyNewPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        // Jeśli Noclip jest włączony, igorujemy zderzenie z przeszkodą
        if (g_noclipEnabled) {
            return;
        }
        PlayLayer::destroyPlayer(player, object);
    }
};
