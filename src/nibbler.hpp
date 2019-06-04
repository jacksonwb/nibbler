/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:45:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/06/04 11:34:38 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

# define GAME_SIZE_MIN 10
# define GAME_SIZE_MAX 45

# define FOOD_CHAR 'f'

# define H_U 1
# define H_R 2
# define H_D 3
# define H_L 4

# define S_UD 11
# define S_RL 12
# define S_LU 13
# define S_RU 14
# define S_DR 15
# define S_LD 16

# define T_U 21
# define T_R 22
# define T_D 23
# define T_L 24

# define ESC_KEY 27

enum class eDirection {Up = 1, Right, Down, Left};

#endif