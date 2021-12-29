cmake_minimum_required(VERSION 2.6)

project(libubx C)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
include(GNUInstallDirs)

find_package(M REQUIRED)
find_package(Threads REQUIRED)

set (CMAKE_C_STANDARD 11)
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(UBX_VERSION_MAJOR 1)
set(UBX_VERSION_MINOR 1)
set(UBX_VERSION_RELEASE 2)
set(UBX_VERSION "${UBX_VERSION_MAJOR}.${UBX_VERSION_MINOR}.${UBX_VERSION_RELEASE}")
set(UBX_SOVERSION ${UBX_VERSION_MAJOR})

set(SOURCES
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss_pwr.c
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss_info.c
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss_cfg.c
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss_util.c
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss_pos.c
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss.c
${CMAKE_SOURCE_DIR}/gnss/src/u_gnss_private.c
${CMAKE_SOURCE_DIR}/port/clib/u_port_clib_strtok_r.c
${CMAKE_SOURCE_DIR}/port/clib/u_port_clib_isblank.c
${CMAKE_SOURCE_DIR}/port/clib/u_port_clib_mktime.c
${CMAKE_SOURCE_DIR}/port/clib/u_port_clib_mktime64.c
${CMAKE_SOURCE_DIR}/port/platform/static_size/stubs/u_lib_stub.c
${CMAKE_SOURCE_DIR}/port/platform/static_size/stubs/u_port_stub.c
${CMAKE_SOURCE_DIR}/port/platform/static_size/stubs/u_main_stub.c
${CMAKE_SOURCE_DIR}/port/platform/common/event_queue/u_port_event_queue.c
${CMAKE_SOURCE_DIR}/port/platform/common/heap_check/u_heap_check.c
${CMAKE_SOURCE_DIR}/common/ubx_protocol/src/u_ubx_protocol.c
${CMAKE_SOURCE_DIR}/common/utils/src/u_hex_bin_convert.c
${CMAKE_SOURCE_DIR}/common/utils/src/u_ringbuffer.c
${CMAKE_SOURCE_DIR}/common/utils/src/u_time.c
${CMAKE_SOURCE_DIR}/common/at_client/src/u_at_client.c
${CMAKE_SOURCE_DIR}/common/lib_common/src/u_lib_handler.c
${CMAKE_SOURCE_DIR}/common/sock/src/u_sock.c
${CMAKE_SOURCE_DIR}/common/short_range/src/u_short_range_edm_stream.c
${CMAKE_SOURCE_DIR}/common/short_range/src/u_short_range.c
${CMAKE_SOURCE_DIR}/common/short_range/src/u_short_range_private.c
${CMAKE_SOURCE_DIR}/common/short_range/src/u_short_range_sec_tls.c
${CMAKE_SOURCE_DIR}/common/short_range/src/u_short_range_edm.c
${CMAKE_SOURCE_DIR}/common/mqtt_client/src/u_mqtt_client.c
${CMAKE_SOURCE_DIR}/common/location/src/u_location.c
${CMAKE_SOURCE_DIR}/common/location/src/u_location_shared.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_cfg.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_loc.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_sock.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_sec_tls.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_pwr.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_net.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_sec.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_sec_c2c.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_gpio.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_file.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_private.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_mqtt.c
${CMAKE_SOURCE_DIR}/cell/src/u_cell_info.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_data_intmod.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_private.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_cfg_intmod.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_extmod.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_data_extmod.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_intmod.c
${CMAKE_SOURCE_DIR}/ble/src/u_ble_cfg_extmod.c
   )

