/*
  Common variable method
*/
#define wifiSsid "PDCN"
#define wifiPasswd "248366796"
#define bafaToken "843ac2ca8da440278224ed13a7e06ccb"
#define bafaTopic "switch001"
#define switch001 26
#define ServerAddr "139.155.245.132"
#define ServerMqttPort 8883
#define launchBoxPort 8030
#define launchBoxWebSocketUrl "/board"

void setupWifi();
bool setupWifi(const char* ssid, const char* passwd);

void apWifiConfig();

