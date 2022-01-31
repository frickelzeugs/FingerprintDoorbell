# FingerprintDoorbell FAQ

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

...to be continued

# How to build it
## Wiring
<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/wiring.png"  width="500">

I would not solder the cables directly to the ESP32 but recommend using a connector between ESP32 and Sensor. Otherwise, the cables must first be fed through the 25mm hole for the sensor and then soldered on. Replacing the Sensor will be a pain then. The original plug used on the sensor is a 6-pin Micro JST SH 1.00mm but it'll be fine to use any other 6-pin connector that you have on hand if you replace both sides.


