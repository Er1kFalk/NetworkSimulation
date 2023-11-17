#ifndef TUPLEGREATERTHAN_H_
#define TUPLEGREATERTHAN_H_

template <typename T>
struct  TupleGreaterThan {
bool operator()(std::tuple<T, uint64_t>& x1, std::tuple<T, uint64_t>& x2) {
        return std::get<uint64_t>(x1) > std::get<uint64_t>(x2);
    }
};

#endif