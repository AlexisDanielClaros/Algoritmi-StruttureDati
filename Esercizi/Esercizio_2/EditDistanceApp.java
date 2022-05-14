import java.util.ArrayList;
import java.io.File;
import java.util.Scanner;
import java.io.IOException;
import java.util.concurrent.TimeUnit;
import java.util.*;

public class EditDistanceApp extends EditDistance{

    public static void main(String args[]) throws IOException {
        String array[] = new String[49];
        ArrayList<String> dictionary = new ArrayList<String>();
        int i = 0;
        String supp;

        Scanner scanner = new Scanner(new File("correctme.txt"));
        scanner.useDelimiter("[;.,:\\s]+");
        while (scanner.hasNext()) {
            supp = scanner.next();
            array[i] = supp;
            i++;
        }
        scanner.close();

        Scanner scanner2 = new Scanner(new File("dictionary.txt"));
        while (scanner2.hasNext()) {
            supp = scanner2.next();
            dictionary.add(supp);
        }
        scanner2.close();

        long start = System.nanoTime();
        app_edit_distance(array, dictionary);
        long duration = System.nanoTime() - start;

        System.out.println("\nThe total time is: " + duration / 1000000000.000 + " seconds");
    }

    public static int getMin(int[] temp) {
        int min;

        min = temp[0];
        for (int i = 1; i < temp.length; i++) {
            if (min > temp[i])
                min = temp[i];
        }
        return min;
    }

    // Check the distance of all words and find in the dictionary the words with the minimun distance
    static void app_edit_distance(String[] a, ArrayList<String> b) {
        ArrayList<String> result = new ArrayList<String>();
        int temp[] = new int[661562];
        int min, l, k;


        for (int i = 0; i < a.length; i++) {
            l = a[i].length();  // take length for the distance method
            for (int j = 0; j < b.size(); j++) {
                k = b.get(j).length(); // take length for the distance method
                int matrix[][] = new int[l + 1][k + 1]; // i add + 1 for the case where they are empty
                fillMatrix(matrix);
                temp[j] = edit_distance_dyn(a[i], b.get(j), l, k, matrix); //i store the results in an array
            }
            min = getMin(temp);
            if(min > 0) {
                // Check in the array with the distances of every word in dictionary, if it's the same as the minimum
                // and then adding it in the result list
                for (int n = 0; n < temp.length; n++) {
                    if (min == temp[n])
                        result.add(b.get(n));
                }
            }
            System.out.println(a[i] + ": " + min + " -->  " + result);
            if(min != 0)
                result.clear();

        }
    }
}



