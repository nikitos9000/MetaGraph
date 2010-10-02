#ifndef BASE_H
#define BASE_H

#include <tr1/unordered_set>

typedef size_t vertex_t;
typedef std::pair< vertex_t, vertex_t > arc_t;

class vertex_hash
{
    public:
        inline size_t operator()(const vertex_t& value) const
        {
            return value;
        }
};

class arc_hash
{
    public:
        inline size_t operator()(const arc_t& value) const
        {
            return _hash(value.first | (static_cast< unsigned long long >(value.second) << sizeof(unsigned long) * 8));
        }

    private:
        std::tr1::hash< unsigned long long > _hash;
};

#endif // BASE_H
