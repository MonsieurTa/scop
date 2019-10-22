/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:42:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/22 16:20:09 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glut.h>
#include "SDL.h"
#include "libft.h"

int	main(void)
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_GLContext	gl_ctx;

	// create SDL window
	window = SDL_CreateWindow(
		"Scop", 0, 0, 640, 480,
		SDL_WINDOW_OPENGL
	);

	// create openGL context based on SDL window
	gl_ctx = SDL_GL_CreateContext(window);

	// then we can use openGL API
	glViewport(0, 0, 640, 480);

	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}
	}

	// clean exit
	SDL_GL_DeleteContext(gl_ctx);
	SDL_DestroyWindow(window);


	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		ft_putstr_fd("Could not initialize SDL.\n", STDERR_FILENO);
	}
	ft_putstr("SDL initialized.\n");

	ft_putstr("Quiting SDL.\n");
	SDL_Quit();
	ft_putstr("Quiting...\n");
	return (0);
}
