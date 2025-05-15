import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String s = br.readLine();

        boolean upper = false, under = false, isError = false;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if (Character.isUpperCase(c)) {
                if (i == 0) isError = true;
                upper = true;
            }
            else if (c == '_') {
                if (i == 0 || i == s.length() - 1) isError = true;
                else if (s.charAt(i - 1) == '_') isError = true;
                under = true;
            }
        }

        boolean isJava = !under && !isError;
        boolean isCpp = !upper && !isError;

        StringBuilder sb = new StringBuilder();

        if (isError) sb.append("Error!");
        else if (isJava) {
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (Character.isLowerCase(c)) sb.append(c);
                else sb.append('_').append(Character.toLowerCase(c));
            }
        }
        else if (isCpp) {
             for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (i > 0 && s.charAt(i - 1) == '_') sb.append(Character.toUpperCase(c));
                else if (Character.isLowerCase(c)) sb.append(c);
            }
        }
        else sb.append("Error!");

        System.out.println(sb);

    }
}