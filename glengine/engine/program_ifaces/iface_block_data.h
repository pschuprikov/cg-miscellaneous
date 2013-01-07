#ifndef IFACE_BLOCK_DATA_H
#define IFACE_BLOCK_DATA_H

#include <gleshader_block.h>

#include "iface_common_data.h"

namespace gle
{

struct iface_block_variable_data_t
    : iface_base_variable_data_t
{
public:
    iface_block_variable_data_t(std::string const& name, GLenum type, int offset)
        : iface_base_variable_data_t(name, type)
        , offset_(offset)
    {}

    int offset() const { return offset_; }

private:
    int offset_;
};

struct iface_block_array_data_t
    : iface_base_array_data_t
{
public:
    iface_block_array_data_t(std::string const& name, int size, GLenum type, int stride, int offset)
        : iface_base_array_data_t(name, size, type)
        , offset_(offset)
        , stride_(stride)
    {}

    int stride() const { return stride_; }
    int offset() const { return offset_; }

    iface_block_variable_data_t const operator[](int idx) const
    {
        return iface_block_variable_data_t(name() + "[..]", type(), offset() + stride() * idx);
    }

private:
    int offset_;
    int stride_;
};

struct iface_block_data_t
{
    typedef std::map<std::string, iface_block_variable_data_t> block_vars_map_t;
    typedef boost::shared_ptr<block_vars_map_t> block_vars_map_ptr;

    typedef std::map<std::string, iface_block_array_data_t> block_array_map_t;
    typedef boost::shared_ptr<block_array_map_t> block_array_map_ptr;
public:
    iface_block_data_t(std::string const& name, int idx, int data_size, shader_block_type_t type,
                       block_vars_map_ptr var_members, block_array_map_ptr arr_members, int binding)
        : name_(name), idx_(idx), data_size_(data_size), type_(type)
        , var_members_(var_members)
        , array_members_(arr_members)
        , binding_(binding)
    {}

public:
    int idx() const { return idx_; }
    std::string const& name() const { return name_; }
    int data_size() const { return data_size_; }

    int binding() const { return binding_; }
    void set_binding(int idx) { binding_ = idx; }

    shader_block_type_t type() const { return type_; }

    iface_block_variable_data_t const& var(std::string const& member) { return var_members_->at(member); }
    iface_block_array_data_t const& array(std::string const& member) { return array_members_->at(member); }
private:
    std::string name_;
    int idx_;
    int data_size_;

    shader_block_type_t type_;

    block_vars_map_ptr var_members_;
    block_array_map_ptr array_members_;

    int binding_;
};
typedef boost::shared_ptr<iface_block_data_t> iface_block_data_ptr;

}

#endif // IFACE_BLOCK_DATA_H
