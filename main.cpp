/*
# ___________________________________________________________
# ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
# CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
#
# #RVCGEEKS rvcvault
# created on 27.01.2019
# 
# AES 128 bit file Encryption / Decryption
#
*/

#include<iostream>
#include<fstream>
#include"aes.h"
#include"banners.c"
#define PIPE_CHUNK_SIZE 1024 //process 1 kB of data at a time
using namespace std;
//assuming that keyfile and initialization vector file smaller than plaintext... however will work fine with opposite case as well

int vault(fstream& _Utter_trash_,fstream& _My_Precious_ ,fstream& _Key_,fstream& _init_vec_,char _AES_Mode_[],char _Mode_){
     unsigned char block[PIPE_CHUNK_SIZE],key[AES_SIZE],initialization_vector[AES_SIZE];int cnt=0;
    void (*ecb_worker)(unsigned char*,unsigned char*,int);
    void (*cbc_worker)(unsigned char*,unsigned char*,int,unsigned char*);
    ecb_worker=_Mode_=='e'?aes_ecb_encrypt:aes_ecb_decrypt;
    cbc_worker=_Mode_=='e'?aes_cbc_encrypt:aes_cbc_decrypt;
    bool is_cbc=!strcmp(_AES_Mode_,"-cbc");
    while(!_My_Precious_.eof()){
        memset(block,0,sizeof(block));
        memset(key,0,sizeof(key));
        memset(initialization_vector,0,sizeof(initialization_vector));
        _My_Precious_.read(reinterpret_cast<char*>(&block),sizeof(block));
        if(_Key_.eof())_Key_.seekg(0);                        
        _Key_.read(reinterpret_cast<char*>(&key),AES_SIZE);
        if(is_cbc){
            if(_init_vec_.eof())_init_vec_.seekg(0); 
            _init_vec_.read(reinterpret_cast<char*>(&initialization_vector),AES_SIZE);
            cbc_worker(
                reinterpret_cast<unsigned char*>(block),
                reinterpret_cast<unsigned char*>(key),
                PIPE_CHUNK_SIZE,
                reinterpret_cast<unsigned char*>(initialization_vector)
            );
        }else ecb_worker(
            reinterpret_cast<unsigned char*>(block),
            reinterpret_cast<unsigned char*>(key),
            PIPE_CHUNK_SIZE
        );
        _Utter_trash_.write(reinterpret_cast<char*>(&block),PIPE_CHUNK_SIZE);
        cout<<"\e[?25l"<<(++cnt)/float(1024)<<" MB of "<<(_Mode_=='e'?"encryption":"decryption")<<" done...\033[40D";
    }return cnt;
}

int main(int argc,char **argv){
    cout<<hackergirl<<"\n     \033[107;41m AES (Advanced Encryption Standard) 128 bit secure file encryption/decryption :: Rijndael S-box by @rvcgeeks____ \033[0m\n";
    if(argc<2){
        cout<<"\n SYNOPSIS:\n"
              "   ~$ "<<argv[0]<<" -ecb [-e|-d] [precious file path] [keyfile path] [output file path]\n"
              "   ~$ "<<argv[0]<<" -cbc [-e|-d] [precious file path] [keyfile path] [output file path] [initialization vector file path]\n\n"
              " USAGE:\n"
              "   Encrypt your precious files by a key file...\n"
              "   '-e' encryption mode.\n   '-d' decryption mode.\n"
              "   '-ecb' is for Electronic Code Book mode of AES\n"
              "   '-cbc' is for Cipher Block Chaining mode of AES\n\n"
              " Type 'man rvcvault' for detailed command syntax...\n\n";
        return 0;
    }fstream my_precious(argv[3],ios::in|ios::binary),
            keyfile(argv[4],ios::in|ios::binary),init_vec_file,
            utter_thrash(argv[5],ios::out|ios::binary);
    if(strcmp(argv[1],"-cbc")&&strcmp(argv[1],"-ecb"))
        cout<<"Please specify AES mode '-cbc' (Cipher Block Chaining) or '-ecb' (Electronic Code Book) ...\n\n";
    else if(strcmp(argv[2],"-e")&&strcmp(argv[2],"-d"))
        cout<<"What to do with input files ?!? :/ flag is either -e or -d\n"<<argv[2]<<" is a wrong flag ...aborting!!!\n\n";
    else if(!my_precious.is_open())
        cout<<"FATAL ERROR: Unable to open your input file "<<argv[3]<<" ...aborting!!!\n\n";
    else if(!keyfile.is_open())
        cout<<"FATAL ERROR: Unable to open your key file "<<argv[4]<<" ...aborting!!!\n\n";
    else if(!utter_thrash.is_open())
        cout<<"FATAL ERROR: Internal error: Unable to create a new file "<<argv[5]<<" ...aborting!!!\n\n";
    else{int k;
        if(!strcmp(argv[1],"-cbc")){
            init_vec_file.open(argv[6],ios::in|ios::binary);
            if(!init_vec_file.is_open()){
                cout<<"FATAL ERROR: Unable to open initialization vector file "<<argv[2]<<" ...aborting!!!\n\n";
                return 0;
            }
        }k=vault(utter_thrash,my_precious,keyfile,init_vec_file,argv[1],argv[2][1]);
        init_vec_file.close();my_precious.close();keyfile.close();utter_thrash.close();
        cout<<endl<<skull<<"\n\033[107;41m"<<argv[3]<<"\033[0m ("<<k<<" kB) has been "<<(argv[2][1]=='e'?"encrypted":"decrypted")<<" to \033[107;41m"<<argv[5]<<"\033[0m using keyfile \033[107;41m"<<argv[4]<<"\033[0m by \033[107;41m"<<argv[0]<<"\033[0m\033[0m !!!\e[?25h"<<endl;
    }return 0;
}