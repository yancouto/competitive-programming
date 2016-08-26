import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;
public class Main {
	public static void main(String[] args) throws Exception {
		BigInteger[] b;
		int N = 561199;
		b = new BigInteger[N + 12];
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(in.readLine());
		for(int i = 0; i != N; ++i) b[i] = BigInteger.ZERO;
		for(int i = 0; i != n; ++i) {
			String l[] = in.readLine().split(" ");
			int ai = Integer.parseInt(l[0]);
			if(ai >= N) { System.out.println("No"); return; }
			b[ai] = new BigInteger(l[1]);
		}
		BigInteger s = BigInteger.ZERO;
		for(int i = N-1; i != 0; --i) {
			b[i] = b[i].add(s);
			if(b[i].remainder(BigInteger.valueOf(i)).compareTo(BigInteger.ZERO) > 0) {
				System.out.println("No");
				return;
			}
			s = s.add(b[i].divide(BigInteger.valueOf(i)));
		}
		System.out.println("Yes");
	}
}
