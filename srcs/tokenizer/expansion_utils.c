/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:40:39 by machouba          #+#    #+#             */
/*   Updated: 2024/07/29 17:15:43 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTES)
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *str)
{
	char	*cleaned_str;
	int		i;
	int		quotes_count;

	i = 0;
	quotes_count = count_quotes(str);
	cleaned_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - quotes_count
				+ 1));
	if (!cleaned_str)
		return (NULL);
	while (str && *str)
	{
		if (*str != SINGLE_QUOTE && *str != DOUBLE_QUOTES)
		{
			cleaned_str[i] = *str;
			i++;
		}
		str++;
	}
	cleaned_str[i] = '\0';
	return (cleaned_str);
}

char	*extract_until_limit(char *str, char *limset)
{
	char	*extracted_str;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(limset, str[i]) == NULL)
		i++;
	if (i == 0)
		return (NULL);
	extracted_str = ft_substr(str, 0, i);
	return (extracted_str);
}

char	*extract_variable_name(char *str)
{
	int		i;
	char	*var_name;

	if (!str || *str != '$')
		return (NULL);
	str++;
	if (str && *str == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(*str))
		return (ft_substr(str, 0, 1));
	i = 0;
	while (str[i] && ft_is_var(str[i]))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*get_expansion(t_data *data, char *var_name, char *str)
{
	char	*var_content;

	if (var_name == NULL)
	{
		if (ft_is_var(*(str + 1)) == FALSE && ft_isquote(*(str
					+ 1)) == FALSE)
			return (ft_strdup("$"));
		return (NULL);
	}
	if (*var_name == '?')
		return (ft_itoa(data->exit_return));
	var_content = get_env(data->envs, var_name);
	if (!var_content)
		return (NULL);
	return (var_content);
}
