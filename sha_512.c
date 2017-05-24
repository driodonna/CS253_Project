#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>


//http://www.askyb.com/cpp/openssl-sha512-hashing-example-in-cpp/

void compute_sha512(char *string, char output[129]){
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, string, strlen(string));
    SHA256_Final(hash, &ctx);
    int i = 0;
    for(i = 0; i < SHA512_DIGEST_LENGTH; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[128] = 0;
}

void sha512_file(char *filename, char output[129]){
    FILE *file = fopen(filename, "rb");
    unsigned char hash[SHA512_DIGEST_LENGTH];
    const int bufferSize = 32768;
    char *buffer = malloc(bufferSize);
    int bytesRead = 0;


	SHA512_CTX ctx;
    SHA512_Init(&ctx);
    while((bytesRead = fread(buffer, 1, bufferSize, file)))
    {
        SHA512_Update(&ctx, buffer, bytesRead);
    }
    SHA512_Final(hash, &ctx);

    compute_sha512(hash, output);
    fclose(file);
    free(buffer);
}


int main(){
    static unsigned char buffer[129]; //buffer size is computed through this: 512 bits / 8 = 64 bytes | 64 * 2 (hex combination) = 128 | 128 + 1 = 129
	sha512_file("lena512color.tiff", buffer);
	printf("%s\n", buffer);
}


