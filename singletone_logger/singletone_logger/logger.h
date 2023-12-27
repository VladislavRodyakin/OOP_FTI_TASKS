#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

class logstream final {
    static inline std::string m_prefix{};
    static inline std::stringstream m_buffer{};
    static inline std::ofstream m_outFile{};
    static inline bool m_isFirstInput{};

    ~logstream() {
        writeInFile();
    }

    static void writeInFile() {
        if (m_outFile.is_open()) {
            m_outFile << m_buffer.str();
            m_outFile.flush();
        }
        else {
            throw std::exception("file not opened");
        }
    }

    static void clearBuf() {
        m_buffer.str("");
        m_isFirstInput = true;
    }

public:
    static logstream& getInstance() {
        static logstream instance;
        return instance;
    }

    static inline void writelog(const std::string& prefix = std::string()) {
        m_prefix = prefix;
    }

    static void set_log_file(const std::string& name, std::ios::openmode mode = std::ios::app) {
        if (m_outFile.is_open()) {
            writeInFile();
            clearBuf();
        }
        m_outFile = std::ofstream(name, mode);
    }

    template <typename T>
    inline logstream& operator << (const T& rhs) {
        if (!this->m_outFile.is_open()) {
            throw std::exception("file not opened");
        }
        if (this->m_isFirstInput) {
            this->m_buffer << this->m_prefix;
            this->m_isFirstInput = false;
        }
        this->m_buffer << rhs;
        return *this;
    }
    
    inline logstream& operator << (std::ostream& (*var)(std::ostream&)) {
        if (!this->m_outFile.is_open()) {
            throw std::exception("file not opened");
        }
        this->m_buffer << std::endl;
        this->writeInFile();
        this->clearBuf();
        return *this;
    }
private:
    logstream() = default;
    logstream(const logstream&) = delete;
    void operator=(const logstream&) = delete;
};
