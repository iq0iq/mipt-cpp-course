#pragma once

struct Chunk {
  Chunk *next;
};

class PoolAllocator {
public:
  PoolAllocator(size_t chunksPerBlock)
      : chunksPerBlock_(chunksPerBlock), alloc_(nullptr) {}

  void *allocate(size_t size) {
    if (alloc_ == nullptr) {
      alloc_ = allocateBlock(size);
    }
    Chunk *copy = alloc_;
    alloc_ = alloc_->next;
    return copy;
  }

  void deallocate(void *chunk, size_t size) {
    ::operator delete(chunk);
    if (alloc_ == nullptr) {
      alloc_ = reinterpret_cast<Chunk *>(chunk);
      return;
    }
    Chunk *next_ = alloc_->next;
    alloc_->next = reinterpret_cast<Chunk *>(chunk);
    if (next_ != nullptr)
      alloc_->next->next = next_;
  }

private:
  size_t chunksPerBlock_;
  Chunk *alloc_;

private:
  Chunk *allocateBlock(size_t chunkSize) {
    char *start =
        reinterpret_cast<char *>(::operator new(chunkSize *chunksPerBlock_));
    Chunk *current = new (start) Chunk();
    for (size_t i = 1; i < chunksPerBlock_; ++i) {
      current->next = reinterpret_cast<Chunk *>(start + i * chunkSize);
      current = new (current->next) Chunk();
    }
    current->next = nullptr;
    return reinterpret_cast<Chunk *>(start);
  }
};
