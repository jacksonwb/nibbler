/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/30 21:06:14 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Food::Food(unsigned width, unsigned height) {
	x = rand() % width;
	y = rand() % height;
	while (x == 0) {
		x = rand() % width;
	}
}

void Food::respawn(unsigned width, unsigned height) {
	this->x = (rand() % (width - 1)) + 1;
	this->y = (rand() % (height - 1)) + 1;
}

Game::Game(unsigned width, unsigned height) : snake(width / 2, height / 2),
	food(width, height), move_interval(150000), last_move(clock()), score(0),
	map_width(width), map_height(height), paused(false), game_over(false)
{
	bzero(ar, sizeof(ar));
};

void Game::update(void) {
	clock_t now = clock();
	static bool grow = false;
	if (game_over)
		return;
	if (now > last_move + move_interval)
	{
		grow ? snake.grow() : snake.move();
		grow = false;
		if (snake.getX() >= map_width || snake.getX() == 0 || snake.getY() >= map_height
			|| snake.getY() == 0)
		{
			game_over = true;
		}
		if (snake.getX() == food.x && snake.getY() == food.y) {
			score++;
			food.respawn(map_width, map_height);
			grow = true;
		}
		last_move = now;
		updateMap();
	}
}

void Game::updateMap(void) {
	bzero(ar, sizeof(ar));
	ar[food.x][food.y] = FOOD_CHAR;
	for (auto section : snake.snake_segments)
	{
		ar[section.x][section.y] = SECTION_CHAR;
	}
	ar[snake.head().x][snake.head().y] = HEAD_CHAR;
}

void Game::reset(void) {
	score = 0;
	snake = Snake(map_width / 2, map_height / 2);
	paused = false;
	food.respawn(map_width, map_height);
	game_over = false;
}

bool Game::isPaused(void) const {
	return paused;
}

bool Game::isGameOver(void) const {
	return game_over;
}

unsigned Game::getWidth(void) const {
	return map_width;
}

unsigned Game::getHeight(void) const {
	return map_height;
}

Snake &Game::getSnake(void) {
	return snake;
}

Game::~Game() {};
