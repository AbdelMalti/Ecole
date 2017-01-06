
/**
 * 
 * @author MALTI Abdeljelil 1746988, 
 *
 */
public class DoubleHashingTable<AnyType>
{
    /**
     * Construct the hash table.
     */
    public DoubleHashingTable( )
    {
        this( DEFAULT_TABLE_SIZE );
    }

    /**
     * Construct the hash table.
     * @param size the approximate initial size.
     */
    public DoubleHashingTable( int size )
    {
        allocateArray( size );
        makeEmpty( );
    }

    /**
     * 
     * @return la taille de la table.
     */
    public int nbElement(){
    	return currentSize;
    }

    /**
     * 
     * @param x
     * @return element selon la cle de la map
     */
    public AnyType get(AnyType x){
    	//verifie que la cle est belle est bien dans la table
    	if(this.contains(x)) {
    		// Met la cle de X dans dans index.
    		int index = this.findPos(x);
    		//va retourner l'element cherche
    		return array[index].element;
    	} else {
    		//dans le cas ou on ne trouve pas la cle, on retourn un null.
    		return null;
    	}
    }
    
  /**
   * 
   * @param x
   * @return l'index est retourne
   */
    public int firstHash(AnyType x){
    	//La taille du tableau est enregistrer dans la variable taille
    	int size = array.length; 
    	// retourne l'index
    	return x.hashCode() % size; 
    }
    
    /**
     * 
     * @param x
     * @return l'index avec le nouveau nombre premier est retourner
     */
    public int secondHash(AnyType x){
    	int size = array.length; 
    	// mettre la valeur d'ou la recherche doit debuter dans une variable.
    	//Cette valeur est la taille du tableau -1, car taille est un nombre premier.
    	int nouveauNombrePremier = size - 1; 
    	//Ici, on va trouver le nombre premier juste avant taille 
    	//(Ex: si taille = 23, le nombre premier juste avant taille est 17.)
    	while (!isPrime(nouveauNombrePremier)){
    		nouveauNombrePremier--;
    	}
    	//Ici, on doit calculer l'index de x avec le nouveau nombre premier.
    	return (nouveauNombrePremier-(x.hashCode()%nouveauNombrePremier));
    }
    /**
     * Insert into the hash table. If the item is
     * already present, do nothing.
     * @param x the item to insert.
     */
    public void insert( AnyType x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return;

        array[ currentPos ] = new HashEntry<AnyType>( x, true );

            // Rehash; see Section 5.5
        if( ++currentSize > array.length / 2 )
            rehash( );
    }

    /**
     * Expand the hash table.
     */
    private void rehash( )
    {
        HashEntry<AnyType> [ ] oldArray = array;

            // Create a new double-sized, empty table
        allocateArray( nextPrime( 2 * oldArray.length ) );
        currentSize = 0;

            // Copy table over
        for( int i = 0; i < oldArray.length; i++ )
            if( oldArray[ i ] != null && oldArray[ i ].isActive )
                insert( oldArray[ i ].element );
    }

    /**
     * Method that performs quadratic probing resolution.
     * @param x the item to search for.
     * @return the position where the search terminates.
     */
    private int findPos( AnyType x )
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ] != null &&
                !array[ currentPos ].element.equals( x ) )
        {
            currentPos += offset;  // Compute ith probe
            //offset += 2;
            currentPos = (firstHash(x) + offset*secondHash(x)) % array.length;
            if( currentPos >= array.length )
                currentPos -= array.length;
        }
        
        return currentPos;
    }

    /**
     * Remove from the hash table.
     * @param x the item to remove.
     */
    public void remove( AnyType x )
    {
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            array[ currentPos ].isActive = false;
    }

    /**
     * Find an item in the hash table.
     * @param x the item to search for.
     * @return the matching item.
     */
    public boolean contains( AnyType x )
    {
        int currentPos = findPos( x );
        return isActive( currentPos );
    }

    /**
     * Return true if currentPos exists and is active.
     * @param currentPos the result of a call to findPos.
     * @return true if currentPos is active.
     */
    private boolean isActive( int currentPos )
    {
        return array[ currentPos ] != null && array[ currentPos ].isActive;
    }

    /**
     * Make the hash table logically empty.
     */
    public void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.length; i++ )
            array[ i ] = null;
    }

    private int myhash( AnyType x )
    {
        int hashVal = x.hashCode( );

        hashVal %= array.length;
        if( hashVal < 0 )
            hashVal += array.length;

        return hashVal;
    }
    
    private static class HashEntry<AnyType>
    {
        public AnyType  element;   // the element
        public boolean isActive;  // false if marked deleted

        public HashEntry( AnyType e )
        {
            this( e, true );
        }

        public HashEntry( AnyType e, boolean i )
        {
            element  = e;
            isActive = i;
        }
    }

    private static final int DEFAULT_TABLE_SIZE = 11;

    private HashEntry<AnyType> [ ] array; // The array of elements
    private int currentSize;              // The number of occupied cells

    /**
     * Internal method to allocate array.
     * @param arraySize the size of the array.
     */
    private void allocateArray( int arraySize )
    {
        array = new HashEntry[ nextPrime( arraySize ) ];
    }

    /**
     * Internal method to find a prime number at least as large as n.
     * @param n the starting number (must be positive).
     * @return a prime number larger than or equal to n.
     */
    private static int nextPrime( int n )
    {
        if( n % 2 == 0 )
            n++;

        for( ; !isPrime( n ); n += 2 )
            ;

        return n;
    }

    /**
     * Internal method to test if a number is prime.
     * Not an efficient algorithm.
     * @param n the number to test.
     * @return the result of the test.
     */
    private static boolean isPrime( int n )
    {
        if( n == 2 || n == 3 )
            return true;

        if( n == 1 || n % 2 == 0 )
            return false;

        for( int i = 3; i * i <= n; i += 2 )
            if( n % i == 0 )
                return false;

        return true;
    }


    // Simple main
    public static void main( String [ ] args )
    {
        QuadraticProbingHashTable<String> H = new QuadraticProbingHashTable<String>( );

        final int NUMS = 400000;
        final int GAP  =   37;

        System.out.println( "Checking... (no more output means success)" );


        for( int i = GAP; i != 0; i = ( i + GAP ) % NUMS )
            H.insert( ""+i );
        for( int i = 1; i < NUMS; i+= 2 )
            H.remove( ""+i );

        for( int i = 2; i < NUMS; i+=2 )
            if( !H.contains( ""+i ) )
                System.out.println( "Find fails " + i );

        for( int i = 1; i < NUMS; i+=2 )
        {
            if( H.contains( ""+i ) )
                System.out.println( "OOPS!!! " +  i  );
        }
    }

}

