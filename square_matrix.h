#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include <algorithm>

#include <ctime>

template< typename T >
class square_matrix
{
public:
    square_matrix() : _matrix(0), _size(0), _capacity(0) {}
    square_matrix(size_t n) : _matrix(new T[n * n]), _size(0), _capacity(n) {}

    ~square_matrix() { delete[] _matrix; }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

    T& at(size_t row, size_t column)
    {
        return _matrix[row * _capacity + column];
    }

    const T& at(size_t row, size_t column) const
    {
        return _matrix[row * _capacity + column];
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

                T* new_matrix = new T[new_capacity * new_capacity];

                if (_capacity > 0)
                {
                    for(size_t index = 0; index < _size; ++index)
                    {
                        T* matrix_row = _matrix + index * _capacity;
                        T* new_matrix_row = new_matrix + index * new_capacity;
                        copy(matrix_row, matrix_row + _size, new_matrix_row);
                    }
                    delete[] _matrix;
                }
                _matrix = new_matrix;
                _capacity = new_capacity;
            }

            for (size_t line = _size; line < new_size; ++line)
                for (size_t index = 0; index < new_size; ++index)
                {
                    _matrix[line + index * _capacity] = value;
                    _matrix[line * _capacity + index] = value;
                }
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
};

#endif // SQUARE_MATRIX_H
