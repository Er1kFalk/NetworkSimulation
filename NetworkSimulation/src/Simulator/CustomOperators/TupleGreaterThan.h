#ifndef TUPLEGREATERTHAN_H_
#define TUPLEGREATERTHAN_H_

template <typename T>
struct  TupleGreaterThan {
bool operator()(std::tuple<T, uint32_t, uint32_t>& x1, std::tuple<T, uint32_t, uint32_t>& x2) {
        return std::get<1>(x1) == std::get<1>(x2) ? std::get<2>(x1) > std::get<2>(x2) : std::get<1>(x1) > std::get<1>(x2);
    }
};

#endif