import java.util.ArrayList;
import java.util.Hashtable;
import java.util.NoSuchElementException;

public class HeapPriorityQueue<AnyType> implements PriorityQueue<AnyType>{

	private static final int DEFAULT_CAPACITY = 20;

	private int currentSize;              // nombre d'�l�ments pr�sents
	private PQEntry<AnyType>[] items;     // tableau contenant les �l�ments ordonn�s en tas
	Hashtable<AnyType, Integer> indexMap; // Mappe associant � chaque �l�ment Anytype un entier 
	// (sa position dans items)

	/**
	 * M�thodes d�j� impl�ment�es
	 */
	public HeapPriorityQueue(){
		initialize();
	}

	public int size(){
		return currentSize;
	}

	public void clear(){
		initialize();
	}

	public boolean isEmpty( ){
		return currentSize == 0;
	}

	public boolean contains(AnyType x){
		return indexMap.containsKey(x);
	}

	@SuppressWarnings("unchecked")
	private void enlargeArray( int newSize )
	{
		if(newSize <= (currentSize+1)) return;

		PQEntry<AnyType> [] old = items;
		items = (PQEntry<AnyType>[]) new PQEntry[ newSize ];

		for( int i = 0; i <= old.length; i++ )
			items[ i ] = old[ i ];        
	}

	private void initialize(){
		initialize( DEFAULT_CAPACITY );
	}

	@SuppressWarnings("unchecked")
	private void initialize(int capacity){
		if(capacity < 0)
			capacity = DEFAULT_CAPACITY;
		currentSize = 0;
		items = (PQEntry<AnyType>[]) new PQEntry[ capacity ];
		indexMap = new Hashtable<AnyType, Integer>( capacity );
	}

	public String toString(){
		String output = "";

		for(int i=1; i<=currentSize; i++)
			output += items[i] + ((i!=currentSize) ? ", " : "");

		return output;
	}

	/**
	 * M�thodes � impl�menter
	 */

	// Commentez la ligne de add1 et d�commenter la ligne de add2 pour l'exercice 5
	public boolean add(AnyType x, int priority) throws NullPointerException, IllegalArgumentException {
		//return add1(x, priority); // Exercice 1
		return add2(x, priority); // Exercice 5
	}

	/**
	 * Exercice 1
	 */
	private boolean add1(AnyType x, int priority) throws NullPointerException, IllegalArgumentException {
		// completer

		if(priority < 0) // Ici, on verifie si priority n'est pas inferieur a zero, car cela ne ferait pas de sens
			throw new IllegalArgumentException(); // Si c'est le cas, on lance une exception.

		if(x == null) //Ici on verifie si X est null,
			throw new NullPointerException(); // si c le cas on lance une exception.

		if(currentSize == items.length-1){
			enlargeArray(items.length*2 + 1);
		}
		int hole = ++currentSize;
		for(; hole > 1 && priority < items[hole/2].priority; hole/=2){ 
			items[hole] = items[hole/2];
		}
		items[hole] = new PQEntry(x,priority); // On convertie x au type de items.
		return true;
	}

	// Commentez la ligne de poll1 et d�commenter la ligne de poll2 pour l'exercice 6
	public AnyType poll(){ 
		//return poll1(); // Exercice 2
		return poll2(); // Exercice 6
	}

	/**
	 * Exercice 2
	 */
	private AnyType poll1(){ 
		// completer
		if(isEmpty())
			throw new NullPointerException();
		
		AnyType minItem = items[1].value;//stock la valeur  prioritaire dans une variable temporaire afin de la retourner par la suite
		items[1] = items[currentSize--];// remplace la valeur prioritaire par la moins prioritaire
		percolateDown1(1);//on percolate
		return minItem;// on retourne l'element prioritaire retire
		
	}

