/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:57:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/24 18:50:23 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "shader.h"

#include <stdio.h>

static char	*get_src_content(const GLchar *filepath)
{
	char	buffer[SHADER_BUFF_SIZE + 1];
	char	*content;
	size_t	total_len;
	size_t	read_ret;
	int		fd;

	if ((fd = open(filepath, O_RDONLY)) == -1) {
		printf("%d\n", fd);
		return (NULL);
	}
	total_len = 0;
	while ((read_ret = read(fd, buffer, SHADER_BUFF_SIZE)) > 0)
		total_len += read_ret;
	close(fd);
	if (!(content = (char*)malloc(sizeof(char) * (total_len + 1))))
		return (NULL);
	content[total_len] = '\0';
	total_len = 0;
	if ((fd = open(filepath, O_RDONLY)) == -1)
		return (NULL);
	while ((read_ret = read(fd, buffer, SHADER_BUFF_SIZE)) > 0)
	{
		ft_memcpy(content + total_len, buffer, read_ret);
		total_len += read_ret;
	}
	close(fd);
	return (content);
}

static void	create_shader(t_shader *ctx, const GLenum type, const GLchar *src)
{
	uint32_t	id;
	int			success;
	char		*content;
	char		infoLog[512];

	id = glCreateShader(type);
	if ((content = get_src_content(src)) == NULL)
		return ;
	glShaderSource(id, 1, (const GLchar**)&content, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
	}
	ctx->shader_ids[ctx->active] = id;
	ctx->active++;
	ft_strdel(&content);
}

static void	attach_shaders(t_shader *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->active)
	{
		glAttachShader(ctx->id, ctx->shader_ids[i]);
		i++;
	}
}

static void	link_program(t_shader *ctx)
{
	int		success;
	char	info_log[512];

	glLinkProgram(ctx->id);
	glGetProgramiv(ctx->id, GL_LINK_STATUS, &success);
	if (!success)
		glGetProgramInfoLog(ctx->id, 512, NULL, info_log);
}

static void	delete_shaders(t_shader *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->active)
	{
		glDeleteShader(ctx->shader_ids[i]);
		i++;
	}
}

/*
**	v_path: vertex shader source file
**	f_path: fragment shader source file
*/
t_shader	new_shader(void)
{
	t_shader	ctx;

	ft_bzero(&ctx, sizeof(t_shader));
	ctx.id = glCreateProgram();
	ctx.create = create_shader;
	ctx.attach_shaders = attach_shaders;
	ctx.link_program = link_program;
	delete_shaders(&ctx);
	return ctx;
}
