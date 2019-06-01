/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/31 18:54:38 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define  GAME_HPP
#include <vector>
#include <chrono>
#include "Snake.hpp"

class Food {
	public:
		Food(unsigned width, unsigned height);
		void respawn(unsigned x, unsigned y, Snake& snake);
		unsigned x;
		unsigned y;
};

class Game {
	Snake snake;
	Food food;
	std::chrono::duration<double> move_interval;
	std::chrono::steady_clock::time_point last_move;
	void updateMap(void);
	public:
		unsigned score;
		unsigned const map_width;
		unsigned const map_height;
		bool paused;
		bool game_over;
		char ar[GAME_SIZE_MAX + 1][GAME_SIZE_MAX + 1];
		Game(unsigned, unsigned);
		void update();
		void reset();
		bool isPaused() const;
		bool isGameOver() const;
		void init(void);
		unsigned getWidth(void) const;
		unsigned getHeight(void) const;
		Snake &getSnake(void);
		~Game();
};

#endif
