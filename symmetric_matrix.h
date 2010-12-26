#ifndef SYMMETRIC_MATRIX_H
#define SYMMETRIC_MATRIX_H

#include <algorithm>

template< typename T >
class symmetric_matrix
{
public:
    symmetric_matrix() : _matrix(0), _size(0), _capacity(0) {}
    symmetric_matrix(size_t n) : _matrix(new T[(n * (n + 1)) / 2]), _size(0), _capacity(n) {}

    ~symmetric_matrix() { delete[] _matrix; }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

    T& at(size_t row, size_t column)
    {
        return _matrix[index(row, column)];
    }

    const T& at(size_t row, size_t column) const
    {
        return _matrix[index(row, column)];
    }

    void push_back(const T& value = T())
    {
        resize(_size + 1, value);
    }

    void pop_back()
    {
        if (_size > 0) resize(_size - 1);
    }

    void resize(size_t new_size, const T& value = T())
    {
        if (new_size > _size)
        {
            if (new_size > _capacity)
            {
                size_t new_capacity = std::max(_capacity, size_t(1) << 2);

                while (new_capacity < new_size)
                    new_capacity = new_capacity << 1;

                T* new_matrix = new T[(new_capacity * (new_capacity + 1)) / 2];

                if (_capacity > 0)
                {
                    std::copy(_matrix, _matrix + (_size * (_size + 1)) / 2, new_matrix);
                    delete[] _matrix;
                }
                _matrix = new_matrix;
                _capacity = new_capacity;
            }

            std::fill_n(_matrix + (_size * (_size + 1)) / 2, (new_size * (new_size + 1)) / 2, value);
        }
        _size = new_size;
    }

    void clear()
    {
        _size = 0;
    }

private:
    T* _matrix;
    size_t _size;
    size_t _capacity;

    size_t index(size_t row, size_t column) const
    {
        if (row < column)
            return (column * (column + 1)) / 2 + row;
        else
            return (row * (row + 1)) / 2 + column;
    }
};

#endif // SYMMETRIC_MATRIX_H
