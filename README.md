# Clone your remote app for the Cardputer

The app is intended to work with any generic IR receiver module for the Arduino. You don't even need to have it wired with GROVE connector. 
You can just wire it yourself with the jumper wires according to the module pinout. Attach signal pin to G1 pin of the GROVE port.

## Docs

### Supported IR protocols

- All that [IRRemote](https://github.com/Arduino-IRremote/Arduino-IRremote) library supports 

### Current features

- Read signals from your remote. (All of that you read is stored in the array for the later send and limited to 42 entries).
- Send signals that were read before.
- Copy your remote to the SD card folder
- Load copied remote from the SD card
- Check Cardputer battery status
- Settings (currently empty)

### Development status

- This is a very raw app version and tested only with a Samsung TV remote. Let's assume it's alpha 0.0.1

---

## Roadmap

- Improve save remote process and screens
- Add StampS3 internal LED indication for the battery
- Implement settings
- Test more remotes


Sincerely yours, 

Warko
