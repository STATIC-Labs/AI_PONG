#include <cstdlib>
#include <time.h>


#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_1_p, player_1_dp;
float player_2_p, player_2_dp;

float arena_half_size_x = 85;
float arena_half_size_y = 45;

float player_half_size_x = 2;
float player_half_size_y = 10;

float ball_half_size = 1;

bool player_1_won = false;
bool player_2_won = false;

int player_1_score = 0;
int player_2_score = 0;

bool vs_ai = true;

int random_y_gen() {

	srand(time(0));
	int random = rand();
	random %= 30;

	if (random % 2 == 0) 
		return +random;
	
	else if (random % 2 == 1)
		return -random;

}


int random_x_gen() {

	srand(time(0));
	int random = rand();
	
	if (random % 2 == 0)
		return -100;
	else
		return 100;

}

float at_x;
float ball_p_x, ball_p_y, ball_dp_x = random_x_gen(), ball_dp_y = random_y_gen();

internal void simpulate_player(float* p, float* dp, float ddp, float dt) {

	ddp -= *dp * 10.f;

	*p = *p + *dp * dt + *dp * dt * dt * 0.5f;
	*dp = *dp + ddp * dt;

	if (*p + player_half_size_y > arena_half_size_y) {
		*p = arena_half_size_y - player_half_size_y;
		*dp *= 0;
	}
	else if (*p - player_half_size_y < -arena_half_size_y) {
		*p = -arena_half_size_y + player_half_size_y;
		*dp *= 0;
	}

}


internal bool ball_collision(float bpx, float bpy, float bhsx, float bhsy, float pxp, float pyp, float phsx, float phsy) {

	return (bpx + bhsx > pxp - phsx &&
		bpx - bhsx < pxp + phsx &&
		bpy + bhsy > pyp - phsy &&
		bpy + bhsy < pyp + phsy);

}


internal void simulate_game(Input* input, float dt) {

	clear_screen(0x7851a9);

	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0x000000);

	float player_1_ddp = 0.f;
	if (is_down(BUTTON_W))
		player_1_ddp += 2000;
	if (is_down(BUTTON_S))
		player_1_ddp -= 2000;

	float player_2_ddp = 0.f;

	if (!vs_ai) {
		if (is_down(BUTTON_UP))
			player_2_ddp += 2000;
		if (is_down(BUTTON_DOWN))
			player_2_ddp -= 2000;
	}
	else {
		if (ball_p_x > 10) {
			if (ball_p_y > player_2_p)
				player_2_ddp += 2000;
			else
				player_2_ddp -= 2000;
		}
	}
	
	simpulate_player(&player_1_p, &player_1_dp, player_1_ddp, dt);
	simpulate_player(&player_2_p, &player_2_dp, player_2_ddp, dt);

	ball_p_x += (ball_dp_x * dt) * 1.05f;
	ball_p_y += ball_dp_y * dt;

	if (ball_collision(ball_p_x, ball_p_y, ball_half_size, ball_half_size, -80, player_1_p, player_half_size_x, player_half_size_y)) {

		ball_p_x = -80 + player_half_size_x + ball_half_size;
		ball_dp_x *= -1;

		ball_dp_y = player_1_dp * 0.5f + (ball_p_y - player_1_p);

	}
	else if (ball_collision(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 80, player_2_p, player_half_size_x, player_half_size_y)) {

		ball_p_x = 80 - player_half_size_x - ball_half_size;
		ball_dp_x *= -1;

		ball_dp_y = player_2_dp * 0.5f + (ball_p_y - player_2_p);

	}

	if (ball_p_y + ball_half_size > arena_half_size_y) {
		ball_p_y = arena_half_size_y - ball_half_size;
		ball_dp_y *= -1;
	}
	else if (ball_p_y - ball_half_size < -arena_half_size_y) {
		ball_p_y = -arena_half_size_y + ball_half_size;
		ball_dp_y *= -1;
	}

	if (ball_p_x + ball_half_size > arena_half_size_x) {
		if (!player_1_won && !player_2_won) {
			player_1_score += 1;
			ball_p_x = 0;
			ball_p_y = 0;
			ball_dp_x *= -1;
		}
	}
	else if (ball_p_x - ball_half_size < -arena_half_size_x) {
		if (!player_1_won && !player_2_won) {
			player_2_score += 1;
			ball_p_x = 0;
			ball_p_y = 0;
			ball_dp_x *= -1;
		}
	}

	at_x = -80;
	for (int i = 0; i < player_1_score; i++) {
		draw_rect(at_x, 47.5f, 1.f, 1.f, 0xFFFFFF);
		at_x += 2.5;
	}

	at_x = 80;
	for (int i = 0; i < player_2_score; i++) {
		draw_rect(at_x, 47.5f, 1.f, 1.f, 0xFFFFFF);
		at_x -= 2.5;
	}

	draw_number(player_1_score, -10, 40, 1.f, 0xFFFFFF);
	draw_number(player_2_score, 10, 40, 1.f, 0xFFFFFF);

	if (player_1_score == 7)
		player_1_won = true;
	else if (player_2_score == 7)
		player_2_won = true;

	if (!player_1_won && !player_2_won)
		draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xFFFFFF);

	draw_rect(-80, player_1_p, player_half_size_x, player_half_size_y, 0xFFFFFF);
	draw_rect(80, player_2_p, player_half_size_x, player_half_size_y, 0xFFFFFF);

}
