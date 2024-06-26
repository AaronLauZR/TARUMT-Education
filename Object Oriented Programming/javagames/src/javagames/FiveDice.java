/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javagames;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;
import java.util.InputMismatchException;

/**
 *
 * @author andre
 */
public class FiveDice {

    /**
     * @param args the command line arguments
     */
    FiveDice(){
        //Random number
        Scanner scan = new Scanner(System.in);
        Random random = new Random();
        
        //Initilize Game Round & Dice (Fixed)
        final int round = 10;
        final int dice = 5;
       
        //Initilize Player and Computer's Score
        int playerScore = 0;
        int computerScore = 0;

        //Initilize Playing variable
        int playing = 0;
        
        //Print Game Rule
        printGameRule();
        
        //If the player did not choose to exit, each round will continue to be looped (EXIT => 2)
        while(playing != 2) {

            //Initilize Player
            int[][] player_fiveDice = new int[round][dice];
            int[] player_numberOfEachDice = new int[6];
            int[] player_numberOfKind = new int[4];
            int[] player_sumOfKind = new int[4];
            //Initilize Computer
            int[][] computer_fiveDice = new int[round][dice];
            int[] computer_numberOfEachDice = new int[6];
            int[] computer_numberOfKind = new int[4];
            int[] computer_sumOfKind = new int[4];
            int confirmRoll = 0; //Reset the number of time that player roll the dice in each new game
            int roll = 0; //Reset the counter in each new game
            
            //Reset the player score and computer score for each new game
            playerScore = 0;
            computerScore = 0;
            
            //Generate random Player and Computer's Dice for 10 rounds
            generateRandomDice(round, dice, player_fiveDice, computer_fiveDice, random);
            
            int rollInput = 0;
            
            //Loop for 10 rounds in 1 game
            //If the roll atempt is more than 10 and the player choose to exit, the do while loop will stopped
            do {
                //Initilize validation for rolling dice
                boolean rollVerifyErr = true;
                rollInput = 0;
                
                //Verify the user input whether to proceed rolling the dice
                rollInput = checkRollVerify(rollVerifyErr, rollInput, roll);
                
                //If the player choose to roll the dice (ROLL => 1, EXIT => 2)
                if (rollInput == 1) {

                    //Display the Player five dice
                    System.out.println("Player: " + Arrays.toString(player_fiveDice[roll]));
                    //Calculate the number of each face dice from the player five dice
                    player_numberOfEachDice = calculateNumberOfEachFaceDice(dice, roll, player_fiveDice);
                    //Calculate the frequency number of two, three, four and five of kind from player
                    player_numberOfKind = calculateFrequencyKindOfDice(player_numberOfEachDice);
                    //Calculate the sum of two, three, four and five of kind from player
                    player_sumOfKind = calculateSumKindOfDice(player_numberOfEachDice);

                    //Display the Player five dice
                    System.out.println("Computer: " + Arrays.toString(computer_fiveDice[roll]));
                    //Calculate the number of each face dice from the computer five dice
                    computer_numberOfEachDice = calculateNumberOfEachFaceDice(dice, roll, computer_fiveDice);
                    //Calculate the frequency number of two, three, four and five of kind from computer
                    computer_numberOfKind = calculateFrequencyKindOfDice(computer_numberOfEachDice);
                    //Calculate the sum of two, three, four and five of kind from computer
                    computer_sumOfKind = calculateSumKindOfDice(computer_numberOfEachDice);

                    //Result Status in each round
                    int resultStatus = checkGameResult(player_numberOfKind, player_sumOfKind, computer_numberOfKind, computer_sumOfKind);

                    //Check Result Status (WIN => 1, LOSE => 0, TIE => 2)
                    System.out.print("Result: ");
                    if (resultStatus == 1) {
                        playerScore++;
                        System.out.println("PLAYER WIN!");
                    }else if (resultStatus == 0) {
                        computerScore++;
                        System.out.println("COMPUTER WIN!");
                    }else{
                        System.out.println("TIE!");
                    } 

                    roll++; //After the player roll the dice, the roll will be incremented by one which considered as one attempt that is used
                    System.out.println("");
                }

            }while(roll < round && rollInput != 2);
                
            //Print Game Result
            if (rollInput == 1) {
                printGameResult(playerScore, computerScore, player_fiveDice, computer_fiveDice);
            }else{
                System.out.println("Game Over.\n");
            }
            //Ask player to play new 10 round of five dice game, 
            //Store the input option into Playing variable in order to proceed whether to start the new game
            playing = newGame();
        }
        //If the player choose to exit the game (PLAY => 1, EXIT => 2)
        if (playing == 2) {
            System.out.println("Game Over.");
            System.out.println("Thank for playing!!!");
        }

    }
        
        
    
    
    //Print the game rule
    public static void printGameRule() {
        System.out.println("\nWELCOME TO FIVE DICE GAME\n");
        System.out.println("=============================== Five Dice Rule ===============================");
        System.out.println("You have 10 rounds to throws five dice.\n"
                + "Any higher combination beats a lower one. For example: \n"
                + "1) Five of a kind beats four of a kind\n"
                + "2) Four of a kind beats three of a kind\n"
                + "3) Three of a kind beats two of a kind\n"
                + "4) If there is the same kind, the greater value beats the smaller value.\n"
                + "*==============================================================================\n");
    }
    
