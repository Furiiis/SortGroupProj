#include "file_manager.hpp"

#include <sstream>

void file_manager::ParseFile(Storage& storage, const std::string& file_path) {
  std::ifstream inputFile(file_path);
  if (inputFile.is_open()) {
    std::string line;
    while (std::getline(inputFile, line)) {
      Record record;
      std::istringstream iss(line);

      if (iss >> record.name >> record.x >> record.y >> record.type >>
          record.timestamp) {
        storage.add(std::move(record));
      } else {
        std::cerr << "Failed to parse record: " << line << std::endl;
      }
    }

    inputFile.close();
  } else {
    std::cerr << "Failed to open the input file." << std::endl;
  }
}

void file_manager::ClearFile(const std::string& file_path) {
  std::ofstream outputFile(file_path, std::ios::trunc);
  if (outputFile.is_open()) {
    outputFile.close();
  } else {
    std::cerr << "Failed to open the file for clearing." << std::endl;
  }
}
