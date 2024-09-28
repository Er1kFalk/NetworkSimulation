#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <tuple>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class BaseConfigReader {
private:
    /*The operator BOOST use to go into (nested) json objects*/
    static const std::string NEST_OPERATOR;

public:


    /*Given a list of json keys, it makes a path that can be used
    to read the corresponding value in a nested json structure*/
    std::string jsonpath(std::vector<std::string> v);

    /*function to convert json number list to a c++ vector*/
    template<typename T>
    std::vector<T> read_json_list(std::string key, boost::property_tree::ptree json) {
        std::vector<T> v;
        
        for (boost::property_tree::ptree::value_type &val : json.get_child(key)) {
            v.push_back(std::stoi(val.second.data()));
        }

        return v;
    }

    /*read json list as stringlist*/
    std::vector<std::string> read_json_list(std::string key, boost::property_tree::ptree json) {
        std::vector<std::string> v;

        for (boost::property_tree::ptree::value_type &val : json.get_child(key)) {
            v.push_back(val.second.data());
        }

        return v;
    }


    template<typename T>
    std::vector<std::vector<T>> read_json_list_of_lists(std::string key, boost::property_tree::ptree json) {
        std::vector<std::vector<T>> v;

        for (boost::property_tree::ptree::value_type &val1 : json.get_child(key)) {
            std::vector<T> temp = {};
            for (boost::property_tree::ptree::value_type &val2 : val1.second) {
                temp.push_back(stoi(val2.second.data()));
            }
            v.push_back(temp);
        }

        return v;
    }

    BaseConfigReader();
};

#endif
