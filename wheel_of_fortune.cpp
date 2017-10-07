/************************
 * Program: assign4.cpp
 * Author: Kaitlin Hill
 * Date: 2/19/17
 * Description: A fun, family-friendly game of wheel of Fortune that you can player with 1-3 people.
 * Input: The number of players, amount of rounds, the secret message, and the letter they guess. 
 * Output: The puzzle, the if the letter was found, what they spun of the wheel, how much money the user won/lost during the round, the game winner, and grand winner. 
 *************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int start_game(int &);
void secret_message_player(string &, string &);
void create_puzzle(string &, string &);
int player_choice(int &, int &, int &, string &, string, int &, int &);
void spin_wheel_function(int &, string, string &, int &, int &, int &, int &);
void guess_letter(string, string &, int &, int &, int &, int &, int &);
void check_letter(char, char, string, string &, int &, int &, int &, int &, int &);
void check_buy_vowel_money(int &, string &, string, int &, int &, int &, int &);
void print_finding_non_vowel(int &, int &, int &, int &, int &);
void print_finding_vowel(int &, int &, int &, int &);
int player_round_total(int &, int &, int &);
int solve_the_puzzle(string &);
int who_turn(int, int &);
int change_back_player(int, int &);
void to_end(int, int, int);

/*******************
 * Function: int start_game
 * Description: This is the first menu that the user sees when they start the game. It asks inititial info like number of player and number of rounds. 
 * Parameters: num_of_players
 * Pre-conditions: none
 * Post-conditions: num_of_players must be between 1-3 and rounds_for_winning must be a positive int.
 * Return: Returns rounds_for_winning to main. 
 * ***************/ 
int start_game(int &num_of_players){
   int rounds_for_winning;

   cout<< "Welcome to Wheel of Fortune!"<< endl;
   cout<< "Enter num of players (1-3)"<<endl;
   cin >> num_of_players;
   cin.ignore();
   cout<< "How many rounds do you want to play?"<<endl;
   cin >> rounds_for_winning;
   cin.ignore();
   return rounds_for_winning;
}

/********************
 * Function: secret_message_player
 * Description: Takes in the secret message from the user and clears the screen.
 * Parameters: secret_message, puzzle
 * Pre-conditions: secret_message and puzzle must be empty strings.
 * Post-conditions: secret_message must hold some string of letters.
 * Return: none
 * ****************/
void secret_message_player(string &secret_message, string &puzzle){
   cout<< "What do you want the secret message to be?"<<endl;
   getline(cin, secret_message);
   for (int i = 0; i<secret_message.length(); i++){
      secret_message.at(i) = tolower(secret_message.at(i));
   }
   system("clear");
   create_puzzle(secret_message, puzzle);
}

/*********************
 * Function: create_puzzle
 * Description: uses secret_message and turns it into a puzzle that is then printed to the screen.
 * Parameters: secret_message, puzzle
 * Pre-conditions: secret_message must hold a string of letters.
 * Post_conditons: puzzle holds a string of dashes and spaces.
 * Return: none
 * ****************/
void create_puzzle(string &secret_message, string &puzzle){
   for (int i=0; i < secret_message.length(); i++ ){
      if (secret_message.at(i) == ' ')
	 puzzle += "  ";
      else
	 puzzle +=  "_ ";
   }
   cout<< puzzle <<endl;
}

/********************
 * Function: player_choice
 * Description: Takes in if the user wants to spin, buy a vowel, or solve and calls the appropriate funcion.
 * Parameters: player, num_on_wheel, round_player, puzzle, secret_message, amount, x
 * Pre-conditions: secret_message must hold a string of letters, puzzle must hold a string of dashes and spaces
 * Post-conditions: none
 * Return: j which tells main if the puzzle has been solved or not.
 * ***************/