include_directories(
    ${CMAKE_SOURCE_DIR}/wifi
    ${CMAKE_SOURCE_DIR}/cfg
    ${CMAKE_SOURCE_DIR}/port
    ${CMAKE_SOURCE_DIR}/port/clib
    ${CMAKE_SOURCE_DIR}/port/api
    ${CMAKE_SOURCE_DIR}/port/platform
    ${CMAKE_SOURCE_DIR}/port/platform/static_size
    ${CMAKE_SOURCE_DIR}/port/platform/static_size/stubs
    ${CMAKE_SOURCE_DIR}/port/platform/lint
    ${CMAKE_SOURCE_DIR}/port/platform/lint/stubs
    ${CMAKE_SOURCE_DIR}/port/platform/common
    ${CMAKE_SOURCE_DIR}/port/platform/common/event_queue
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker/host
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker/host/scripts
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker/host/udev
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker/agent
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker/agent/settings
    ${CMAKE_SOURCE_DIR}/port/platform/common/automation/docker/agent/scripts
    ${CMAKE_SOURCE_DIR}/port/platform/common/mbedtls
    ${CMAKE_SOURCE_DIR}/port/platform/common/heap_check
    ${CMAKE_SOURCE_DIR}/port/platform/common/runner
    ${CMAKE_SOURCE_DIR}/readme_images
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/common/security
    ${CMAKE_SOURCE_DIR}/common/security/src
    ${CMAKE_SOURCE_DIR}/common/security/api
    ${CMAKE_SOURCE_DIR}/common/network
    ${CMAKE_SOURCE_DIR}/common/network/src
    ${CMAKE_SOURCE_DIR}/common/network/api
    ${CMAKE_SOURCE_DIR}/common/ubx_protocol
    ${CMAKE_SOURCE_DIR}/common/ubx_protocol/src
    ${CMAKE_SOURCE_DIR}/common/ubx_protocol/api
    ${CMAKE_SOURCE_DIR}/common/utils
    ${CMAKE_SOURCE_DIR}/common/utils/src
    ${CMAKE_SOURCE_DIR}/common/utils/api
    ${CMAKE_SOURCE_DIR}/common/at_client
    ${CMAKE_SOURCE_DIR}/common/at_client/src
    ${CMAKE_SOURCE_DIR}/common/at_client/api
    ${CMAKE_SOURCE_DIR}/common/lib_common
    ${CMAKE_SOURCE_DIR}/common/lib_common/src
    ${CMAKE_SOURCE_DIR}/common/lib_common/api
    ${CMAKE_SOURCE_DIR}/common/lib_common/platform
    ${CMAKE_SOURCE_DIR}/common/lib_common/platform/zephyr
    ${CMAKE_SOURCE_DIR}/common/sock
    ${CMAKE_SOURCE_DIR}/common/sock/src
    ${CMAKE_SOURCE_DIR}/common/sock/api
    ${CMAKE_SOURCE_DIR}/common/error
    ${CMAKE_SOURCE_DIR}/common/error/api
    ${CMAKE_SOURCE_DIR}/common/short_range
    ${CMAKE_SOURCE_DIR}/common/short_range/src
    ${CMAKE_SOURCE_DIR}/common/short_range/api
    ${CMAKE_SOURCE_DIR}/common/mqtt_client
    ${CMAKE_SOURCE_DIR}/common/mqtt_client/src
    ${CMAKE_SOURCE_DIR}/common/mqtt_client/api
    ${CMAKE_SOURCE_DIR}/common/location
    ${CMAKE_SOURCE_DIR}/common/location/src
    ${CMAKE_SOURCE_DIR}/common/location/api
    ${CMAKE_SOURCE_DIR}/cmake_modules
    ${CMAKE_SOURCE_DIR}/cell
    ${CMAKE_SOURCE_DIR}/cell/src
    ${CMAKE_SOURCE_DIR}/cell/api
    ${CMAKE_SOURCE_DIR}/ble
    ${CMAKE_SOURCE_DIR}/ble/src
    ${CMAKE_SOURCE_DIR}/ble/api
    ${CMAKE_SOURCE_DIR}/gnss
    ${CMAKE_SOURCE_DIR}/gnss/src
    ${CMAKE_SOURCE_DIR}/gnss/api

    )
include_directories(${CMAKE_INCLUDE_PATH})
link_directories(${CMAKE_LIBRARY_PATH})

add_library(ubx STATIC ${SOURCES})
set_target_properties(ubx PROPERTIES VERSION ${UBX_VERSION} SOVERSION ${UBX_SOVERSION})

target_link_libraries(ubx ${M_LIB})

install(TARGETS ubx LIBRARY DESTINATION ${LIB_INSTALL_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_type.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_info.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_cfg.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_pos.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_module_type.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/gnss/api/u_gnss_pwr.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_uart.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_debug.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_crypto.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_gpio.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_gatt.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_event_queue.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/port/api/u_port_os.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/security/api/u_security_tls.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/security/api/u_security.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/security/api/u_security_credential.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/network/api/u_network_config_cell.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/network/api/u_network_config_gnss.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/network/api/u_network_config_wifi.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/network/api/u_network_handle.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/network/api/u_network.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/network/api/u_network_config_ble.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/ubx_protocol/api/u_ubx_protocol.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/utils/api/u_hex_bin_convert.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/utils/api/u_ringbuffer.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/utils/api/u_time.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/at_client/api/u_at_client.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/lib_common/test/test_lib/api/lib_fibonacci.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/lib_common/api/u_lib_internal.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/lib_common/api/u_lib.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/lib_common/example/api/lib_fibonacci.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/sock/api/u_sock_errno.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/sock/api/u_sock.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/sock/api/u_sock_security.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/error/api/u_error_common.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/short_range/api/u_short_range.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/short_range/api/u_short_range_sec_tls.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/short_range/api/u_short_range_edm_stream.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/short_range/api/u_short_range_module_type.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/mqtt_client/api/u_mqtt_common.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/mqtt_client/api/u_mqtt_client.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/common/location/api/u_location.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_info.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_sock.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_mqtt.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_file.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_gpio.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_net.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_cfg.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_loc.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_sec.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_pwr.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_module_type.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/cell/api/u_cell_sec_tls.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/ble/api/u_ble_cfg.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/ble/api/u_ble_module_type.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/ble/api/u_ble_data.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)
install(FILES ${CMAKE_SOURCE_DIR}/ble/api/u_ble.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ubx)

