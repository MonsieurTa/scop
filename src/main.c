/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:42:10 by wta               #+#    #+#             */
/*   Updated: 2019/11/06 18:43:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "scop.h"
#include "shader.h"
#include "tga_loader.h"

int	main(void)
{
	t_env	env;
	float v1[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	uint32_t	indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	uint32_t	VBO;
	uint32_t	VAO;
	uint32_t	EBO;
	t_shader	shader_ctx;

	ft_bzero(&env, sizeof(t_env));
	if (sdl_ctx_init(&env.sdl_ctx) == -1)
		exit(0);
	glViewport(0, 0, W_WIDTH, W_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	ft_printf("OpenGL: version: %s\n", glGetString(GL_VERSION));

	shader_ctx = new_shader();
	shader_ctx.create(&shader_ctx, GL_VERTEX_SHADER, "src/shaders/tex_vertex.vs");
	shader_ctx.create(&shader_ctx, GL_FRAGMENT_SHADER, "src/shaders/tex_fragment.fs");
	shader_ctx.attach_shaders(&shader_ctx);
	shader_ctx.link_program(&shader_ctx);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v1), v1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Loading img and texture

	unsigned int texture;
	t_tga_loader	tga_loader = new_tga_loader();
	tga_loader.load(&tga_loader, "resources/textures/img1.tga");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (tga_loader.data)
	{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				tga_loader.getWidth(&tga_loader),
				tga_loader.getHeight(&tga_loader),
				0, GL_RGB, GL_UNSIGNED_BYTE,
				tga_loader.data);
			glGenerateMipmap(GL_TEXTURE_2D);
			tga_loader.destroy(&tga_loader);
	}
	else
		ft_printf("OpenGL: Failed to load texture\n");

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLfloat	offset[3] = {0.0f, 0.0f, 0.0f};
	while (1)
	{
		if (!event_handler(&env))
			break ;
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shader_ctx.id);

		shader_ctx.set_3fv(&shader_ctx, "offset", offset);

		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(env.sdl_ctx.window);
	}
	sdl_ctx_destroy(&env.sdl_ctx);
	return (0);
}