int player_choice(int &player, int &num_on_wheel, int &round_player, string &puzzle, string secret_message, int &amount, int &x){
   int player_choice;
   int j;
   cout<<"Player "<< player<< ": Would you like to spin (1), buy a vowel (2), or solve (3)"<<endl;
   cin>> player_choice;
   cin.ignore();
   if (player_choice == 1){
      spin_wheel_function(num_on_wheel, secret_message,puzzle, amount, x, player, round_player);
      j = 0;
   }
   else if(player_choice == 2){
      check_buy_vowel_money(round_player, puzzle, secret_message, amount, x, num_on_wheel, player);
      j = 0;
   }
   else if(player_choice == 3){
      j = solve_the_puzzle(secret_message);
   }
   return j;
}

/********************
 * Function: spin_wheel
 * Description: "spins the wheel" and tells user if they landed on a number, lose a turn, or bankrupt.
 * Parameters: num_on_wheel, secret_message, puzzle, amount, x, player, round_player
 * Pre-conditions: secret_message must hold a string of letters, puzzle must hold a string of underscores and spaces
 * Post_conditions: none
 * Return: none
 * *****************/
void spin_wheel_function(int &num_on_wheel, string secret_message, string &puzzle, int &amount, int &x, int &player, int &round_player){
   srand(time(NULL));
   num_on_wheel = rand() % 22;
   if (num_on_wheel > 0 && num_on_wheel < 21){
      cout << "You landed on: "<< num_on_wheel <<endl;
      guess_letter(secret_message, puzzle, amount, x, num_on_wheel, player, round_player);
   }
   else if (num_on_wheel == 21){
      cout << "Sorry, lose a turn"<< endl;
   }
   else if (num_on_wheel == 0){
      cout << "Sorry, bankrupt" <<endl;
      round_player = 0;
      player_round_total(player, round_player, amount);
   }
}

/**********************
 * Function: guess_letter
 * Description: Takes in user input for the letter they are guessing and it it's capital, it gets turned into a lowercase.
 * Parameters: secret_message, puzzle, amount, x, num_on_wheel, player, round_player
 * Pre-conditions: none
 * Post-conditions: either user_char or new_user_char is a lowercase letter
 * Return: none
 * *******************/
void guess_letter(string secret_message, string &puzzle, int &amount, int &x, int &num_on_wheel, int &player, int &round_player){
   char user_char;
   char new_user_char;
   
   cout<< "Enter a letter: "<<endl;
   cin >> user_char;
   cin.ignore();
   if (user_char > 64 || user_char < 91){
      new_user_char = user_char + 32;
   }
   check_letter(user_char, new_user_char, secret_message, puzzle, amount, x, num_on_wheel, player, round_player);
}

/************************
 * Function: check_letter
 * Description: Checks to see if the letter the user guessed is in the puzzle.
 * Parameters: user_char, new_user_char, secret_message, puzzle, amount, x, num_on_wheel, player, round_player
 * Pre-conditions: user_char and new_user_char must be letters, secret_message must be a string that holds letter, puzzle is a string that holds underscores and spaces.
 * Post-conditions: puzzle may hold underscore, spaces and letters
 * Return: none
 * **********************/
void check_letter(char user_char, char new_user_char, string secret_message, string &puzzle, int &amount, int &x, int &num_on_wheel, int &player, int &round_player){ 
   x = 0;
   for (int i = 0; i < puzzle.length(); i+=2){
      if (user_char == secret_message.at(i/2) || new_user_char == secret_message.at(i/2)){
         puzzle.at(i) = user_char;
	 x += 1;
      }
   }
   cout<< puzzle<<endl;
   if ((user_char == 97 || user_char == 101 || user_char == 105 || user_char == 111 || user_char == 117) ||(new_user_char == 97 || new_user_char == 101 || new_user_char == 105 ||
	 new_user_char == 111 || new_user_char == 117)){
      print_finding_vowel(amount, x, player, round_player);
   }
   else{
      print_finding_non_vowel(amount, x, num_on_wheel, player, round_player);
   }
}

/************************
 * Function: print_finding_non_vowel
 * Description: Prints out how many time the user's non-vowel was found and the amount of money the user earned.
 * Parameters: amount, x, num_on_wheel, player, round_player
 * Pre-conditions: x must hold an int, num_on_wheel must hlod an int
 * Post-conditions: amount will hold an int
 * Return: none
 * ***********************/
