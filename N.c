#include "ft_philosophers.h"

static int      ft_issign(int c)
{
        return ((char)c == '-' || (char)c == '+');
}

static int      ft_isdigit(int c)
{
        return (c >= '0' && c <= '9');
}

static int      ft_iswhitespace(int c)
{
        return ((char)c == '\t' || (char)c == '\v' || (char)c == '\f'
                || (char)c == '\r' || (char)c == '\n' || (char)c == ' ');
}

static  int     ft_checkoverflow(int res, int term, int sign)
{
        long long int   result;

        result = res;
        result = (result * 10) + term;
        result = result * sign;
        if (result > +2147483647)
                return (-1);
        else if (result < -2147483648)
                return (0);
        return (1);
}

int     ft_atoi(const char *str)
{
        int     i;
        int     res;
        int     sign;

        i = 0;
        res = 0;
        sign = 1;
        while (str[i] != '\0' && ft_iswhitespace(str[i]))
                i++;
        if (str[i] != '\0' && !ft_isdigit(str[i]))
                return (-1);
        if (str[i] != '\0' && ft_issign(str[i]))
        {
                if (str[i++] == '-')
                        sign *= -1;
        }
        while (str[i] != '\0' && ft_isdigit(str[i]))
        {
                if (ft_checkoverflow(res, (str[i] - '0'), sign) != 1)
                        return (ft_checkoverflow(res, (str[i] - '0'), sign));
                res = res * 10 + (str[i] - '0');
                i++;
        }
        return (res * sign);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:33:51 by kricky            #+#    #+#             */
/*   Updated: 2021/11/18 10:35:09 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int     ft_validation(int argc, char **argv)
{
        if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0)
                return (0);
        if (ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
                return (0);
        if (argc > 5 && ft_atoi(argv[5]) < 0)
                return (0);
        return (1);
}

int     ft_init(int argc, char **argv, t_env *env)
{
        if (!ft_validation(argc, argv))
        {
                free(env);
                return (ft_throw(ERROR_ARGS, 0));
        }
        env->n_philosophers = ft_atoi(argv[1]);
        if (!env->n_philosophers)
        {
                free(env);
                return (0);
        }
        env->die_time = ft_atoi(argv[2]);
        env->eat_time = ft_atoi(argv[3]);
        env->sleep_time = ft_atoi(argv[4]);
        if (argc < 6)
                env->eat_count = -1;
        else
                env->eat_count = ft_atoi(argv[5]);
        env->philosophers = malloc(sizeof(t_philosopher) * env->n_philosophers);
        env->forks = malloc(sizeof(t_mutex) * env->n_philosophers);
        env->print = malloc(sizeof(t_mutex));
        if (!env->forks || !env->philosophers || !env->print)
                return (ft_throw(ERROR_MALLOC, 0));
        env->start_time = ft_timestamp();
        return (1);
}

void    ft_init_philosophers(t_env *env)
{
        int     i;

        i = -1;
        pthread_mutex_init(env->print, NULL);
        while (++i < env->n_philosophers)
                pthread_mutex_init(&env->forks[i], NULL);
        i = -1;
        while (++i < env->n_philosophers)
        {
                env->philosophers[i].index = i + 1;
                env->philosophers[i].eat_time = env->eat_time;
                env->philosophers[i].sleep_time = env->sleep_time;
                env->philosophers[i].ate_last_time = 0;
                env->philosophers[i].left_fork = &env->forks[i];
                env->philosophers[i].right_fork
                        = &env->forks[(i + 1) % env->n_philosophers];
                env->philosophers[i].start_time = env->start_time;
                env->philosophers[i].print = env->print;
                env->philosophers[i].eat_counter = env->eat_count;
        }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:33:51 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 13:07:41 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void    ft_threads_destroy(t_env *env)
{
        int     i;

        i = 0;
        while (i < env->n_philosophers)
        {
                pthread_detach(env->philosophers[i].thread_id);
                pthread_mutex_destroy(env->philosophers->right_fork);
                pthread_mutex_destroy(env->philosophers->left_fork);
                i++;
        }
        i = 0;
        while (i < env->n_philosophers)
        {
                pthread_mutex_destroy(&env->forks[i]);
                i++;
        }
        pthread_mutex_destroy(env->print);
        free(env->print);
        free(env->philosophers);
        free(env->forks);
        free(env);
}

int     ft_observer(t_env *env)
{
        int     i;
        int     time;

        i = -1;
        while (++i < env->n_philosophers)
        {
                time = ft_timestamp()
                        - env->philosophers[i].start_time
                        - env->philosophers[i].ate_last_time;
                if (time > env->die_time)
                {
                        pthread_mutex_lock(env->philosophers[i].print);
                        usleep(469);
                        if (env->philosophers[i].eat_counter > 0
                                || env->philosophers[i].eat_counter == -1)
                                printf("%d %d died\n", ft_timestamp()
                                        - env->philosophers[i].start_time, i + 1);
                        return (EXIT_DEAD);
                }
        }
        return (1);
}

int     main(int argc, char **argv)
{
        t_env   *env;

        env = malloc(sizeof(t_env));
        if (!env)
                return (1);
        if (argc < 5 || argc > 6)
                return (ft_throw(ERROR_USAGE, 1));
        if (!ft_init(argc, argv, env))
                return (1);
        ft_init_philosophers(env);
        if (ft_init_threads(env) != 0)
        {
                ft_threads_destroy(env);
                return (ft_throw(ERROR_CREATE_THREAD, 1));
        }
        while (1)
        {
                if (!ft_observer(env))
                {
                        ft_threads_destroy(env);
                        return (0);
                }
        }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:33:51 by kricky            #+#    #+#             */
/*   Updated: 2021/11/18 10:35:09 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void    ft_take_forks(t_philosopher *philosopher)
{
        int     time;

        pthread_mutex_lock(philosopher->left_fork);
        time = ft_timestamp() - philosopher->start_time;
        pthread_mutex_lock(philosopher->print);
        printf("%d %d \033[0;42mhas taken a fork\033[0m\n",
                time, philosopher->index);
        pthread_mutex_unlock(philosopher->print);
        pthread_mutex_lock(philosopher->right_fork);
        time = ft_timestamp() - philosopher->start_time;
        pthread_mutex_lock(philosopher->print);
        printf("%d %d \033[0;41mhas taken a fork\033[0m\n",
                time, philosopher->index);
        pthread_mutex_unlock(philosopher->print);
}

void    ft_action_eat(t_philosopher *philosopher)
{
        philosopher->ate_last_time = ft_timestamp() - philosopher->start_time;
        pthread_mutex_lock(philosopher->print);
        printf("%d %d is eating\n", philosopher->ate_last_time,
                philosopher->index);
        pthread_mutex_unlock(philosopher->print);
        ft_sleep(philosopher->eat_time);
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);
}

void    ft_action_sleep(t_philosopher *philosopher)
{
        int     time;

        time = ft_timestamp() - philosopher->start_time;
        pthread_mutex_lock(philosopher->print);
        printf("%d %d is sleeping\n", time, philosopher->index);
        pthread_mutex_unlock(philosopher->print);
        ft_sleep(philosopher->sleep_time);
        time = ft_timestamp() - philosopher->start_time;
        pthread_mutex_lock(philosopher->print);
        printf("%d %d is thinking\n", time, philosopher->index);
        pthread_mutex_unlock(philosopher->print);
}

void    *ft_philosophy(void *ph_ptr)
{
        t_philosopher   *philosopher;

        philosopher = (t_philosopher *)ph_ptr;
        pthread_detach(philosopher->thread_id);
        while (philosopher->eat_counter != 0)
        {
                ft_take_forks(philosopher);
                ft_action_eat(philosopher);
                ft_action_sleep(philosopher);
                if (philosopher->eat_counter > 0)
                        philosopher->eat_counter--;
                if (!philosopher->eat_counter)
                        return (0);
        }
        return (0);
}

int     ft_init_threads(t_env *env)
{
        int     i;
        int     status;

        i = -1;
        status = 0;
        while (++i < env->n_philosophers)
        {
                if (i % 2 == 0)
                {
                        status |= pthread_create(&env->philosophers[i].thread_id,
                                        NULL, &ft_philosophy, &env->philosophers[i]);
                        usleep(135);
                }
        }
        i = -1;
        while (++i < env->n_philosophers)
        {
                if (i % 2 != 0)
                {
                        status |= pthread_create(&env->philosophers[i].thread_id,
                                        NULL, &ft_philosophy, &env->philosophers[i]);
                        usleep(135);
                }
        }
        return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:33:51 by kricky            #+#    #+#             */
/*   Updated: 2021/11/18 10:35:09 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int     ft_timestamp(void)
{
        struct timeval  time;
        size_t                  milliseconds;

        gettimeofday(&time, NULL);
        milliseconds = time.tv_sec * 1000;
        milliseconds += time.tv_usec / 1000;
        return ((int) milliseconds);
}

void    ft_sleep(size_t milliseconds)
{
        size_t  start_time;

        start_time = ft_timestamp();
        while (ft_timestamp() - start_time < milliseconds)
                usleep(50);
}

int     ft_throw(const char *error, int code)
{
        printf("%s: ", PROGRAM_NAME);
        printf("%s\n", error);
        return (code);
}
