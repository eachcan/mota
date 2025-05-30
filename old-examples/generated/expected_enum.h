#pragma once
#include "base_model.h"
#include <optional>
#include <vector>
#include <map>

enum class Color {
    Red = 1,
    Green = 2,
    Blue = 3,
};

QString toString(Color value);
Color fromString(const QString& str); 