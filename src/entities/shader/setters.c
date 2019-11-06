/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 11:08:34 by wta               #+#    #+#             */
/*   Updated: 2019/10/25 11:34:57 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shader.h"

void	set_int(t_shader *ctx, GLchar *name, GLint value)
{
	glUniform1i(glGetUniformLocation(ctx->id, name), value);
}

void	set_float(t_shader *ctx, GLchar *name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(ctx->id, name), value);
}

void	set_3fv(t_shader *ctx, GLchar *name, GLfloat *value)
{
	glUniform3fv(glGetUniformLocation(ctx->id, name), 1, value);
}
