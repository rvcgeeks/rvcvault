#include<iostream>
#include"aes_lib/aes.h"
using namespace std;

int main() {

    //Electronic Code Book (ECB) mode
    unsigned char message[] = "I LOVE 2 ENCRYPT WORDS WITH AES!";
    unsigned char key[] = "YELLOW SUBMARINE";

    cout<<"This message will be encrypted using ECB mode: "<<message<<endl;
    cout<<"With this key: "<<key<<endl;
    aes_ecb_encrypt(message, key, 32);
    cout<<"Here is the encrypted result: "<<message<<endl;
    aes_ecb_decrypt(message, key, 32);
    cout<<"Here is the decrypted message: "<<message<<"\n\n";

    
    //Cipher Block Chaining (CBC) mode, Initilization Vector (IV) required
    memcpy(message, "I LOVE 2 ENCRYPT WORDS WITH CBC!" ,32);
    memcpy(key, "HERE IS MY KEY!!",16);
    unsigned char iv[] = "HERE IS MY IV!!!";

    cout<<"This message will be encrypted using CBC mode: "<<message<<endl;
    cout<<"With this key: "<<key<<" and this IV: "<<iv<<endl;
    aes_cbc_encrypt(message, key, 32, iv);
    cout<<"Here is the encrypted result: "<<message<<endl;
    aes_cbc_decrypt(message, key, 32, iv);
    cout<<"Here is the decrypted message: "<<message<<endl;
    return 0;

}