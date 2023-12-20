#include "string.h"

typedef void Canvas;

#define FONT_WIDTH 6

#define ELEMENTS_MAX_LINES_NUM (7)
#define ELEMENTS_BOLD_MARKER '#'
#define ELEMENTS_MONO_MARKER '*'
#define ELEMENTS_INVERSED_MARKER '!'


/** Alignment enumeration */
typedef enum {
    AlignLeft,
    AlignRight,
    AlignTop,
    AlignBottom,
    AlignCenter,
} Align;

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t leading_min;
    uint8_t leading_default;
    uint8_t height;
    uint8_t descender;
    uint8_t len;
    const char* text;
} ElementTextBoxLine;

/** Fonts enumeration */
typedef enum {
    FontPrimary,
    FontSecondary,
    FontKeyboard,
    FontBigNumbers,

    // Keep last for fonts number calculation
    FontTotalNumber,
} Font;

typedef struct {
    uint8_t leading_default;
    uint8_t leading_min;
    uint8_t height;
    uint8_t descender;
} CanvasFontParameters;

uint16_t canvas_string_width(Canvas* canvas, const char* str) {
    FuriString* tmp = furi_string_alloc_set(str);
    uint16_t len = furi_string_utf8_length(tmp) * FONT_WIDTH;
    furi_string_free(tmp);

    return len;
}

const CanvasFontParameters canvas_font_params[FontTotalNumber] = {
    [FontPrimary] = {.leading_default = 12, .leading_min = 11, .height = 8, .descender = 2},
    [FontSecondary] = {.leading_default = 11, .leading_min = 9, .height = 7, .descender = 2},
    [FontKeyboard] = {.leading_default = 11, .leading_min = 9, .height = 7, .descender = 2},
    [FontBigNumbers] = {.leading_default = 18, .leading_min = 16, .height = 15, .descender = 0},
};

const CanvasFontParameters* canvas_get_font_params(const Canvas* canvas, Font font) {
    return &canvas_font_params[font];
}

void canvas_set_font(Canvas* canvas, Font font) {
}

void canvas_invert_color(Canvas* canvas) {
}

void canvas_draw_box(Canvas* canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    printf("canvas_draw_box(%hhu, %hhu, %hhu, %hhu)\n", x, y, width, height);
}

uint8_t canvas_glyph_width(Canvas* canvas, uint16_t symbol) {
    printf("canvas_glyph_width(%hu)\n", symbol);
    return FONT_WIDTH;
}

void canvas_draw_glyph(Canvas* canvas, uint8_t x, uint8_t y, uint16_t ch) {
    printf("canvas_draw_glyph(%hhu, %hhu, %hu)\n", x, y, ch);
}

void canvas_draw_str(Canvas* canvas, uint8_t x, uint8_t y, const char* str) {
    printf("canvas_draw_str(%hhu, %hhu, \"%s\")\n", x, y, str);
}