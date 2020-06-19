// Copyright (c) 2020 ICLUE @ UIUC. All rights reserved.

#ifndef NLNUM_PARTITIONS_IN_H_
#define NLNUM_PARTITIONS_IN_H_

#include <iterator>
#include <vector>

namespace nlnum {

typedef std::vector<int> Partition;

// Iterates through each partition contained within a given partition `limit`.
class PartitionsIn {
 public:
  PartitionsIn(const Partition& limit);

  class const_iterator : std::iterator<std::forward_iterator_tag, Partition> {
   public:
    // This default constructor will be the end of the iterator.
    const_iterator();
    const_iterator(const Partition& limit);
    const_iterator& operator++();
    const Partition& operator*() const;
    bool operator!=(const const_iterator&) const;
    bool operator==(const const_iterator&) const;

   private:
    int level_;
    const Partition limit_;
    Partition last_;
    Partition partition_;
    bool finished_;
  };

 public:
  const_iterator begin() const;
  const_iterator end() const;

 private:
  const Partition limit_;
};

// Computes the intersection of two partitions.
const std::vector<int> Intersection(const Partition&, const Partition&);

}  // namespace nlnum

#endif  // NLNUM_PARTITIONS_IN_H_
