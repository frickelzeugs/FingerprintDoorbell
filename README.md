# FingerprintDoorbell

## What is FingerprintDoorbell?
It's more or less a doorbell with the ability to scan finger prints or a fingerprint reader with the ability to act as doorbell, depending on your perspective ;-). But lets speak some images:

<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/doorbell-sample.jpg"  width="400">

<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/web-manage.png"  width="600">
<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/web-settings.png"  width="600">

## How does it work?
If you put your finger on the sensor the system looks for a matching fingerprint. If it doesn't find one, it rings the bell (MQTT message is published and an GPIO pin is set to high). If a match was found, the matching finger ID together with a name and confidence will be published as MQTT messagage. In combination with a home automation solution (like OpenHAB, ioBroker, Home Assistant...) you can then trigger your door opener or smart lock. You can also define actions depending on the finger that was detected, like left thumb opens front door, right thumb opens garage, middle finger...

  

## What do I need?
- fingerprint reader Grow R503 (available at https://de.aliexpress.com/i/33053783539.html)
- an ESP32 microcontroller (I would prefer the mini-version, because of it's compact size, e.g. available here https://de.aliexpress.com/item/1005001621844145.html or from any other dealer of your trust)

# How to build the hardware
## Wiring
<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/wiring.png"  >

I would not solder the cables directly to the ESP32 but recommend using a connector between ESP32 and Sensor. Otherwise, the cables must first be fed through the 25mm hole for the sensor and then soldered on. Replacing the Sensor will be a pain then. The original plug used on the sensor is a 6-pin Micro JST SH 1.00mm but it'll be fine to use any other 6-pin connector that you have on hand if you replace both sides.

Just as an inpiration:

<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/esp32-shield.jpg"  width="300">

I made a small shield board for the ESP32 mini that contains a 6 pin Micro JST SH 1.00mm socket, a DC-DC step down converter and some screw terminals for the power supply (in my case 24V DC). So I'm now able to easily replace the sensor or ESP32 without touching my soldering iron.

# Flashing the firmware
## Method 1: use precompiled binaries
To flash the ESP32 with the precompiled binaries you can use the python based esptool from espressif. You'll need a running Python environment on your system, so get Python first here if you don't already have it: [Python download](https://www.python.org/downloads/)

After python is available run the following command in your shell/cmd to install esptool:
```
pip install esptool
```

Now esptool should be available in your shell/cmd. Check it by running:
```
esptool.py
```

Now that esptool.py is available you can continue to flash the firmware. To start you will need 5 files:

- bootloader_dio_40m.bin
- boot_app0.bin

download [here](https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/bootloader.zip)

- firmware.bin
- partitions.bin
- spiffs.bin

contained in the [Release packages](https://github.com/frickelzeugs/FingerprintDoorbell/releases)

### Flashing
Copy all 5 files in a local folder, open your command line/shell, navigate to this folder and execute:

```
esptool.py --chip esp32 --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader_dio_40m.bin 0x8000 partitions.bin 0xe000 boot_app0.bin 0x10000 firmware.bin 2686976 spiffs.bin
```

If everything has worked your output should look something like this:

```
esptool.py v3.2
Found 2 serial ports
Serial port COM4
Connecting....
Chip is ESP32-D0WDQ6 (revision 1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: 9c:9c:1f:c7:ac:a0
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 460800
Changed.
Configuring flash size...
Auto-detected Flash size: 4MB
Flash will be erased from 0x00001000 to 0x00005fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Flash will be erased from 0x0000e000 to 0x0000ffff...
Flash will be erased from 0x00010000 to 0x00121fff...
Flash will be erased from 0x00290000 to 0x003fffff...
Compressed 17104 bytes to 11191...
Wrote 17104 bytes (11191 compressed) at 0x00001000 in 0.6 seconds (effective 225.1 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 128...
Wrote 3072 bytes (128 compressed) at 0x00008000 in 0.1 seconds (effective 300.7 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds (effective 463.9 kbit/s)...
Hash of data verified.
Compressed 1119504 bytes to 666873...
Wrote 1119504 bytes (666873 compressed) at 0x00010000 in 16.1 seconds (effective 555.0 kbit/s)...
Hash of data verified.
Compressed 1507328 bytes to 36014...
Wrote 1507328 bytes (36014 compressed) at 0x00290000 in 7.5 seconds (effective 1599.3 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```

Your device should now boot up and the LED ring should start flashing slowly red ("breathing") to signal that it's currently in WiFi Config mode. Proceed with the configuration of the device.

## Method 2: build and flash with Visual Studio Code and PlattformIO
todo

# Configuration
## WiFi Connection
todo

## Enroll your fingerprints
todo

## Configure MQTT connection
todo

## Firmware Update
If you've managed to walk the bumpy path of flashing the firmware on the ESP32 for the first time, be calmed: every further firmware update will be a piece of cake. FingerprintDoorbell is using the really cool Library [AsyncElegantOTA](https://github.com/ayushsharma82/AsyncElegantOTA) to make this as handy as possible. You don't even have to pull the microcontroller out of the wall and connect it to your computer, because the "OTA" in "AsyncElegantOTA" is for "Over-the-air" updates. All you need to do is to browse to the settings page of the WebUI and hit "Firmware update". In the following Dialog you have to upload 2 files

- firmware.bin for the "Firmware" radio button
- spiffs.bin for the "Filesystem" radio button

Done. Reboot your system to get the new firmware live.

# FAQ
## What does the different colors/blinking styles of the LED ring mean?
|LED ring color| sequence | Meaning | 
| -------- | -------- | -------- |
| red | permanent | System is in error state |
| red | breathing | System in WiFi config mode |
| red | flashing  | Finger on sensor detected (no match found yet) |
| blue | permanent | System ready (touch ring disabled) |
| blue | breathing | System ready (touch ring enabled) |
| blue | flashing | System startup (not ready yet) |
| purple | solid | Fingerprint match found or when in enrollment mode this means pass is finished, lift your finger |
| purple | flashing | Enrollment active (waiting for finger) |
