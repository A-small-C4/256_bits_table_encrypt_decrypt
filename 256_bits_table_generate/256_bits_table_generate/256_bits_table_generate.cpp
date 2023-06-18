#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

int main()
{
    // declare and initialize array
    int encrpyt_int[256];
    for (int i = 0; i < 256; i++)
    {
        encrpyt_int[i] = i;
    }

    // create random number generator
    std::mt19937 rng(std::random_device{}());

    // shuffle array
    std::shuffle(std::begin(encrpyt_int), std::end(encrpyt_int), rng);

    char encrpyt_char[256];
    for (int i = 0; i < 256; i++)
    {
        encrpyt_char[i] = encrpyt_int[i];
    }

    // print array
    for (char x : encrpyt_char)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::ofstream encrpyt_table("encrpyt.hex", std::ios::binary);
    if (encrpyt_table.is_open()) {
        encrpyt_table.write(encrpyt_char, sizeof(encrpyt_char));
        encrpyt_table.close();
    }

    // declare and initialize inverse decrypt array
    int decrypt_int[256];
    for (int i = 0; i < 256; i++)
    {
        decrypt_int[i] = i;
    }

    // create inverse array
    for (int i = 0; i < 256; i++)
    {
        decrypt_int[encrpyt_int[i]] = i;
    }

    char decrypt_char[256];
    for (int i = 0; i < 256; i++)
    {
        decrypt_char[i] = decrypt_int[i];
    }


    // print inverse array
    for (char x : decrypt_char)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::ofstream decrypt_table("decrypt.hex", std::ios::binary);
    if (decrypt_table.is_open()) {
        decrypt_table.write(decrypt_char, sizeof(decrypt_char));
        decrypt_table.close();
    }

    return 0;
}
