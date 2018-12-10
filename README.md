# MQTT thermometer 

This is a DHT11 thermometer program that does following things:

 * Connects to configured wifi network
 * Sets up the time using NTP servers
 * In loop
   * takes temperature and humidity values using DHT11 sensor
   * sends those values to a configured MQTT topic
