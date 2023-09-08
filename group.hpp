#pragma once
#include <codecvt>
#include <functional>
#include <list>
#include <locale>
#include <string>
#include <vector>

#include "record.hpp"

class Group {
  using Comparator = std::function<int(const Record&)>;
  std::vector<Comparator> group_sequence_;

 public:
  Group& group(Comparator cmp);
  std::vector<int> getSequenceOfGroupIndexes(const Record& rec) const;
};

struct GroupByDistination {
  int operator()(const Record& rec);
};

struct GroupByName {
  int operator()(const Record& rec);
};

struct GroupByTime {
  int operator()(const Record& rec);
};

class GroupByType {
  struct TypeInfo {
    int index;
    int count;
  };
  int objects_count_;
  std::unordered_map<std::string, TypeInfo> types_;

 public:
  GroupByType(const std::list<Record>& from_types, int count);

  int operator()(const Record& rec);
};