	private void percolateDown1( int hole ){
		// completer
		int child;
		PQEntry tmp = items[ hole ];

		for( ; hole * 2 <= currentSize; hole = child ) 
		{
			child = hole * 2; //Considérer fils de gauche

			if( child != currentSize && // il y a deux fils
					items[ child + 1 ].priority  < items[ child ].priority ) //et fils droit<fils gauche
				child++; //Considérer fils droit
			if( items[ child ].priority < tmp.priority )//fils considéré< élément à percoler
				items[ hole ] = items[ child ];//Remonter le fils courrent de un niveau
			else
				break; //sortir de la boucle. L’élément à percoler sera inséré à position hole
		}

		items[ hole ] = tmp; // Insérer l’élément à percoler à la position hole 
	}

	// Commentez la ligne de buildHeap1 et d�commenter la ligne de buildHeap2 pour l'exercice 7
	public HeapPriorityQueue( AnyType[] items, int[] priorities )throws IllegalArgumentException, NullPointerException{
		//buildHeap1( items, priorities ); // Exercice 3
		buildHeap2( items, priorities ); // Exercice 7
	}

	/**
	 * Exercice 3
	 */
	private void buildHeap1( AnyType[] items, int[] priorities ) throws IllegalArgumentException, NullPointerException{
		// completer
		
		// faire attention aux exceptions
		if(items == null || priorities == null){//Ici on verifie si un des tableaux n'exite pas. 
			throw new NullPointerException();//Si c'est le cas, on lance une exception
		}
		
		this.initialize();
		
		for(int i=0 ; i < items.length ; i++){//Ici, on va verifier si chacun des elements dans les 2 tableaux existe et respecte les conditions.
			if(items[i] == null)//On verifie les elements dans items
				throw new NullPointerException();//Si un d'eux est vide, on lance une exception
			if(priorities[i] < 0)//Ici, on verifie les elements de priorities
				throw new IllegalArgumentException(); //Si un d'eux est inferieur a 0, on lance une exception 
			}
		
		for(int i=0 ; i < items.length ; i++){
			this.add(items[i], priorities[i]);
		}
		
		for(int i= this.currentSize/2 ; i>0 ; i--){
			percolateDown1(i);
		}
		this.toString();
	}


	/**
	 * Exercice 4
	 */
	public ArrayList<AnyType> getMax() {
		// completer
		
		//int biggest = this.items[this.currentSize].priority;
		int priorityMax = 0;
		for(int i = 1 ; i < this.size() ; i++){
			if(priorityMax < this.items[i].priority)
				priorityMax = this.items[i].priority;
		}
		
		ArrayList<AnyType> max = new ArrayList<AnyType>();

	        for( int i = currentSize/2; i <= currentSize; i++ )
	        {
	            if (this.items[i].priority == priorityMax) 
	                max.add( this.items[i].value );
	        }

		return max;  

	}

	/**
	 * Exercice 5
	 */
	private boolean add2(AnyType x, int priority) throws IllegalArgumentException{
		// Completer
		
		if(priority < 0) // Ici, on verifie si priority n'est pas inferieur a zero, car cela ne ferait pas de sens
			throw new IllegalArgumentException(); // Si c'est le cas, on lance une exception.

		if(x == null) //Ici on verifie si X est null,
			throw new NullPointerException(); // si c le cas on lance une exception.
		
		if(currentSize == items.length-1){
			enlargeArray(items.length*2 + 1);
		}
		
		if(indexMap.contains(x)) //On verifie si l'element est deja contenu dans la map
			return false; //si oui, on retourne faux pour eviter les doublons
		
		int hole = ++currentSize;
		for(; hole > 1 && priority < items[hole/2].priority; hole/=2){ 
			items[hole] = items[hole/2]; //On place la bonne valeur a la bonne position. 
			indexMap.replace(items[hole].value, hole);
			
		}
		items[hole] = new PQEntry(x,priority); // On convertie x au type de items.
		indexMap.put(x, hole); //On met l'alveole contenant x et hole dans la map.
		return true;
	}

