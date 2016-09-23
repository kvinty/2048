#pragma once

#include <QtWidgets>

constexpr long dimensionMin = 2;
constexpr long dimensionDefault = 4;
constexpr long dimensionMax = 7;

constexpr bool enable_tile_4 = true;
constexpr long percentage_tile_4 = 10;

constexpr int fontSize[] = {0, 0, 48, 32, 24, 20, 16, 14, 10, 8};


const QString gameFont = "DroidSans";

const QColor boardBackgroundColor(187, 173, 160);
const QColor neutralButtonColor(237, 207, 114);
const QColor brightButtonColor(245, 164, 53);
const QColor emptyTileColor(204, 192, 179);
const QColor shadowColor(246, 226, 166, 88);
const QColor tileTextColor(119, 110, 101);
const QColor blackColor(48, 48, 48);

const QMap<int, QColor> tileColor = {
    {2, QColor(238, 228, 218)},
    {4, QColor(237, 224, 200)},
    {8, QColor(242, 177, 121)},
    {16, QColor(245, 149, 99)},
    {32, QColor(246, 124, 95)},
    {64, QColor(246, 94, 59)},
    {128, QColor(237, 207, 114)},
    {256, QColor(237, 204, 97)},
    {512, QColor(237, 200, 80)},
    {1024, QColor(237, 197, 63)},
    {2048, QColor(237, 194, 46)},
    {4096, QColor(193, 152, 183)},
    {8192, QColor(184, 125, 176)}
};

struct GameData {
    long score;
    long values[dimensionMax][dimensionMax];
    bool gameOver;
};
