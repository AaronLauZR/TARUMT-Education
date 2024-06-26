/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javagames;

import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author andre
 */
public class Hangman {
    
    //user is given 10 attempts to guess the word --> set as constant
    final static int MAX_CHANCES = 10;
    
    //to print coloured text
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_GREEN = "\u001B[32m";
    
    
    
        Hangman(){
            Scanner scanner = new Scanner(System.in);
       Random random = new Random();
       
       //store all words to be guessed in an array
       String[] vocabulary ={"REPLAY","PROGRAMME","HAPPY","DANCE","PRETTY",
                             "HANGMAN","HUMAN","COMPUTER","INTERACT","OBJECT",
                             "ORIENTED","DEVICES","PHONES","UNCLE","AUNTY",
                             "FATHER","MOTHER","CHILDREN","MEDIUM","RECYCLE"};
       
       boolean PlayingGame = true;
       //while PlayingGame is true, execute the code below
       while(PlayingGame){
           System.out.println("\n=====================================");
           System.out.println("          Welcome to Hangman");
           System.out.println("=====================================");
           System.out.println("~This is a simple word guessing game~");
           System.out.println("=====================================");
           //use random class generate a random number within the total number of word in vacabulary array
           //then, the random number will be use to select the word to be guessed by the player
           //eg. random number generated = 3 --> Word to be guess  =  DANCE
           //.tocharArray --> converts string into character array 
           //eg. DANCE --> D,A,N,C,E
           char[] WordToGuess = vocabulary[random.nextInt(vocabulary.length)].toCharArray();
           
           //create an array to store player input,the size of the array set to MAX_CHANCES, which is 10
           //why 10? because the player has 10 attempts to guees the word
           //initially storing all '*'
           char[] playerGuess = new char[MAX_CHANCES];
           for(int i = 0; i < WordToGuess.length; i++){
               playerGuess[i] = '*';
           }
           
           //initialize the variable
           boolean wordIsGuessed = false;
           boolean validCharacter = false;
           boolean validAnotherGame = false;
           int attempt = 0;
           char character_input = ' ';
           char upper_character_input = ' ';
           
           // when the player not yet guess the full word correctly 
           // and also the attempts used by the still not more than 10
           // execute the code in this while loop
           while(wordIsGuessed == false && attempt != MAX_CHANCES){
               //print out the current attempts that the player have for every single round
               System.out.println("\nChances left: " + (MAX_CHANCES - attempt));
               
               // print out player current guesses status
               // eg --> D *  N C *, if the player suceesfully guess the leter D, N and C
               System.out.print("Current Guesses: ");
               printCurrentGuess(playerGuess);

               //execute the code in do-while until the player enter the correct input
               do{
                   try{
                        //prompt the player to enter a single a single character to guess the word
                        //accept the player's input value
                        //only the first character that the player entered will be accept
                        //eg. player input --> asdgthds
                        //the value stored is only 'a'
                        System.out.print("Enter a single character: ");
                        character_input = scanner.nextLine().charAt(0); 
                        upper_character_input = Character.toUpperCase(character_input);
   
                   // when player did not entered any input, error message is displayed    
                   }catch(IndexOutOfBoundsException e) {
                        System.out.println(ANSI_RED +  "No character input is not allowed. Please enter a character." + ANSI_RESET);
                        validCharacter = false;  
                        attempt--;
                   }
  
               }while(validCharacter);
             

               // the player input is valid, the attempt used by the player increase one
               attempt++;        
                
               //check the input is already displayed on the screen(the player guessed the correct letter previously) or not
               //so, checkRepeatedWord() method is called
               //if return true, then the error message will be displayed
               if(checkRepeatedWord(playerGuess,upper_character_input)){
                   System.out.println(ANSI_RED + "Letter has already been displayed, please enter another letter." + ANSI_RESET);
                   //with repeated input, it is not counted as one attempt, can re-enter a new letter
                   attempt--;
               }
               //if the player input a number, the error message will be displayed
               if(Character.isDigit(character_input)){
                          System.out.println(ANSI_RED + "Must be a letter!"+ ANSI_RESET);
                          //validCharacter = false;
                          //with number input, it is not counted as one attempt, can re-enter a new letter
                          attempt--;
                
               }else{
                   // if the letter guessed is correct, playerGuess array should be updated
                   // so that the current guesses shown on the screen for the next round will be always the lastest 
                   for(int i = 0; i < WordToGuess.length; i++){
                       if(WordToGuess[i] == upper_character_input){
                           playerGuess[i] = upper_character_input;
                       }
                   }
                   // if the full word is guessed suceesfully, print out the congrats message
                   // isWordGuessed() method is called to check whether the word is successfully guessed
                   // numberOfMissed() method is also called 
                   // to check the player did not guess correctly for how many time(s) before successfully guessed the word)
                   if(isWordGuessed(playerGuess)){
                       wordIsGuessed = true;
                       System.out.println(ANSI_GREEN + "Congratulation, you guessed the word correctly!" + ANSI_RESET);
                       System.out.println(ANSI_GREEN + "Number of misses: " + numberOfMissed(WordToGuess, attempt)+ ANSI_RESET);
                   }
               }
           }
           // if the word is not successfully guessed by the player
           // display the answer by calling wordSelected() method 
           // and also display a motivating message.
           if(!wordIsGuessed){
               wordSelected(WordToGuess);
               System.out.println(ANSI_YELLOW + "Sorry, you ran out of guesses. You may play again~" + ANSI_RESET );
           }
           
           // asks the player whether to continue for another word
           // if the player entered n or N, game over
           // if the player entered other characters, continue for another game
           // exception handling
           do{
               try {
                    System.out.print("\nDo you want to play for another round? (Y -> Yes / N -> No) :" );;
                    char anotherGame = scanner.nextLine().charAt(0);
                    
                    if(anotherGame == 'Y'|| anotherGame == 'y') {
                        validAnotherGame = true;
                        PlayingGame = true;
                        break;
                    }
                    if(anotherGame == 'N' || anotherGame == 'n'){
                        validAnotherGame = true;
                        PlayingGame = false;
                        break;
                    }
                    else{
                   
                        System.out.println(ANSI_RED + "Invalid input. Only Y or N is allowed." + ANSI_RESET);
                        validAnotherGame = false;
                }
               // when player did not entered any input, error message is displayed 
               }catch (IndexOutOfBoundsException e) {
                    System.out.println(ANSI_RED +  "No character input is not allowed. Please Y or N." + ANSI_RESET);
                    validAnotherGame = false;
               }          
           }while(!validAnotherGame);
 
       }
       // print out a message to tell the player that the game is over
       System.out.println("\n=====================================");
       System.out.println("              Game Over!");
       System.out.println("=====================================");
       System.out.println("        ~Thank you for playing~");
       System.out.println("=====================================");
    }
    
    
    // output player current guesses status
    // eg. D *  N C *
    public static void printCurrentGuess(char[] array){
        for(int i = 0; i < array.length; i++){
            System.out.print(array[i] + " ");
        }
        System.out.println();
        
    }
    
    //check whether the player guessed the word correctly or not
    public static boolean isWordGuessed(char[] array){
        for(int i = 0; i < array.length; i++){
            if(array[i] == '*') return false;
        }
        return true;
    }
    
    //check the letter entered by the user 
    //is same as the letter already displayed or not 
    public static boolean checkRepeatedWord (char[] array, char input){
        for(int i = 0; i < array.length; i++){
            if(array[i] == input) return true;
        }
        return false;
    }
    
    
    //print out random word selected
    public static void wordSelected (char[] randomWord){
        System.out.print("\nWord To Guess: ");
                for(int i = 0; i < randomWord.length; i++){
                    System.out.print(randomWord[i]);
                }
                System.out.println();
    }
    
    //calculate number of incorrect letter that entered by the player
    public static int numberOfMissed (char[] randomWord, int tries){
        int count = 0;
        int no_of_missed = 0;
        
        for(int i = 0; i < randomWord.length; i++){
              for(int j = 0; j < i; j++){
                  if(randomWord[i] ==  randomWord[j]){
                      count++;
                  }
              }
        }
        no_of_missed = (tries + count) - randomWord.length;
        
        return no_of_missed;
    }
       
}
    

