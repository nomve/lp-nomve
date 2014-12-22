#ifndef BLE_PALS_H_
#define BLE_PALS_H_

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"

//base UUID used by all (service, characteristic)
//f4e5XXXX-820a-11e4-a864-0002a5d5c51b lsbn first
#define PALS_UUID_BASE			{0x1b, 0xc5, 0xd5, 0xa5, 0x02, 0x00, 0x64, 0xa8, 0xe4, 0x11, 0x0a, 0x82, 0x00, 0x00, 0xe5, 0xf4}
//values that replace XXXX in PALS_UUID_BASE
#define PALS_UUID_SERVICE		0x27e0
#define PALS_UUID_LOCATION_CHAR	0x27e1

//
typedef struct ble_pals_s
{
	uint16_t					service_handle;
	ble_gatts_char_handles_t	location_char_handles;
	uint8_t						uuid_type;
} ble_pals_t;


uint32_t ble_pals_init( ble_pals_t * p_pals );


#endif
