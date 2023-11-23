#include "sgx_trts.h"
#include "sgx_tcrypto.h"
#include "Enclave_t.h"

static sgx_ec256_private_t private_key;
static sgx_ec256_public_t public_key;
static int keys_initialized = 0; // Flag to check if keys are already initialized

static int first_number;
static int second_number;

// Generate key pair inside the enclave
void ecall_generate_key() {
    // Check if keys are already generated
    if (keys_initialized) {
        return;
    }

    sgx_ecc_state_handle_t ecc_handle;
    sgx_status_t status = sgx_ecc256_open_context(&ecc_handle);
    if (status != SGX_SUCCESS) {
        // Handle error
        return;
    }

    status = sgx_ecc256_create_key_pair(&private_key, &public_key, ecc_handle);
    if (status != SGX_SUCCESS) {
        // Handle error
        sgx_ecc256_close_context(ecc_handle);
        return;
    }

    sgx_ecc256_close_context(ecc_handle);
    keys_initialized = 1; // Set the flag as keys are now initialized
}

// Get the enclave public key
void ecall_get_public_key(sgx_ec256_public_t* key) {
    if (key != NULL && keys_initialized) {
        memcpy(key, &public_key, sizeof(sgx_ec256_public_t));
    }
}

// Decrypt and store provided number
void ecall_store_input_number(uint8_t* encrypted_data, size_t len, int is_second) {
    // TODO: implement decryption logic
    int decrypted_number = 123;
    // Store the number
    if (!is_second) {
        first_number = decrypted_number;
    } else {
        second_number = decrypted_number;
    }
}

void ecall_get_sum(int* sum) {
    *sum = first_number + second_number;
}
