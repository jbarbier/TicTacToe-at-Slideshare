#include "_lib.h"
#include "_ttt.h"

int check_inputs_sizes(int ac, char **av)
{
  if (ac != 2 || _str_len(av[1]) != SIZE_TIC_TAC_TOE)
    {
      _print_error(USAGE);
      return (-1);
    }
  return (0);
}

int compute(char *str, int *cross, int *omega, int *space)
{
  int position, nb_cross, nb_omega, diff;

  position = nb_omega = nb_cross = 0;
  while (*str)
    {
      if (*str == CROSS_CHAR) { *cross += 1<<position; nb_cross++; }
      else if (*str == OMEGA_CHAR) { *omega += 1<<position; nb_omega++; }
      else if (*str == EMPTY_CHAR) *space += 1<<position;
      else
	{
	  _print_error("Unrecognized char. ");
	  _print_error(USAGE);
	  return (-1);
	}
      str++;
      position++;
    }
  diff = nb_cross - nb_omega;
  if (diff < -1 || diff > 1)
    {
      _print_error("Someone cheated and played too many times!\n");
      return (-1);
    }
  return (0);
}

int check_solutions(int cross, int omega)
{
  int i, cross_wins, omega_wins, total_wins;
  
  cross_wins = omega_wins = 0;
  for (i = 0; i < NB_SOLUTIONS; i++)
    {
      if ((cross & solutions[i]) == solutions[i]) cross_wins++;
      if ((omega & solutions[i]) == solutions[i]) omega_wins++;
    }
  total_wins = cross_wins + omega_wins;
  if (total_wins > 1)
    {
      _print_error("So many wins...\n");
      return (total_wins);
    }
  if (!total_wins)
    {
      _print_message("Nobody won...\n");
    }
  else
    {
      if (cross_wins) _print_message("Cross wins!\n");
      else _print_message("Omega wins!\n");
    }
  return (total_wins);
}

void check_future(int cross, int omega, int space)
{
  int i, cross_wins, omega_wins, total_wins;
  
  cross_wins = omega_wins = 0;
  for (i = 0; i < NB_SOLUTIONS; i++)
    {
      if (((cross | space) & solutions[i]) == solutions[i]) cross_wins++;
      if (((omega | space) & solutions[i]) == solutions[i]) omega_wins++;
    }
  if (cross_wins)
    {
      _print_message("Cross could potentially win\n");
    }
  if (omega_wins)
    {
      _print_message("Omega could potentially win\n");
    }
  if (omega_wins + cross_wins == 0)
    {
      _print_message("I see a tie in the future!\n");
    }
}

int main(int ac, char **av)
{
  int cross, omega, space;

  if (check_inputs_sizes(ac, av)) return (1);
  cross = omega = space = 0;
  if (compute(av[1], &cross, &omega, &space)) return (1);
  if (!check_solutions(cross, omega))
    {
      if (space) check_future(cross, omega, space);
      else _print_message("It's a tie\n");
    }
  return (0);
}
