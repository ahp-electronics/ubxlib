# Introduction
This directory contains the cellular APIs, designed to provide a simple control interface to a u-blox cellular module.

The cellular APIs are split into the following groups:

- `<no group>`: init/deinit of the cellular API and adding a cellular instance.
- `cfg`: configuration of the cellular module.
- `pwr`: powering up and down the cellular module.
- `net`: attaching to the cellular network.
- `info`: obtaining information about the cellular module.
- `sock`: sockets, for exchanging data (but see the `common/sock` component for the best way to do this).

The module types supported by this implementation are listed in `cell.h` (see the definition of `uCellModuleType_t`).

HOWEVER, this is the detailed API; if all you would like to do is bring up a bearer as simply as possible and then get on with exchanging data, please consider using the `common/network` API, along with the `common/sock` API.  You may still dip down into this API from the network level as the handles used at the network level are the ones generated here.

This `api` relies upon the `at-client` common component to send commands to and parse responses received from a cellular module.

# Usage
The `api` directory contains the files that define the cellular APIs, each API function documented in its header file.  In the `src` directory you will find the implementation of the APIs and in the `test` directory the tests for the APIs that can be run on any platform.

A simple usage example is given below.

Throughout the `cell` API, in functions which can take more than a few seconds to complete, you will find a `keepGoingCallback()` parameter.  This parameter is intended for situations where the application needs control of the timeout of the API call or needs to feed a watchdog timer.  The callback will be called approximately once a second while the API function is operating and, if it returns `false`, the API function will be terminated.  Set the parameter to `NULL` if no specific timeout is required, or no watchdog needs to be fed.

```
#include "stdio.h"
#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"

#include "u_cfg_sw.h"
#include "u_cfg_os_platform_specific.h"
#include "u_cfg_app_platform_specific.h"

#include "u_error_common.h"

#include "u_port.h"
#include "u_port_debug.h"
#include "u_port_uart.h"

#include "u_at_client.h"

#include "u_sock.h"

#include "u_cell.h"
#include "u_cell_net.h"
#include "u_cell_pwr.h"

int main() {
    int32_t uartHandle;
    uAtClientHandle_t atHandle;
    int32_t cellHandle;
    char buffer[U_CELL_NET_IP_ADDRESS_SIZE];
    int32_t mcc;
    int32_t mnc;

    // Initialise the APIs we will need
    uPortInit();
    uAtClientInit();
    uCellInit();

    // Open a UART with the recommended buffer length
    // on your chosen UART HW block and on the pins
    // where the cellular module's UART interface is
    // connected to your MCU: you need to know these
    // for your hardware, either set the #defines
    // appropriately or replace them with the right
    // numbers, using -1 for a pin that is not connected.
    uartHandle = uPortUartOpen(U_CFG_APP_CELL_UART,
                               115200, NULL,
                               U_CELL_UART_BUFFER_LENGTH_BYTES,
                               U_CFG_APP_PIN_CELL_TXD,
                               U_CFG_APP_PIN_CELL_RXD,
                               U_CFG_APP_PIN_CELL_CTS,
                               U_CFG_APP_PIN_CELL_RTS);

    // Add an AT client on the UART with the recommended
    // default buffer size.
    atClientHandle = uAtClientAdd(uartHandle,
                                  U_AT_CLIENT_STREAM_TYPE_UART,
                                  NULL,
                                  U_CELL_AT_BUFFER_LENGTH_BYTES);

    // Set printing of AT commands by the cellular driver,
    // which can be useful while debugging.
    uAtClientPrintAtSet(atClientHandle, true);

    // Add a cell instance, in this case a SARA-R5 module,
    // giving it the AT client handle and the pins where
    // the cellular module's control interface is 
    // connected to your MCU: you need to know these for
    // your hardware; again use -1 for "not connected".
    cellHandle = uCellAdd(U_CELL_MODULE_TYPE_SARA_R5,
                          atClientHandle,
                          U_CFG_APP_PIN_CELL_ENABLE_POWER,
                          U_CFG_APP_PIN_CELL_PWR_ON,
                          U_CFG_APP_PIN_CELL_VINT, false);

    // Power up the cellular module
    if (uCellPwrOn(cellHandle, NULL, NULL) == 0) {
        // Connect to the cellular network with all default parameters
        if (uCellNetConnect(cellHandle, NULL, NULL, NULL, NULL, NULL) == 0) {

            // Do things, for example
            if (uCellNetGetOperatorStr(cellHandle, buffer, sizeof(buffer)) >= 0) {
                printf("Registered on \"%s\".\n", buffer);
            }
            if (uCellNetGetMccMnc(cellHandle, &mcc, &mnc) == 0) {
                printf("The MCC/MNC of the network is %d%d.\n", mcc, mnc);
            }
            if (uCellNetGetIpAddressStr(cellHandle, buffer) >= 0) {
                printf("Our IP address is \"%s\".\n", buffer);
            }
            if (uCellNetGetApnStr(cellHandle, buffer, sizeof(buffer)) >= 0) {
                printf("The APN used was \"%s\".\n", buffer);
            }

            // When finished with the connection
            uCellNetDisconnect(cellHandle, NULL);
        }
        // When finished using the module
        uCellPwrOff(cellHandle, NULL);
    }

    // Calling these will also deallocate all the handles that
    // were allocated above.
    uCellDeinit();
    uAtClientDeinit();
    uPortDeinit();

    return 0;
}
```