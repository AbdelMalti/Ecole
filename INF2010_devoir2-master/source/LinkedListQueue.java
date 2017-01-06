
public class LinkedListQueue<AnyType> implements Queue<AnyType>
{	
	// Un noeud de la file
	@SuppressWarnings("hiding")
	private class Node<AnyType> 
	{
		private AnyType data;
		private Node next;
		
		public Node(AnyType data, Node next) 
		{
			this.data = data;
			this.next = next;
		}

		public void setNext(Node next) 
		{
			this.next = next;
		}
		
		public Node<AnyType> getNext() 
		{
			return next;
		}
		
		public AnyType getData() 
		{
			return data;
		}
	}
   
	private int size = 0;		//Nombre d'elements dans la file.
	private Node<AnyType> last;	//Dernier element de la liste
	private Node<AnyType> head; // Il s'agit du première élément de la liste
	
	//Indique si la file est vide
	public boolean empty() 
	{ 
		return size == 0; 
	}
	
	//Retourne la taille de la file
	public int size() 
	{ 
		return size; 
	}
	
	//Retourne l'element en tete de file
	//Retourne null si la file est vide
	//complexité asymptotique: O(1)
	public AnyType peek()
	{
		//A completer
		if(size > 0){
			return head.getData();
		}
		return null;
		
	}
	
	//Retire l'element en tete de file
	//complexité asymptotique: O(1)
	public void pop() throws EmptyQueueException
	{
		//A completer
		if(size > 0){
			head = head.getNext();
			size--;
			}
		else if(empty()){
			throw new EmptyQueueException();	
			}
		
	}
	
	//Ajoute un element a la fin de la file
	//complexité asymptotique: O(1)
	public void push(AnyType item)
	{		
		//A completer
		Node element = new Node(item, null);
		if (size == 0){
			head =  element;
		}
		else{
			last.setNext( element);
		}
		last =  element;
		size++;
		
	}  
}
