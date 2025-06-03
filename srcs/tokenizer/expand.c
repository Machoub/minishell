/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:24:38 by machouba          #+#    #+#             */
/*   Updated: 2024/08/07 21:52:12 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_next_segment_length(char *str, char *parsed_str)
{
	char	*variable_name;
	int		length;

	if (!str || *str == '\0')
		return (0);
	if ((*str == DOUBLE_QUOTES || *str == SINGLE_QUOTE) && *(str + 1))
		return (ft_strchr(str + 1, *str) - str + 1);
	if (*str == '$')
	{
		variable_name = extract_variable_name(str);
		length = ft_strlen(variable_name) + 1;
		free(variable_name);
		return (length);
	}
	return (ft_strlen(parsed_str));
}

static char	*extract_next_segment(t_data *data, char *str)
{
	char	*segment;
	char	*result;

	segment = NULL;
	result = NULL;
	if (str && ft_isquote(*str) && (str + 1))
	{
		result = extract_quoted_string(data, str);
		if (!result)
			return (ft_strdup("\0"));
	}
	else if (str && *str == '$' && (str + 1))
	{
		segment = extract_variable_name(str);
		result = get_expansion(data, segment, str);
		free(segment);
	}
	else
		result = extract_until_limit(str, " \t\n\r\v\f$\'\"");
	return (result);
}

char	*expand_string(t_data *data, char *str)
{
	char	*expanded_str;
	char	*temp;
	char	*next_segment;

	expanded_str = NULL;
	next_segment = NULL;
	if (ft_strncmp(str, "~/", 2) == 0 || ft_strcmp(str, "~") == 0)
	{
		next_segment = get_env(data->envs, "HOME");
		str++;
		temp = ft_strsjoin(expanded_str, next_segment);
		expanded_str = temp;
	}
	while (*str)
	{
		next_segment = extract_next_segment(data, str);
		str += get_next_segment_length(str, next_segment);
		temp = ft_strsjoin(expanded_str, next_segment);
		expanded_str = temp;
	}
	return (expanded_str);
}

void	expand_tokens(t_data *data, t_token **token_list)
{
	t_token	*current_token;
	char	*new_value;

	new_value = NULL;
	current_token = *token_list;
	while (current_token != NULL)
	{
		if (current_token->type == WORD)
		{
			new_value = expand_string(data, current_token->value);
			free(current_token->value);
			current_token->value = new_value;
		}
		else if (current_token->type == LIM)
		{
			if (ft_strchr(current_token->value, '\'') != NULL
				|| ft_strchr(current_token->value, '\"') != NULL)
				current_token->expand_flag = false;
			new_value = remove_quotes(current_token->value);
			free(current_token->value);
			current_token->value = new_value;
		}
		current_token = current_token->next;
	}
}
