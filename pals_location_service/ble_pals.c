#include "ble_pals.h"
#include <string.h>
#include "nrf.h"
#include "ble_gatts.h"
#include "app_error.h"

void ble_pals_on_ble_evt( ble_pals_t * p_pals, ble_evt_t * p_ble_evt )
{
	//uint32_t err_code;
	
    switch (p_ble_evt->header.evt_id)
    {
        //TODO
		//write event
        default:
            // No implementation needed.
            break;
    }
}

static uint32_t pals_location_char_add( ble_pals_t * p_pals, const uint32_t pals_lat_lng[] ) {
	
	ble_gatts_char_md_t 	char_md;
    ble_uuid_t          	ble_uuid;
    ble_gatts_attr_md_t 	attr_md;
    ble_gatts_attr_t    	attr_char_value;	
	
	//characteristic declaration/metadata
	memset(&char_md, 0, sizeof(char_md));
	
	//set characteristic property
	char_md.char_props.broadcast 	= 1;
	char_md.char_props.read			= 1;
	char_md.char_props.write		= 0;
	//cccd only needed for notify/indicate properties
	char_md.p_cccd_md = NULL;
	char_md.p_sccd_md = NULL;
	//TODO
	//user description string
	char_md.p_char_user_desc = NULL;
	char_md.p_user_desc_md = NULL;
	
	//characteristic uuid
	ble_uuid.type = p_pals->uuid_type;
	ble_uuid.uuid = PALS_UUID_LOCATION_CHAR;
	
	//characteristic value attribute metadata
	memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);
	//characteristic value attribute is located on the stack
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
	
	//characteristic value attribute
	memset( &attr_char_value, 0, sizeof(attr_char_value) );
	
	attr_char_value.p_attr_md 	= &attr_md;
	attr_char_value.p_uuid 		= &ble_uuid;
	attr_char_value.p_value		= (uint8_t *) pals_lat_lng;
	
	attr_char_value.init_len	= sizeof(uint32_t) * 2;
	attr_char_value.init_offs	= 0;
	attr_char_value.max_len		= sizeof(uint32_t) * 2;
	
	
	return sd_ble_gatts_characteristic_add( p_pals->service_handle, &char_md,
												&attr_char_value,
												&p_pals->location_char_handles );
}

uint32_t ble_pals_init( ble_pals_t * p_pals, const uint32_t pals_lat_lng[] ) {
	
	uint32_t		err_code;
	ble_uuid_t		ble_uuid;
	
	//service's base uuid
	ble_uuid128_t base_uuid = PALS_UUID_BASE;
	
	//add service internally (to "ble stack"), store uuid_type
	err_code = sd_ble_uuid_vs_add( &base_uuid, &p_pals->uuid_type );
	if ( err_code != NRF_SUCCESS )
		return err_code;
	
	//set the returned type and service uuid
	ble_uuid.type = p_pals->uuid_type;
	ble_uuid.uuid = PALS_UUID_SERVICE;
	
	//add service to the attribute table
	err_code = sd_ble_gatts_service_add( BLE_GATTS_SRVC_TYPE_PRIMARY,
											&ble_uuid, &(p_pals->service_handle) );
	if ( err_code != NRF_SUCCESS )
		return err_code;
	
	//add location characteristic
	err_code = pals_location_char_add( p_pals, pals_lat_lng );
	
	return NRF_SUCCESS;
}