    //Generate the random number of dice from 1 to 6 value into the five dice for player and computer
    public static void generateRandomDice(int round, int dice, int[][] playerDice, int[][] computerDice, Random random) {
        for (int i = 0; i < round; i++) {
            for (int j = 0; j < dice; j++) {
                playerDice[i][j] = random.nextInt(6) + 1;
                computerDice[i][j] = random.nextInt(6) + 1;
            }
        }
    }
    
    //Check and verify the user input whether it is roll or exit
    public static int checkRollVerify(boolean rollVerifyErr, int rollInput, int roll) {
        Scanner scan = new Scanner(System.in);
        
        while(rollVerifyErr) {
            try{
                System.out.println("=================== Round " + (roll + 1) + " ===================");
                System.out.println("[1] Roll  [2] Exit");
                System.out.print("Input: ");
                rollInput = scan.nextInt();

                if (rollInput == 1 || rollInput == 2) {
                    rollVerifyErr = false;
                }else{
                    System.out.println("Enter either 1 or 2 only. Please try again!\n");
                    rollVerifyErr = true;
                }

            }catch(InputMismatchException e){
                System.out.println("Enter Integer only. Please try again!\n");
                scan.next();
            }
        }
        return rollInput;
    }
    
    //Calculate the number of each face dice(1 dot, 2 dots, 3 dots, 4 dots, 5 dots, 6 dots) from player and computer's five dice
    public static int[] calculateNumberOfEachFaceDice(int dice, int counter, int[][] fiveDice) {
        int numberOfEachDice[] = new int[6];
        
        for (int i = 0; i < dice; i++) {
            if (fiveDice[counter][i] == 1) {
                numberOfEachDice[0]++;
            }
            else if (fiveDice[counter][i] == 2) {
                numberOfEachDice[1]++;
            }
            else if (fiveDice[counter][i] == 3) {
                numberOfEachDice[2]++;
            }
            else if (fiveDice[counter][i] == 4) {
                numberOfEachDice[3]++;
            }
            else if (fiveDice[counter][i] == 5) {
                numberOfEachDice[4]++;
            }
            else {
                numberOfEachDice[5]++;
            }
        }
        return numberOfEachDice;
    }
    
    //Store frequency of two, three, four and five kind of dice into an array => [2, 3, 4, 5]
    public static int[] calculateFrequencyKindOfDice(int[] numberOfEachDice) {
        int frequencyKind[] = new int[4];
        
        for (int i = 0; i < numberOfEachDice.length; i++) {
            if (numberOfEachDice[i] == 2) {
                 frequencyKind[0]++;
            }
            else if (numberOfEachDice[i] == 3) {
                 frequencyKind[1]++;
            }
            else if (numberOfEachDice[i] == 4) {
                 frequencyKind[2]++;
            }
            else if (numberOfEachDice[i] == 5) {
                 frequencyKind[3]++;
            }
        }
        return frequencyKind;
    }
    
