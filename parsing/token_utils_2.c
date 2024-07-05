/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:07:13 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/05 19:07:28 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_error(char *field, t_error_type type, char *input)
{
	free(field);
	error(type, input);
}

int	is_not_space(char *input, int i)
{
	if ((input[i] && !is_meta_char(input[i]) && input[i] != ' ' \
		&& input[i] != '\t' && input[i] != '\n'))
		return (1);
	else
		return (0);
}
