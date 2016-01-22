#include "application.h"
#include "DataPublisher.h"

InfluxDBDataPublisher::InfluxDBDataPublisher(IPAddress ipAddress, UDP * udpClient, unsigned int udpPort, String dbName)
{
	_udpAddress = ipAddress;
	_udpClient = udpClient;
	_udpPort = udpPort;
	_dbName = dbName;
	_deviceId = "monkey01";// System.deviceID();
}

void InfluxDBDataPublisher::init()
{
	_udpClient->begin(8888);
}

void InfluxDBDataPublisher::publish(String metricName, float value)
{
	_udpClient->beginPacket(_udpAddress, _udpPort);
	_udpClient->write(String::format("%s,device=%s,sensor=%s value=%f", _dbName.c_str(), _deviceId.c_str(), metricName.c_str(), value));
	_udpClient->endPacket();
}
