#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "storage.hpp"

namespace file_manager {
const std::string kDefaultInputPath = "input_records.txt";
const std::string kDefaultOutputPath = "output_records.txt";

void ParseFile(Storage& storage, const std::string& file_path);

void ClearFile(const std::string& file_path);

template <typename Records>
void WriteToFile(const Records& records, const std::string& file_path) {
  std::ofstream outputFile(file_path, std::ios::app);
  if (outputFile.is_open()) {
    for (const auto& record : records) {
      outputFile << record.name << " " << record.x << " " << record.y << " "
                 << record.type << " " << record.timestamp << "\n";
    }
    outputFile.close();
  } else {
    std::cerr << "Failed to open the output file." << std::endl;
  }
}
}  // namespace file_manager
