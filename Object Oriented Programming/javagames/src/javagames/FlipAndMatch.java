/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javagames;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javax.swing.JOptionPane;

/**
 *
 * @author andre
 */
public class FlipAndMatch {
    
    // Declare global variable
    char[] ch;
    char matchrespone;
    char completegame; 
    public static int guestnum1; 
    public static int guestnum2;
    List<Integer> llist = new ArrayList<>();
    List<Integer> gridlist = new ArrayList<>();
    ArrayList<Integer> list3 = new ArrayList<>();
    int inputconfirm; 

    /************************************ 
    *  1. random generate grid letter   *
    *************************************/
    public void GenerateLetter(){  
        StringBuilder letters = new StringBuilder("abcdefghijabcdefghij");
        Random rand = new Random();
        for (int i = letters.length() - 1; i > 1; i--) {
            int swapWith = rand.nextInt(i);
            char tmp = letters.charAt(swapWith);
            letters.setCharAt(swapWith, letters.charAt(i));
            letters.setCharAt(i, tmp);
        }
        /*convert string to character*/
        //creating array of string length
        ch = new char[letters.length()];
        
        // copy character by character into array
        for(int i = 0; i < letters.length(); i++){
            ch[i] =  letters.charAt(i);
        }
    }
   
    /************************************ 
    *  2. display grid number           *
    *************************************/
    int[] Displaydgrid(){
        
        int row, column;
        int gridarray[][] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, { 16, 17, 18, 19, 20}};
        
        // Convert 2D array to list
        for(int x = 0; x < 4; x++){
            for(int y = 0; y < 5; y++) {
                gridlist.add(gridarray[x][y]);
            }
        }
        
        // Check do the gridletter of two input digits is matched? 
        if("Y".equals(Character.toString(matchrespone))){
            llist.add(guestnum1);
            llist.add(guestnum2);
                
        } else {
            guestnum1 = 0;
            guestnum1 = 0; 
        }
        
        // Find common elements
        // while iterating through list1
        gridlist.stream().filter((temp) -> (llist.contains(temp))).forEachOrdered((temp) -> {
            // Since present, add it to list3
            list3.add(temp);
        }); // Check if theis element is
        // present in list2 or not
       
        for(row = 0; row < 4; row++){
                for(column = 0; column < 5; column++){
                    int tempnum = gridarray[row][column];
                    if(list3.contains(tempnum)){
                        System.out.print("   [    ]");
                    }else if(gridarray[row][column] <10){
                        System.out.print("   [ 0"+ gridarray[row][column]+" ]");
                    }else{
                        System.out.print("   [ "+ gridarray[row][column] +" ]");
                    };

                }
                System.out.println();
        }
         
        return null;
    };
    
    /********************** 
    *  3. get user input  *
     * @return 
    ***********************/
    int GetInput(){
            int ans = 0;
            guestnum1 = 0;
            guestnum2 = 0;
            while(ans == 0){
                String input = JOptionPane.showInputDialog("Please enter 2 digits (Example: 1,2) : ");
                if(input == null)   
                {
                    inputconfirm = 1; 
                    ans = 1;
                }else{
                    if(input.length() >= 3){
                        String[] Ans = input.split(",");
                         try{ 
                            guestnum1 = Integer.parseInt(Ans[0]); 
                            guestnum2 = Integer.parseInt(Ans[1]);
                            if((guestnum2 <= 0 || guestnum2 <= 0)||(guestnum1 > 20 || guestnum2 > 20)){
                                JOptionPane.showMessageDialog(null, "Please enter input in range 1 to 20.", "Error Input", JOptionPane.ERROR_MESSAGE);
                                ans = 0;
                            } else if((llist.contains(guestnum1) && llist.contains(guestnum2))||(llist.contains(guestnum2) || llist.contains(guestnum1))){ 
                                JOptionPane.showMessageDialog(null, "This number of grid have been matched. Please Enter another digits for match.  ", "Alert", JOptionPane.WARNING_MESSAGE);
                                ans = 0;
                            }else if(guestnum1 == guestnum2){
                                JOptionPane.showMessageDialog(null, "Please enter 2 diferent digits.", "Alert", JOptionPane.WARNING_MESSAGE);
                            }
                            else{
                                inputconfirm = 0; 
                                ans = 1;}
                            }  
                        catch (NumberFormatException e)  
                        {  // Check for input format, only integer in range 1 to 20 is allowed.  
                            JOptionPane.showMessageDialog(null, "Only integer is allowed", "Alert", JOptionPane.WARNING_MESSAGE);
                            ans = 0;
                        }
                    }else{
                        ans = 0;
                    }
                    
                    }
            }
            return 0;
            
    }
    
    /****************************************** 
    *  4. match user input with grid letters  *
    *******************************************/
    char LetterCompare(){
        System.out.println("  ");
        System.out.print("[ " + guestnum1 +" ] = " + ch[(guestnum1)-1]);
        System.out.print(", [ " + guestnum2 +" ] = " + ch[(guestnum2)-1]);
        System.out.println("  ");
           if(ch[(guestnum1)-1] == ch[(guestnum2)-1]){
               matchrespone = 'Y';
               System.out.println("Letters match successfully! Continue to match......");
               System.out.println("  ");
           }else{
               matchrespone = 'N'; 
               System.out.println("Letters CANNOT match. Please try again. ");
               System.out.println("  ");
           }
           
        return 0;
    }
    /**
     * @param args the command line arguments
     */
    
    FlipAndMatch(){
        // TODO code application logic here
       
        char playconfirm = 'y';
        System.out.println("*                                             *");
        System.out.println("*      Welcome to Flip And Match Game!!       *");
        System.out.println("*                                             *");
        // 0 = yes, 1 = no, 2 = calcel
        while(playconfirm != 'n'){
            int startgameconfirm = JOptionPane.showConfirmDialog(null, "Do you want to start the game?", "Flip and Match Game",JOptionPane.YES_NO_OPTION);
            if(startgameconfirm == 0){
                // Display Welcome Message 
                // FlipAndMatchGame game = new FlipAndMatchGame();
                this.GenerateLetter();
                while(this.llist.size() < 18){
                    // While loop to loop the game until all grid have been match
                    System.out.println("----------------------------------------------");
                    System.out.println("|           Flip And Match Game              |");
                    System.out.println("----------------------------------------------");
                    this.Displaydgrid();
                    System.out.println("----------------------------------------------");
                    this.GetInput(); 
                    if(this.inputconfirm != 0){
                        break; 
                    }
                    this.LetterCompare();
                }
                if(this.inputconfirm != 1){
                    System.out.println("----------------------------------------------");
                    System.out.println("              You win the game!!              ");
                    System.out.println("----------------------------------------------");
                    this.Displaydgrid();
                    System.out.println("----------------------------------------------");
                }
                System.out.println("  _____                         ____                 ");
                System.out.println(" / ____|                       / __ \\                ");
                System.out.println("| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ ");
                System.out.println("| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|"); 
                System.out.println(" | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   "); 
                System.out.println(" \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   ");  
                System.out.println("  "); 
            }
            int exitconfirm = JOptionPane.showConfirmDialog(null, "Do you want to exit the game?", "Flip and Match Game",JOptionPane.YES_NO_OPTION);
                if(exitconfirm == 1){
                    playconfirm = 'y';
                }else{
                    playconfirm = 'n';
            }    
        }

    }
        
    

   
    
}
