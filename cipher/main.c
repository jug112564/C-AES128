#include "AES128.h"
#include <stdio.h>
#include <string.h>

void PrintHex(BYTE* hexValue, int valueLen)
{
    for (int i = 0; i < valueLen; i++)
    {
        printf("%02x", hexValue[i]);
    }
    printf("\n");
}

int main()
{
    // Test
    printf("<test>\n");

    BYTE origin[64] = "Hello Wolrd 1234! This is an 5678example text *&!#";
    int originLen = strlen((char*)origin);
    printf("origin text : %s\n", origin);

    AESKEY key[16] = { 0x26, 0x7f, 0xb8, 0x06, 0xa2, 0x7e, 0xb4, 0xa8, 0x47, 0x8a, 0x04, 0x68 , 0xfd, 0x11, 0xef, 0x05 };

    printf("key value : ");
    PrintHex(key,16);

    // 블록 수 계산 및 패딩을 위한 길이 조정
    int blockCount = (originLen % (BLOCKSIZE * 4)) ? (originLen / (BLOCKSIZE * 4) + 1) : (originLen / (BLOCKSIZE * 4));
    int paddedLen = blockCount * BLOCKSIZE * 4;

    BYTE eResult[128] = { 0, };  // 암호화 결과 저장
    BYTE padded_origin[128] = { 0, };  // 패딩된 원본 데이터
    memcpy(padded_origin, origin, originLen);  // 원본 데이터를 복사하여 패딩된 배열에 저장

    // AES 암호화
    for (int i = 0; i < blockCount; i++)
    {
        AESEncrypt(&padded_origin[i * BLOCKSIZE * 4], &eResult[i * BLOCKSIZE * 4], key);
    }

    // 암호화 결과 출력
    printf("encryption result : ");
    PrintHex(eResult, paddedLen);

    // AES 복호화
    BYTE dResult[128] = { 0, };
    for (int i = 0; i < blockCount; i++)
    {
        AESDecrypt(&eResult[i * BLOCKSIZE * 4], &dResult[i * BLOCKSIZE * 4], key);
    }

    printf("decryption result : %s\n", dResult);  // 복호화된 결과 출력

    return 0;
}
