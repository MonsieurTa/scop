/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:00:28 by wta               #+#    #+#             */
/*   Updated: 2019/10/23 15:16:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "ft_printf.h"

int		event_handler(t_env *env)
{
	SDL_Event	*e;

	e = &env->sdl_ctx.event;
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			return (0);
		if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_ESCAPE)
				return (0);
		}
		else if (e->type == SDL_KEYUP)
		{

		}
	}
	return (1);
}
