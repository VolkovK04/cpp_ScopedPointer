#include <iostream>

template <typename T>
class ScopedPointerDeepCopy {
public:
    ScopedPointerDeepCopy(T* ptr = nullptr) : ptr_(ptr) {}

    ~ScopedPointerDeepCopy() {
        delete ptr_;
    }

    ScopedPointerDeepCopy(const ScopedPointerDeepCopy& other) {
        if (other.ptr_ != nullptr) {
            ptr_ = new T(*other.ptr_);
        } else {
            ptr_ = nullptr;
        }
    }

    ScopedPointerDeepCopy& operator=(const ScopedPointerDeepCopy& other) {
        if (this != &other) {
            delete ptr_;
            if (other.ptr_ != nullptr) {
                ptr_ = new T(*other.ptr_);
            } else {
                ptr_ = nullptr;
            }
        }
        return *this;
    }

    T* operator->() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

private:
    T* ptr_;
};

template <typename T>
class ScopedPointerTransferOwnership {
public:
    ScopedPointerTransferOwnership(T* ptr = nullptr) : ptr_(ptr) {}

    ~ScopedPointerTransferOwnership() {
        delete ptr_;
    }

    ScopedPointerTransferOwnership(ScopedPointerTransferOwnership&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    ScopedPointerTransferOwnership& operator=(ScopedPointerTransferOwnership&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T* operator->() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

private:
    T* ptr_;
};

int main() {
    ScopedPointerDeepCopy<int> p1(new int(42));
    ScopedPointerDeepCopy<int> p2 = p1;
    std::cout << *p1 << " " << *p2 << std::endl;

    ScopedPointerTransferOwnership<int> p3(new int(42));
    ScopedPointerTransferOwnership<int> p4 = std::move(p3);
    std::cout << *p4 << std::endl;

    return 0;
}
