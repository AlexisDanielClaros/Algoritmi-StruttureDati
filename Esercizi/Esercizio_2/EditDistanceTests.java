
import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.Before;

public class EditDistanceTests extends EditDistance{

    String s1 = "";
    String s2 = "";
    String s3 = "hello";
    String s4 = "hello";
    String s5 = "house";
    String s6 = "abcde";
    int matrix1[][] = new int[1 + s1.length()][1 + s2.length()];
    int matrix2[][] = new int[1 + s3.length()][1 + s4.length()];
    int matrix3[][] = new int[1 + s5.length()][1 + s6.length()];
    int[] array = {1, 2, 3};

    @Test
    public void emptyStrings(){
        assertEquals(0, Edit_distance(s1,s2, s1.length(), s2.length()));
    }

    @Test
    public void equalsStrings(){
        assertEquals(0, Edit_distance(s3,s4, s3.length(), s4.length()));
    }

    @Test
    public void DifferentStrings(){
        assertEquals(8, Edit_distance(s5,s6, s5.length(),s6.length()));
    }

    @Test
    public void minInts(){
        assertEquals(3, Min(3,5));
        assertEquals(6, Min(10,6));
        assertEquals(0, Min(0,0));
    }

    @Before
    public void filledMatrix(){
        fillMatrix(matrix1);
        fillMatrix(matrix2);
        fillMatrix(matrix3);
        assertEquals(-1, matrix1[0][0]);
        assertEquals(-1, matrix2[0][0]);
        assertEquals(-1, matrix3[0][0]);
    }

    @Test
    public void emptyStringsDP(){
        fillMatrix(matrix1);
        assertEquals(0, edit_distance_dyn(s1,s2, s1.length(), s2.length(), matrix1));
    }

    @Test
    public void equalsStringsDP(){
        fillMatrix(matrix2);
        assertEquals(0, edit_distance_dyn(s3,s4, s3.length(), s4.length(), matrix2));
    }

    @Test
    public void differentStringsDP(){
        fillMatrix(matrix3);
        assertEquals(8, edit_distance_dyn(s5,s6, s5.length(), s6.length(), matrix3));
    }
}
