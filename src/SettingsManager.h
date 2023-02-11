#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <Preferences.h>
#include "global.h"

struct WifiSettings {    
    String ssid = "";
    String password = "";
    String hostname = "";
};

struct AppSettings {
    String mqttServer = "";
    String mqttUsername = "";
    String mqttPassword = "";
    String mqttRootTopic = "fingerprintDoorbell";
    String ntpServer = "pool.ntp.org";
    String sensorPin = "00000000";
    String sensorPairingCode = "";
    int8_t touchRingActiveColor = 2;
    int8_t touchRingActiveSequence = 1;
    int8_t scanColor = 1;
    int8_t matchColor = 3;
    bool   sensorPairingValid = false;
};

class SettingsManager {       
  private:
    WifiSettings wifiSettings;
    AppSettings appSettings;

    void saveWifiSettings();
    void saveAppSettings();

  public:
    bool loadWifiSettings();
    bool loadAppSettings();

    WifiSettings getWifiSettings();
    void saveWifiSettings(WifiSettings newSettings);
    
    AppSettings getAppSettings();
    void saveAppSettings(AppSettings newSettings);

    bool isWifiConfigured();

    bool deleteAppSettings();
    bool deleteWifiSettings();

    String generateNewPairingCode();

};

#endif