#include "SettingsManager.h"
#include <Crypto.h>

bool SettingsManager::loadWifiSettings() {
    Preferences preferences;
    if (preferences.begin("wifiSettings", true)) {
        wifiSettings.ssid = preferences.getString("ssid", String(""));
        wifiSettings.password = preferences.getString("password", String(""));
        wifiSettings.hostname = preferences.getString("hostname", String("FingerprintDoorbell"));
        preferences.end();
        return true;
    } else {
        return false;
    }
}

bool SettingsManager::loadAppSettings() {
    Preferences preferences;
    if (preferences.begin("appSettings", true)) {
        appSettings.mqttServer = preferences.getString("mqttServer", String(""));
        appSettings.mqttUsername = preferences.getString("mqttUsername", String(""));
        appSettings.mqttPassword = preferences.getString("mqttPassword", String(""));
        appSettings.mqttRootTopic = preferences.getString("mqttRootTopic", String("fingerprintDoorbell"));
        appSettings.ntpServer = preferences.getString("ntpServer", String("pool.ntp.org"));
        appSettings.sensorPin = preferences.getString("sensorPin", "00000000");
        appSettings.sensorPairingCode = preferences.getString("pairingCode", "");
        appSettings.sensorPairingValid = preferences.getBool("pairingValid", false);
        appSettings.touchRingActiveColor = preferences.getShort("ringActCol", 2);
        appSettings.touchRingActiveSequence = preferences.getShort("ringActSeq", 1);
        appSettings.scanColor = preferences.getShort("scanColor", 1);
        appSettings.matchColor = preferences.getShort("matchColor", 3);
        preferences.end();
        return true;
    } else {
        return false;
    }
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
    preferences.putString("sensorPin", appSettings.sensorPin);
    preferences.putString("pairingCode", appSettings.sensorPairingCode);
    preferences.putBool("pairingValid", appSettings.sensorPairingValid);
    preferences.putShort("ringActCol", appSettings.touchRingActiveColor);
    preferences.putShort("ringActSeq", appSettings.touchRingActiveSequence);
    preferences.putShort("scanColor", appSettings.scanColor);
    preferences.putShort("matchColor", appSettings.matchColor);
    preferences.end();
}

WifiSettings SettingsManager::getWifiSettings() {
    return wifiSettings;
}

void SettingsManager::saveWifiSettings(WifiSettings newSettings) {
    wifiSettings = newSettings;
    saveWifiSettings();
}

AppSettings SettingsManager::getAppSettings() {
    return appSettings;
}

void SettingsManager::saveAppSettings(AppSettings newSettings) {
    appSettings = newSettings;
    saveAppSettings();
}

bool SettingsManager::isWifiConfigured() {
    if (wifiSettings.ssid.isEmpty() || wifiSettings.password.isEmpty())
        return false;
    else
        return true;
}

bool SettingsManager::deleteAppSettings() {
    bool rc;
    Preferences preferences;
    rc = preferences.begin("appSettings", false); 
    if (rc)
        rc = preferences.clear();
    preferences.end();
    return rc;
}

bool SettingsManager::deleteWifiSettings() {
    bool rc;
    Preferences preferences;
    rc = preferences.begin("wifiSettings", false); 
    if (rc)
        rc = preferences.clear();
    preferences.end();
    return rc;
}

String SettingsManager::generateNewPairingCode() {

    /* Create a SHA256 hash */
    SHA256 hasher;

    /* Put some unique values as input in our new hash */
    hasher.doUpdate( String(esp_random()).c_str() ); // random number
    hasher.doUpdate( String(millis()).c_str() ); // time since boot
    hasher.doUpdate(getTimestampString().c_str()); // current time (if NTP is available)
    hasher.doUpdate(appSettings.mqttUsername.c_str());
    hasher.doUpdate(appSettings.mqttPassword.c_str());
    hasher.doUpdate(wifiSettings.ssid.c_str());
    hasher.doUpdate(wifiSettings.password.c_str());

    /* Compute the final hash */
    byte hash[SHA256_SIZE];
    hasher.doFinal(hash);
    
    // Convert our 32 byte hash to 32 chars long hex string. When converting the entire hash to hex we would need a length of 64 chars.
    // But because we only want a length of 32 we only use the first 16 bytes of the hash. I know this will increase possible collisions,
    // but for detecting a sensor replacement (which is the use-case here) it will still be enough.
    char hexString[33];
    hexString[32] = 0; // null terminatation byte for converting to string later
    for (byte i=0; i < 16; i++) // use only the first 16 bytes of hash
    {
        sprintf(&hexString[i*2], "%02x", hash[i]);
    }

    return String((char*)hexString);
}

