import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.runner.JUnitCore;

public class Run_test {

    public static void main(String[] args) {
        Result result  = JUnitCore.runClasses(EditDistanceTests.class);
        
        for (Failure failure : result.getFailures()) {
            System.out.println(failure.toString());
         }
         System.out.println("The tests are successful?  " + result.wasSuccessful());
    }
}
