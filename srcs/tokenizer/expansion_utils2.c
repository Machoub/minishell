/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:42:26 by machouba          #+#    #+#             */
/*   Updated: 2024/07/29 17:13:25 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*extract_string_in_double_quotes(t_data *data, char *str)
{
	char	*variable_name;
	char	*result_str;
	char	*addition;
	char	*ptr;

	result_str = NULL;
	addition = NULL;
	while (str != NULL && *str != '\0')
	{
		if (*str == '$')
		{
			variable_name = extract_variable_name(str);
			addition = get_expansion(data, variable_name, str);
			str += ft_strlen(variable_name) + 1;
			free(variable_name);
		}
		else
		{
			addition = extract_until_limit(str, "$\"");
			str += ft_strlen(addition);
		}
		ptr = ft_strsjoin(result_str, addition);
		result_str = ptr;
	}
	return (result_str);
}

char	*extract_quoted_string(t_data *data, char *str)
{
	char	*grab;
	char	*result;

	grab = NULL;
	result = NULL;
	if (str && *str == SINGLE_QUOTE && *(str + 1))
		result = extract_until_limit(str + 1, "\'");
	else if (str && *str == DOUBLE_QUOTES && *(str + 1))
	{
		grab = extract_until_limit(str + 1, "\"");
		result = extract_string_in_double_quotes(data, grab);
		free(grab);
	}
	else
		return (NULL);
	return (result);
}
