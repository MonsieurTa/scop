/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:42:10 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 17:41:27 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "scop.h"
#include "shader.h"
#include "gl_tex.h"
#include <stdio.h>
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
	t_shader	shader;

	ft_bzero(&env, sizeof(t_env));
	if (sdl_ctx_init(&env.sdl_ctx) == -1)
		exit(0);
	glViewport(0, 0, W_WIDTH, W_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	ft_printf("OpenGL: version: %s\n", glGetString(GL_VERSION));

	shader = new_shader();
	shader.create(&shader, GL_VERTEX_SHADER, "src/shaders/tex_vertex.vs");
	shader.create(&shader, GL_FRAGMENT_SHADER, "src/shaders/tex_fragment.fs");
	shader.attach_shaders(&shader);
	shader.link_program(&shader);

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

	unsigned int texture[2];
	t_gl_tex gl_tex = gl_tex_init();

	gl_tex.enable_alpha();

	gl_tex.load(&gl_tex, "resources/textures/img1.tga", store_data);
	glGenTextures(2, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, gl_tex.internal_format, gl_tex.width,
		gl_tex.height, 0, gl_tex.format, GL_UNSIGNED_BYTE, gl_tex.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	gl_tex.destroy(&gl_tex);

	gl_tex.load(&gl_tex, "resources/textures/omega.tga", store_data);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, gl_tex.internal_format, gl_tex.width,
		gl_tex.height, 0, gl_tex.format, GL_UNSIGNED_BYTE, gl_tex.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	gl_tex.destroy(&gl_tex);

	GLfloat	offset[3] = {0.0f, 0.0f, 0.0f};
	while (1)
	{
		if (!event_handler(&env))
			break ;
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		glUseProgram(shader.id);


		shader.set_3fv(&shader, "offset", offset);
		shader.set_int(&shader, "texture1", 0);
		shader.set_int(&shader, "texture2", 1);
		shader.set_float(&shader, "blend", env.blend);
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(env.sdl_ctx.window);
	}
	sdl_ctx_destroy(&env.sdl_ctx);
	return (0);
}
