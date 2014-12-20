#include "ble_pals.h"

uint32_t ble_pals_init( ble_pals_t * p_pals ) {
	
	uint32_t		err_code;
	ble_uuid_t		ble_uuid;
	
	//service's base uuid
	ble_uuid128_t base_uuid = PALS_UUID_BASE;
	
	//add service internally (to "ble stack"), store uuid_type
	err_code = sd_ble_uuid_vs_add(&base_uuid, &p_pals->uuid_type );
	if ( err_code != NRF_SUCCESS )
		return err_code;
	
	//set the returned type and service uuid
	ble_uuid.type = p_pals->uuid_type;
	ble_uuid.uuid = PALS_UUID_SERVICE;
	
	//add service to the attribute table
	err_code = sd_ble_gatts_service_add( BLE_GATTS_SRVC_TYPE_PRIMARY,
											&ble_uuid, &p_pals->service_handle );
	if ( err_code != NRF_SUCCESS )
		return err_code;
	
	
	
	
	
	return NRF_SUCCESS;
}