#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>
#include <string.h>
#include <QString>

class AES_CBC
{

public:
    explicit AES_CBC();
    ~AES_CBC();
    QByteArray encrypt(QByteArray input);
    QByteArray decrypt(QByteArray input);


private:
    uint8_t *key;
    uint8_t *iv;

    const char * base64char;

    int encrypt_buf_len(int length);
    int base64_enc_len(int plainLen);
    char *base64_encode(char * base64, const unsigned char * bindata, int binlength);
    uint8_t base64_decode(const char * base64, unsigned char * bindata);

};
#endif //_AES_H_
