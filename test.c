#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "includes/canvas.h"
#include "includes/_ansi.h"
#include "includes/string.h"

#define __furi_assert(__e, __m) \
    do {                        \
        ((void)(__e));          \
        ((void)(__m));          \
    } while(0)

#define __FURI_ASSERT_MESSAGE_FLAG (0x01)

#define furi_assert(...) \
    M_APPLY(__furi_assert, M_DEFAULT_ARGS(2, (__FURI_ASSERT_MESSAGE_FLAG), __VA_ARGS__))


#define MAX(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })


void furi_crash() {
    abort();
}

#include "elements/elements_get_max_chars_to_fit.c"
#include "elements/elements_scrollable_text_line.c"
#include "elements/elements_string_fit_width.c"
#include "elements/elements_multiline_text_aligned.c"
#include "elements/elements_text_box.c"

/////// Place for tests /////////

int main() {
    Canvas* canvas = NULL;
    FuriString* str;
    uint16_t len;
    char* cstr;

    // elements_string_fit_width
    printf("elements_string_fit_width\n");

    str = furi_string_alloc_set("RRRRRRRRRRRRRRRRRRRR");
    elements_string_fit_width(canvas, str, 70);
    len = canvas_string_width(canvas, furi_string_get_cstr(str));
    printf("width=%d, \"%s\"\n", len, furi_string_get_cstr(str));
    furi_string_free(str);

    str = furi_string_alloc_set("ЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯ");
    elements_string_fit_width(canvas, str, 70);
    len = canvas_string_width(canvas, furi_string_get_cstr(str));
    printf("width=%d, \"%s\"\n", len, furi_string_get_cstr(str));
    furi_string_free(str);

    str = furi_string_alloc_set("ЕхалЕхалЕхалЕхалЕхалЕхалЕхалЕхал");
    elements_string_fit_width(canvas, str, 70);
    len = canvas_string_width(canvas, furi_string_get_cstr(str));
    printf("width=%d, \"%s\"\n", len, furi_string_get_cstr(str));
    furi_string_free(str);

    str = furi_string_alloc_set("ЕхалЕхалЕхалЕхалЕхалЕхалЕхалЕхал");
    elements_string_fit_width(canvas, str, 10);
    len = canvas_string_width(canvas, furi_string_get_cstr(str));
    printf("width=%d, \"%s\"\n", len, furi_string_get_cstr(str));

    // elements_scrollable_text_line
    printf("\nelements_scrollable_text_line\n");

    str = furi_string_alloc_set("ABCDEABCDEabcdeabcde");
    elements_scrollable_text_line(canvas, 0, 20, 100, str, 3, true);
    furi_string_free(str);

    str = furi_string_alloc_set("АБВГДАБВГДабвгдабвгд");
    elements_scrollable_text_line(canvas, 0, 20, 100, str, 3, true);
    furi_string_free(str);

    // elements_multiline_text_aligned
    printf("\nelements_multiline_text_aligned\n");

    cstr = "ABCDEABCDEabcdeabcdeABCDEABCDEabcdeabcde";
    elements_multiline_text_aligned(canvas, 0, 20, AlignLeft, AlignCenter, cstr);

    cstr = "АБВГДАБВГДабвгдабвгдАБВГДАБВГДабвгдабвгд";
    elements_multiline_text_aligned(canvas, 0, 20, AlignLeft, AlignCenter, cstr);


    // elements_text_box
    printf("\nelements_text_box\n");
    elements_text_box(canvas, 0, 20, 100, 40, AlignLeft, AlignTop, "ABCDEABCDEabcdea", false);
    elements_text_box(canvas, 0, 20, 100, 40, AlignLeft, AlignTop, "АБВГДАБВГДабвгда", false);
}
