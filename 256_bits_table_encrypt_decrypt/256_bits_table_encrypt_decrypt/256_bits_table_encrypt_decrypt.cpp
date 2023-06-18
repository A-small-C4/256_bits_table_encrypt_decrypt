#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include <string>

int main(int argc, char* argv[]) {
    // Create a map of hexadecimal values and their replacements
    std::map<char, char> hex_table;

    // Open the table file as a binary stream
    std::ifstream table("table.hex", std::ios::binary);

    // Check if the file is opened successfully
    if (table.is_open()) {
        // Get the size of the file
        table.seekg(0, std::ios::end);
        int size = table.tellg();
        table.seekg(0, std::ios::beg);

        // Create an array of char to store the file content
        char* buffer = new char[size];

        // Read the file into the buffer
        table.read(buffer, size);

        // Close the file
        table.close();

        // Populate the map with the values from the buffer
        for (int i = 0; i < size; i++) {
            hex_table['\x00' + i] = buffer[i];
        }

        // Delete the buffer
        delete[] buffer;
    }
    else {
        std::cerr << "Error opening table file\n";
    }

    std::string output_file_name = argv[1];
    output_file_name += ".txt";

    // Open the file as a binary stream
    std::ifstream input(argv[1], std::ios::binary);
    std::ofstream output(output_file_name, std::ios::binary);

    // Check if the file is opened successfully
    if (input.is_open() && output.is_open()) {
        // Read one byte at a time
        char byte;
        while (input.get(byte)) {
            // Check if the byte is in the map
            if (hex_table.count(byte) > 0) {
                // Replace the byte with the mapped value
                output.put(hex_table[byte]);
            }
            else {
                // Copy the byte as it is
                output.put(byte);
            }
        }
        // Close the files
        input.close();
        output.close();
        std::cout << "Done!\n";
    }
    else {
        std::cerr << "Error opening file\n";
    }
    return 0;
}