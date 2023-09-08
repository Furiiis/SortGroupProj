#include "group.hpp"

#include <climits>

Group& Group::group(Comparator cmp) {
  group_sequence_.push_back(cmp);
  return *this;
}

std::vector<int> Group::getSequenceOfGroupIndexes(const Record& rec) const {
  std::vector<int> sequence;
  for (const auto& cmp : group_sequence_) {
    sequence.push_back(cmp(rec));
  }
  return sequence;
}

int GroupByDistination::operator()(const Record& rec) {
  double dist = getDist(rec.x, rec.y);
  if (dist <= 100) {
    return 1;
  }
  if (dist > 100 && dist <= 1000) {
    return 2;
  }
  if (dist > 1000 && dist <= 10000) {
    return 3;
  }
  return 4;
}

int GroupByName::operator()(const Record& rec) {
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
  std::u32string u32str = converter.from_bytes(rec.name);

  if (!rec.name.empty()) {
    char32_t first_letter = u32str[0];
    int first_letter_code = static_cast<int>(first_letter);
    // from russian 'А' to 'Я'
    if (first_letter_code >= 1040 && first_letter_code <= 1071)
      return first_letter_code;
    else
      return 1072;  // for other symbols
  }
  return -1;
}

GroupByType::GroupByType(const std::list<Record>& from_types, int count)
    : objects_count_(count) {
  int i = 0;
  for (const Record& rec : from_types) {
    types_[rec.type].count++;
    types_[rec.type].index = i;
    i++;
  }
}

int GroupByType::operator()(const Record& rec) {
  if (types_[rec.type].count >= objects_count_) {
    return types_[rec.type].index;
  } else
    return INT_MAX;
}

int GroupByTime::operator()(const Record& rec) {
  auto record_time = static_cast<time_t>(rec.timestamp);
  std::tm record_tm = *std::localtime(&record_time);

  std::time_t current_time = std::time(nullptr);
  std::tm current_tm = *std::localtime(&current_time);

  if (record_tm.tm_year == current_tm.tm_year &&
      record_tm.tm_mon == current_tm.tm_mon &&
      record_tm.tm_mday == current_tm.tm_mday) {
    return 1;  // Today
  }

  std::time_t yesterday_time = current_time - (24 * 60 * 60);
  std::tm yesterday_tm = *std::localtime(&yesterday_time);

  if (record_tm.tm_year == yesterday_tm.tm_year &&
      record_tm.tm_mon == yesterday_tm.tm_mon &&
      record_tm.tm_mday == yesterday_tm.tm_mday) {
    return 2;  // Yesterday
  }

  if (record_tm.tm_year == current_tm.tm_year &&
      record_tm.tm_mon == current_tm.tm_mon) {
    return 3;  // This month
  }

  if (record_tm.tm_year == current_tm.tm_year) {
    return 4;  // This year
  }

  return 5;  // Later
}
