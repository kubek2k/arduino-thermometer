# MQTT thermometer 

This is a DHT11 thermometer program that does following things:

 * Connects to configured wifi network
 * Sets up the time using NTP servers
 * In loop
   * takes temperature and humidity values using DHT11 sensor
   * sends those values to a configured MQTT topic

# Builing 

To build this you need a configured https://github.com/plerup/makeEspArduino file. Additionally you need to provide 
a config file with defines required for building. The build should look more or less like this:
```
CONFIG_FILE=config-living-room.h make flash 
```
