#pragma once
#include <list>
#include <unordered_set>

#include "record.hpp"

class Storage {
  std::unordered_set<Record, RecordHasher> unique_records_;
  std::list<Record> records_;

 public:
  Storage() = default;
  Storage(const Storage& other);
  std::list<Record> get() const;
  void add(const Record& record);
};
