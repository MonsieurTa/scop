/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:51:05 by wta               #+#    #+#             */
/*   Updated: 2019/10/25 10:41:24 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "ft_printf.h"
#include "error.h"
#include "scop.h"

/*
**	SDL_Init -> video
**	SDL_CreateWindow
**	SDL_GL_CreateContext
*/

int	sdl_ctx_init(t_sdl_ctx *ctx)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (throw_error(ERR_SDL_VIDEO));
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	ctx->window = SDL_CreateWindow(
		NAME, 0, 0, W_WIDTH, W_HEIGHT,
		SDL_WINDOW_OPENGL);
	if (!ctx->window)
		return (throw_error(ERR_SDL_CREAT_WIN));
	ctx->gl_ctx = SDL_GL_CreateContext(ctx->window);
	if (!ctx->gl_ctx)
	{
		ft_printf("sdl: %s\n", SDL_GetError());
		return (throw_error(ERR_SDL_GL_CTX));
	}
	return (0);
}
