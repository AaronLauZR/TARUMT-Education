/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javagames;

import java.util.Random;
import javax.swing.JOptionPane; 

/**
 *
 * @author andre
 */
public class ScissorsRockPaper {

    ScissorsRockPaper(){
         //Display start menu.
         StartMenu();
         double finalSelection = 0.0;
         
         do {
             String[] playerList = new String[10];
             String[] comList = new String[10];
             int draw = 0, win = 0, lose = 0;            
             boolean finalerrorInput = true;
         
             //Loop for 10 rounds.
             for (int i = 1; i < 11; i++) {
                 System.out.println("[Round " + i + "]");
         
                 boolean errorInput = true;
                 double userSelection = 3.0;
             
                 //Prompt and get player selection.
                 do {
                     do {
                         try {
                             String userinput = JOptionPane.showInputDialog(null, "(0)Scissors   (1)Rock   (2)Paper",
                                     "Round " + i, JOptionPane.QUESTION_MESSAGE);
                             if (userinput == null) {
                                 System.out.println("\n------------- Game Over -------------");
                                //  System.exit(0);
                                return;
                                
                             }
                             userSelection = Double.parseDouble(userinput);
                             errorInput = false;
                         }
                         catch (Exception e) {        
                             System.out.println("Invalid input! Please enter available number.");
                         }
                     } while (errorInput);
 
                     PlayerTurn(userSelection);
                 } while (userSelection != 0 && userSelection != 1 && userSelection != 2);
                 
                 //Store player selection into array.
                 playerList[i-1] = PlayerTurn(userSelection);
                 String playerChoice = playerList[i-1];
                 System.out.println("Player Choose: " + playerChoice);
         
                 //Get and store random computer selection into array.
                 comList [i-1] = ComputerTurn();
                 String computerChoice = comList[i-1];
                 System.out.println("Computer Choose: " + computerChoice);
         
                 //Compare player and computer selection, calculate the result. 
                 if (playerChoice.equals(computerChoice)) {
                    System.out.println("Result: Draw\n");
                    JOptionPane.showMessageDialog(null, "Draw!", "Round " + i + " Result", JOptionPane.WARNING_MESSAGE);
                    draw++;
                }
                else if ("Scissors".equals(playerChoice) && "Rock".equals(computerChoice)) {
                    System.out.println("Result: You Lose\n");
                    JOptionPane.showMessageDialog(null, "You Lose!", "Round " + i + " Result", JOptionPane.ERROR_MESSAGE);
                    lose++;
                }
                else if ("Scissors".equals(playerChoice) && "Paper".equals(computerChoice)) {
                    System.out.println("Result: You Win\n");
                    JOptionPane.showMessageDialog(null, "You Win!", "Round " + i + " Result", JOptionPane.INFORMATION_MESSAGE);
                    win++;
                }
                else if ("Rock".equals(playerChoice) && "Paper".equals(computerChoice)) {
                    System.out.println("Result: You Lose\n");
                    JOptionPane.showMessageDialog(null, "You Lose!", "Round " + i + " Result", JOptionPane.ERROR_MESSAGE);
                    lose++;
                }
                else if ("Rock".equals(playerChoice) && "Scissors".equals(computerChoice)) {
                    System.out.println("Result: You Win\n");
                    JOptionPane.showMessageDialog(null, "You Win!", "Round " + i + " Result", JOptionPane.INFORMATION_MESSAGE);
                    win++;
                }
                else if ("Paper".equals(playerChoice) && "Rock".equals(computerChoice)) {
                    System.out.println("Result: You Win\n");
                    JOptionPane.showMessageDialog(null, "You Win!", "Round " + i + " Result", JOptionPane.INFORMATION_MESSAGE);
                    win++;
                }
                else if ("Paper".equals(playerChoice) && "Scissors".equals(computerChoice)) {
                    System.out.println("Result: You Lose\n");
                    JOptionPane.showMessageDialog(null, "You Lose!", "Round " + i + " Result", JOptionPane.ERROR_MESSAGE);
                    lose++;
                }   
             } 
         
             //Display all player and computer choices, total rounds of draw, win and win.
             DisplayResult(playerList, comList, draw, win, lose);
                     
             //Ask user to play again or not.
             System.out.println("\nPlay again?");
         
             do {
                 do {
                     try {
                         String finalinput = JOptionPane.showInputDialog(null, "(1)Yes   (2)No",
                                 "Do you want to play again?", JOptionPane.QUESTION_MESSAGE);
                         if (finalinput == null) {
                             System.out.println("\n------------- Game Over -------------");
                             //system.exit(0);
                             return;
                         }
                         finalSelection = Double.parseDouble(finalinput);
                         finalerrorInput = false;
                     }
                     catch (Exception e) {        
                         System.out.println("Invalid input! Please enter available number.");
                     }
                 } while (finalerrorInput);
         
                 AskUserContinue(finalSelection);
             }while (finalSelection != 1 && finalSelection != 2);
         } while (finalSelection == 1);
    }
        
           
    
    
    public static void StartMenu() {
        System.out.println("=========================================\n"
                + "          SCISSORS, ROCK, PAPER\n"
                + "=========================================\n\n"
                + "Rules:\n"
                + "1)Enter 0 for scissors, 1 for rock, and 2 for paper.\n"
                + "2)Rock wins against scissors, scissors wins against paper, paper wins against rock.\n"
                + "3)You will having 10 rounds of games, win as much as you can!\n\n"
                + "------------- Game Start -------------\n");
    }
    
    public static String PlayerTurn(double userSelection) {
        String playerSelection = null;
        
            if (userSelection == 0.0) {
                playerSelection = "Scissors";
            }
            else if (userSelection == 1.0) {
                playerSelection = "Rock";
            }
            else if (userSelection == 2.0) {
                playerSelection = "Paper";
            }
            else {
                System.out.println("Invalid input! Please only enter 0, 1 or 2.");
            }
            
        return playerSelection;
    }
    
    public static String ComputerTurn() {
        Random random = new Random();
        
        String computerSelection = null;
        int randomAnswer = random.nextInt(3)+0;
        
        if (randomAnswer == 0) {
            computerSelection = "Scissors";
        }
        else if (randomAnswer == 1) {
            computerSelection = "Rock";
        }
        else {
            computerSelection = "Paper";
        }
        
        return computerSelection;
    }
    
    public static void DisplayResult(String[] playerList, String[] comList, int draw, int win, int lose) {
        System.out.println("------------------------------");
        System.out.format("%-8s%-11s%-11s\n", "Round", "Player", "Computer");
        System.out.println("------------------------------");
        for (int x = 1; x < 11; x++) {
            System.out.format("%-8s%-11s%-11s\n", x + ")", playerList[x-1], comList[x-1]);
        }
            
        System.out.println("\nDraw Match: " + draw + " round(s)"
                + "\nPlayer Win: " + win + " round(s)"
                + "\nComputer Win: " + lose + " round(s)");
    }
    
    public static void AskUserContinue(double finalSelection) {
        if (finalSelection == 1) {
            System.out.println("Yes!\n");
        }
        else if (finalSelection == 2) {
            System.out.println("No!\n"
                + "Thanks for playing!\n\n"
                + "------------- Game Over -------------");
        }
        else {
            System.out.println("Invalid input! Please only enter 1 or 2.");
        }
    }
}
