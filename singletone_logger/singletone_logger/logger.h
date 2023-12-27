#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

class logstream final {
    const std::string m_prefix{};
    std::stringstream m_buffer{};
    std::ofstream m_outFile{};
    bool m_isFirstInput{};

    void write_m() {
        if (m_outFile.is_open()) {
            m_outFile << m_buffer.str();
            m_outFile.flush();
        }
        else {
            throw std::exception("file not opened");
        }
    }

    ~logstream() {
        writeInFile();
    }

    void writeInFile() {
        if (m_outFile.is_open()) {
            m_outFile << m_buffer.str();
            m_outFile.flush();
        }
        else {
            throw std::exception("file not opened");
        }
    }

    void clearBuf() {
        m_buffer.str("");
        m_isFirstInput = true;
    }

public:
    static logstream& getInstance() {
        static logstream instance;
        return instance;
    }
    

    void set_log_file(const std::string& name) {
        if (m_outFile.is_open()) {
            writeInFile();
            clearBuf();
        }
    }

    template <typename T> inline logstream& operator << (const T& rhs) {
        if (!this->m_outFile.is_open()) {
            throw std::exception("file not opened");
        }
        if (this->m_isFirstInput) {
            this->m_buffer << this->m_prefix;
            this->m_isFirstInput = false;
        }
        this->m_buffer << t;
        return *this;
    }
private:
    logstream() = default;
    //logstream(const std::string& prefix = std::string()) : m_prefix{ prefix } {};
    logstream(const logstream&) = delete;
    void operator=(const logstream&) = delete;
};