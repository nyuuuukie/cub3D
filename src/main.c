/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 07:47:28 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char*	get_map_error(int code)
{
	const int n = 10; //Cannot use const due to norm error
	static char* errors[10];

	errors[0] = "Unknown error";
	errors[1] = "Bad extension of map";
	errors[2] = "No such file or directory";
	errors[3] = "";
	errors[4] = "";
	errors[5] = "";
	errors[6] = "";
	errors[7] = "";
	errors[7] = "";
	errors[8] = "";
	errors[9] = "";
	
	code = (code < 1 && code > n - 1) ? 0 : code;
	return (errors[code]);
}

int link_start()
{
	return (0);
}

int make_screenshot()
{
	return (0);
}

void	set_defaults(t_prm *prm)
{
	prm->r_height = 0;
	prm->r_width = 0;
}

int main(int argc, char **argv)
{
	t_prm	prm;

	set_defaults(&prm);
	if (argc == 2 || argc == 3)
	{
		if (check_map_arg(argv[1]))
			return (-1);
		if (argc == 3 && check_save_arg(argv[2]))
			return (-1);
		if (check_map(argv[1], &prm))
			return (-1);
		(argc == 2) ? link_start() : make_screenshot();
	}
	else
		print_error("Argument error", "Invalid number of arguments", 0);
	return (0);
}