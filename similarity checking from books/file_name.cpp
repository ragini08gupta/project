#include <iostream>
#include <fstream>
#include <filesystem>

int main() {
    const std::string directoryPath = "C:\\Similarity Checking from Books\\Book-Txt\\Book-Txt";
    const std::string outputPath = "file_list.txt";
    
    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << outputPath << std::endl;
        return 1;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            outputFile << entry.path().filename().string() << std::endl;
        }
    }

    outputFile.close();
    std::cout << "File list created successfully in file_list.txt." << std::endl;
    return 0;
}