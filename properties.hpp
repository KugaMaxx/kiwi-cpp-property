#pragma once

#include <random>
#include <iostream>
#include <stdlib.h>
#include <fmt/core.h>
#include <Eigen/Dense>

namespace dv::toolkit {

template <class T>
class Property {
private:
    std::function<T()> get;
    std::function<void(const T&)> set;

public:
    Property(){};

    Property(std::function<T()> get, std::function<void(const T&)> set) 
        : get(get), set(set) {};

    operator T() const {
        return get();
    }

    void operator=(T const & value) {
        set(value);
    }

    T operator()() const {
        return get();
    }

    friend std::ostream& operator<<(std::ostream& os, const Property<T>& prop) {
        os << prop.get();
        return os;
    }
};

template <class T>
class ROProperty : public Property<T> {
public:
    ROProperty(){};

    ROProperty(std::function<T()> get) 
        : Property<T>(
            get, 
            [](const T& value){ throw std::runtime_error("Read only property!"); }
        ) {};

    ROProperty(T value_)
        : Property<T>(
            [value_](){ return value_; }, 
            [](const T& value){ throw std::runtime_error("Read only property!"); }
        ) {};
};

}
