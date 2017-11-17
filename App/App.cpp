#include "App.h"

#include "sgx_uae_service.h"
#include "sgx_capable.h"


/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
	(void)(argc);
	(void)(argv);

	sgx_device_status_t sgx_device_status;
	sgx_status_t sgx_ret = sgx_cap_enable_device(&sgx_device_status);
	if (sgx_ret != SGX_SUCCESS) {
		printf("Failed to get SGX device status.\n");
		return -1;
	}
	else {
		switch (sgx_device_status) {
			case SGX_ENABLED:
			printf("Enabled\n");
			return 0;
			case SGX_DISABLED_REBOOT_REQUIRED:
			printf("SGX device has been enabled. Please reboot your machine.\n");
			return -1;
			case SGX_DISABLED_LEGACY_OS:
			printf("SGX device can't be enabled on an OS that doesn't support EFI interface.\n");
			return -1;
			case SGX_DISABLED:
			printf("SGX device not found.\n");
			return -1;
			default:
			printf("Unexpected error.\n");
			return -1;
		}
	}


	return -1;
}

