import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	static int comb[][] = new int[31][31];
	
	public static void main(String[] args) throws Exception {
		int N, M, T;
		generateCombination();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokenizer = new StringTokenizer(br.readLine());
		
		
		T = Integer.parseInt(tokenizer.nextToken());
		StringBuilder sb = new StringBuilder();
		
		for (int i = 0; i < T; i++) {
			tokenizer = new StringTokenizer(br.readLine());
			N = Integer.parseInt(tokenizer.nextToken());
			M = Integer.parseInt(tokenizer.nextToken());
			
			sb.append(comb[M][N] + "\n");
		}
	
		System.out.println(sb.toString());
	}

	private static void generateCombination(){
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				if (j == 0) comb[i][j] = 1;
				else if (i == 0) comb[i][j] = 0;
				else {
					comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
				}
			}
		}
	}
}