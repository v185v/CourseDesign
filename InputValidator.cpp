#include "InputValidator.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

void InputValidator::clearInputError() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::vector<std::string> InputValidator::splitCsvFields(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    std::stringstream ss(line);
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

bool InputValidator::hasCsvUnsafeChar(const std::string& value) {
    return value.find_first_of(",\r\n") != std::string::npos;
}

bool InputValidator::readToken(const std::string& prompt,
                               std::string& value,
                               const std::string& fieldName,
                               bool allowNone) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        clearInputError();
        std::cout << fieldName << "输入失败，请重新操作。" << std::endl;
        return false;
    }

    if (value.empty() || (!allowNone && value == "none")) {
        std::cout << fieldName << "不能为空。" << std::endl;
        return false;
    }

    if (hasCsvUnsafeChar(value)) {
        std::cout << fieldName << "不能包含逗号或换行符。" << std::endl;
        return false;
    }

    return true;
}

bool InputValidator::readYesNo(const std::string& prompt, bool& value) {
    std::string input;
    if (!readToken(prompt, input, "选择")) {
        return false;
    }

    if (input == "y" || input == "Y") {
        value = true;
        return true;
    }

    if (input == "n" || input == "N") {
        value = false;
        return true;
    }

    std::cout << "请选择 y 或 n。" << std::endl;
    return false;
}

bool InputValidator::readIntMin(const std::string& prompt,
                                int& value,
                                int minValue,
                                const std::string& fieldName) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        clearInputError();
        std::cout << fieldName << "必须是整数。" << std::endl;
        return false;
    }

    if (value < minValue) {
        std::cout << fieldName << "不能小于 " << minValue << "。" << std::endl;
        return false;
    }

    return true;
}

bool InputValidator::readIntRange(const std::string& prompt,
                                  int& value,
                                  int minValue,
                                  int maxValue,
                                  const std::string& fieldName) {
    if (!readIntMin(prompt, value, minValue, fieldName)) {
        return false;
    }

    if (value > maxValue) {
        std::cout << fieldName << "不能大于 " << maxValue << "。" << std::endl;
        return false;
    }

    return true;
}

bool InputValidator::readDoubleMin(const std::string& prompt,
                                   double& value,
                                   double minValue,
                                   const std::string& fieldName) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        clearInputError();
        std::cout << fieldName << "必须是数字。" << std::endl;
        return false;
    }

    if (value < minValue) {
        std::cout << fieldName << "不能小于 " << minValue << "。" << std::endl;
        return false;
    }

    return true;
}

bool InputValidator::readDateValue(const std::string& prompt,
                                   Date& date,
                                   const std::string& fieldName) {
    int y, m, d;
    std::cout << prompt;
    if (!(std::cin >> y >> m >> d)) {
        clearInputError();
        std::cout << fieldName << "必须按 年 月 日 输入。" << std::endl;
        return false;
    }

    date = Date(y, m, d);
    if (!date.isValid()) {
        std::cout << fieldName << "不合法。" << std::endl;
        return false;
    }

    return true;
}

bool InputValidator::validateDateRange(const Date& startDate, const Date& endDate) {
    if (!startDate.isValid() || !endDate.isValid()) {
        std::cout << "日期范围不合法。" << std::endl;
        return false;
    }

    if (startDate.toNumber() > endDate.toNumber()) {
        std::cout << "起始日期不能晚于结束日期。" << std::endl;
        return false;
    }

    return true;
}

void InputValidator::requireNonEmpty(const std::string& value, const std::string& fieldName) {
    if (value.empty()) {
        throw std::invalid_argument(fieldName + " cannot be empty");
    }
}

int InputValidator::parseNonNegativeInt(const std::string& value, const std::string& fieldName) {
    int result = std::stoi(value);
    if (result < 0) {
        throw std::invalid_argument(fieldName + " cannot be negative");
    }
    return result;
}

int InputValidator::parsePositiveInt(const std::string& value, const std::string& fieldName) {
    int result = std::stoi(value);
    if (result <= 0) {
        throw std::invalid_argument(fieldName + " must be positive");
    }
    return result;
}

double InputValidator::parseNonNegativeDouble(const std::string& value, const std::string& fieldName) {
    double result = std::stod(value);
    if (result < 0) {
        throw std::invalid_argument(fieldName + " cannot be negative");
    }
    return result;
}

Date InputValidator::parseValidDate(const std::string& value, const std::string& fieldName) {
    Date date = Date::fromString(value);
    if (!date.isValid()) {
        throw std::invalid_argument(fieldName + " is invalid");
    }
    return date;
}