	/**
	 * Exercice 6
	 */
	private AnyType poll2(){ 
		// completer
		
		if(isEmpty())
			throw new NullPointerException();
		
		AnyType minItem = items[1].value;//stock la valeur  prioritaire dans une variable temporaire afin de la retourner par la suite
		items[1] = items[currentSize--];// remplace la valeur prioritaire par la moins prioritaire
		indexMap.remove(1); // On retire items[1] de la map.
		percolateDown2(1);//on percolate
		return minItem;// on retourne l'element prioritaire retire
	}

	private void percolateDown2( int hole ){
		// completer
		
		int child;
		PQEntry tmp = items[ hole ];

		for( ; hole * 2 <= currentSize; hole = child ) 
		{
			child = hole * 2; //Considérer fils de gauche

			if( child != currentSize && // il y a deux fils
					items[ child + 1 ].priority  < items[ child ].priority ) //et fils droit<fils gauche
				child++; //Considérer fils droit
			if( items[ child ].priority < tmp.priority ){//fils considéré< élément à percoler
				items[ hole ] = items[ child ];//Remonter le fils courrent de un niveau
				indexMap.replace(items[child].value, hole); // Ici, on remonte les childs dans le niveau courant de la map.
			}
			else
				break; //sortir de la boucle. L’élément à percoler sera inséré à position hole
		}

		items[ hole ] = tmp; // Insérer l’élément à percoler à la position hole 
		indexMap.put(items[hole].value, hole); // On insert l'element a la position hole de la map.
	}

	/**
	 * Exercice 7
	 */
	private void buildHeap2( AnyType[] items, int[] priorities ) throws IllegalArgumentException, NullPointerException{
		// completer
		
		// faire attention aux exceptions
		if(items == null || priorities == null){//Ici on verifie si un des tableaux n'exite pas. 
			throw new NullPointerException();//Si c'est le cas, on lance une exception
		}
		
		this.initialize();
		
		for(int i=0 ; i < items.length ; i++){//Ici, on va verifier si chacun des elements dans les 2 tableaux existe et respecte les conditions.
			if(items[i] == null)//On verifie les elements dans items
				throw new NullPointerException();//Si un d'eux est vide, on lance une exception
			if(priorities[i] < 0)//Ici, on verifie les elements de priorities
				throw new IllegalArgumentException(); //Si un d'eux est inferieur a 0, on lance une exception 
			if(! this.contains(items[i])){
				//this.items[i+1] = new PQEntry<AnyType> (items[i], priorities[i]);
				this.add(items[i], priorities[i]);
				indexMap.put(items[i], i+1);
			}
				
		}
		
		for(int i= this.currentSize/2 ; i>0 ; i--){
			percolateDown2(i);
		}
		this.toString();
		
	}

	/**
	 * Exercice 8
	 */
	public void updatePriority(AnyType x, int priority){
		// completer  
		
		//Verification des exceptions
		if(x == null)
        	throw new NullPointerException();
		if(priority <0)
			throw new IllegalArgumentException();
		
		if(! this.contains(x)) //Ici, on verifie si l'element n'est pas contenue dans l'objet.
			return;
		
		//PQEntry<AnyType> varible = items[this.indexMap.get(x)];
		
		int indiceDeElement = this.indexMap.get(x); //On retrouve l'indice de l'element rechercher
		
		PQEntry<AnyType> theOldRoot = this.items[1]; // On garde la valeur de l'ancienne racine.
		this.items[1] = new PQEntry<AnyType>(x, priority); // On remplace l'ancienne racine par la nouvelle. 
		indexMap.remove(theOldRoot); //On retire la vielle racine du hashmap
		indexMap.put(this.items[1].value, this.items[1].priority);//On ajout la vielle racine du hashmap
		this.add(theOldRoot.value, theOldRoot.priority);
		
	}
}
