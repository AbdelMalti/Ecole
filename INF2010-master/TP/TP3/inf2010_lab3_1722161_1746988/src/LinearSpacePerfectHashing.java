
import java.util.Random;
import java.util.ArrayList;

public class LinearSpacePerfectHashing<AnyType>
{
   static int p = 46337;
   
   QuadraticSpacePerfectHashing<AnyType>[] data;
   int a, b;
   
   LinearSpacePerfectHashing()
   {
      a=b=0; 
      data = null;
   }
   
   LinearSpacePerfectHashing(ArrayList<AnyType> array)
   {
      AllocateMemory(array);
   }
   
   public void SetArray(ArrayList<AnyType> array)
   {
      AllocateMemory(array);
   }
      
   @SuppressWarnings("unchecked")
   private void AllocateMemory(ArrayList<AnyType> array)
   {
      Random generator = new Random( System.nanoTime() );
      
      if(array == null || array.size() == 0)
      {
         // A completer
    	  a = b = 0;
    	  data = null;
         return;
      }
      if(array.size() == 1)
      {
         a = b = 0;
         // A completer
         data = new QuadraticSpacePerfectHashing[1];
         data[0].SetArray(array);
	         return;
      }

      // A completer
      //la valeur de doit se situer entre 0 et p, mais ne doit pas etre egal a ces valeurs la.
      a = generator.nextInt(p-1)+1;
      //la valeur de b peut etre egal a 0 et/ou a p et a n'importe quelle valeur entre les 2.
      b = generator.nextInt(p);
      
      //Initialisation de data et de ces cases.
      data = new QuadraticSpacePerfectHashing[array.size()];
      for(int i=0; i<data.length; i++){
    	  data[i] = new QuadraticSpacePerfectHashing<AnyType>();
      }
      
      //premiere boucle afin d'avoir acces a chaque case du data[X]   
      for(int i=0; i< data.length; i++){
    	  //Nous avons remarqué que cette partie de code à été répété 
    	  //énormémant de fois dans cette méthode. Alors, nous l'avons 
    	  //mis dans une variable pur simplifier la lecture du code.
    	  int tailleData = ((a*array.get(i).hashCode()+b) % p) % data.length;
    	//Creation d'un tableau temporaire qui va stocker les nombres qui vont se situer dans la case data[X].
    	  ArrayList<AnyType> temp = new ArrayList<AnyType>();
    	  
    	  if(data[tailleData].equals(0)){
    		  temp.add(array.get(i));
    	  }
    	  
    	  else{
    		  for(int j=0; j < data[tailleData].Size(); j++){
    			  if(data[tailleData].items[j] != null){
    				  temp.add(data[tailleData].items[j]);
    			  }
    			  
    		  }
    		  temp.add(array.get(i));
    	  }
    	  data[tailleData].SetArray(temp);
      }
      
   }
   
   public int Size()
   {
      if( data == null ) 
    	  return 0;
      
      int size = 0;
      for(int i=0; i<data.length; ++i)
      {
         size += (data[i] == null ? 1 : data[i].Size());
      }
      return size;
   }
   
   public boolean contains(AnyType x )
   {
      if( Size() == 0 ) 
    	  return false;
      
      int m = data.length;
      
      int index = ( ( a*x.hashCode() + b ) % p ) % m;
      
      index = ( index < 0 ? index + m : index );
      
      return ((data[index] != null) && (data[index].contains(x)));
   }
}
