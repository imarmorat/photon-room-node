
class DataPublisher
{
public:
	void init();
	void publish(String metricName, float value);
};

class InfluxDBDataPublisher : public DataPublisher
{
public:
	InfluxDBDataPublisher(IPAddress ipAddress, UDP * udpClient, unsigned int udpPort, String dbName);
	void init();
	void publish(String metricName, float value);
private:
	UDP * _udpClient;
	IPAddress _udpAddress;
	unsigned int _udpPort;
	String _dbName;
	String _deviceId;
}; 
