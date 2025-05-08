/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 09:48:48 by juperez           #+#    #+#             */
/*   Updated: 2024/07/21 10:07:31 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

//sem_open sem_close sem_post sem_wait sem_unlink
# include <semaphore.h>

//gettimeofday
# include <sys/time.h>

//waitpid
# include <sys/wait.h>

//bool
# include <stdbool.h>

//pthread_create pthread_detach pthread_join
# include <pthread.h>

// kill
# include <signal.h>

//malloc free exit
# include <stdlib.h>

//write usleep fork
# include <unistd.h>

//limits
# include <limits.h>

//printf
# include <stdio.h>

//flags
# include <fcntl.h>

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

// DEBUG MODE
# ifndef DEBUG
#  define DEBUG 0
# endif

# define TOP_D		"┏━━━━━━━━━━━┳━━━━━━┳━━━━━━━━━━━━━━━━━━━━━┓\n"
# define MID_D		"┣━━━━━━━━━━━╋━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫\n"
# define BOT_D		"┗━━━━━━━━━━━┻━━━━━━┻━━━━━━━━━━━━━━━━━━━━━┛\n"
# define SEP		"┃"
# define TIME		"\e[94mTimestamp\e[0m"
# define ID			"\e[94mID\e[0m"
# define EVENT		"\e[94mEvent\e[0m"

// EVENTS STRINGS
# define TAKEN_FORK		"has taken a fork"
# define IS_EATING		"is eating"
# define IS_SLEEPING	"is sleeping"
# define IS_THINKING	"is thinking"
# define DIED			"died"

# define EMOJI_FORK		"🍴"
# define EMOJI_EAT		"🍝"
# define EMOJI_SLEEP	"💤"
# define EMOJI_THINK	"💭"
# define EMOJI_DEAD		"💀"

// COLORS
# define R				"\e[91m"
# define G				"\e[92m"
# define Y				"\e[93m"
# define X				"\e[0m"

// ERRORS MESSAGES
# define NAME			"philo_bonus: "
# define ERROR_ARG		"wrong arguments\n"
# define ERROR_ARG_NB	"wrong number of arguments\n"
# define ERROR_MEM		"memory allocation failed\n"
# define ERROR_SEM		"semaphore creation failed\n"
# define ERROR_FORK		"fork failed\n"
# define ERROR_TCREATE	"thread creation failed\n"
# define ERROR_TJOIN	"thread join failed\n"

// SEMAPHORES NAMES
# define SEM_STOP		"/sem_stop"
# define SEM_MSG		"/sem_msg"
# define SEM_FORKS		"/sem_forks"

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

// EVENTS ENUM
typedef enum e_event
{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_event;

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

// PARAMETERS STRUCTURE
typedef struct s_param
{
	int		amount;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		eat_limit;
	long	start_time;
	sem_t	*sem_stop;
	sem_t	*sem_msg;
	sem_t	*sem_forks;
}			t_param;

// PHILOSOPHER STRUCTURE
typedef struct s_philo
{
	pid_t		pid;
	pthread_t	status;
	int			id;
	int			eat_count;
	long		last_meal;
	t_param		*param;
}				t_philo;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// ERROR
void	ft_error(char *error, t_philo *philo, t_param *param);

// DEBUG
void	ft_debug_print_label(void);
void	ft_debug_print_event(t_param *param, int id, t_event event);

// INIT HELPER
void	ft_init(int ac, char *av[]);

// PHILO HELPER
void	ft_start(t_philo *philo, t_param *param);

// UTILS
size_t	ft_strlen(char *s);
bool	ft_strisdigit(char *s);
ssize_t	ft_atol(char *s);

// TIME UTILS
long	ft_time(void);
void	ft_usleep(long time);

// STRING UTILS
char	*ft_get_string_event(t_event event);
char	*ft_get_emoji_event(t_event event);
void	ft_msg(t_param *param, int id, t_event event);

#endif
