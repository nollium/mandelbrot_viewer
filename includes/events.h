/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:52:42 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/01 01:15:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "structs.h"
# include "libc.h"

int     loop_handler(t_game *game);
int		press_handler(int keycode, t_game *game);
int		release_handler(int keycode, t_game *game);
void	hooks(t_window *win, t_game *game);
int		key_handler(long keys, t_game *game);

# ifdef __linux__

#  ifndef QWERTY
#   define FORWARD_KEY		122
#   define BACKWARD_KEY		115
#   define LEFT_KEY			113
#   define RIGHT_KEY		100
#   define CTRL_KEY			65507
#   define ALT_KEY			65513
#   define C_KEY			99
#  endif

#  ifdef QWERTY
#   define FORWARD_KEY		119
#   define BACKWARD_KEY		115
#   define LEFT_KEY			97
#   define RIGHT_KEY		100
#   define CTRL_KEY			65507
#   define ALT_KEY			65506
#   define C_KEY			99
#  endif

# endif

# ifdef __APPLE__

#  define FORWARD_KEY		13
#  define BACKWARD_KEY		1
#  define LEFT_KEY			0
#  define RIGHT_KEY			2
#  define CTRL_KEY			256
#  define ALT_KEY			258
#  define C_KEY				8

# endif

/*
** EVENT DEFINITION
*/

# define NOEVENT_MASK			    0L
# define KEYPRESS_MASK			    1L
# define KEYRELEASE_MASK			2L
# define BUTTONPRESS_MASK			4L
# define BUTTONRELEASE_MASK		    8L
# define ENTERWINDOW_MASK			16L
# define LEAVEWINDOW_MASK			32L
# define POINTERMOTION_MASK		    64L
# define POINTERMOTIONHINT_MASK	    128L

/*
** # define Button1MotionMask		(1L<<8)
** # define Button2MotionMask		(1L<<9)
** # define Button3MotionMask		(1L<<10)
** # define Button4MotionMask		(1L<<11)
** # define Button5MotionMask		(1L<<12)
** # define ButtonMotionMask		(1L<<13)
** # define KeymapStateMask			(1L<<14)
** # define ExposureMask			(1L<<15)
** # define VisibilityChangeMask	(1L<<16)
** # define StructureNotifyMask		(1L<<17)
** # define ResizeRedirectMask		(1L<<18)
** # define SubstructureNotifyMask	(1L<<19)
** # define SubstructureRedirectMask	(1L<<20)
** # define FocusChangeMask			(1L<<21)
** # define PropertyChangeMask		(1L<<22)
** # define ColormapChangeMask		(1L<<23)
** # define OwnerGrabButtonMask		(1L<<24)
*/

# define KEY_PRESS		    2
# define KEY_RELEASE		3
# define BUTTON_PRESS		4
# define BUTTON_RELEASE	    5

/*
** # define MotionNotify	    6
** # define EnterNotify		    7
** # define LeaveNotify		    8
** # define FocusIn			    9
** # define FocusOut		    10
** # define KeymapNotify	    11
** # define Expose			    12
** # define GraphicsExpose	    13
** # define NoExpose		    14
** # define VisibilityNotify    15
** # define CreateNotify		16
** # define DestroyNotify		17
** # define UnmapNotify		    18
** # define MapNotify		    19
** # define MapRequest		    20
** # define ReparentNotify		21
** # define ConfigureNotify		22
** # define ConfigureRequest	23
** # define GravityNotify		24
** # define ResizeRequest		25
** # define CirculateNotify		26
** # define CirculateRequest	27
** # define PropertyNotify		28
** # define SelectionClear		29
** # define SelectionRequest	30
** # define SelectionNotify		31
** # define ColormapNotify		32
** # define ClientMessage		33
** # define MappingNotify		34
** # define GenericEvent		35
** # define LASTEvent		    36
*/

# define FORWARD_PRESSED 1L
# define BACKWARD_PRESSED (1L << 1)
# define RIGHT_PRESSED (1L << 2)
# define LEFT_PRESSED (1L << 3)

# define FORWARD_PRESSED_MASK 0b0001
# define BACKWARD_PRESSED_MASK 0b0010
# define RIGHT_PRESSED_MASK 0b0100
# define LEFT_PRESSED_MASK 0b1000

# define FORWARD_RELEASED_MASK 0b1110
# define BACKWARD_RELEASED_MASK 0b1101
# define RIGHT_RELEASED_MASK 0b1011
# define LEFT_RELEASED_MASK 0b0111

#endif
