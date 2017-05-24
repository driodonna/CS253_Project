#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

void encrypt(FILE *src, FILE *dest, unsigned char *key){
    EVP_CIPHER_CTX ctx;
	int destSize1 = 0, destSize2 = 0, srcSize;
    unsigned char *srcData, *destData;
   
	fseek(src, 0L, SEEK_END); //how to get file size (https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c)
    srcSize = ftell(src);
	rewind(src);

	srcData = malloc(srcSize);
    destData = malloc(srcSize*2);

    fread(srcData,sizeof(char),srcSize, src); //reading the src file

	//how to set up the encryption (https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption)
  	if(1 != EVP_EncryptInit(&ctx,EVP_aes_128_ecb(),key,NULL)) handleErrors();
  	if(1 != EVP_EncryptUpdate(&ctx,destData,&destSize1,srcData,srcSize)) handleErrors();
  	if(1 != EVP_EncryptFinal(&ctx,destData + destSize1,&destSize2)) handleErrors();
	fwrite(destData,sizeof(char),destSize1 + destSize2,dest);
}

void decrypt(FILE *src, FILE *dest, unsigned char *key){
    EVP_CIPHER_CTX ctx;
	int destSize1 = 0, destSize2 = 0, srcSize;
    unsigned char *srcData, *destData;
   
	fseek(src, 0L, SEEK_END); //how to get file size (https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c)
    srcSize = ftell(src);
	rewind(src);

	srcData = malloc(srcSize);
    destData = malloc(srcSize*2);

    fread(srcData,sizeof(char),srcSize, src); //reading the src file

	//how to set up the encryption (https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption)
	if(1 != EVP_DecryptInit(&ctx,EVP_aes_128_ecb(),key,NULL)) handleErrors();
	if(1 != EVP_DecryptUpdate(&ctx,destData,&destSize1,srcData,srcSize)) handleErrors();
	if(1 != EVP_DecryptFinal(&ctx,destData + destSize1,&destSize2)) handleErrors();
  	fwrite(destData,sizeof(char),destSize1 + destSize2,dest);


}

int main(int argc, char *argv[]){        
    
	unsigned char *key =  "0123456789012345";  //set up key and initialiaztion vector
	FILE *src, *dest;
	
    src = fopen("lena512color.tiff", "rb");	//encrypt the lena image
    dest = fopen("ecb_ciphertext.txt", "wb"); //output the ciphertext
    encrypt(src, dest, key); //encrypt function
    fclose(src);
    fclose(dest);

    src = fopen("ecb_ciphertext.txt", "rb"); //read the ciphertext
    dest = fopen("ecb_decrypted.tiff", "wb"); //decrypt the ciphertext
    decrypt(src,dest, key);
    fclose(src);
    fclose(dest);

    return 0;
}
