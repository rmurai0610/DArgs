#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

namespace DArgs {

class DArgs {
private:
    std::vector<std::string> tokens_;
    std::map<std::string, std::string> help_;

    template <class T>
    T get_arg_with_default(const std::set<std::string> &keys, T default_val) {
        if (tokens_.size() == 0) { return default_val; }
        T val;
        for (size_t i = 0; i < tokens_.size() - 1; ++i) {
            if (keys.count(tokens_[i])) {
                std::stringstream ss(tokens_[i + 1]);
                tokens_.erase(tokens_.begin() + i, tokens_.begin() + i + 2);
                ss >> val;
                return val;
            }
        }
        return default_val;
    }

    template <>
    bool get_arg_with_default<bool>(const std::set<std::string> &keys, bool default_val) {
        if (tokens_.size() == 0) { return default_val; }
        for (size_t i = 0; i < tokens_.size(); ++i) {
            if (keys.count(tokens_[i])) {
                if (i == tokens_.size() - 1 || (tokens_[i + 1] != "true" && tokens_[i + 1] != "false")) {
                    tokens_.erase(tokens_.begin() + i);
                    return true;
                }
                bool val = tokens_[i + 1] == "true";
                tokens_.erase(tokens_.begin() + i, tokens_.begin() + i + 2);
                return val;
            }
        }
        return default_val;
    }

public:
    DArgs (int argc, char *argv[]) {
        if (argc > 1) {
            tokens_ = std::vector<std::string>(argv + 1, argv + argc);
        }
    }

    template <class T>
    T operator()(const std::string &option_flag, const std::string &desc, T default_val) {
        help_[option_flag] = desc;
        return get_arg_with_default({option_flag}, default_val);
    }

    template <class T>
    T operator()(const std::string &option_flag, const std::string &short_flag, const std::string &desc, T default_val) {
        std::string help_key = option_flag + ", " + short_flag;
        help_[help_key] = desc;
        return get_arg_with_default({option_flag, short_flag}, default_val);
    }

    bool check() const { return tokens_.size() == 0; }

    void print_help() const {
        size_t ws = 0;
        for (auto [k, _] : help_) { ws = std::max(ws, k.size()); }
        for (auto [k, v] : help_) {
            std::cout << std::left << std::setw(ws + 1) << k << ": " << v << "\n";
        }
    }
};

};
