#ifndef __INCLUDED_SYMBOLSET_INFO_HPP__
#define __INCLUDED_SYMBOLSET_INFO_HPP__

#include <map>
#include <vector>
#include <string>
#include <initializer_list>

namespace symbolset {
    // Template parameter T is symbolset class.
    template<class T>
    class info {
    public:
        using name_type = std::string;
        using symbol_type = typename T::value_type;
        using pair = std::pair<symbol_type, name_type>;
        using name_table = std::map<symbol_type, name_type>;
        using symbol_table = std::map<name_type, symbol_type>;
        using name_list = std::vector<name_type>;
        using symbol_list = std::vector<symbol_type>;
        using pair_list = std::vector<pair>;
        
    protected:
        name_table name_table_;
        symbol_table symbol_table_;
        name_list names_;
        symbol_list symbols_;
        pair_list data_;
        
    public:
        info() {}
        
        info(const info & parent,  std::initializer_list<pair> list) {
            for (auto & v: parent.data()) {
                this->data_.push_back(v);
                this->names_.push_back(v.second);
                this->symbols_.push_back(v.first);
                this->name_table_[v.first] = v.second;
                this->symbol_table_[v.second] = v.first;
            }
            
            for (auto & v: list) {
                this->data_.push_back(v);
                this->names_.push_back(v.second);
                this->symbols_.push_back(v.first);
                this->name_table_[v.first] = v.second;
                this->symbol_table_[v.second] = v.first;
            }
        }
        
        name_type name_of(symbol_type v) const {
            try {
                return this->name_table_.at(v);
            }
            catch (std::out_of_range &) {
                return "invalid";
            }
        }
        
        symbol_type symbol_of(name_type v) const {
            try {
                return this->symbol_table_.at(v);
            }
            catch (std::out_of_range &) {
                return T::invalid;
            }
        }
        
        const name_list & names() const {
            return this->names_;
        }
        
        const symbol_list & symbols() const {
            return this->symbols_;
        }
        
        const pair_list & data() const {
            return this->data_;
        }
    };
}

#endif // __INCLUDED_SYMBOLSET_INFO_HPP__
