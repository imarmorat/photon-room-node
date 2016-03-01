# photon-room-node

The aim of this project is to build a range of sensors around the house to monitor various measurements.
Currently it is using the Particle Photon (https://www.particle.io/).
The photon gets the following values:
- temperature, humidity and pressure from a BME-280
- smoke, CO and LPG levels from a MQ-2

A ILI9341 display allows for generic and more details view of each sensor.

An alerting system allows for IFTTT extension; each measurement can define a Warning and Critical zone which will be checked each time a measurement collection is done. 
An overall "alarm" status is computed from all the measurements; if any warning or critical measurement found, the display will alert the user and display which sensor shows worrying values.

As the Particle Photon dashboard does not have anything fancy yet, I am using a raspberry pi to hostsInfluxDb and Grafana (see http://padcom13.blogspot.co.uk/2015/12/influxdb-telegraf-and-grafana-on.html for prebuild packages). Because InfluxDB is progressively phasing out JSon for performance reasons, I am sending values through UDP (REST under photon is cumbersome at the time of writting).
WebHooks could have been an option but the current implementation does not allow for free format and means having a roundtrip local-network to web to local-network that is unnecessary.

# dependencies
Please not that the Adafruit_BME280 and Adafruit_SSD1306 used are the following as needed to be adapted to the Photon
- https://github.com/mhaack/Adafruit_BME280_Library
- https://github.com/imarmorat/Adafruit_ILI9341 (forked to accommodate to Photon linked constraints)
- Adafruit_mfGFX library

# external licences
Icons used are licensed, please look at the Icons directory for more information

