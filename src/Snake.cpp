/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/31 18:51:54 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

SnakeSection::SnakeSection(SnakeSection const &in) {
	*this = in;
}

Snake::Snake(unsigned x, unsigned y) : s_direct (eDirection::Up), next_direct(eDirection::Up) {
	for (int i = 0; i < 4; i++) {
		snake_segments.push_back(SnakeSection(x, y - i));
	}
};

SnakeSection &SnakeSection::operator=(SnakeSection const &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

SnakeSection const &Snake::head(void) {
	return (snake_segments.front());
}

void Snake::move(void) {
	s_direct = next_direct;
	for (int i = snake_segments.size() - 1; i > 0; i--) {
		snake_segments[i].x = snake_segments[i - 1].x;
		snake_segments[i].y = snake_segments[i - 1].y;
	}
	switch (s_direct)
	{
		case eDirection::Up:
			snake_segments[0].y += 1;
			break;
		case eDirection::Down:
			snake_segments[0].y -= 1;
			break;
		case eDirection::Left:
			snake_segments[0].x -= 1;
			break;
		case eDirection::Right:
			snake_segments[0].x += 1;
			break;
	}
}

void Snake::turn(enum eDirection direction) {
	if (((int)direction + 1) % 4 + 1 == (int)s_direct)
		return;
	next_direct = direction;
}

void Snake::grow() {
	s_direct = next_direct;
	SnakeSection end = snake_segments.back();
	move();
	snake_segments.push_back(end);
}

unsigned Snake::getX(void) const {
	return (snake_segments.front().x);
}

unsigned Snake::getY(void) const {
	return (snake_segments.front().y);
}

Snake::~Snake() {};

