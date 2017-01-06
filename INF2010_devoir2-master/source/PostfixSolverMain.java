import java.io.*;
import java.util.Stack;

public class PostfixSolverMain 
{
	
	public static void main(String[] args) throws IOException, EmptyQueueException 
	{
		Stack<Double> stack = new Stack<Double>();
		
		String s = "25 5 2 * + 15 3 / 5 - +";
		//L'expression est separee en tokens selon les espaces
		for(String token : s.split("\\s")) 
		{
			double num1;
			double num2;
		
			//A completer
			switch (token){
			case "+":
				num1 = (stack.peek());
				stack.pop();
				num2 = (stack.peek());
				stack.pop();
				stack.push(num1+num2);
				break;
				
			case "-":

				num1 = (stack.peek());
				stack.pop();
				num2 = (stack.peek());
				stack.pop();
				stack.push(num1-num2);
				break;
				
			case "*":

				num1 = (stack.peek());
				stack.pop();
				num2 = (stack.peek());
				stack.pop();
				stack.push(num1*num2);
				break;
				
			case "/":

				num1 = (stack.peek());
				stack.pop();
				num2 = (stack.peek());
				stack.pop();
				stack.push(num2/num1);
				break;
			default:
				stack.push(Double.parseDouble(token));
				break;
			}
		}
     
		System.out.println("25 + 5*2 + 15/3 - 5 = "+stack.peek());
		if(stack.peek() == 35)
			System.out.println("It's all good");
		else
			System.out.println("Erreur: mauvais resultat");
     }
	
	public static String add(String operator){
		return "";
	}
}
