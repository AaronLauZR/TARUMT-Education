/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package javagames;

import java.util.Scanner;

/**
 *
 * @author andre
 */
public class JavaGames {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int choose;
        Scanner sc=new Scanner(System.in);
        while(true){
                System.out.println("\n=============================== Java Games ===============================");
                System.out.println("Choose One Game to play.");
                System.out.println("1. Hangman");
                System.out.println("2. ScissorsRockPaper");
                System.out.println("3. TicTacToe");
                System.out.println("4. FlipAndMatchGame");
                System.out.println("5. FiveDice");
                System.out.println("6. Exit Java Games");
                try {
                    System.out.print("\nOption: ");
                    choose=sc.nextInt();
                    
                    switch(choose){
                        case 1:
                            new Hangman();
                            break;
                        case 2:
                            new ScissorsRockPaper();
                            break;
                        case 3:
                            new TicTacToe();
                            break;
                        case 4:
                            new FlipAndMatch();
                            break;
                        case 5:
                            new FiveDice();
                            break;
                        case 6:
                            System.out.println("Exit Java Games");
                            System.exit(0);
                            break;
                        default:
                            System.out.println("Please Integer only 1-6");
                            break;
                    }
                } catch (Exception e) {
                   System.out.println("Please Integer only");
                   sc.next();
                }  
        }
    }
}
