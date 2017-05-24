# CS253_Project

To be able to run the following C programs, OpenSSL should have been configured upon installation so that it will be located in the /usr/local directory. Example setting is: $ ./config --prefix=/usr/local --openssldir=/usr/local/openssl. Had you installed it on a different directory, you should specify on the command where your installation is located using the -I option. 

Moreover, the linker may encounter errors on finding some of the functions used. To avoid this, one should also include in the command the libraries to be linked.

The following are the commands to run the programs:

symmetric encryption: gcc symmetric_cbc.c -lssl -lcrypto -ldl | gcc symmetric_ecb.c -lssl -lcrypto -ldl
hashing: gcc sha_256.c -lssl -lcrypto | gcc sha_512.c -lssl -lcrypto | gcc sha_1.c -lssl -lcrypto
