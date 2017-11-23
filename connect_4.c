#include <stdlib.h>
#include <unistd.h>

void show_game(char **game_array)
{
  int counter_y;
  counter_y = 0;
  write(1, "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n", 30);
  write(1, "-----------------------------\n", 30);
  while(counter_y < 6)
    {
      write(1,"| ",2);
      write(1, &game_array[counter_y][0], 1);
      write(1," | ",3);
      write(1, &game_array[counter_y][1], 1);
      write(1," | ",3);
      write(1, &game_array[counter_y][2], 1);
      write(1," | ",3);
      write(1, &game_array[counter_y][3], 1);
      write(1," | ",3);
      write(1, &game_array[counter_y][4], 1);
      write(1," | ",3);
      write(1, &game_array[counter_y][5], 1);
      write(1," | ",3);
      write(1, &game_array[counter_y][6], 1);
      write(1," |\n",3);
      
      counter_y++;
    }
  write(1,"\n\0",2);
}

void a_toi_de_jouer(int player_id)
{
  if(player_id == 1)
    {
      write(1, "\n\n", 2);
      write(1, "Player #1's turn : \0 ", 21);
    }
  if(player_id == 2)
    {
      write(1, "\n\n", 2);
      write(1, "Player #2's turn :  \0", 21);
    }
}


void read_joueur(char **game_array, char *buf)
{

  int pos;
  int bonne_valeur;
  ssize_t bytes_read;
  char *buffle;
  
  bonne_valeur = 0;
  buffle = malloc(100 * sizeof(char));
  while(bonne_valeur == 0)
    {
      
      bytes_read = read(0, buffle, 100);
      buffle[bytes_read] = '\0';
      
      pos = buffle[0] - 49;
      
      if(bytes_read > 2)
	{
	  write(1, "\nPlease enter a valid value\n\0", 29);
	}
      else
	{
	  if(pos < 0 || pos > 6)
	    {
	      write(1, "\nPlease enter a valid value\n\0", 29);
	    }
	  else
	    {
	      if(game_array[0][pos] != '-')
		{
		  write(1, "\nPlease enter a valid value\n\0", 29);
		}
	      else
		{
		  buf[0] = buffle[0];
		  buf[1] = '\0';
		  bonne_valeur = 1;
		}
	    }
	}
    }
  free(buffle);
}

void saut_de_ligne()
{
  write(1, "\n\n\n", 3);
}

void update_grid(char **game_array, char *jou_koi, int player_id)
{
  int pos, c;
  pos = jou_koi[0]-49;
  if(player_id == 1)
    {
      c = 5;
      while(game_array[c][pos]!='-' && c >=0)
	{
	  c--;
	}
      game_array[c][pos] = 'X';
    }
  if(player_id == 2)
    {
      c = 5;
      while(game_array[c][pos]!='-' && c >=0)
	{
	  c--;
	}
      game_array[c][pos] = 'O';
    }
}


