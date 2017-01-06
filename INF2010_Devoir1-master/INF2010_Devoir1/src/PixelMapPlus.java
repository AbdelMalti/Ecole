import java.awt.PageAttributes.ColorType;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;

/**
 * Classe PixelMapPlus
 * Image de type noir et blanc, tons de gris ou couleurs
 * Peut lire et ecrire des fichiers PNM
 * Implemente les methodes de ImageOperations
 * @author : 
 * @date   : 
 */

public class PixelMapPlus extends PixelMap implements ImageOperations 
{
	/**
	 * Constructeur creant l'image a partir d'un fichier
	 * @param fileName : Nom du fichier image
	 */
	PixelMapPlus(String fileName)
	{
		super( fileName );
	}
	
	/**
	 * Constructeur copie
	 * @param type : type de l'image a creer (BW/Gray/Color)
	 * @param image : source
	 */
	PixelMapPlus(PixelMap image)
	{
		super(image); 
	}
	
	/**
	 * Constructeur copie (sert a changer de format)
	 * @param type : type de l'image a creer (BW/Gray/Color)
	 * @param image : source
	 */
	PixelMapPlus(ImageType type, PixelMap image)
	{
		super(type, image); 
	}
	
	/**
	 * Constructeur servant a allouer la memoire de l'image
	 * @param type : type d'image (BW/Gray/Color)
	 * @param h : hauteur (height) de l'image 
	 * @param w : largeur (width) de l'image
	 */
	PixelMapPlus(ImageType type, int h, int w)
	{
		super(type, h, w);
	}
	
	/**
	 * Genere le negatif d'une image
	 */
	public void negate()
	{
		// compléter
		switch (imageType){
		//Cas image noir et blanc
		case BW:
			imageData = new BWPixel(); 
			break;
			
			//Cas Gray
		case Gray:
			break;
			
			//Case image couleur
		case Color:
			break;
			
			//Cas image transparent
		case Transparent:
			break;
		}
	}
	
	/**
	 * Convertit l'image vers une image en noir et blanc
	 */
	public void convertToBWImage()
	{
		// compléter
		super.toBWImage(); //fait
	}
	
	/**
	 * Convertit l'image vers un format de tons de gris
	 */
	public void convertToGrayImage()
	{
		// compléter
		super.toGrayImage(); //fait
	}
	
	/**
	 * Convertit l'image vers une image en couleurs
	 */
	public void convertToColorImage()
	{
		// compléter
		super.toColorImage(); //fait
	}
	
	public void convertToTransparentImage()
	{
		// compléter
		super.toTransparentImage(); //fait
	}
	
	/**
	 * Fait pivoter l'image de 10 degres autour du pixel (row,col)=(0, 0)
	 * dans le sens des aiguilles d'une montre (clockWise == true)
	 * ou dans le sens inverse des aiguilles d'une montre (clockWise == false).
	 * Les pixels vides sont blancs.
	 * @param clockWise : Direction de la rotation 
	 */
	public void rotate(int x, int y, double angleRadian)
	{
		// compléter
		AffineTransform image[][];

	}
	
	/**
	 * Modifie la longueur et la largeur de l'image 
	 * @param w : nouvelle largeur
	 * @param h : nouvelle hauteur
	 */
	public void resize(int w, int h) throws IllegalArgumentException
	{
		if(w < 0 || h < 0)
			throw new IllegalArgumentException();
		
		// compléter
		
		height = h; 
		width = w;
		imageData = new AbstractPixel[h][w];
	}
	
	/**
	 * Insert pm dans l'image a la position row0 col0
	 */
	public void inset(PixelMap pm, int row0, int col0)
	{
		// compléter  -  Fait
		for(int i=row0; i<pm.height ; i++){
			for(int j=col0; j<pm.width ; j++){
				imageData[i][j] = pm.imageData[i][j];
			}
		}
	}
	
	/**
	 * Decoupe l'image 
	 */
	public void crop(int h, int w)
	{
		// compléter		//Fait
		AbstractPixel[][] img = imageData;
		for(int i=0 ; i < h ; i++){
			for(int j=0 ; j < w ; j++){
				imageData[i][j] = img[i][j];
			}
		}
		img = null;
	}
	
	/**
	 * Effectue une translation de l'image 
	 */
	public void translate(int rowOffset, int colOffset)
	{
		// compléter	
		AbstractPixel[][] img = imageData;
		for(int i=0 ; i < height; i++){
			for(int j=0 ; j < width; j++){
				if(rowOffset+i < height && colOffset+j < width)
					imageData[rowOffset+i][colOffset+j] = img[i][j];
				else
					break;
			}
		}
	}
	
	/**
	 * Effectue un zoom autour du pixel (x,y) d'un facteur zoomFactor 
	 * @param x : colonne autour de laquelle le zoom sera effectue
	 * @param y : rangee autour de laquelle le zoom sera effectue  
	 * @param zoomFactor : facteur du zoom a effectuer. Doit etre superieur a 1
	 */
	public void zoomIn(int x, int y, double zoomFactor) throws IllegalArgumentException
	{
		if(zoomFactor < 1.0)
			throw new IllegalArgumentException();
		
		// compléter
		int tempHeight = height;
		int tempWidth = width;
		
		height *= zoomFactor;
		width *= zoomFactor;
		
		
		
	}
}
