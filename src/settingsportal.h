#pragma once

#include "base/dbus.h"

#include <cstdint>
#include <string>

class SettingsPortal
{
public:
    // `servicesConfig` is properdesktop-services' settings file, read once for
    // the dark mode until the live value arrives.
    SettingsPortal(properdesktop::base::dbus::Connection *bus, const std::string &servicesConfig);

    bool publish();

    uint32_t version() const { return 1; }

private:
    void readAll(properdesktop::base::dbus::MethodCall &call) const;
    void read(properdesktop::base::dbus::MethodCall &call) const;
    void setDarkMode(bool darkMode);
    void refreshAppearance();

    properdesktop::base::dbus::Connection *m_bus;
    properdesktop::base::dbus::Object m_object;
    properdesktop::base::dbus::Proxy m_appearance;
    properdesktop::base::dbus::Match m_darkModeChanged;
    properdesktop::base::dbus::NameWatch m_appearanceOwner;
    properdesktop::base::dbus::PendingCall m_refresh;
    uint32_t m_colorScheme = 2;
};
