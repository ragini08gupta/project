// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <map>
// #include <algorithm>

// // Function to convert string to uppercase
// std::string toUppercase(const std::string& str) {
//     std::string result;
//     for (char c : str) {
//         result += std::toupper(c);
//     }
//     return result;
// }

// // Function to remove common words from a string
// std::string removeCommonWords(const std::string& str) {
//     const std::vector<std::string> commonWords = {"a", "and", "an", "of", "in", "the"};
//     std::istringstream iss(str);
//     std::ostringstream oss;
    
//     std::string word;
//     while (iss >> word) {
//         if (std::find(commonWords.begin(), commonWords.end(), word) == commonWords.end()) {
//             oss << word << " ";
//         }
//     }
    
//     return oss.str();
// }

// // Function to count frequent words and calculate normalization
// void countFrequentWords(const std::string& str, std::map<std::string, int>& wordCount) {
//     std::istringstream iss(str);
//     std::string word;
    
//     while (iss >> word) {
//         wordCount[toUppercase(word)]++;
//     }
// }

// // Function to calculate similarity index
// int calculateSimilarityIndex(const std::map<std::string, int>& wordCount1,
//                              const std::map<std::string, int>& wordCount2) {
//     int similarity = 0;
//     for (const auto& pair : wordCount1) {
//         if (wordCount2.find(pair.first) != wordCount2.end()) {
//             similarity += pair.second * wordCount2.at(pair.first);
//         }
//     }
//     return similarity;
// }

// // Function to find top 10 similar pairs
// void findTopSimilarPairs(const std::vector<std::map<std::string, int>>& wordCounts,
//                           std::vector<std::pair<int, int>>& similarPairs) {
//     int n = wordCounts.size();
    
//     // Create similarity matrix
//     std::vector<std::vector<int>> similarityMatrix(n, std::vector<int>(n));
//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             similarityMatrix[i][j] = calculateSimilarityIndex(wordCounts[i], wordCounts[j]);
//             similarityMatrix[j][i] = similarityMatrix[i][j];
//         }
//     }
//     // Print similarity matrix
//     std::cout << "Similarity Matrix:" << std::endl;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             std::cout << similarityMatrix[i][j] << "\t";
//         }
//         std::cout << std::endl;
//     }
 
    
//     // Find top 10 similar pairs excluding self-similarity
//     std::vector<std::pair<int, int>> allPairs;
//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             allPairs.emplace_back(i, j);
//         }
//     }
    
//     std::sort(allPairs.begin(), allPairs.end(), [&](const std::pair<int, int>& p1,
//                                                      const std::pair<int, int>& p2) {
//         return similarityMatrix[p1.first][p1.second] > similarityMatrix[p2.first][p2.second];
//     });
    
//     similarPairs.resize(10);
//     for (int i = 0; i < 10 && i < allPairs.size(); i++) {
//         similarPairs[i] = allPairs[i];
//     }
// }

// int main() {
//     const std::string directoryPath = "C:\\Similarity Checking from Books\\Book-Txt\\Book-Txt";
    
//     std::vector<std::map<std::string, int>> wordCounts(64);
    
//     // Read all 64 text files and preprocess them
//     for (int i = 0; i < 64; i++) {
//         std::string filePath = directoryPath + "\\Book" + std::to_string(i + 1) + ".txt";
//         std::ifstream file(filePath);
//         if (!file.is_open()) {
//             std::cerr << "Error opening file: " << filePath << std::endl;
//             return 1;
//         }
        
//         std::string content((std::istreambuf_iterator<char>(file)),
//                             std::istreambuf_iterator<char>());
//         content = removeCommonWords(content);
        
//         countFrequentWords(content, wordCounts[i]);
//         file.close();
//     }
    
//     std::vector<std::pair<int, int>> similarPairs;
//     findTopSimilarPairs(wordCounts, similarPairs);
    
