import java.util.Random;
import java.util.Stack;

public class mainTest {
	static final int COUNT = 30;
	static final int MAX_VALUE = 1000;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		/*Queue<Integer> arrayQueue = new ArrayQueue<Integer>();
		//Queue<Integer> listQueue = new LinkedListQueue<Integer>();
		int pushCounter = 0;
		int popCounter = 0;
		
		for(int i=0; i < 15 ; i++){
			arrayQueue.push(i);
		}
		
		int c = arrayQueue.size();
		int popC = 0;
		
		System.out.println("\ntaille du array : "+arrayQueue.size());
		for(int i=0; i < c ; i++){
			if(arrayQueue.peek() != popC || listQueue.peek() != popCounter)
			{
				System.out.println("Erreur: l'ordre de sortie(FIFO) n'est pas respecte");
				return;
			}
			System.out.println(arrayQueue.peek()+ ", "+popC);
			try{
				arrayQueue.pop();
				popC++;
			}catch(Exception e){
				System.err.print("something is wrong");
			};
			
		}
		
		
		System.out.println("\ntaille du array : "+arrayQueue.size());*/
		boolean sortIsGood = true;
		
		Random generator = new Random( System.nanoTime() );
		Stack<Integer> stack = new Stack<Integer>();
		
		for(int i = 0; i < COUNT; i++)
			stack.push(generator.nextInt(MAX_VALUE));
		System.out.println(stack.size());
		
		System.out.print("END");
	}

}
