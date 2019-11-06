/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:56:06 by wta               #+#    #+#             */
/*   Updated: 2019/10/25 16:40:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft.h"
#include "tga_loader.h"
#include "shader.h"

/*
**	TODO: change return values to handle errors
*/

void	create_shader(t_shader *ctx, const GLenum type, const GLchar *src)
{
	uint32_t	id;
	t_file		file;
	int			success;
	char		info_log[512];

	if (ctx->active >= MAX_SHADER)
		return ;
	id = glCreateShader(type);
	store_data(&file, src);
	glShaderSource(id, 1, (const GLchar**)&file.content, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetProgramInfoLog(id, 512, NULL, info_log);
	ctx->shader_ids[ctx->active] = id;
	ctx->active++;
	munmap(file.content, file.file_stat.st_size);
}

void	attach_shaders(t_shader *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->active)
	{
		glAttachShader(ctx->id, ctx->shader_ids[i]);
		i++;
	}
}

void	link_program(t_shader *ctx)
{
	int		success;
	char	info_log[512];

	glLinkProgram(ctx->id);
	glGetProgramiv(ctx->id, GL_LINK_STATUS, &success);
	if (!success)
		glGetProgramInfoLog(ctx->id, 512, NULL, info_log);
}