cd /D C:\Users\mahesh_tripathi\eclipse-workspace\Smart_configure\build\esp-idf\esp32 || exit /b
python C:/msys32/home/mahesh_tripathi/esp/esp-idf/tools/ldgen/ldgen.py --config C:/Users/mahesh_tripathi/eclipse-workspace/Smart_configure/sdkconfig --fragments C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/soc/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/heap/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/xtensa-debug-module/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/app_trace/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/freertos/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp_ringbuf/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/spi_flash/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/lwip/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/espcoredump/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp32/linker.lf	C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp32/ld/esp32_fragments.lf --input C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp32/ld/esp32.project.ld.in --output C:/Users/mahesh_tripathi/eclipse-workspace/Smart_configure/build/esp-idf/esp32/esp32.project.ld --sections C:/Users/mahesh_tripathi/eclipse-workspace/Smart_configure/build/ldgen.section_infos --kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/Kconfig --env "COMPONENT_KCONFIGS= C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/app_trace/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/aws_iot/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/bt/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/driver/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/efuse/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp32/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp_adc_cal/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp_event/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp_http_client/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp_http_server/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esp_https_ota/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/espcoredump/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/ethernet/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/fatfs/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/freemodbus/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/freertos/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/heap/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/libsodium/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/log/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/lwip/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/mbedtls/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/mdns/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/mqtt/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/nvs_flash/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/openssl/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/pthread/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/spi_flash/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/spiffs/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/tcpip_adapter/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/unity/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/vfs/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/wear_levelling/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/wifi_provisioning/Kconfig C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/wpa_supplicant/Kconfig" --env "COMPONENT_KCONFIGS_PROJBUILD= C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/app_update/Kconfig.projbuild C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/bootloader/Kconfig.projbuild C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/esptool_py/Kconfig.projbuild C:/msys32/home/mahesh_tripathi/esp/esp-idf/components/partition_table/Kconfig.projbuild" --env IDF_CMAKE=y --env IDF_PATH=C:/msys32/home/mahesh_tripathi/esp/esp-idf --env IDF_TARGET=esp32 || exit /b
