SGX_SDK ?= /path/to/sgx/sdk
SGX_LIBRARY_PATH := $(SGX_SDK)/lib64
SGX_ENCLAVE_SIGNER := $(SGX_SDK)/bin/x64/sgx_sign
SGX_EDGER8R := $(SGX_SDK)/bin/x64/sgx_edger8r

all: app enclave

app: App.c Enclave_u.o
    gcc -o app App.c Enclave_u.o -I$(SGX_SDK)/include -L$(SGX_LIBRARY_PATH) -lsgx_urts -lpthread

enclave: Enclave.c Enclave_t.o
    gcc -o enclave.so Enclave.c Enclave_t.o -I$(SGX_SDK)/include -L$(SGX_LIBRARY_PATH) -lsgx_trts -lsgx_tservice -Wl,-z,noexecstack -Wl,-z,relro,-z,now -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined -Wl,-pie,-eenclave_entry -Wl,--export-dynamic -Wl,--defsym,__ImageBase=0

Enclave_t.o: Enclave.edl
    $(SGX_EDGER8R) --trusted Enclave.edl
