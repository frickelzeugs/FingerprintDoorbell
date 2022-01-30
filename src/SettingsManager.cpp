#include "SettingsManager.h"

void SettingsManager::loadWifiSettings() {
    Preferences preferences;
    preferences.begin("wifiSettings", true); 
    wifiSettings.ssid = preferences.getString("ssid", String(""));
    wifiSettings.password = preferences.getString("password", String(""));
    wifiSettings.hostname = preferences.getString("hostname", String("FingerprintDoorbell"));
    preferences.end();
}

void SettingsManager::loadAppSettings() {
    Preferences preferences;
    preferences.begin("appSettings", true); 
    appSettings.mqttServer = preferences.getString("mqttServer", String(""));
    appSettings.mqttUsername = preferences.getString("mqttUsername", String(""));
    appSettings.mqttPassword = preferences.getString("mqttPassword", String(""));
    appSettings.mqttRootTopic = preferences.getString("mqttRootTopic", String("fingerprintDoorbell"));
    appSettings.ntpServer = preferences.getString("ntpServer", String("pool.ntp.org"));
    preferences.end();
}
   
void SettingsManager::saveWifiSettings() {
    Preferences preferences;
    preferences.begin("wifiSettings", false); 
    preferences.putString("ssid", wifiSettings.ssid);
    preferences.putString("password", wifiSettings.password);
    preferences.putString("hostname", wifiSettings.hostname);
    preferences.end();
}

void SettingsManager::saveAppSettings() {
    Preferences preferences;
    preferences.begin("appSettings", false); 
    preferences.putString("mqttServer", appSettings.mqttServer);
    preferences.putString("mqttUsername", appSettings.mqttUsername);
    preferences.putString("mqttPassword", appSettings.mqttPassword);
    preferences.putString("mqttRootTopic", appSettings.mqttRootTopic);
    preferences.putString("ntpServer", appSettings.ntpServer);
    preferences.end();
}

WifiSettings SettingsManager::getWifiSettings() {
    return wifiSettings;
}

void SettingsManager::setWifiSettings(WifiSettings newSettings) {
    wifiSettings = newSettings;
    saveWifiSettings();
}

AppSettings SettingsManager::getAppSettings() {
    return appSettings;
}

void SettingsManager::setAppSettings(AppSettings newSettings) {
    appSettings = newSettings;
    saveAppSettings();
}

bool SettingsManager::isWifiConfigured() {
    if (wifiSettings.ssid.isEmpty() || wifiSettings.password.isEmpty())
        return false;
    else
        return true;
}
