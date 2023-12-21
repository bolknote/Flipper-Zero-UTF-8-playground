// Changed

void elements_scrollable_text_line(
    Canvas* canvas,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    FuriString* string,
    size_t scroll,
    bool ellipsis) {
    FuriString* line = furi_string_alloc_set(string);

    size_t len_px = canvas_string_width(canvas, furi_string_get_cstr(line));
    if(len_px > width) {
        if(ellipsis) {
            width -= canvas_string_width(canvas, "...");
        }

        // Calculate scroll size
        size_t scroll_size = furi_string_size(line);
        size_t right_width = 0;
        for(size_t i = scroll_size - 1; i > 0; i--) {
            while((furi_string_get_char(line, i) & 0xC0) == 0x80) {
                i--;
            }

            FuriStringUTF8State state = FuriStringUTF8StateStarting;
            FuriStringUnicodeValue value = 0;

            size_t offset = i;
            do {
                furi_string_utf8_decode(furi_string_get_char(line, offset), &state, &value);
                offset++;
            } while(state != FuriStringUTF8StateStarting);

            right_width += canvas_glyph_width(canvas, value);
            if(right_width > width) break;
            scroll_size--;
            if(!scroll_size) break;
        }

        // Ensure that we have something to scroll
        if(scroll_size) {
            scroll_size += 3;
            scroll = scroll % scroll_size;

            size_t offset = 0;
            for(; scroll > 0; offset++) {
                if((furi_string_get_char(line, offset) & 0xC0) != 0x80) {
                    scroll--;
                }
            }

            // Step back to the end of the previous symbol
            offset--;
            furi_string_right(line, offset);
        }

        len_px = canvas_string_width(canvas, furi_string_get_cstr(line));
        while(len_px > width) {
            size_t offset = 1;
            size_t len = furi_string_size(line);

            while((furi_string_get_char(line, len - offset) & 0xC0) == 0x80) {
                offset++;
            }

            furi_string_left(line, len - offset);
            len_px = canvas_string_width(canvas, furi_string_get_cstr(line));
        }

        if(ellipsis) {
            furi_string_cat(line, "...");
        }
    }

    canvas_draw_str(canvas, x, y, furi_string_get_cstr(line));
    furi_string_free(line);
}
