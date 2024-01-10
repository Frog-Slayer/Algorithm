import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] strings = br.readLine().split(" ");
        BigInteger n = new BigInteger(strings[0]);
        BigInteger m = new BigInteger(strings[1]);

        System.out.println(n.divide(m));
        System.out.println(n.mod(m));
    }
}