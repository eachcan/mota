#include "models.h"
#include <QCborMap>
#include <QCborArray>

QString toString(Color value) {
    switch (value) {
        case Color::Red: return "Red";
        case Color::Green: return "Green";
        case Color::Blue: return "Blue";
        default: return QString();
    }
}

Color fromString(const QString& str) {
    if (str == "Red") return Color::Red;
    if (str == "Green") return Color::Green;
    if (str == "Blue") return Color::Blue;
    return Color::Red;
} 