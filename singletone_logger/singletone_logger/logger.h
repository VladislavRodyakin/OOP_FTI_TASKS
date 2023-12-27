#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

class logstream final {
    static inline std::string prefix_string{};
    static inline std::stringstream buffered_output{};
    static inline std::ofstream output_file{};
    static inline bool need_prefix{};

    ~logstream() {
        buffer_to_file();
    }

    static void buffer_to_file() {
        if (output_file.is_open()) {
            output_file << buffered_output.str();
            output_file.flush();
        }
        else {
            throw std::exception("file not opened");
        }
    }

    static void reset_buffer() {
        buffered_output.str("");
        need_prefix = true;
    }

public:
    static logstream& getInstance() {
        static logstream instance;
        return instance;
    }

    static inline void writelog(const std::string& prefix = std::string()) {
        prefix_string = prefix;
    }

    static void set_log_file(const std::string& file_name, std::ios::openmode mode = std::ios::app) {
        if (output_file.is_open()) {
            buffer_to_file();
            reset_buffer();
        }
        output_file = std::ofstream(file_name, mode);
    }

    template <typename T>
    inline logstream& operator << (const T& rhs) {
        if (!this->output_file.is_open()) {
            throw std::exception("file not opened");
        }
        if (this->need_prefix) {
            this->buffered_output << this->prefix_string;
            this->need_prefix = false;
        }
        this->buffered_output << rhs;
        return *this;
    }
    
    inline logstream& operator << (std::ostream& (*var)(std::ostream&)) {
        if (!this->output_file.is_open()) {
            throw std::exception("file not opened");
        }
        this->buffered_output << std::endl;
        this->buffer_to_file();
        this->reset_buffer();
        return *this;
    }
private:
    logstream() = default;
    logstream(const logstream&) = delete;
    void operator=(const logstream&) = delete;
};
