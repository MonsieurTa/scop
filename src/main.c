/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:42:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/24 18:50:51 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "scop.h"
#include "shader.h"

int	main(void)
{
	t_env	env;
	float v1[] = {
		-0.4f,  0.5f, 0.0f,
		-0.8f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
	};
	float v2[] = {
		0.4f,  0.5f, 0.0f,
		0.8f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};
	float colours[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	// uint32_t	indices[] = {
	// 	0, 1, 2, 0, 3, 2
	// };

	uint32_t	VBO[2];
	uint32_t	VBO_colours;
	uint32_t	VAO[2];
	// uint32_t	EBO;
	t_shader	shader_ctx;


	ft_bzero(&env, sizeof(t_env));
	if (sdl_ctx_init(&env.sdl_ctx) == -1)
		exit(0);
	glViewport(0, 0, W_WIDTH, W_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	ft_printf("OpenGL: version: %s\n", glGetString(GL_VERSION));

	shader_ctx = new_shader();
	shader_ctx.create(&shader_ctx, GL_VERTEX_SHADER, "src/shaders/vertex_shader.vs");
	shader_ctx.create(&shader_ctx, GL_FRAGMENT_SHADER, "src/shaders/fragment_shader.fs");
	shader_ctx.attach_shaders(&shader_ctx);

	glBindAttribLocation(shader_ctx.id, 0, "v_pos");
	glBindAttribLocation(shader_ctx.id, 1, "v_colour");

	shader_ctx.link_program(&shader_ctx);

	glGenVertexArrays(2, VAO);

	glGenBuffers(2, VBO);
	glGenBuffers(1, &VBO_colours);
	// glGenBuffers(1, &EBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v1), v1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v2), v2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (1)
	{
		if (!event_handler(&env))
			break ;
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_ctx.id);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(env.sdl_ctx.window);
	}

	sdl_ctx_destroy(&env.sdl_ctx);
	return (0);
}
