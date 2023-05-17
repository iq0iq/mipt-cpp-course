template <class Iterator> class IndexedIterator : public Iterator {

private:
  Iterator it_;
  size_t index_ = 0;

public:
  IndexedIterator(Iterator it, size_t index) : it_(it), index_(index) {}

  auto &operator*() { return *it_; }
  const auto &operator*() const { return *it_; }

  IndexedIterator &operator++() {
    ++it_;
    ++index_;
    return *this;
  }

  IndexedIterator operator++(int) {
    auto copy = *this;
    ++*this;
    return copy;
  }

  IndexedIterator operator+(long long x) {
    return IndexedIterator(it_ + x, index_ + x);
  }

  long long operator-(const IndexedIterator &it) { return it_ - it.it_; }

  IndexedIterator operator-(long long x) {
    return IndexedIterator(it_ - x, index_ - x);
  }

  bool operator<(const IndexedIterator &it) { return it_ < it.it_; }

  bool operator!=(const IndexedIterator &it) { return it_ != it.it_; }

  bool operator!=(const Iterator &it) { return it_ != it; }

  bool operator==(const IndexedIterator &it) { return it_ == it.it_; }

  size_t index() const { return index_; }
};

template <class Iterator>
IndexedIterator<Iterator> operator+(long long x,
                                    const IndexedIterator<Iterator> &it) {
  return it + x;
}

template <class Iterator>
IndexedIterator<Iterator> operator!=(const Iterator &x,
                                     const IndexedIterator<Iterator> &it) {
  return it != x;
}

template <class It>
IndexedIterator<It> CreateIndexedIterator(It iterator, size_t index = 0) {
  return IndexedIterator<It>(iterator, index);
}
