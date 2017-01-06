/**
 * 
 * @author KAMATE Ala-eddine (1722161), MALTI Abdeljelil (1746988)
 *
 * @param <AnyType>
 */
public class ArrayQueue<AnyType> implements Queue<AnyType>
{
	private int size = 0;		//Nombre d'elements dans la file.
	private int startindex = 0;	//Index du premier element de la file
	private AnyType[] table;
   
	@SuppressWarnings("unchecked")
	public ArrayQueue() 
	{
		//A completer
		table = (AnyType[]) new Object[10];
		size = 0;
	}
	
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
		return table[startindex];
	}
	
	//Retire l'element en tete de file
	//complexité asymptotique: O(1)
	public void pop() throws EmptyQueueException
	{
		//A completer
		if(empty()){
			startindex = 0;
			throw new EmptyQueueException();
		}
		else{
	
			table[startindex] = null;
			size--;
			startindex = (startindex+1)%table.length;
		}
		/*
		// Si la file contient  elements (au moins un)
		if (!this.empty()) {
			// Eliminer l'element a la tete de la file
			table[startindex] = null;			
			// Un element a ete retire donc il faut enlever 1 au nombre d'elements
			size--;			
			// Si la file est devenue vide, retourner au debut du tableau
			if (size == 0){
				startindex = 0;
			} else { 
				// Sinon, avancer la tete d'une case
				startindex++;
			}	
		} else { // Si la file etait deja vide avant le pop, lancer une exception
			throw new EmptyQueueException();
		}*/
		
	}
	
	//Ajoute un element a la fin de la file
	//Double la taille de la file si necessaire (utiliser la fonction resize definie plus bas)
	//complexité asymptotique: O(1) ( O(N) lorsqu'un redimensionnement est necessaire )
	public void push(AnyType item)
	{
		int endIndex = startindex + size;
		//A completer
		if(endIndex >= table.length ){
			this.resize(2);
		}
		table[endIndex] = item;
		size++;
		
		/*
		int endIndex = startindex + size;
		// Si on depasse le tableau, double la taille du tableau
		if (endIndex >= table.length){
			this.resize(2);
		}
		// Ajouter le nouvel element a la suite de la file
		table[endIndex] = item;
		// Le nombre d'elements de la file augmente
		size++;*/
		
	}
   
	//Redimensionne la file. La capacite est multipliee par un facteur de resizeFactor.
	//Replace les elements de la file au debut du tableau
	//complexité asymptotique: O(N)
	@SuppressWarnings("unchecked")
	private void resize(int resizeFactor)
	{
		/*//A completer
		AnyType[] temp = table;
		table = (AnyType[])new Object[table.length*2];
		for(int i=0; i < temp.length ; i++){
			table[(startindex+i)%temp.length] = temp[i];
		}
		startindex = 0; 
		temp = null;*/
		
		

		AnyType[] tableTemp = table;
		table = (AnyType[]) new Object[(tableTemp.length)*resizeFactor];
		for (int i = 0; i < tableTemp.length; i++){
			table[i] = tableTemp[i];
		}
		tableTemp = null;
	}   
}

