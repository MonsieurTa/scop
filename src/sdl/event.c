/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:00:28 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 17:45:23 by wta              ###   ########.fr       */
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
			if (e->key.keysym.sym == SDLK_UP)
				env->blend += env->blend < 1 ? 0.05 : 0;
			if (e->key.keysym.sym == SDLK_DOWN)
				env->blend -= env->blend > 0 ? 0.05 : 0;
		}
	}
	return (1);
}
