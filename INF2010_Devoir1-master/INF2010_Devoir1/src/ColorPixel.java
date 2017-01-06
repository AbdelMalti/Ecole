/**
 * Classe de pixel en couleurs 
 * @author :
 * @date : 
 */

public class ColorPixel extends AbstractPixel
{
	public int[] rgb; // donnees de l'image
	
	/**
	 * Constructeur par defaut (pixel blanc)
	 */
	ColorPixel()
	{
		rgb = new int[3];
		rgb[0] = 255;
		rgb[1] = 255;
		rgb[2] = 255;
	}
	
	/**
	 * Assigne une valeur au pixel
	 * @param rgb: valeurs a assigner 
	 */
	ColorPixel(int[] rgb)
	{
		// compléter
		this.rgb = new int[3];
		this.rgb[0] = rgb[0];
		this.rgb[1] = rgb[1];
		this.rgb[2] = rgb[2];
	}
	
	/**
	 * Renvoie un pixel copie de type noir et blanc
	 */
	public BWPixel toBWPixel()
	{
		// compléter
		int r = rgb[0];
		int g = rgb[1];
		int b = rgb[2];
		int moyenne = (r+g+b)/3;
		boolean pixelVal;
		if(moyenne >= 128)
			pixelVal = true;
		else
			pixelVal = false;
		BWPixel bwp = new BWPixel(pixelVal); // FAIT
		return bwp;
	}
	
	/**
	 * Renvoie un pixel copie de type tons de gris
	 */
	public GrayPixel toGrayPixel()
	{
		// compléter
		int r = rgb[0];
		int g = rgb[1];
		int b = rgb[2];
		int moyenne = (r+g+b)/3;
		int pixelVal = moyenne;
		GrayPixel gp = new GrayPixel(pixelVal);
		return gp;
	}
	
	/**
	 * Renvoie un pixel copie de type couleurs
	 */
	public ColorPixel toColorPixel()
	{
		// compléter
		return new ColorPixel(this.rgb);
		
	}
	
	public TransparentPixel toTransparentPixel()
	{
		// compléter
		int[] rgba = new int[4];
		rgba[0] = this.rgb[0];
		rgba[1] = this.rgb[1];
		rgba[2] = this.rgb[2];
		rgba[3] = 255;
		TransparentPixel cp = new TransparentPixel(rgba);
		return cp;
	}
	
	/**
	 * Renvoie le negatif du pixel (255-pixel)
	 */
	public AbstractPixel Negative()
	{
		// compléter
		int[] rgb = new int[3];
		rgb[0] = 255 - this.rgb[0];
		rgb[1] = 255 - this.rgb[1];
		rgb[2] = 255 - this.rgb[2];
		return new ColorPixel(rgb);
		
	}
	
	public void setAlpha(int alpha)
	{
		//ne fait rien
	}
	
	/**
	 * Convertit le pixel en String (sert a ecrire dans un fichier 
	 * (avec un espace supplémentaire en fin)s
	 */
	public String toString()
	{
		return  ((Integer)rgb[0]).toString() + " " + 
				((Integer)rgb[1]).toString() + " " +
				((Integer)rgb[2]).toString() + " ";
	}
}