// Unchanged

static size_t
    elements_get_max_chars_to_fit(Canvas* canvas, Align horizontal, const char* text, uint8_t x) {
    const char* end = strchr(text, '\n');
    if(end == NULL) {
        end = text + strlen(text);
    }
    size_t text_size = end - text;
    FuriString* str;
    str = furi_string_alloc_set(text);
    furi_string_left(str, text_size);
    size_t result = 0;

    uint16_t len_px = canvas_string_width(canvas, furi_string_get_cstr(str));
    uint8_t px_left = 0;
    if(horizontal == AlignCenter) {
        if(x > (canvas_width(canvas) / 2)) {
            px_left = (canvas_width(canvas) - x) * 2;
        } else {
            px_left = x * 2;
        }
    } else if(horizontal == AlignLeft) {
        px_left = canvas_width(canvas) - x;
    } else if(horizontal == AlignRight) {
        px_left = x;
    } else {
        furi_crash();
    }

    if(len_px > px_left) {
        size_t excess_symbols_approximately =
            ceilf((float)(len_px - px_left) / ((float)len_px / (float)text_size));
        // reduce to 5 to be sure dash fit, and next line will be at least 5 symbols long
        if(excess_symbols_approximately > 0) {
            excess_symbols_approximately = MAX(excess_symbols_approximately, 5u);
            result = text_size - excess_symbols_approximately - 1;
        } else {
            result = text_size;
        }
    } else {
        result = text_size;
    }

    furi_string_free(str);
    return result;
}
