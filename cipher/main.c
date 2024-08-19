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

    // ��� �� ��� �� �е��� ���� ���� ����
    int blockCount = (originLen % (BLOCKSIZE * 4)) ? (originLen / (BLOCKSIZE * 4) + 1) : (originLen / (BLOCKSIZE * 4));
    int paddedLen = blockCount * BLOCKSIZE * 4;

    BYTE eResult[128] = { 0, };  // ��ȣȭ ��� ����
    BYTE padded_origin[128] = { 0, };  // �е��� ���� ������
    memcpy(padded_origin, origin, originLen);  // ���� �����͸� �����Ͽ� �е��� �迭�� ����

    // AES ��ȣȭ
    for (int i = 0; i < blockCount; i++)
    {
        AESEncrypt(&padded_origin[i * BLOCKSIZE * 4], &eResult[i * BLOCKSIZE * 4], key);
    }

    // ��ȣȭ ��� ���
    printf("encryption result : ");
    PrintHex(eResult, paddedLen);

    // AES ��ȣȭ
    BYTE dResult[128] = { 0, };
    for (int i = 0; i < blockCount; i++)
    {
        AESDecrypt(&eResult[i * BLOCKSIZE * 4], &dResult[i * BLOCKSIZE * 4], key);
    }

    printf("decryption result : %s\n", dResult);  // ��ȣȭ�� ��� ���

    return 0;
}
