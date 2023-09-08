#pragma once
#include <math.h>
#include <string>

struct Record {
  std::string name;
  double x;
  double y;
  std::string type;
  double timestamp;
};

bool operator==(const Record& lhs, const Record& rhs);

struct RecordHasher {
 public:
  RecordHasher() = default;

  std::size_t operator()(const Record& record) const;
};

double getDist(double x, double y);

template <typename First, typename Second>
struct Chain {
  Chain(const First& f_, const Second& s_) : f(f_), s(s_) {}

  bool operator()(const Record& lhs, const Record& rhs) {
    if (f(lhs, rhs)) return true;
    if (f(rhs, lhs)) return false;

    return s(lhs, rhs);
  }

  template <typename Next>
  Chain<Chain, Next> chain(const Next& next) const {
    return Chain<Chain, Next>(*this, next);
  }

  First f;
  Second s;
};

struct False {
  bool operator()(const Record&, const Record&) { return false; }
};

template <typename Op>
Chain<False, Op> make_chain(const Op& op) {
  return Chain<False, Op>(False(), op);
}

struct CmpName {
  bool operator()(const Record& lhs, const Record& rhs);
};

struct CmpX {
  bool operator()(const Record& lhs, const Record& rhs);
};

struct CmpY {
  bool operator()(const Record& lhs, const Record& rhs);
};

struct CmpType {
  bool operator()(const Record& lhs, const Record& rhs);
};

struct CmpTimestamp {
  bool operator()(const Record& lhs, const Record& rhs);
};

struct CmpDistination {
  bool operator()(const Record& lhs, const Record& rhs);
};
