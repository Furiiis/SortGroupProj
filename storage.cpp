#include "storage.hpp"

Storage::Storage(const Storage& other) {
  unique_records_ = other.unique_records_;
  records_ = other.records_;
}
std::list<Record> Storage::get() const { return records_; }

void Storage::add(const Record& record) {
  bool is_dublicate = !unique_records_.insert(record).second;
  if (is_dublicate) return;
  records_.push_back(record);
}
