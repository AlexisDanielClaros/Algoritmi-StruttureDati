import java.util.Arrays;
import java.util.Scanner;

public class EditDistance{
/*
    //Main for the first part of the exercise
   public static void main(String[] args) {
       String str1;
       String str2;
       int distance, i, j;

       System.out.println("Select the first string: ");
       str1 = new Scanner(System.in).nextLine();
       System.out.println("Now select the second string: ");
       str2 = new Scanner(System.in).nextLine();
       i = str1.length();
       j = str2.length();
       distance = edit_distance_dyn(str1, str2, i, j);
       System.out.println("The edit distance between these two strings is: " + distance);
   }
*/

   public static int Edit_distance(String s1, String s2, int i, int j){

           // if the first string is empty we do j deletes
           if (i== 0)
               return j;
           // if  the second is empty we do I inserts
           else if (j == 0)
               return i;

           // if the characters are the same, we do no-op and look the substring without the same chars
           if (s1.charAt(i - 1) == s2.charAt(j - 1))
               return Edit_distance(s1, s2, i - 1, j - 1);

           // if they are not the same, we take the minimun distance between the cases where we do a delete or
           // an insert and add 1 to that number
           else {
               return 1 + Min(Edit_distance(s1, s2, i,j - 1), Edit_distance(s1, s2, i - 1, j));
           }
   }

    static int Min(int a, int b) {
        if (a <= b)
            return a;
        else return b;
    }

    // i set all the matrix with -1 because the default 0 in this case means that aren't recuired operations
    public static void fillMatrix(int[][] matrix){
        for (int[] row : matrix) 
                    Arrays.fill(row, -1);
    }
    public static int edit_distance_dyn(String str1, String str2, int i, int j, int[][] matrix) {

        // A value of greater than -1 in the memo grid means that the value for
        // this combination of i and j has already been calculated and can be
        // promptly returned.
        if (matrix[i][j] > -1) return matrix[i][j];

        if (i == 0) {
            matrix[i][j] = j;
            return j;
        }

        if (j == 0) {
            matrix[i][j] = i;
            return i;
        }

        if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
            matrix[i][j] = edit_distance_dyn(str1, str2, i - 1, j - 1, matrix);
            return matrix[i][j];
        }

        matrix[i][j] = 1 + Min(edit_distance_dyn(str1, str2, i, j - 1, matrix),      // insert
                edit_distance_dyn(str1, str2, i - 1, j, matrix));    // delete

        return matrix[i][j];
    }

}




