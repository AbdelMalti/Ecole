/**
 * Classe de pixel transparent
 * @author :
 * @date : 
 */

public class TransparentPixel extends AbstractPixel
{
	public int[] rgba; // donnees de l'image
	
	/**
	 * Constructeur par defaut (pixel blanc)
	 */
	TransparentPixel()
	{
		rgba = new int[4];
		rgba[0] = 255;
		rgba[1] = 255;
		rgba[2] = 255;
		rgba[3] = 255;
	}
	
	/**
	 * Assigne une valeur au pixel
	 * @param rgb: valeurs a assigner 
	 */
	TransparentPixel(int[] rgba)
	{
		this.rgba = new int[4];
		this.rgba[0] = rgba[0];
		this.rgba[1] = rgba[1];
		this.rgba[2] = rgba[2];
		this.rgba[3] = rgba[3]; //FAIT
	}
	
	/**
	 * Renvoie un pixel copie de type noir et blanc
	 */
	public BWPixel toBWPixel()
	{
		// compléter
		int r= rgba[0];
		int g= rgba[1];
		int b= rgba[2];
		int a= rgba[3];
		int moyenne = (r+g+b+a)/4;
		boolean pixelVal;
		if(moyenne >= 128){
			pixelVal = true;
		}
		else
			pixelVal = false;
		
		BWPixel bwp = new BWPixel(pixelVal); //FAIT
		return bwp;
		
	}
	
	/**
	 * Renvoie un pixel copie de type tons de gris
	 */
	public GrayPixel toGrayPixel()
	{
		// compléter
		int r= rgba[0];
		int g= rgba[1];
		int b= rgba[2];
		int a= rgba[3];
		int moyenne = (r+g+b+a)/4;
		int pixelVal = moyenne;
		GrayPixel gp = new GrayPixel(pixelVal); //FAIT
		return gp;
	}
	
	/**
	 * Renvoie un pixel copie de type couleurs
	 */
	public ColorPixel toColorPixel()
	{
		// compléter
		int rgb[] = new int[3];
		rgb[0] = rgba[0];
		rgb[1] = rgba[1];
		rgb[2] = rgba[2];
		ColorPixel cp = new ColorPixel(rgb); //FAIT
		return cp;
	}
	
	/**
	 * Renvoie le negatif du pixel (255-pixel)
	 */
	public TransparentPixel Negative()
	{
		// compléter
		int rgba[] = new int[4];
		rgba[0] = 255-this.rgba[0];
		rgba[1] = 255-this.rgba[1];
		rgba[2] = 255-this.rgba[2];
		rgba[3] = 255-this.rgba[3];
		return new TransparentPixel(rgba); //FAIT
	}
	
	public TransparentPixel toTransparentPixel()
	{
		// compléter
		return new TransparentPixel(rgba); //FAIT
	}
	
	public void setAlpha(int alpha)
	{
		rgba[3] = alpha;
	}
	
	/**
	 * Convertit le pixel en String (sert a ecrire dans un fichier 
	 * (avec un espace supplémentaire en fin)s
	 */
	public String toString()
	{
		return  ((Integer)rgba[0]).toString() + " " + 
				((Integer)rgba[1]).toString() + " " +
				((Integer)rgba[2]).toString() + " " +
				((Integer)rgba[3]).toString() + " ";
	}
}