    //Store sum of two, three, four and five kind of dice into an array => [2, 3, 4, 5]
    public static int[] calculateSumKindOfDice(int[] numberOfEachDice) {
        int SumKind[] = new int[4];
        
        for (int i = 0; i < numberOfEachDice.length; i++) {
            if (numberOfEachDice[i] == 2) {
                 SumKind[0] += i + 1;
            }
            else if (numberOfEachDice[i] == 3) {
                 SumKind[1] += i + 1;
            }
            else if (numberOfEachDice[i] == 4) {
                 SumKind[2] += i + 1;
            }
            else if (numberOfEachDice[i] == 5) {
                 SumKind[3] += i + 1;
            }
        }
        return SumKind;
    }
    
    //Compare the frequency number and sum of two, three, four and five kind dice from player and computer
    //If player and computer meet different number of kind dice, then it will proceed to check which one has greater number of kind dice
    //If the player and computer meet different sum of kind dice, then it will proceed to check which one has greater sum of kind dice
    public static int checkGameResult(int[] player_numberOfKind, int[] player_sumOfKind, int[] 
            computer_numberOfKind, int[] computer_sumOfKind) {
        
        int gameResult = 0; //Game Result (WIN = 1), (LOSE = 0), (TIE = 2)
        int counter = 0;
        boolean tie = true;
        
        do {
            if (player_numberOfKind[counter] != computer_numberOfKind[counter]) {
                if (player_numberOfKind[counter] > computer_numberOfKind[counter]) {
                    gameResult = 1;
                    tie = false;
                }else{
                    gameResult = 0;
                    tie = false;
                }
            }else if (player_sumOfKind[counter] != computer_sumOfKind[counter]) {
                if (player_sumOfKind[counter] > computer_sumOfKind[counter]) {
                    gameResult = 1;
                    tie = false;
                }else{
                    gameResult = 0;
                    tie = false;
                }
            } 
            counter++;
            
        } while (counter < player_numberOfKind.length);
        
        if (tie) {
            gameResult = 2;
        }

        //Clear data for number and sum of kind dice in order to reuse it in each round
        player_numberOfKind = null; player_sumOfKind = null; computer_numberOfKind = null; computer_sumOfKind = null;
        tie = true;
        counter = 0;

        return gameResult;
    }
    
    //Print the game result of the player and computer's score
    public static void printGameResult(int playerScore, int computerScore, int[][] player_fiveDice, int[][] computer_fiveDice) {
        int tieScore = 10 - (playerScore + computerScore);
        
        //Final Result
        System.out.println("=================================== Result ===================================");
        System.out.format("%-10s%-20s%-15s\n", "Round", "Player", "Computer");
        for (int i = 0; i < 10; i++) {           
            System.out.format("%-10s%-20s%-15s\n", (i + 1), Arrays.toString(player_fiveDice[i]), Arrays.toString(computer_fiveDice[i]));
        }
        System.out.println("==============================================================================");
        System.out.println("Number of times that player won: " + playerScore);
        System.out.println("Number of times that computer won: " + computerScore);
        System.out.println("Number of times that is tie game: " + tieScore);
        
        System.out.print("Final Result: ");
        if (playerScore > computerScore) {
            System.out.println("PLAYER WIN!");
        }else if (playerScore < computerScore) {
            System.out.println("COMPUTER WIN!");
        }else{
            System.out.println("TIE!");
        }
        System.out.println("==============================================================================");
        System.out.println("Game Over.\n");

    }
    
    //Check and verify the player's input whether it is play new round or exit the game
    public static int newGame() {
        Scanner scan = new Scanner(System.in);
        boolean newGameVerifyErr = true;
        int newGameInput = 0;

        while(newGameVerifyErr) {
            try{
                System.out.println("=============== Play new round? ===============");
                System.out.println("[1] Play  [2] Exit");
                System.out.print("Input: ");
                newGameInput = scan.nextInt();

                if (newGameInput == 1 || newGameInput == 2) {
                    newGameVerifyErr = false;
                }else{
                    System.out.println("Enter either 1 or 2 only. Please try again!\n");
                    newGameVerifyErr = true;
                }

            }catch(InputMismatchException e){
                System.out.println("Enter Integer only. Please try again!\n");
                scan.next();
            }
        }
        System.out.println("");
        
        return newGameInput;
    }
    
}
