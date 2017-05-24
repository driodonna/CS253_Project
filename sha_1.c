#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>


//https://stackoverflow.com/questions/9284420/how-to-use-sha1-hashing-in-c-programming

void compute_sha1(char *string, char output[41]) //https://stackoverflow.com/questions/26441931/sha1-encoding-to-hex-has-40-characters-and-160-bits?rq=1
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, string, strlen(string));
    SHA1_Final(hash, &ctx);
    int i = 0;
    for(i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[40] = 0;
}

void sha1_file(char *filename, char output[41]){
    FILE *file = fopen(filename, "rb");
    unsigned char hash[SHA_DIGEST_LENGTH];
    const int bufferSize = 32768;
    char *buffer = malloc(bufferSize);
    int bytesRead = 0;

	
	SHA_CTX ctx;
    SHA1_Init(&ctx);
    while((bytesRead = fread(buffer, 1, bufferSize, file)))
    {
        SHA1_Update(&ctx, buffer, bytesRead);
    }
    SHA1_Final(hash, &ctx);

    compute_sha1(hash, output);
    fclose(file);
    free(buffer);
}


int main(){
    static unsigned char buffer[41]; //buffer size is computed through this: 160 bits / 8 = 20 bytes | 20 * 2 (hex combination) = 40 | 40 + 1 = 41
	sha1_file("lena512color.tiff", buffer);
	printf("%s\n", buffer);
}


