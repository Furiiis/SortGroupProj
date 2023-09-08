#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "file_manager.hpp"
#include "group.hpp"
#include "record.hpp"
#include "storage.hpp"

void GroupAndSortBy(Storage storage_snapshot, const auto& sort_chain,
                    const Group& group) {
  using Groups = std::vector<int>;
  std::map<Groups, std::vector<Record>> by_group;
  for (const Record& record : storage_snapshot.get()) {
    by_group[group.getSequenceOfGroupIndexes(record)].push_back(record);
  }

  for (auto& [prop_val, objects] : by_group) {
    std::sort(objects.begin(), objects.end(), sort_chain);
  }

  for (auto& [prop_val, objects] : by_group) {
    file_manager::WriteToFile(objects, file_manager::kDefaultOutputPath);
  }
}

int main() {
  Storage storage;
  file_manager::ParseFile(storage, file_manager::kDefaultInputPath);

  for (std::string line; std::cout << "write your line: " << std::endl,
                         std::getline(std::cin, line);) {
    file_manager::ClearFile(file_manager::kDefaultOutputPath);
    std::istringstream is(line);
    std::string command;
    is >> command;
    if (command == "GroupBy") {
      std::string group_type;
      is >> group_type;
      if (group_type == "Distination") {
        GroupAndSortBy(storage, make_chain(CmpDistination()),
                       Group().group(GroupByDistination()));
      } else if (group_type == "Name") {
        GroupAndSortBy(storage, make_chain(CmpName()),
                       Group().group(GroupByName()));
      } else if (group_type == "Type") {
        int object_count;
        is >> object_count;
        GroupAndSortBy(storage, make_chain(CmpName()),
                       Group().group(GroupByType(storage.get(),
                       object_count)));
      } else if (group_type == "Time")
        GroupAndSortBy(storage, make_chain(CmpTimestamp()),
                       Group().group(GroupByTime()));
      else
        continue;
    }
    if (command == "Exit") {
      break;
    }
  }
  return 0;
}
