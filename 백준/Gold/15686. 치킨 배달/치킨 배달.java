import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

class Pair{
	int x;
	int y;

	Pair(){}
	
	Pair(int x, int y){
		this.x = x;
		this.y = y;
	}
}

public class Main {
	static List<Pair> houses = new ArrayList<Pair>();
	static List<Pair> chickens = new ArrayList<Pair>();
	static List<Pair> selectedChickens = new ArrayList<Pair>();
	static int chickensSize;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] str;
		int N, M;
		int chickenMap[][];
		str = br.readLine().split(" ");
		N = Integer.parseInt(str[0]);
		M = Integer.parseInt(str[1]);
		chickenMap = new int[N][N];

		for (int i= 0; i < N; i++) {
			str = br.readLine().split(" ");
			for (int j = 0; j < N; j++) {
				chickenMap[i][j] = Integer.parseInt(str[j]);
				if (chickenMap[i][j] == 1) {//집
					houses.add(new Pair(i, j));
				}
				else if (chickenMap[i][j] == 2) {//치킨집
					chickens.add(new Pair(i, j));
				}
			}
		}
		chickensSize = chickens.size();
		int cnt = 0;
		int minChickenDist = Integer.MAX_VALUE;
		int chickenDist;
		//조합을 통해서 M개의 치킨집을 고르고 그 때의 치킨 거리를 구함
		for (int i = 0; i < (1 <<chickensSize); i++) {
			cnt = 0;
			for (int j = 0; j < chickensSize; j++) if (((1 << j) & i) != 0) cnt++;
			if (cnt != M) continue;
			selectedChickens = new ArrayList<Pair>();
			for (int j = 0; j < chickensSize; j++) 
				if (((1 << j) & i) != 0) selectedChickens.add(chickens.get(j));
			
			chickenDist = getChickenDist(selectedChickens);
			if (chickenDist < minChickenDist) minChickenDist = chickenDist;
		}
		System.out.print(minChickenDist);
		
	}
	
	private static int getChickenDist(List<Pair> selected) {
		int totalChickenDist = 0;
		for (Pair house : houses) {
			int chickenDist = Integer.MAX_VALUE;
			for (Pair chicken : selected) {
				chickenDist = Math.min(chickenDist, Math.abs(house.x - chicken.x) + Math.abs(house.y - chicken.y));
			}
			totalChickenDist += chickenDist;
		}
		return totalChickenDist;
	}
}