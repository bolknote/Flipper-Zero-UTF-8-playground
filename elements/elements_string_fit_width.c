// Changed

void elements_string_fit_width(Canvas* canvas, FuriString* string, uint8_t width) {
    furi_assert(canvas);
    furi_assert(string);

    uint16_t len_px = canvas_string_width(canvas, furi_string_get_cstr(string));
    if(len_px > width) {
        uint16_t ellipsis_width = canvas_string_width(canvas, "...");
        if (width < ellipsis_width) {
            furi_string_reset(string);
        } else {
            width -= ellipsis_width;
            do {
                size_t len = furi_string_size(string);
                size_t offset = 1;

                while((furi_string_get_char(string, len - offset) & 0xC0) == 0x80) {
                    offset++;
                }

                furi_string_left(string, len - offset);
                len_px = canvas_string_width(canvas, furi_string_get_cstr(string));
            } while(len_px > width);
            furi_string_cat(string, "...");
        }
    }
}