int my_check_winner(char **game_array)
{
  int i,j, nb_cases_libres;
  nb_cases_libres = 0;
  for(i=0 ; i<7 ; i++)
    {
      for(j=0 ; j<6 ; j++)
	{
	  if(game_array[j][i]=='-')
	    {
	      nb_cases_libres = nb_cases_libres + 1;
	    }
	}
    }
  if(nb_cases_libres == 0)
     {
       return -1;
     }

  for(j=0 ; j<3 ; j++)
    {
      for(i=0 ; i<4 ; i++)
	{
	  if(game_array[j][i]=='X' && game_array[j+1][i+1]=='X' &&  game_array[j+2][i+2]=='X' && game_array[j+3][i+3]=='X')
	    {
	      return 1;
	    }
	  if(game_array[j][i]=='O' && game_array[j+1][i+1]=='O' &&  game_array[j+2][i+2]=='O' && game_array[j+3][i+3]=='O')
	    {
	      return 2;
	    }
	}
    }
  for(j=0 ; j<3 ; j++)
    {
      for(i=3 ; i<7 ; i++)
	{
	  if(game_array[j][i]=='X' && game_array[j+1][i-1]=='X' &&  game_array[j+2][i-2]=='X' && game_array[j+3][i-3]=='X')
	    {
	      return 1;
	    }
	  if(game_array[j][i]=='O' && game_array[j+1][i-1]=='O' &&  game_array[j+2][i-2]=='O' && game_array[j+3][i-3]=='O')
	    {
	      return 2;
	    }      
	}
    }
  for(j=0 ; j<3 ; j++)
    {
      for(i=0 ; i<7 ; i++)
	{
	  if(game_array[j][i]=='X' && game_array[j+1][i]=='X' &&  game_array[j+2][i]=='X' && game_array[j+3][i]=='X')
	    {
	      return 1;
	    }
	  if(game_array[j][i]=='O' && game_array[j+1][i]=='O' &&  game_array[j+2][i]=='O' && game_array[j+3][i]=='O')
	    {
	      return 2;
	    }
	}
    }
  for(j=0 ; j<6 ; j++)
    {
      for(i=0 ; i<4 ; i++)
	{
	  if(game_array[j][i]=='X' && game_array[j][i+1]=='X' &&  game_array[j][i+2]=='X' && game_array[j][i+3]=='X')
	    {
	      return 1;
	    }
	  if(game_array[j][i]=='O' && game_array[j][i+1]=='O' &&  game_array[j][i+2]=='O' && game_array[j][i+3]=='O')
	    {
	      return 2;
	    }
	}
    }
  return 0;
}

int joueur_change(int joueur_ki_jou)
{
  if(joueur_ki_jou ==1)
    {
      return 2;
    }
  else
    {
      return 1;
    }
}

void initialize_grid(char **grid)
{
  grid = malloc(6*sizeof(char *));

  for(int j=0 ; j<6 ; j++)
    {
      grid[j] = malloc(7 * sizeof(char));
      for(int i=0 ; i<7 ; i++)
	{
	 grid[j][i] = '-';
	}
    }
}

char** initialized_grid()
{
  char **grid;
  
  grid = malloc(6*sizeof(char *));

  for(int j=0 ; j<6 ; j++)
    {
      grid[j] = malloc(7 * sizeof(char));
      for(int i=0 ; i<7 ; i++)
	{
	 grid[j][i] = '-';
	}
    }
  return grid;
}

void initialize(char **grid, char *jou_koi)
{
  initialize_grid(grid);
  jou_koi = malloc(2 * sizeof(char));
}
void initialize_jou_koi(char *jou_koi)
{
  jou_koi = malloc(2 * sizeof(char));
}

void message_winner(int winner)
{
  if(winner == 1)
    {
      write(1, "Congratulation Player #1, you win !\n", 36);
    }
  if(winner == 2)
    {
      write(1, "Congratulation Player #2, you win !\n", 36);
    }
  if(winner == -1)
    {
      write(1, "It's a draw !\n", 14);
    }
}

void free_grid(char **grid)
{
  for(int j=0 ; j<6 ; j++)
    {
      free(grid[j]);
    }
  
  free(grid);
}

void free_arrays(char **grid, char *jou_koi)
{
  free(jou_koi);
  free_grid(grid);
}

int main(int argc, char **argv)
{
  char **game_grid;
  int joueur_ki_jou;
  char *jou_koi;
  int winner;
  
  game_grid = initialized_grid();
  
  jou_koi = malloc(2 * sizeof(char));

  
  winner = 0;
  joueur_ki_jou = 1;

  show_game(game_grid);
  while(winner == 0)
    {
      
      a_toi_de_jouer(joueur_ki_jou);
      read_joueur(game_grid, jou_koi);
      
      saut_de_ligne();
      update_grid(game_grid, jou_koi, joueur_ki_jou);

      show_game(game_grid);
      joueur_ki_jou = joueur_change(joueur_ki_jou);
      winner = my_check_winner(game_grid);
    
    }

  message_winner(winner);

  free_arrays(game_grid, jou_koi);
  return 0;
}
