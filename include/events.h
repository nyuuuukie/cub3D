/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 19:07:55 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/16 19:15:49 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define KEY_PRESS_EVENT 2
# define KEY_RELEASE_EVENT 3
# define KEY_PRESS_MASK 1L<<0
# define KEY_RELEASE_MASK 1L<<1

#ifdef LINUX
	# define KEY_CLOSE_EVENT 33
	# define KEY_CLOSE_MASK 1L<<17
#else
	# define KEY_CLOSE_EVENT 17
	# define KEY_CLOSE_MASK 1L<<17
#endif

#endif