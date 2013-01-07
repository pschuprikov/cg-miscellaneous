#ifndef IFACE_COMMON_DATA_H
#define IFACE_COMMON_DATA_H

#include <glecommon.h>

namespace gle
{

struct iface_base_variable_data_t
{
public:
    iface_base_variable_data_t(std::string const& name, GLenum type)
        : name_(name), type_(type) {}

    std::string const& name() const { return name_; }
    GLenum type() const { return type_; }
private:
    std::string name_;
    GLenum type_;
};

struct iface_base_array_data_t
{
    iface_base_array_data_t(std::string const& name, int size, GLenum type)
        : name_(name), size_(size), type_(type)
    {}

public:
    std::string const& name() const { return name_; }

    int size() const { return size_; }
    GLenum type() const { return type_; }

private:
    std::string name_;

    int size_;
    GLenum type_;
};

}

#endif // IFACE_COMMON_DATA_H
