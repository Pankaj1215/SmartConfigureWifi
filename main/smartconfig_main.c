/* Esptouch example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "esp_smartconfig.h"
#include "non_volatile_lib.h"


#define P_Testing  // Added for only testing auto restarted.. take wifi creditentials from NVS.

#ifdef P_Testing
	#define NVS_LUCIDTRON_SSID_KEY   "ssid"
	#define NVS_LUCIDTRON_PASS_KEY  "pass"
    #define  MAX_STR_BUFF_SIZE  20


   // char user_ssid[MAX_STR_BUFF_SIZE];
   // char user_pass[MAX_STR_BUFF_SIZE];
//
    uint8_t user_ssid[32];
    uint8_t user_pass[64];

//    uint8_t *user_ssid;
//    uint8_t *user_pass;

wifi_config_t *wifi_config;

void setSSID_PASS_ToNVS(void);
void EraseSSID_PASS_FromNVS(void);
void getSSID_PASS_FromNVS(void);

void StorageTestNVS(void);
#endif




/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
static const int CONNECTED_BIT = BIT0;
static const int ESPTOUCH_DONE_BIT = BIT1;
static const char *TAG = "sc";

void smartconfig_example_task(void * parm);





static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        xTaskCreate(smartconfig_example_task, "smartconfig_example_task", 4096, NULL, 3, NULL);
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(s_wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(s_wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

static void initialise_wifi(void)
{
    tcpip_adapter_init();
    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}


static void sc_callback(smartconfig_status_t status, void *pdata)
{
#ifdef P_Testing
	wifi_config = pdata;   // only for testing
	// memcpy(wifi_config->sta.ssid,"moto", sizeof(wifi_config->sta.ssid));
	// memcpy(wifi_config->sta.password,"Heyramram", sizeof(wifi_config->sta.password));

	// memcpy(wifi_config->sta.ssid,user_ssid, sizeof(wifi_config->sta.ssid));
	// memcpy(wifi_config->sta.password,user_pass, sizeof(wifi_config->sta.password));

	//printf("wifi_config->sta.ssid %s \n", wifi_config->sta.ssid);
    // printf("wifi_config->sta.ssid %s \n ", wifi_config->sta.ssid);
#endif

	printf("status %d :",status);

    switch (status) {
        case SC_STATUS_WAIT:
            ESP_LOGI(TAG, "SC_STATUS_WAIT");
            break;
        case SC_STATUS_FIND_CHANNEL:
            ESP_LOGI(TAG, "SC_STATUS_FINDING_CHANNEL");

//#ifdef P_Testing
//       	    memcpy(wifi_config->sta.ssid,"moto", sizeof(wifi_config->sta.ssid));
//       	    memcpy(wifi_config->sta.password,"Heyramram", sizeof(wifi_config->sta.password));
//#endif
            break;
        case SC_STATUS_GETTING_SSID_PSWD:
            ESP_LOGI(TAG, "SC_STATUS_GETTING_SSID_PSWD");
            break;
        case SC_STATUS_LINK:
            ESP_LOGI(TAG, "SC_STATUS_LINK");

#ifdef P_Testing
           // wifi_config = pdata;   // only for testing
       	   // memcpy(wifi_config->sta.ssid,user_ssid, sizeof(wifi_config->sta.ssid));
       	   // memcpy(wifi_config->sta.password,user_ssid, sizeof(wifi_config->sta.password));

#else
             wifi_config_t *wifi_config = pdata;  // Original line  // Commented only for testing
#endif

            ESP_LOGI(TAG, "SSID:%s", wifi_config->sta.ssid);
            ESP_LOGI(TAG, "PASSWORD:%s", wifi_config->sta.password);

			#ifdef P_Testing

              printf("wifi_config->sta.ssid %s \n", wifi_config->sta.ssid);
        	  printf("wifi_config->sta.password %s \n ", wifi_config->sta.password);

        	  memcpy(user_ssid,wifi_config->sta.ssid, sizeof(user_ssid));
        	  memcpy(user_pass, wifi_config->sta.password, sizeof(user_pass));

              setSSID_PASS_ToNVS();
			#endif

            ESP_ERROR_CHECK( esp_wifi_disconnect() );
            ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, wifi_config) );
            ESP_ERROR_CHECK( esp_wifi_connect() );
            break;
        case SC_STATUS_LINK_OVER:
            ESP_LOGI(TAG, "SC_STATUS_LINK_OVER");
            if (pdata != NULL) {
                uint8_t phone_ip[4] = { 0 };
                memcpy(phone_ip, (uint8_t* )pdata, 4);
                ESP_LOGI(TAG, "Phone ip: %d.%d.%d.%d\n", phone_ip[0], phone_ip[1], phone_ip[2], phone_ip[3]);
            }
            xEventGroupSetBits(s_wifi_event_group, ESPTOUCH_DONE_BIT);
            break;
        default:
            break;
    }
}


void smartconfig_example_task(void * parm)
{
    EventBits_t uxBits;
    ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH) );

    ESP_ERROR_CHECK( esp_smartconfig_start(sc_callback) );

    while (1) {
        uxBits = xEventGroupWaitBits(s_wifi_event_group, CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY); 
        if(uxBits & CONNECTED_BIT) {
            ESP_LOGI(TAG, "WiFi Connected to ap");
        }
        if(uxBits & ESPTOUCH_DONE_BIT) {
            ESP_LOGI(TAG, "smartconfig over");
            esp_smartconfig_stop();
            vTaskDelete(NULL);
        }
    }
}


#ifdef P_Testing
void getSSID_PASS_FromNVS(void)
{
	// get_string_from_storage(NVS_LUCIDTRON_SSID_KEY, user_ssid);
	// get_integer_from_storage(NVS_LUCIDTRON_SSID_KEY, user_ssid);

	//get_string_from_storage(NVS_LUCIDTRON_PASS_KEY, user_pass);

	  memcpy(user_ssid, "moto", sizeof(user_ssid));
	  memcpy(user_pass, "Heyramramji", sizeof(user_pass));

	// memcpy(wifi_config->sta.ssid,user_ssid, sizeof(wifi_config->sta.ssid));
	// memcpy(wifi_config->sta.password,user_ssid, sizeof(wifi_config->sta.password));

    printf("During GET SSID AND PASSWORD \n ");
   // printf("wifi_config->sta.ssid %s \n", wifi_config->sta.ssid);
   // printf("wifi_config->sta.ssid %s \n ", wifi_config->sta.ssid);

    printf("user_ssid %s \n ", user_ssid);
    printf("user_pass %s \n ", user_pass);

}// end of void getSSID_PASS_FromNVS()



void setSSID_PASS_ToNVS(void)
{
	// strcpy(user_ssid, (char*)wifi_config->sta.ssid);
	// strcpy(user_ssid,(char*)wifi_config->sta.password);

	// set_string_to_storage(NVS_LUCIDTRON_SSID_KEY, user_ssid);
	// set_integer_to_storage(NVS_LUCIDTRON_SSID_KEY, user_ssid);

	// set_string_to_storage(NVS_LUCIDTRON_PASS_KEY, user_pass);

    printf("During SET SSID AND PASSWORD \n ");

   // printf("wifi_config->sta.ssid %s \n", wifi_config->sta.ssid);
   //  printf("wifi_config->sta.password %s \n ", wifi_config->sta.password);

   // memcpy(wifi_config->sta.ssid, user_ssid, sizeof(wifi_config->sta.ssid));
   // memcpy(user_ssid,wifi_config->sta.ssid, sizeof(user_ssid));
    // memcpy(user_pass, wifi_config->sta.password, sizeof(user_pass));

   // memcpy(wifi_config->sta.password, user_pass, sizeof(wifi_config->sta.password));
   // memcpy(user_pass, wifi_config->sta.password, sizeof(user_pass));

    printf("user_ssid %s \n ", user_ssid);
    printf("user_pass %s \n ", user_pass);

}// end of void setSSID_PASS_ToNVS()



void EraseSSID_PASS_FromNVS(void)
{
	erase_string_in_storage(NVS_LUCIDTRON_SSID_KEY);
	erase_string_in_storage(NVS_LUCIDTRON_PASS_KEY);
}// end of void setSSID_PASS_ToNVS()



void StorageTestNVS(void)
{
	    // storage test
	    char str_test[10] = "";
	    int int_test = 0;
	    get_integer_from_storage("int_test", &int_test);

	    printf("int_test=%d\r\n", int_test);

	    ++int_test;
	    set_integer_to_storage("int_test", int_test);
	    get_string_from_storage("str_test", str_test);

	    printf("str_test=%s\r\n", str_test);

	    sprintf(str_test, "str_test %d", int_test);
	    set_string_to_storage("str_test", str_test);

	    if (int_test > 1) {
	        erase_integer_in_storage("int_test");
	        erase_string_in_storage("str_test");
	    }
}// end of void StorageTestNVS(void)
#endif



void app_main()
{

#ifdef P_Testing

	//nvs_flash_erase();


	//erase_data_in_storage(NVS_LUCIDTRON_SSID_KEY);
	//erase_data_in_storage(NVS_LUCIDTRON_PASS_KEY);

	erase_string_in_storage(NVS_LUCIDTRON_SSID_KEY);
	erase_string_in_storage(NVS_LUCIDTRON_PASS_KEY);

	erase_storage_all();
	nvs_flash_erase();

	//while(1);
    // memset(user_ssid, 0, sizeof(user_ssid));
    //  memset( user_pass, 0, sizeof( user_pass));
    nvs_storage_init();
    StorageTestNVS();

    // while(1);
	 getSSID_PASS_FromNVS();
	 ESP_ERROR_CHECK( nvs_flash_init());
#else
    ESP_ERROR_CHECK( nvs_flash_init());
#endif

    initialise_wifi();
}

