global_variable float render_scale = 0.01f;

void clear_screen(u32 color) {

	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}

}


void draw_rect_pixels(int x1, int y1, int x2, int y2, u32 color) {

	x1 = clamp(0, x1, render_state.width);
	x2 = clamp(0, x2, render_state.width);
	y1 = clamp(0, y1, render_state.height);
	y2 = clamp(0, y2, render_state.height);

	for (int y = y1; y < y2; y++) {
		u32* pixel = (u32*)render_state.memory + x1 + y * render_state.width;
		for (int x = x1; x < x2; x++) {
			*pixel++ = color;
		}
	}

}


void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * render_scale;		    // 0 * 720 = 0
	y *= render_state.height * render_scale;			// 0 * 720 = 0
	half_size_x *= render_state.height * render_scale;	// 0.2 * 720 = 144
	half_size_y *= render_state.height * render_scale; // 0.2 * 720 = 144

	x += render_state.width / 2.f;  // 0 + (1280 / 2.0) = 640
	y += render_state.height / 2.f;	// 0 + (720 / 2.0) = 360

	int x1 = x - half_size_x; // 640 - 144 = 496
	int x2 = x + half_size_x; // 640 + 144 = 788
	int y1 = y - half_size_y; // 360 - 144 = 216
	int y2 = y + half_size_y; // 360 + 144 = 504

	draw_rect_pixels(x1, y1, x2, y2, color); // 496 to the right, 216 upwards, draw 788 to the right, draw 504, color

}


void draw_point(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * render_scale;		    // 0 * 720 = 0
	y *= render_state.height * render_scale;			// 0 * 720 = 0
	half_size_x *= render_state.height * render_scale;	// 0.2 * 720 = 144
	half_size_y *= render_state.height * render_scale; // 0.2 * 720 = 144

	x += render_state.width / 2.f;  // 0 + (1280 / 2.0) = 640
	y += render_state.height / 2.f;	// 0 + (720 / 2.0) = 360

	int x1 = x - half_size_x; // 640 - 144 = 496
	int x2 = x + half_size_x; // 640 + 144 = 788
	int y1 = y - half_size_y; // 360 - 144 = 216
	int y2 = y + half_size_y; // 360 + 144 = 504

	draw_rect_pixels(x1, y1, x1 + 1, y1 + 1, color); // 496 to the right, 216 upwards, draw 788 to the right, draw 504, color

}

// 	draw_number(player_1_score, -10, 40, 1.f, 0x7851a9);

internal void draw_number(int number, float x, float y, float size, u32 color) {
	float half_size = size * 0.5f;
	switch (number) {
		case 0: {
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + size * 2.f, half_size, half_size, color);
			draw_rect(x, y - size * 2.f, half_size, half_size, color);
		} break;

		case 1: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
		} break;

		case 2: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
		} break;

		case 3: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
		} break;

		case 4: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size * 1.5f, half_size, size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
		} break;

		case 5: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
		} break;

		case 6: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
		} break;

		case 7: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
		} break;
	}
}