//     std::cout << "Top 10 similar pairs of textbooks:" << std::endl;
//     for (const auto& pair : similarPairs) {
//         std::cout << "Book " << pair.first + 1 << " and Book " << pair.second + 1 << std::endl;
//     }
    
//     return 0;
// }
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Function to convert string to uppercase
std::string toUppercase(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::toupper(c);
    }
    return result;
}

// Function to remove common words from a string
std::string removeCommonWords(const std::string& str) {
    const std::vector<std::string> commonWords = {"a", "and", "an", "of", "in", "the"};
    std::istringstream iss(str);
    std::ostringstream oss;
    
    std::string word;
    while (iss >> word) {
        if (std::find(commonWords.begin(), commonWords.end(), word) == commonWords.end()) {
            oss << word << " ";
        }
    }
    
    return oss.str();
}

// Function to count frequent words
void countFrequentWords(const std::string& str, std::map<std::string, int>& wordCount) {
    std::istringstream iss(str);
    std::string word;
    
    while (iss >> word) {
        wordCount[toUppercase(word)]++;
    }
}

// Function to calculate similarity index
int calculateSimilarityIndex(const std::map<std::string, int>& wordCount1,
                             const std::map<std::string, int>& wordCount2) {
    int similarity = 0;
    for (const auto& pair : wordCount1) {
        if (wordCount2.find(pair.first) != wordCount2.end()) {
            similarity += pair.second * wordCount2.at(pair.first);
        }
    }
    return similarity;
}

// Function to find top 10 similar pairs
void findTopSimilarPairs(const std::vector<std::map<std::string, int>>& wordCounts,
                         std::vector<std::pair<int, int>>& similarPairs) {
    int n = wordCounts.size();
    
    // Create similarity matrix
    std::vector<std::vector<int>> similarityMatrix(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            similarityMatrix[i][j] = calculateSimilarityIndex(wordCounts[i], wordCounts[j]);
            similarityMatrix[j][i] = similarityMatrix[i][j];
        }
    }

    // Print similarity matrix
    std::cout << "Similarity Matrix:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << similarityMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    // Find top 10 similar pairs excluding self-similarity
    std::vector<std::pair<int, int>> allPairs;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            allPairs.emplace_back(i, j);
        }
    }
    
    std::sort(allPairs.begin(), allPairs.end(), [&](const std::pair<int, int>& p1,
                                                     const std::pair<int, int>& p2) {
        return similarityMatrix[p1.first][p1.second] > similarityMatrix[p2.first][p2.second];
    });
    
    similarPairs.resize(10);
    for (int i = 0; i < 10 && i < allPairs.size(); i++) {
        similarPairs[i] = allPairs[i];
    }
}

int main() {
    const std::string directoryPath = "C:\\Similarity Checking from Books\\Book-Txt\\Book-Txt";
    
    std::vector<std::map<std::string, int>> wordCounts;
    std::vector<std::string> filenames;
    
    // Open the file list and read each filename
    std::ifstream fileList("file_list.txt");
    if (!fileList.is_open()) {
        std::cerr << "Error opening file list." << std::endl;
        return 1;
    }

    std::string filename;
    while (std::getline(fileList, filename)) {
        std::string filePath = directoryPath + "\\" + filename;
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            continue;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        content = removeCommonWords(content);
        
        std::map<std::string, int> wordCount;
        countFrequentWords(content, wordCount);
        wordCounts.push_back(wordCount);
        filenames.push_back(filename);
        
        file.close();
    }
    fileList.close();
    
    std::vector<std::pair<int, int>> similarPairs;
    findTopSimilarPairs(wordCounts, similarPairs);
    
    std::cout << "Top 10 similar pairs of books:" << std::endl;
    for (const auto& pair : similarPairs) {
        std::cout << filenames[pair.first] << " and " << filenames[pair.second] << std::endl;
    }
    
    return 0;
}