void print_finding_non_vowel(int &amount, int &x, int &num_on_wheel, int &player, int &round_player){
   amount = x*num_on_wheel;
   cout<<"You found the letter "<< x << " times"<<endl;
   cout<<"You earned $"<< amount <<endl;
   x = 0;
   player_round_total(player, round_player, amount);
}

/*********************
 * Function: print_finding_vowel
 * Description: Prints out how many times the user's vowel was found and the amount of money it costs.
 * Parameters: amount, x, player, round_player
 * Pre-conditions: x must be a positive int
 * Post-conditions: none
 * Return: none
 * *******************/
void print_finding_vowel(int &amount, int &x, int &player, int &round_player){
   amount = -10;
   cout<< "You found the letter "<< x << " times"<<endl;
   cout<< "You lost $10"<<endl;
   x = 0;
   player_round_total(player, round_player, amount);
}

/***********************
 * Function: check_buy_vowel
 * Description: checks to see if user has enough money to buy a vowel
 * Parameters: round_player, puzzle, secret_message, amount, x, num_on_wheel, player
 * Pre-conditions: round_player must be a positive int or zero
 * Post-conditions: none
 * Return: none
 * *******************/
void check_buy_vowel_money(int &round_player, string &puzzle, string secret_message, int &amount, int &x, int &num_on_wheel, int &player){
   if (round_player < 10){
      cout<<"Sorry, you can't buy a vowel"<<endl;
   }
   else if (round_player >= 10){
      guess_letter(secret_message, puzzle, amount, x, num_on_wheel, player, round_player);
   }
}

/***************************
 * Function: player_round_total
 * Description: adds the round total of each player
 * Parameters: player, round_player, amount
 * Pre-conditions: player must equal 1, 2, or 3
 * Post-conditions: round_player must be a positive int
 * Return: round_player or the amount the player has earned for the round
 * *************************/
int player_round_total(int &player, int &round_player, int &amount){
   if (player == 1){
      round_player += amount;
      cout<< "Player 1 round total: "<< round_player << endl;
      return round_player;
   }
   else if (player == 2){
      round_player += amount;
      cout<< "Player 2 round total: "<< round_player << endl;
      return round_player;
   }
   else if (player == 3 ){
      round_player += amount;
      cout << "Player 3 round total: "<< round_player <<endl;
      return round_player;
   }
}

/***********************
 * Function: solve_the_puzzle
 * Description: takes in what the user thinks the puzzle is and tells them if they guessed it correctly
 * Parameters: secret_message
 * Pre-conditions: secret_message must be a string that contains letters
 * Post-conditions: none
 * Return: j or if the user got it right and the round is over or if they got it wrong and it should move on to the next player
 * **********************/
int solve_the_puzzle(string &secret_message){
   string user_guess_solve;
   int j;
   cout<< "Guess the puzzle: "<<endl;
   getline(cin, user_guess_solve);
   for (int i = 0; i< user_guess_solve.length(); i++){
      user_guess_solve.at(i) = tolower(user_guess_solve.at(i));
   }
   if (user_guess_solve == secret_message){
      cout<< "Congraduations! You guessed it!"<<endl;
      j = 1;
   }
   else if(user_guess_solve != secret_message){
      cout<< "Sorry, that's not right."<<endl;
      j = 0;
   }
   return j;
}

/*************************************
 * Function: who_turn
 * Description: changes the player
 * Parameters: num_of_players, player
 * Pre-conditions: num_of_players must be 1,2, or 3 and player must be 1, 2, or 3
 * Post-conditions: player will be 1, 2, or 3
 * Return: player or who's turn it is
 * ***********************************/
