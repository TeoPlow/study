#pragma once

#include <memory>

#include "figure.h"

template <class T>
class Array{
    private:
        size_t _size;
        std::shared_ptr<T[]> _figures;

    public:
        Array() {
            _size = 0;
            _figures = nullptr;
        }

        Array(size_t size) {
            _size = size;
            _figures = std::shared_ptr<T[]>(new T[size]);
        }

        ~Array() {
            _size = 0;
            _figures = nullptr;
        }
            
        void del_figure() {
            _size--;
        }

        double avg_area() {
            double summ = 0;
            for (int i = 0; i < _size; ++i) {
                summ += (double)_figures[i];
            }
        return summ;
        }
        
        T& operator[](size_t index) {
            if (index > _size) throw std::invalid_argument("Error: ");
            return _figures[index];
        }

        void add_figure(size_t index, T& other) {
            if(_figures[index] != nullptr) {
                _figures[index] = nullptr;
            }
            _figures[index] = other;
        }

        size_t get_size(){
            return _size;
        }
};
