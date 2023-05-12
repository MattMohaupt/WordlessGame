#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <cassert>
#include <cctype>
using namespace std;

//defines the content of the dictionary
void dictionarydefining(vector<string> &dict){
  ifstream stream;
  stream.open("dictionary.txt");
  assert(stream.fail() == false);
  dict.clear();
  string tempstring;
  while(stream >> tempstring){
    dict.push_back(tempstring);
  }
  stream.close();
}

//binarysearch
bool searchingdict(string word, vector<string> dict){
  int left = 0;
  int right = dict.size();
  int mid;
  
  while(left <= right){
    mid = left + (right - left) / 2;
    if(dict.at(mid) == word){
      return true;
    }
    else if(dict.at(mid) < word){
      left = mid + 1;
    }
    else{
      right = mid - 1;
    }
  }
  return false;
}

//defines the answer to the wordles
void quests(vector<string> &compans){
  ifstream stream;
  stream.open("wordlewords.txt");
  assert(stream.fail() == false);
  compans.clear();
  string tempstring;
  while(stream >> tempstring){
    compans.push_back(tempstring);
  }
  stream.close();
}

//to make sure user answer is valid
bool uivalidation(string ui, int game, vector<string> dict){
  bool tf;
  if(ui.length() == game){
    tf = true;
  }
  else{
    tf = false;
    cout << "Invalid word entry - please enter a word that is " << game << " characters long." << endl;
    return tf;
  }
  tf = searchingdict(ui, dict);
  if(tf == false){
    cout << "Not a playable word, please select another word." << endl;
  }
  return tf;
}

//sets the computer answer
void randomans(vector<string> answers, int game, int rando, string &answer){
  if(game == 3){
    rando = rand() % 1065;
  }
  else{
    rando = rand() % 2499 + 1065;
  }
  answer = answers.at(rando);
}

//comparing comp answer to user answer
void compared(string comp, string ans, string &temp){
  for(int i = 0; i < ans.length(); i++){
    for(int j = 0; j < comp.length(); j++){
      if(ans[i] == comp[j]){
        if(i == j){
          temp[i] = toupper(ans[i]);
          
        }
        else{
          temp[i] = ans[i];
        }
        break;
      }
      else{
        temp[i] = '*';
        continue;
      }
    }
  }
}

bool checkwin(string comp, string ans){
  for(int i = 0; i < ans.length(); i++){
    ans[i] = toupper(ans[i]);
  }
  for(int j = 0; j < comp.length(); j++){
    comp[j] = toupper(comp[j]);
  }
  //cout << ans << endl;
  //cout << comp << endl;
  if(comp == ans){
    //cout << "same";
    return true;
  }
  else{
    //cout << "no";
    return false;
  }
}

