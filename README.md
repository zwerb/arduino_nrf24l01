# Arduino Wireless Communications using Arduino Nano and NRF24L01+ Modules (and a DHT11 Temperature Sensor)

This is an (in-progress) microcontroller project where two Arduino Nano boards communicate basic information over 2.4 GHz wireless communications. The boards communicate via NRF24L01+ modules on 2.4 GHz which is a Wi-Fi band, but these communicate directly using a library command radio.write(&text, sizeof(text)); which feels more like serial communication protocol rather than connecting to a Wi-Fi network and using some higher level communication.
