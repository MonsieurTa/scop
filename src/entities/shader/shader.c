/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:57:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/25 11:41:00 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shader.h"

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
	ctx.set_int = set_int;
	ctx.set_float = set_float;
	ctx.set_3fv = set_3fv;
	delete_shaders(&ctx);
	return (ctx);
}
