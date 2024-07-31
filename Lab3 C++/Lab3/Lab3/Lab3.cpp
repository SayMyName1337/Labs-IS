//#include <iostream>
//#include <gcrypt.h>
//
//using namespace std;
//
//int main() {
//    gcry_error_t gcryError;
//    gcry_md_hd_t gcryMdHd;
//    const char* plaintext = "The quick brown fox jumps over the lazy dog";
//    const char* key = "secretkey";
//
//    gcryError = gcry_md_open(&gcryMdHd, GCRY_MD_WHIRLPOOL, 0);
//    if (gcryError) {
//        cout << "gcry_cipher_open error: " << gcry_strsource(gcryError) << endl;
//        return 1;
//    }
//
//    gcryError = gcry_cipher_setkey(gcryCipherHd, key, strlen(key));
//    if (gcryError) {
//        cout << "gcry_cipher_setkey error: " << gcry_strsource(gcryError) << endl;
//        gcry_cipher_close(gcryCipherHd);
//        return 1;
//    }
//
//    gcryError = gcry_cipher_encrypt(gcryCipherHd, plaintext, strlen(plaintext), NULL, 0);
//    if (gcryError) {
//        cout << "gcry_cipher_encrypt error: " << gcry_strsource(gcryError) << endl;
//        gcry_cipher_close(gcryCipherHd);
//        return 1;
//    }
//
//    gcry_cipher_close(gcryCipherHd);
//
//    cout << "Whirlpool hash of the plaintext is: " << plaintext << endl;
//
//    return 0;
//}

//#include <iostream>
//#include <gcrypt.h>
//
//using namespace std;
//
//int main() {
//    gcry_error_t gcryError;
//    gcry_md_hd_t gcryMdHd;
//    const char* plaintext = "Hello";
//
//    gcryError = gcry_md_open(&gcryMdHd, GCRY_MD_WHIRLPOOL, 0);
//    if (gcryError) {
//        cout << "gcry_md_open error: " << gcry_strsource(gcryError) << endl;
//        return 1;
//    }
//
//    gcry_md_write(gcryMdHd, plaintext, strlen(plaintext));
//
//    const int size = gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL);
//    cout << size;
//    cout << "\n";
//
//    gcry_md_final(gcryMdHd);
//    unsigned char* digest = gcry_md_read(gcryMdHd, 0);
//    //gcry_md_extract(gcryMdHd, GCRY_MD_WHIRLPOOL, &digest, gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL));
//    /*if (!digest) {
//        cout << "gcry_md_read error" << endl;
//        gcry_md_close(gcryMdHd);
//        return 1;
//    }*/
//
//    gcry_md_close(gcryMdHd);
//
//    cout << "Whirlpool hash of the plaintext is: ";
//    // cout << hex << digest; gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL)
//    for (int i = 0; i < gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL) - 1; i++) {
//        printf("%02x", digest[i]);
//    }
//    cout << endl;
//
//    return 0;
//}


//#include <iostream>
//#include <gcrypt.h>
//
//using namespace std;
//
//int main() {
//    gcry_error_t gcryError;
//    gcry_md_hd_t gcryMdHd;
//    const char* plaintext = "The quick brown fox jumps over the lazy dog";
//    const int size = gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL);
//
//    gcryError = gcry_md_open(&gcryMdHd, GCRY_MD_WHIRLPOOL, 0);
//    if (gcryError) {
//        cout << "gcry_md_open error: " << gcry_strsource(gcryError) << endl;
//        return 1;
//    }
//
//    gcry_md_write(gcryMdHd, plaintext, strlen(plaintext));
//
//    unsigned char digest[gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL)];
//    gcry_md_read(gcryMdHd, GCRY_MD_WHIRLPOOL, digest);
//
//    gcry_md_close(gcryMdHd);
//
//    cout << "Whirlpool hash of the plaintext is: ";
//    for (int i = 0; i < gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL); i++) {
//        printf("%02x", digest[i]);
//    }
//    cout << endl;
//
//    return 0;
//}


#include <iostream>
#include <gcrypt.h>

using namespace std;

int main() {
    gcry_error_t gcryError;
    gcry_md_hd_t gcryMdHd;
    const char* plaintext = "The quick brown fox jumps over the lazy dog";

    gcryError = gcry_md_open(&gcryMdHd, GCRY_MD_WHIRLPOOL, 0);
    if (gcryError) {
        cout << "gcry_md_open error: " << gcry_strsource(gcryError) << endl;
        return 1;
    }

    gcry_md_write(gcryMdHd, plaintext, strlen(plaintext));

    unsigned char* digest = new unsigned char[gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL)];
    gcry_md_read(gcryMdHd, GCRY_MD_WHIRLPOOL);

    gcry_md_close(gcryMdHd);

    cout << "Whirlpool hash of the plaintext is: ";
    for (int i = 0; i < gcry_md_get_algo_dlen(GCRY_MD_WHIRLPOOL); i++) {
        printf("%02x", digest[i]);
    }
    cout << endl;

    delete[] digest;

    return 0;
}

