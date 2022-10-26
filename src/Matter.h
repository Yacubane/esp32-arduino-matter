#define CHIP_HAVE_CONFIG_H true
#define CHIP_ADDRESS_RESOLVE_IMPL_INCLUDE_HEADER <lib/address_resolve/AddressResolve_DefaultImpl.h>

// undef ESP32 while importing Matter
// ESP32 define makes some defines in Matter headers not working
#undef ESP32
// import sdkconfig from exported Matter project
#include "sdkconfig_matter.h"
#include "esp_matter.h"
#include "esp_matter_console.h"
#include "esp_matter_ota.h"
#define ESP32

// use some method from esp32-hal-bt.c to force linking it
// and so that it will override btInUse method in esp32-hal-misc.c 
// to disable releasing BT memory, that can't be later re-allocated
#include "esp32-hal-bt.h"
namespace MatterUnused {
    bool _ = btStarted();
}