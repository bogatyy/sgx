#include <stdio.h>
#include "sgx_urts.h"
#include "Enclave_u.h"

#define ENCLAVE_FILE "Enclave.signed.so"

int main() {
    sgx_enclave_id_t eid;
    sgx_status_t ret;
    sgx_launch_token_t token = {0};
    int updated = 0;

    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("Error creating enclave: %d\n", ret);
        return -1;
    }

    ecall_generate_key(eid);

    sgx_ec256_public_t public_key;
    ecall_get_public_key(eid, &public_key);

    int first_number = 123;
    int second_number = 321;

    // TODO: actual encryption for first number
    uint8_t* encrypted_data;
    size_t len;
    ecall_store_input_number(encrypted_data, len, 0);
    // TODO: actual encryption for second number
    ecall_store_input_number(encrypted_data, len, 1);

    int sum;
    ecall_get_sum(&sum);
    printf("The sum of two numbers is %d\n", sum);

    sgx_destroy_enclave(eid);
    return 0;
}
