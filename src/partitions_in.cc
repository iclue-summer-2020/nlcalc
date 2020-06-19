// Copyright 2020 ICLUE @ UIUC. All rights reserved.

#include <algorithm>
#include <climits>
#include <vector>

#include <nlnum/partitions_in.h>

namespace nlnum {

PartitionsIn::PartitionsIn(const nlnum::Partition& limit) : limit_{limit} {}

PartitionsIn::const_iterator PartitionsIn::begin() const { return limit_; }

PartitionsIn::const_iterator PartitionsIn::end() const {
  return const_iterator{};
}

PartitionsIn::const_iterator::const_iterator() : finished_{true} {}

PartitionsIn::const_iterator::const_iterator(const nlnum::Partition& limit)
    : level_{limit.size() > 0 ? limit.size() - 1 : 0}, limit_{limit} {
  // The initial partition is all zeros.
  partition_ = Partition(limit.size());
  last_ = partition_;

  for (int part : limit) {
    if (part < 0) {
      finished_ = true;
      return;
    }
  }

  finished_ = false;
}

PartitionsIn::const_iterator& PartitionsIn::const_iterator::operator++() {
  if (finished_) return *this;

  const int lneighbor = level_ == 0 ? INT_MAX : partition_[level_ - 1];
  if (level_ < 0 || partition_[level_] < std::min(lneighbor, limit_[level_])) {
    ++partition_[level_];
    level_ = static_cast<int>(partition_.size()) - 1;

    last_ = partition_;
    return *this;
  } else {
    partition_[level_--] = 0;

    // We have exhausted everything.
    if (level_ < 0) {
      finished_ = true;
    }
  }

  // Keep iterating if we did not find anything.
  return ++(*this);
}

const Partition& PartitionsIn::const_iterator::operator*() const {
  return last_;
}

bool PartitionsIn::const_iterator::operator!=(
    const nlnum::PartitionsIn::const_iterator& rhs) const {
  return !(*this == rhs);
}

bool PartitionsIn::const_iterator::operator==(
    const PartitionsIn::const_iterator& rhs) const {
  return ((finished_ && finished_ == rhs.finished_) ||
          (partition_ == rhs.partition_ && limit_ == rhs.limit_));
}

// Computes the intersection of two partitions.
const std::vector<int> Intersection(const std::vector<int>& a,
                                    const std::vector<int>& b) {
  const size_t n = std::min(a.size(), b.size());
  std::vector<int> c(n);
  for (size_t i = 0; i < n; ++i) {
    c[i] = std::min(a[i], b[i]);
  }

  return c;
}

}  // namespace nlnum
