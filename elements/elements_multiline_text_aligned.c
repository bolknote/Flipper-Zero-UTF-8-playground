// Unchanged

void elements_multiline_text_aligned(
    Canvas* canvas,
    uint8_t x,
    uint8_t y,
    Align horizontal,
    Align vertical,
    const char* text) {
    furi_assert(canvas);
    furi_assert(text);

    uint8_t lines_count = 0;
    uint8_t font_height = canvas_current_font_height(canvas);
    FuriString* line;

    /* go through text line by line and count lines */
    for(const char* start = text; start[0];) {
        size_t chars_fit = elements_get_max_chars_to_fit(canvas, horizontal, start, x);
        ++lines_count;
        start += chars_fit;
        start += start[0] == '\n' ? 1 : 0;
    }

    if(vertical == AlignBottom) {
        y -= font_height * (lines_count - 1);
    } else if(vertical == AlignCenter) {
        y -= (font_height * (lines_count - 1)) / 2;
    }

    /* go through text line by line and print them */
    for(const char* start = text; start[0];) {
        size_t chars_fit = elements_get_max_chars_to_fit(canvas, horizontal, start, x);

        if((start[chars_fit] == '\n') || (start[chars_fit] == 0)) {
            line = furi_string_alloc_printf("%.*s", chars_fit, start);
        } else if((y + font_height) > canvas_height(canvas)) {
            line = furi_string_alloc_printf("%.*s...\n", chars_fit, start);
        } else {
            chars_fit -= 1; // account for the dash
            line = furi_string_alloc_printf("%.*s-\n", chars_fit, start);
        }
        canvas_draw_str_aligned(canvas, x, y, horizontal, vertical, furi_string_get_cstr(line));
        furi_string_free(line);
        y += font_height;
        if(y > canvas_height(canvas)) {
            break;
        }

        start += chars_fit;
        start += start[0] == '\n' ? 1 : 0;
    }
}
