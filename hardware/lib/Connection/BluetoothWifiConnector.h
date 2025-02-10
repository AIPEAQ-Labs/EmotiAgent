#include "WiFiProv.h"
#include "WiFi.h"
#include <Preferences.h>
#include <SerialNumber.h>
class BluetoothWifiConnector {
    private:
        static BluetoothWifiConnector* instance;

        static void staticSysProvEvent(arduino_event_id_t event, arduino_event_info_t info) {
            if (instance) {
                arduino_event_t e;
                e.event_id = event;
                e.event_info = info;
                instance->SysProvEvent(&e);
            }
        }

    public:
        BluetoothWifiConnector(Preferences& preferences) : preferences(preferences) {
            instance = this;
        }

        void SysProvEvent(arduino_event_t *sys_event) {
            Serial.println("SysProvEvent");
            Serial.println(sys_event->event_id);
            switch (sys_event->event_id) {
                case ARDUINO_EVENT_WIFI_STA_GOT_IP:
                    Serial.print("\nConnected IP address : ");
                    Serial.println(IPAddress(sys_event->event_info.got_ip.ip_info.ip.addr));
                    break;
                case ARDUINO_EVENT_WIFI_STA_DISCONNECTED: Serial.println("\nDisconnected. Connecting to the AP again... "); break;
                case ARDUINO_EVENT_PROV_START:            Serial.println("\nProvisioning started\nGive Credentials of your access point using smartphone app"); break;
                case ARDUINO_EVENT_PROV_CRED_RECV:
                {
                    const char* ssid = (const char *)sys_event->event_info.prov_cred_recv.ssid;
                    const char* password = (char const *)sys_event->event_info.prov_cred_recv.password;
                    
                    Serial.println("\nReceived Wi-Fi credentials");
                    Serial.print("\tSSID : ");
                    Serial.println(ssid);
                    Serial.print("\tPassword : ");
                    Serial.println(password);

                    preferences.putString("ssid", ssid);
                    preferences.putString("password", password);

                    break;
                }
                case ARDUINO_EVENT_PROV_CRED_FAIL:
                {
                    Serial.println("\nProvisioning failed!\nPlease reset to factory and retry provisioning\n");
                    if (sys_event->event_info.prov_fail_reason == WIFI_PROV_STA_AUTH_ERROR) {
                        Serial.println("\nWi-Fi AP password incorrect");
                    } else {
                        Serial.println("\nWi-Fi AP not found....Add API \" nvs_flash_erase() \" before beginProvision()");
                    }

                    break;
                }
                case ARDUINO_EVENT_PROV_CRED_SUCCESS: Serial.println("\nProvisioning Successful"); break;
                case ARDUINO_EVENT_PROV_END:          {
                    Serial.println("\nProvisioning Ends");
                    break;
                }
                default:                              break;
            }
        }
        void setup() {
            char ssid[33];      // WiFi SSID max length is 32 chars + null terminator
            char password[64];  // WPA2 password max length is 63 chars + null terminator
            
            preferences.getString("ssid", ssid, sizeof(ssid));
            preferences.getString("password", password, sizeof(password));

            bool isFailedToConnect = false;
            isFailedToConnect = true;

            Serial.println("Credentials: ");
            Serial.println(ssid);
            Serial.println(password);

            if (strlen(ssid) > 0 && strlen(password) > 0) {
                unsigned long startTime = millis();

                Serial.println("Connecting to WiFi...");
                WiFi.begin(ssid, password);
                
                while (WiFi.status() != WL_CONNECTED) {
                    if (millis() - startTime > 20000) {
                        Serial.println("Failed to connect to WiFi");
                        isFailedToConnect = true;
                        break;
                    }
                    delay(1000);
                    Serial.println("Connecting to WiFi...");
                }
            } else {
                isFailedToConnect = true;
                Serial.println("No credentials found");
            }

            
            if (isFailedToConnect) {
                WiFi.onEvent(staticSysProvEvent);
                uint8_t uuid[16] = {0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
                               0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02};

                const char* wifi_name = (service_name + SerialNumber::getSerialNumber()).c_str();
                WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, wifi_name, service_key, uuid, reset_provisioned);
                WiFiProv.printQR(wifi_name, pop, "ble");
            }
        }

        static const char* const pop;          
        static const char* const service_name;
        static const char* const service_key;
        static const bool reset_provisioned = true;
        
        Preferences& preferences;
};

BluetoothWifiConnector* BluetoothWifiConnector::instance = nullptr;
const char* const BluetoothWifiConnector::pop = "aipeaq123456";
const char* const BluetoothWifiConnector::service_name = "AIPEAQ_";
const char* const BluetoothWifiConnector::service_key = nullptr;