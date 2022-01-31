# FingerprintDoorbell FAQ

## What is FingerprintDoorbell?
It's more or less a doorbell with the ability to scan finger prints or a fingerprint reader with the ability to act as doorbell, depending on your perspective ;-). But lets speak some images:

<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/doorbell-sample.jpg"  width="400">

<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/web-manage.png"  width="400">
<img  src="https://raw.githubusercontent.com/frickelzeugs/FingerprintDoorbell/master/doc/images/web-settings.png"  width="400">

## How does it work?
If you put your finger on the sensor the system looks for a matching fingerprint. If it doesn't find one, it rings the bell (MQTT message is published and an GPIO pin is set to high). If a match was found, the matching finger ID together with a name and confidence will be published as MQTT messagage. In combination with a home automation solution (like OpenHAB, ioBroker, Home Assistant...) you can then trigger your door opener or smart lock. If this is not enough you can also define actions depending on the finger that was detected, like left thumb opens front door, right thunb opens garage an so on.

  

## What do I need?
- fingerprint reader Grow R503 (https://de.aliexpress.com/i/33053783539.html)
- an ESP32 microcontroller (I would prefer the mini-version: https://de.aliexpress.com/item/1005001621844145.html)

...to be continued