#pragma once
#include "String.h"
#include "LinkedList.h"
#include <fstream>

// CSV Parser utility class
class CSVParser {
private:
    // Parse a single field from CSV (handles quotes)
    static String parseField(const String& line, int& pos) {
        String field;
        bool inQuotes = false;

        while (pos < line.length()) {
            char c = line[pos];

            if (c == '"') {
                inQuotes = !inQuotes;
                pos++;
            } else if (c == ',' && !inQuotes) {
                pos++;  // Skip the comma
                break;
            } else {
                field.append(c);
                pos++;
            }
        }

        return field.trim();
    }

    // Convert string to integer
    static int stringToInt(const String& str) {
        if (str.isEmpty()) return 0;
        
        int result = 0;
        bool negative = false;
        int i = 0;

        if (str[0] == '-') {
            negative = true;
            i = 1;
        }

        for (; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                result = result * 10 + (str[i] - '0');
            } else {
                break;  // Stop at non-digit
            }
        }

        return negative ? -result : result;
    }

    // Convert string to long long
    static long long stringToLongLong(const String& str) {
        if (str.isEmpty()) return 0;
        
        long long result = 0;
        bool negative = false;
        int i = 0;

        if (str[0] == '-') {
            negative = true;
            i = 1;
        }

        for (; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                result = result * 10 + (str[i] - '0');
            } else {
                break;
            }
        }

        return negative ? -result : result;
    }

    // Convert string to double
    static double stringToDouble(const String& str) {
        if (str.isEmpty()) return 0.0;
        
        double result = 0.0;
        double fraction = 0.0;
        bool negative = false;
        bool afterDecimal = false;
        double divisor = 10.0;
        int i = 0;

        if (str[0] == '-') {
            negative = true;
            i = 1;
        }

        for (; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                if (afterDecimal) {
                    fraction += (str[i] - '0') / divisor;
                    divisor *= 10.0;
                } else {
                    result = result * 10.0 + (str[i] - '0');
                }
            } else if (str[i] == '.') {
                afterDecimal = true;
            } else {
                break;
            }
        }

        result += fraction;
        return negative ? -result : result;
    }

    // Split string by delimiter (for genres and actors separated by |)
    static LinkedList<String> split(const String& str, char delimiter) {
        LinkedList<String> result;
        String current;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == delimiter) {
                if (!current.isEmpty()) {
                    result.append(current.trim());
                    current.clear();
                }
            } else {
                current.append(str[i]);
            }
        }

        if (!current.isEmpty()) {
            result.append(current.trim());
        }

        return result;
    }

public:
    // Parse a CSV line into fields
    static LinkedList<String> parseLine(const String& line) {
        LinkedList<String> fields;
        int pos = 0;

        while (pos < line.length()) {
            String field = parseField(line, pos);
            fields.append(field);
        }

        return fields;
    }

    // Read entire CSV file
    static LinkedList<LinkedList<String>> readCSV(const char* filename) {
        LinkedList<LinkedList<String>> data;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "Error: Could not open file " << filename << std::endl;
            return data;
        }

        char buffer[4096];
        bool firstLine = true;

        while (file.getline(buffer, sizeof(buffer))) {
            String line(buffer);
            
            if (firstLine) {
                firstLine = false;
                continue;  // Skip header
            }

            if (!line.isEmpty()) {
                LinkedList<String> fields = parseLine(line);
                data.append(fields);
            }
        }

        file.close();
        return data;
    }

    // Utility: Convert string to int
    static int toInt(const String& str) {
        return stringToInt(str);
    }

    // Utility: Convert string to long long
    static long long toLongLong(const String& str) {
        return stringToLongLong(str);
    }

    // Utility: Convert string to double
    static double toDouble(const String& str) {
        return stringToDouble(str);
    }

    // Utility: Split string by delimiter
    static LinkedList<String> splitString(const String& str, char delimiter) {
        return split(str, delimiter);
    }
};