int who_turn(int num_of_players, int &player){
   if (num_of_players == 1){
      player = 1;
   }
   else if (num_of_players == 2){
      if (player == 1)
	 player = 2;
      else if (player ==2)
	 player = 1;
   }
   else if (num_of_players == 3){
      if (player == 1)
	 player = 2;
      else if (player == 2)
	 player = 3;
      else if (player == 3)
	 player = 1;
   }
   return player;
}
/*************************************
 * Function: change_back_player
 * Description: changes the player back to who actually solved the puzzle after the game
 * Parameters: num_of_plyaers, player
 * Pre-conditions: num_of_players and player must be 1, 2, or 3 
 * Post-conditions: player will be 1, 2, or 3
 * Return: player or who actually won the round
 * *************************************/
int change_back_player(int num_of_players, int &player){
   if (num_of_players == 1){
      player = 1;
   }
   else if (num_of_players == 2){
      if (player == 1)
	 player = 2;
      else if (player ==2)
	 player = 1;
   }
   else if (num_of_players == 3){
      if (player == 1)
	 player = 3;
      else if (player == 2)
	 player = 1;
      else if (player == 3)
	 player = 2;
   }
   return player; 
}

/***********************************************
 * Function: to_end
 * Description: figures out who won the entire game by having the most money
 * Parameters: game_player_1, game_player_2, game_player_3
 * Pre-conditions: game_player1/2/3 must be positive ints or zero
 * Post-conditions: winner is 1/2/3 and big_winner is a positive int or zero
 * Return: none
 * *********************************************/
void to_end(int game_player_1, int game_player_2, int game_player_3){
   int big_winner;
   int winner;
   if ((game_player_1 == game_player_2) &&(game_player_1 == game_player_3))
      cout <<"You all tied!"<<endl;
   else{
      if(game_player_1 > game_player_2){
	 big_winner = game_player_1;
	 winner = 1;
      }
      else{
	 big_winner = game_player_2;
	 winner = 2;
      } 
      if(big_winner > game_player_3){
	 big_winner = big_winner;
      }
      else{
	 big_winner = game_player_3;
	 winner = 3;
      }
     cout<< "CONGRADULATIONS player "<< winner << "! You won the game!!!"<< " You earned: "<< "$"<< big_winner <<endl;
   }
}

/*********************************
 * Function: main
 * Description: runs program
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 * Return: 0
 * ****************************/
int main(){
   int rounds_for_winning;
   int j = 0;
   int num_of_players;
   string puzzle;
   string secret_message;
   int num_on_wheel;
   char user_char;
   char new_user_char;
   int player = 1;
   int amount;
   int x = 0;
   int round_player_1 = 0;
   int round_player_2 = 0;
   int round_player_3 = 0;
   int game_player_1 = 0;
   int game_player_2 = 0;
   int game_player_3 = 0;
   
   rounds_for_winning = start_game(num_of_players);
   for (int i = 0; i < rounds_for_winning; i++){
      puzzle = "";
      secret_message = "";
      secret_message_player(secret_message, puzzle);
      j = 0;
      player = 1;
      round_player_1 = 0;
      round_player_2 = 0;
      round_player_3 = 0;
      while (j == 0){
	 if(player == 1){
            j = player_choice(player, num_on_wheel, round_player_1, puzzle, secret_message, amount, x);
	 }
	 else if(player == 2){
	    j = player_choice(player, num_on_wheel, round_player_2, puzzle, secret_message, amount, x);
	 }
	 else if(player == 3){
	    j = player_choice(player, num_on_wheel, round_player_3, puzzle, secret_message, amount, x);
	 }
	 player = who_turn(num_of_players, player);
      }
      amount = 0;
      player = change_back_player(num_of_players, player);
      if (player == 1){
         game_player_1 += (player_round_total(player, round_player_1, amount));
      }
      else if (player == 2){
         game_player_2 += player_round_total(player, round_player_2, amount);
      }
      else if (player == 3){
         game_player_3 += player_round_total(player, round_player_3, amount);
      }
      cout<< "Player 1 made: "<< game_player_1 << " amount during the game"<<endl;
      cout<< "Player 2 made: "<< game_player_2 << " amount during the game"<<endl;
      cout<< "Player 3 made: "<< game_player_3 << " amount during the game"<<endl;
   }
   to_end(game_player_1, game_player_2, game_player_3);
   return 0;
}
