/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:42:40 by wta               #+#    #+#             */
/*   Updated: 2019/10/25 20:21:11 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# if defined(__APPLE__)
# include <OpenGL/gl3.h>
# else
# include <GLES3/gl3.h>
# endif

# include "SDL.h"

# define NAME		"Scop"

# define W_WIDTH	1280
# define W_HEIGHT	1024

typedef struct	s_sdl_ctx
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_GLContext	gl_ctx;
}				t_sdl_ctx;

typedef struct	s_env
{
	t_sdl_ctx	sdl_ctx;
}				t_env;

int		sdl_ctx_init(t_sdl_ctx *sdl);
void	sdl_ctx_destroy(t_sdl_ctx *sdl);
void	sdl_ctx_quit(void);

int		event_handler(t_env *env);


#endif
