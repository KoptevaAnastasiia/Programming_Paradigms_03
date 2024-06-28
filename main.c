#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void* handle_encrypt = dlopen("./libencrypt.so", RTLD_LAZY);

    if (!handle_encrypt) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    void (*caesar_cipher)(char*, int);
    caesar_cipher = dlsym(handle_encrypt, "caesar_cipher");
    if (!caesar_cipher) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    void* handle_decrypt = dlopen("./libcaesar_decrypt.so", RTLD_LAZY);
    if (!handle_decrypt) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle_encrypt);
        return 1;
    }

    void (*caesar_cipher_decryption)(char*, int);
    caesar_cipher_decryption = dlsym(handle_decrypt, "caesar_cipher_decryption");
    if (!caesar_cipher_decryption) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    char ask[256];
    printf("str ");
    fgets(ask, sizeof(ask), stdin);


    int shift = 1;
    caesar_cipher(ask, shift);
    printf("Encrypted: %s\n", ask);

    caesar_cipher_decryption(ask, shift);
    printf("Decrypted: %s\n", ask);

    dlclose(handle_encrypt);
    dlclose(handle_decrypt);

    return 0;
}
