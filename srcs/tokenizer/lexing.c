/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:12:29 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 12:23:39 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	get_delim(t_token **lst_token)
{
	t_token	*token;

	token = *lst_token;
	while (token)
	{
		if (token->type == HEREDOC && token->next && token->next->type == WORD)
			token->next->type = LIM;
		token = token->next;
	}
}

static int	check_quote(char *input)
{
	int			count_squote;
	int			count_dquote;

	count_squote = 0;
	count_dquote = 0;
	if (!input)
		return (FAIL);
	while (*input)
	{
		if (ft_isquote(*input) && (*input + 1) && ft_strchr(input + 1,
				*input) != NULL)
			input += ft_strchr(input + 1, *input) - input + 1;
		else
		{
			if (*input == '\"')
				count_squote++;
			if (*input == '\'')
				count_dquote++;
			input++;
		}
	}
	if (count_squote % 2 != 0 || count_dquote % 2 != 0)
		return (FAIL);
	return (SUCCESS);
}

int	lexing(t_data *data)
{
	if (check_quote(data->input) == FAIL)
	{
		data->exit_return = 2;
		return (ft_print_err(QUOTES_ERROR), FAIL);
	}
	data->tokens = ft_tokenization(data->input);
	if (!data->tokens)
		return (FAIL);
	get_delim(&data->tokens);
	if (token_checker(data, data->tokens) == FAIL)
		return (FAIL);
	expand_tokens(data, &data->tokens);
	return (1);
}