//main
int main() { 
  //intro stuff
  cout << "Program 3: Wordle Reload\nCS 141, Spring 2022, UIC\nMatthew Mohaupt Replit\n" << endl;
  cout << "The objective of this game is to guess the randomly selected word within a given number of attempts. You can select either a three or five word board.\nAt the conclusion of the game, stats will be displayed.\nIndicators will be given if characters of the user entered word are reflected in the guessed word.\n  - If the character is in the correct position, the character will display as an uppercase value.\n  - If the character is within the random word, the character will display as a lowercase value.\n  - If you enter a character that is not in the word, an asterisk '*' will display.\n" << endl;

  //declaring everything we'll need
  string Cwordle, Uwordle, tempwordle;
  int menuop, seconds, randex, gamemode, dubs, streak, streakz, avtime, guesses, totguess;
  bool loops, valid, win;
  vector<string> wordlequests;
  vector<string> dictionary;
  time_t startTime;
  srand(1);

  //initializing some of things we need
  loops = true;
  win = false;
  dictionarydefining(dictionary);
  quests(wordlequests);
  dubs = 0;
  streak = 0;
  streakz = 0;
  avtime = 0;
  

  //loop for menu
  while(loops){
    cout << "\nSelect a menu option:\n1. To play Wordle Reload 3 letter play\n2. To play Wordle Reload 5 letter play\n3. Exit the program" << endl;
    if(streakz > streak){
      streak = streakz;
    }
    cin >> menuop;
    switch(menuop){
      
      //3 letter wordle
      case 1 :
        seconds = 0;
        totguess = 4;
        gamemode = 3;
        guesses = 0;
        randomans(wordlequests, gamemode, randex, Cwordle);
        cout << "Your choice --> 1\n" << endl;
        cout << "To get started, enter your first 3 letter word.\nYou have " << totguess << " attempts to guess the random word.\nThe timer will start after your first word entry.\nTry to guess the word within 20 seconds.\n" << endl;
        startTime = time( NULL);
        //cout << Cwordle;
        while(guesses < 4){
          cout << "Please enter word -->  ";
          cin >> Uwordle;
          cout << endl;
          valid = uivalidation(Uwordle, gamemode, dictionary);
          if (valid){
            compared(Cwordle, Uwordle, tempwordle);
            for(int i = 0; i < gamemode; i++){
              cout << " [" << tempwordle[i] << "] ";
            }
            cout << "\n" << endl;
            win = checkwin(Cwordle, Uwordle);
            //cout << "test";
            if(win == true){
              seconds = difftime( time( NULL), startTime);
              cout << "Nice Work!  You guessed the correct word\n- You completed the board in: " << seconds << " seconds.\n- It took you " << guesses + 1 << "/" << totguess << " attempts.\n" << endl;
              dubs += 1;
              streakz += 1;
              avtime += seconds;
              break;
              }
            
            
          
          
          }
          if(difftime( time( NULL), startTime) > 120){
            streakz = 0;
            seconds = difftime( time( NULL), startTime);
            cout << "Your time has expired.  Try again.\n  - You are " << seconds - 20 <<" seconds over the 20 second time limit." << endl;
            cout << "the word was: " << Cwordle << endl;
            break;
          }
          guesses++;
          if(guesses >= 4){
            streakz = 0;
            cout << "Maximum amount of attempts have been reached. Try again." << endl;
            cout << "the word was: " << Cwordle << endl;
          }
        }
        break;
      
      //5 letter wordle
      case 2 :
        seconds = 0;
        totguess = 6;
        gamemode = 5;
        guesses = 0;
        randomans(wordlequests, gamemode, randex, Cwordle);
        cout << "Your choice --> 2\n" << endl;
        cout << "To get started, enter your first 5 letter word.\nYou have " << totguess << " attempts to guess the random word.\nThe timer will start after your first word entry.\nTry to guess the word within 20 seconds.\n" << endl;
        startTime = time( NULL);
        //cout << Cwordle;
        while(guesses < 6){
          cout << "Please enter word -->  ";
          cin >> Uwordle;
          cout << endl;
          valid = uivalidation(Uwordle, gamemode, dictionary);
          if (valid){
            compared(Cwordle, Uwordle, tempwordle);
            for(int i = 0; i < gamemode; i++){
              cout << " [" << tempwordle[i] << "] ";
            }
            cout << "\n" << endl;
            win = checkwin(Cwordle, Uwordle);
            //cout << "test";
            if(win == true){
              seconds = difftime( time( NULL), startTime);
              cout << "Nice Work!  You guessed the correct word\n- You completed the board in: " << seconds << " seconds.\n- It took you " << guesses + 1 << "/" << totguess << " attempts.\n" << endl;
              dubs += 1;
              streakz += 1;
              avtime += seconds;
              break;
              }
            
            
          
          
          }
          if(difftime( time( NULL), startTime) > 120){
            streakz = 0;
            seconds = difftime( time( NULL), startTime);
            cout << "Your time has expired.  Try again.\n  - You are " << seconds - 20 <<" seconds over the 20 second time limit." << endl;
            cout << "the word was: " << Cwordle << endl;
            break;
          }
          guesses++;
          if(guesses >= 6){
            streakz = 0;
            cout << "Maximum amount of attempts have been reached. Try again." << endl;
            cout << "the word was: " << Cwordle << endl;
          }
        }
        break;
      
      //exit statement
      case 3 :
       cout << "Your choice --> 3" << endl;
       loops = false;
        cout << "Overall Stats:\n  - You guessed: " << dubs << "\n  - Your longest streak is: " << streak << "\n  - Average word completion time: " << avtime/dubs << "\nExiting program" << endl;
       break; 
      
      //in case number 1,2,3 is not typed in
      default :
        cout << "Please choose and type either 1, 2, or 3." << endl;
    }
  }
  
}