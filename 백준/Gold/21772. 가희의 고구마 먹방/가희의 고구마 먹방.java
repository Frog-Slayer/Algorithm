import java.io.*;
import java.util.StringTokenizer;

class Pos {
    int x;
    int y;
    public Pos(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public class Main {
    static int R, C, T;
    static int []dx = { -1, 0, 0, 1 };
    static int []dy = { 0, -1, 1, 0 };
    static char[][]map;
    static int ans = 0;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());

        map= new char[R][C];
        int gx = -1, gy = -1;

        for (int i = 0; i < R; i++) {
            String s = br.readLine();

            for (int j = 0; j < C; j++) {
                map[i][j] = s.charAt(j);
                if (map[i][j] == 'G') {
                    gx = i;
                    gy = j;
                }
            }
        }

        recursive(new Pos(gx, gy), 0, 0);
        System.out.println(ans);
    }

    static void recursive(Pos p, int t, int cnt) {
        if (t == T) {
            ans = Integer.max(ans, cnt);
            return;
        }
        for (int d = 0; d < 4; d++) {
            int nx = p.x + dx[d];
            int ny = p.y + dy[d];

            if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
            char c = map[nx][ny];
            if (c == '#') continue;
            if (c == 'S') {
                map[nx][ny] = '.';
                recursive(new Pos(nx, ny), t + 1, cnt + 1);
                map[nx][ny] = 'S';
            }
            else recursive(new Pos(nx, ny), t + 1, cnt);
        }

        ans = Integer.max(ans, cnt);
    }
}
