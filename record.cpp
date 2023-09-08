#include <tuple>

#include "record.hpp"

bool operator==(const Record& lhs, const Record& rhs) {
  return std::tie(lhs.name, lhs.x, lhs.y, lhs.type, lhs.timestamp) ==
         std::tie(rhs.name, rhs.x, rhs.y, rhs.type, rhs.timestamp);
}

std::size_t RecordHasher::operator()(const Record& record) const {
  const std::size_t x = 17;

  const std::size_t name_hash = std::hash<std::string>{}(record.name);
  const std::size_t x_hash = std::hash<double>{}(record.x);
  const std::size_t y_hash = std::hash<double>{}(record.y);
  const std::size_t type_hash = std::hash<std::string>{}(record.type);
  const std::size_t timestamp_hash = std::hash<double>{}(record.timestamp);

  return (name_hash * std::pow(x, 4) + x_hash * std::pow(x, 3) +
          y_hash * std::pow(x, 2) + type_hash * std::pow(x, 1) +
          timestamp_hash);
}

double getDist(double x, double y) {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

bool CmpName::operator()(const Record& lhs, const Record& rhs) {
  return lhs.name < rhs.name;
}

bool CmpX::operator()(const Record& lhs, const Record& rhs) {
  return lhs.x < rhs.x;
}

bool CmpY::operator()(const Record& lhs, const Record& rhs) {
  return lhs.y < rhs.y;
}

bool CmpType::operator()(const Record& lhs, const Record& rhs) {
  return lhs.type < rhs.type;
}

bool CmpTimestamp::operator()(const Record& lhs, const Record& rhs) {
  return lhs.timestamp < rhs.timestamp;
}

bool CmpDistination::operator()(const Record& lhs, const Record& rhs) {
  return getDist(lhs.x, lhs.y) < getDist(rhs.x, rhs.y);
}
