/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:56:06 by wta               #+#    #+#             */
/*   Updated: 2019/11/06 18:10:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft.h"
#include "ft_printf.h"
#include "tga_loader.h"
#include "shader.h"

/*
**	TODO: change return values to handle errors
*/

int	create_shader(t_shader *ctx, const GLenum type, const GLchar *src)
{
	uint32_t	id;
	t_file		file;
	int			success;
	char		info_log[512];

	ft_bzero(info_log, 512);
	if (ctx->active >= MAX_SHADER)
		return (0);
	id = glCreateShader(type);
	if (store_data(&file, src) == -1)
	{
		ft_printf("shader:error: could not store data into memory\n", file.filepath);
		return (-1);
	}
	ft_printf("Shader:\n\tUsing \"%s\"\n\t...Mapped into memory\n", file.filepath);
	glShaderSource(id, 1, (const GLchar**)&file.content, NULL);
	ft_printf("\t...Loaded into OpenGL\n", file.filepath);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, info_log);
		ft_printf("error: compilation failed\nmore details:\n\t%s\n", info_log);
		return (-1);
	}
	ctx->shader_ids[ctx->active] = id;
	ctx->active++;
	munmap(file.content, file.file_stat.st_size);
	ft_printf("Shader(%s): Unmapped from memory\n", file.filepath);
	return (0);
}

void	attach_shaders(t_shader *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->active)
	{
		ft_printf("Shader:%d: Linked to program #%d\n", ctx->shader_ids[i], ctx->id);
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
