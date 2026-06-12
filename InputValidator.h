#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "Date.h"
#include <string>
#include <vector>

class InputValidator {
public:
    static void clearInputError();
    static std::vector<std::string> splitCsvFields(const std::string& line);
    static bool hasCsvUnsafeChar(const std::string& value);

    static bool readToken(const std::string& prompt,
                          std::string& value,
                          const std::string& fieldName,
                          bool allowNone = false);
    static bool readYesNo(const std::string& prompt, bool& value);
    static bool readIntMin(const std::string& prompt,
                           int& value,
                           int minValue,
                           const std::string& fieldName);
    static bool readIntRange(const std::string& prompt,
                             int& value,
                             int minValue,
                             int maxValue,
                             const std::string& fieldName);
    static bool readDoubleMin(const std::string& prompt,
                              double& value,
                              double minValue,
                              const std::string& fieldName);
    static bool readDateValue(const std::string& prompt,
                              Date& date,
                              const std::string& fieldName);
    static bool validateDateRange(const Date& startDate, const Date& endDate);

    static void requireNonEmpty(const std::string& value, const std::string& fieldName);
    static int parseNonNegativeInt(const std::string& value, const std::string& fieldName);
    static int parsePositiveInt(const std::string& value, const std::string& fieldName);
    static double parseNonNegativeDouble(const std::string& value, const std::string& fieldName);
    static Date parseValidDate(const std::string& value, const std::string& fieldName);
};

#endif
