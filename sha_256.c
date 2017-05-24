#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>



void compute_sha256(char *string, char output[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, string, strlen(string));
    SHA256_Final(hash, &ctx);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = 0;
}

void sha256_file(char *filename, char output[65]){
    FILE *file = fopen(filename, "rb");
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const int bufferSize = 32768; //https://stackoverflow.com/questions/7015544/calculating-a-hash-code-for-a-large-file-in-parallel
    char *buffer = malloc(bufferSize);
    int bytesRead = 0;

	SHA256_CTX ctx;
    SHA256_Init(&ctx);
    while((bytesRead = fread(buffer, 1, bufferSize, file)))
    {
        SHA256_Update(&ctx, buffer, bytesRead);
    }
    SHA256_Final(hash, &ctx);

    compute_sha256(hash, output);
    fclose(file);
    free(buffer);
}


int main(){
    static unsigned char buffer[65]; //buffer size is computed through this: 256 bits / 8 = 32 bytes | 32 * 2 (hex combination) = 64 | 64 + 1 = 65
	sha256_file("lena512color.tiff", buffer);
	printf("%s\n", buffer);
}


