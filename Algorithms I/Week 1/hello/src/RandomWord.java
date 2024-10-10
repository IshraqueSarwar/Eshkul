import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

class RandomWord{
	public static void main(String[] args){
		String out = "";
		int i = 0;

		while(!StdIn.isEmpty()){
			String word = StdIn.readString();

			boolean p = StdRandom.bernoulli(1 /(i+1.0));
			if(p){
				out = word;
			}
			i++;
		}

		StdOut.println(out);
	}
}