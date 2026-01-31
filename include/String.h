#pragma once
#include <iostream>

// Custom String class to replace std::string (STL not allowed)
class String {
private:
    char* data;
    int len;
    int capacity;

    void resize(int newCapacity) {
        char* newData = new char[newCapacity];
        for (int i = 0; i < len; i++) {
            newData[i] = data[i];
        }
        newData[len] = '\0';
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Default constructor
    String() : data(nullptr), len(0), capacity(1) {
        data = new char[1];
        data[0] = '\0';
    }

    // Constructor from C-string
    String(const char* str) {
        if (str == nullptr) {
            len = 0;
            capacity = 1;
            data = new char[1];
            data[0] = '\0';
        } else {
            len = 0;
            while (str[len] != '\0') len++;
            
            capacity = len + 1;
            data = new char[capacity];
            for (int i = 0; i < len; i++) {
                data[i] = str[i];
            }
            data[len] = '\0';
        }
    }

    // Copy constructor
    String(const String& other) {
        len = other.len;
        capacity = other.capacity;
        data = new char[capacity];
        for (int i = 0; i <= len; i++) {
            data[i] = other.data[i];
        }
    }

    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            len = other.len;
            capacity = other.capacity;
            data = new char[capacity];
            for (int i = 0; i <= len; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Destructor
    ~String() {
        delete[] data;
    }

    // Get length
    int length() const {
        return len;
    }

    // Get C-string
    const char* c_str() const {
        return data;
    }

    // Access operator
    char& operator[](int index) {
        return data[index];
    }

    const char& operator[](int index) const {
        return data[index];
    }

    // Comparison operators
    bool operator==(const String& other) const {
        if (len != other.len) return false;
        for (int i = 0; i < len; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    bool operator<(const String& other) const {
        int minLen = (len < other.len) ? len : other.len;
        for (int i = 0; i < minLen; i++) {
            if (data[i] < other.data[i]) return true;
            if (data[i] > other.data[i]) return false;
        }
        return len < other.len;
    }

    bool operator>(const String& other) const {
        return other < *this;
    }

    // Concatenation
    String operator+(const String& other) const {
        String result;
        delete[] result.data;
        result.len = len + other.len;
        result.capacity = result.len + 1;
        result.data = new char[result.capacity];
        
        for (int i = 0; i < len; i++) {
            result.data[i] = data[i];
        }
        for (int i = 0; i < other.len; i++) {
            result.data[len + i] = other.data[i];
        }
        result.data[result.len] = '\0';
        return result;
    }

    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    // Append character
    void append(char c) {
        if (len + 1 >= capacity) {
            resize(capacity * 2);
        }
        data[len] = c;
        len++;
        data[len] = '\0';
    }

    // Substring
    String substr(int start, int length = -1) const {
        if (start < 0 || start >= len) return String();
        
        int subLen = (length == -1 || start + length > len) ? (len - start) : length;
        
        String result;
        delete[] result.data;
        result.len = subLen;
        result.capacity = subLen + 1;
        result.data = new char[result.capacity];
        
        for (int i = 0; i < subLen; i++) {
            result.data[i] = data[start + i];
        }
        result.data[subLen] = '\0';
        return result;
    }

    // Find character
    int find(char c, int start = 0) const {
        for (int i = start; i < len; i++) {
            if (data[i] == c) return i;
        }
        return -1;
    }

    // Find substring
    int find(const String& str, int start = 0) const {
        if (str.len == 0 || str.len > len - start) return -1;
        
        for (int i = start; i <= len - str.len; i++) {
            bool match = true;
            for (int j = 0; j < str.len; j++) {
                if (data[i + j] != str.data[j]) {
                    match = false;
                    break;
                }
            }
            if (match) return i;
        }
        return -1;
    }

    // Trim whitespace
    String trim() const {
        int start = 0;
        while (start < len && (data[start] == ' ' || data[start] == '\t' || 
               data[start] == '\n' || data[start] == '\r')) {
            start++;
        }
        
        int end = len - 1;
        while (end >= start && (data[end] == ' ' || data[end] == '\t' || 
               data[end] == '\n' || data[end] == '\r')) {
            end--;
        }
        
        return substr(start, end - start + 1);
    }

    // Convert to lowercase
    String toLower() const {
        String result(*this);
        for (int i = 0; i < result.len; i++) {
            if (result.data[i] >= 'A' && result.data[i] <= 'Z') {
                result.data[i] = result.data[i] + ('a' - 'A');
            }
        }
        return result;
    }

    // Convert to uppercase
    String toUpper() const {
        String result(*this);
        for (int i = 0; i < result.len; i++) {
            if (result.data[i] >= 'a' && result.data[i] <= 'z') {
                result.data[i] = result.data[i] - ('a' - 'A');
            }
        }
        return result;
    }

    // Check if empty
    bool isEmpty() const {
        return len == 0;
    }

    // Clear string
    void clear() {
        delete[] data;
        len = 0;
        capacity = 1;
        data = new char[1];
        data[0] = '\0';
    }

    // Remove non-ASCII characters (fixes Unicode display issues)
    String removeNonASCII() const {
        String result;
        for (int i = 0; i < len; i++) {
            // Only keep ASCII characters (0-127)
            if ((unsigned char)data[i] < 128) {
                result.append(data[i]);
            }
        }
        return result;
    }

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }

    // Stream input
    friend std::istream& operator>>(std::istream& is, String& str) {
        str.clear();
        char c;
        while (is.get(c) && c != '\n' && c != ' ') {
            str.append(c);
        }
        return is;
    }
};
