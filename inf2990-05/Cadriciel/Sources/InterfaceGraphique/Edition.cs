///////////////////////////////////////////////////////////////////////////////
/// @file Edition.cs
/// @author Equipe 05
/// @date 2016-11-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using System.Threading;

/// <summary>
/// namespace InterfaceGraphique
/// </summary>

namespace InterfaceGraphique
{
    /// <summary>
    /// class Edition
    /// </summary>
    public partial class Edition : Form
    {

        //private static MenuPrincipal menu = new MenuPrincipal("edition");
        private Point clickInitial;
        private Point pointAvant;
        private bool clickSelection = false;
        private EtatEdition etat;
        private int valeurInitY;
        private const int zoomMax = 3;
        private const int zoomMin = -3;
        private int zoomInitial = 0;
        private bool estZoomIn = false;
        private static string zoneDeJeuEnregistrer_;

        public static bool enDeplacement = false;
        public static bool enEchelle = false;
        public static bool enRotation = false;
        public static bool enDuplication = false;
        public static bool enSelection = false;
        public static bool enZoom = false;
        public static bool enPause = false;
        public static bool modeTest = false;
        public static bool estOrbite = false;
        public static bool estAfficher = false;
        public static int butGauche = 0;
        public static int butDroit = 0;

        //public static int dernierX = 0, dernierY = 0;
        //public static double angleTheta=0.0, anglePhi =0.0;

        public static string ZoneDefaut = System.IO.Directory.GetCurrentDirectory() + "\\zones\\zoneDefaut.xml";
        string dossierZone = System.IO.Directory.GetCurrentDirectory() + "\\zones";
        string zoneCourante = "";
        public char[] temp = new char[200];

        private char toucheJeuEntrer;
        private Configuration c = Program.getNosConfiguration();
        private TournoiConfig t = Program.getNosTournoisConfiguration();
        
        private bool estJoueurHumain = false;
        private string nomJoueurVirtuel1 = "";
        private string nomJoueurVirtuel2 = "";
        private string nomJoueurVirtuel3 = "";
        private string nomJoueurVirtuel4 = "";
        Stopwatch chrono;

        private Point sourie = new Point();
        private Point sourieAvant = new Point(0,0);
        private bool hidePanel2 = true;

        private Point projetction3DRotation = Cursor.Position;

        bool estCliquer = false;

        Thread thread;
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn ToucheDirection
        ///
        /// enum ToucheDirection :
        /// sert à déterminer les touches appuyées par le joueur 2.
        ///
        ////////////////////////////////////////////////////////////////////////
        public enum ToucheDirection
        {
            HAUT = 1,
            BAS = 2,
            GAUCHE = 3,
            DROITE = 4,
            HAUTGAUCHE= 5,
            HAUTDROIT = 6,
            BASGAUCHE = 7,
            BASDROIT = 8
        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn EtatEdition
        ///
        /// enum EtatEdition :
        /// sert à déterminer dans quel état le système se situe.
        ///
        ////////////////////////////////////////////////////////////////////////
        enum EtatEdition
        {
            initial,
            ajoutBonus,
            ajoutMuret,
            ajoutPortail,
            ajoutPointsDeControle,
            deplacement,
            selection,
            selectionRectangulaire,
            deselection,
            miseAEchelle,
            supprimer,
            rotation,
            initialiserDuplication,
            duplication,
            zoom
        }
        /// <summary>
        /// Constructeur de la classe Edition.
        /// </summary>
        /// <param name="zoneDeJeu"></param>
        /// 

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn Edition()
        ///
        /// Constructeur de la classe Edition.
        ///
        ////////////////////////////////////////////////////////////////////////
        public Edition()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            this.Resize += new EventHandler(this.redimensionner);
            InitializeComponent();
            InitialiserAnimation();

            FonctionsNatives.estEdition();

            foreach (Control control in Controls)
            {
                control.KeyPress += new KeyPressEventHandler(this.ToucheEnfonce);
                control.MouseWheel += new MouseEventHandler(this.mouse_Wheel);
            }
            etat = EtatEdition.initial;

            this.ActiveControl = panel1;


            ///
            friction.Value = (decimal)FonctionsNatives.obtenirCoefficientFriction();
            acceleration.Value = (decimal)FonctionsNatives.obtenirAcceleration();
            rebond.Value = (decimal)FonctionsNatives.obtenirCoefficientRebond();
            ///

            File.SetAttributes(ZoneDefaut, FileAttributes.ReadOnly);
            openFileDialog1.InitialDirectory = dossierZone;
            saveFileDialog1.InitialDirectory = dossierZone;

            enregistrerToolStripMenuItem.Enabled = false;
            //chargement de la zone par defaut
            FonctionsNatives.restaurerZoneXml(ZoneDefaut);
            FonctionsNatives.afficherButs();
            zoneCourante = ZoneDefaut;

            FonctionsNatives.tuerMaillet();
            FonctionsNatives.tuerMailletOrdi();
            FonctionsNatives.tuerRondelle();
            

            chargerConfiguration();

            orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
            orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);

            panel2.Hide();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn chargerConfiguration()
        ///
        /// Fonction qui sert à charger la dernière configuration
        /// faite par le joueur.
        ///
        /// @return Rien
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chargerConfiguration()
        {
            estJoueurHumain = ! Program.configuration.EstJoueurVirtuel;//!c.EstJoueurVirtuel; //On charge les options

            //Console.WriteLine("estJoueurHumain = "+estJoueurHumain);
            int[] joueurVirtuel = new int[2];
            joueurVirtuel[0] = c.joueurVirtuelProfil.Vitesse;
            joueurVirtuel[1] = c.joueurVirtuelProfil.Passivite;
            FonctionsNatives.ConfigurationJoueurVirtuel(joueurVirtuel);
        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn InitialiserAnimation()
        ///
        /// Fonction qui sert à initialiser le openGl dans le panel1 de Edition.cs
        ///
        /// @return Rien
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.setOrbite(estOrbite);
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
            Application.Idle += Program.ExecuterQuandInactif;
        }
        

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void MettreAJour(double tempsInterAffichage)
        ///
        /// Fonction qui sert à mettre à jour les changements qui se sont produit dans le openGl.
        /// 
        /// param[in] : tempsInterAffichage
        ///
        /// @return Rien
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();
                });
            }
            catch (Exception)
            {
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ToucheEnfonce(Object o, KeyPressEventArgs e)
        ///
        /// Fonction qui sert à prendre en compte les entrées de l'utilisateur en tout temps.
        /// 
        /// param[in] : o
        /// param[in] : e : contient les informations des touches entrées claviers.
        ///
        /// @return Rien
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Space)
            {
                //System.Console.WriteLine("Barre d'espacement appuyée.");
                if (Program.estTournoi)
                {
                    if (Program.arbreTournoiConfig.Visible)
                        Program.arbreTournoiConfig.Hide();
                    FonctionsNatives.reinitialiserMaillet();
                    FonctionsNatives.reinitialiserMailletOrdi();
                    FonctionsNatives.reinitialiserRondelle();
                    chrono.Restart();
                    FonctionsNatives.butDroit(0);
                    FonctionsNatives.butGauche(0);
                }
                
                if (modeTest == true)
                {
                    FonctionsNatives.reinitialiserMaillet();
                    FonctionsNatives.reinitialiserMailletOrdi();
                    FonctionsNatives.reinitialiserRondelle();
                }

                if (Program.estPartieRapide == true)
                {
                    FonctionsNatives.reinitialiserMaillet();
                    FonctionsNatives.reinitialiserMailletOrdi();
                    FonctionsNatives.reinitialiserRondelle();
                    chrono.Restart();
                    FonctionsNatives.butDroit(0);
                    FonctionsNatives.butGauche(0);
                }

            }

            if (e.KeyChar == '+')
            {
                estZoomIn = true;
                zoomLimit();

               // FonctionsNatives.zoomIn();
            }

            if (e.KeyChar == '-')
            {
                estZoomIn = false;
                zoomLimit();
               // FonctionsNatives.zoomOut();
            }

            /* if(e.KeyChar == 't')
             {
                 modeTest = false;
                 enPause = false;

                 Program.peutAfficher = true;
                 panel2.Show();
                 toolStrip1.Show();
                 tableLayoutPanel1.Show();
                 tableLayoutPanel2.Show();
                 label1.Show();
                 menuStrip1.Show();
                 menuStrip2.Hide();
                 menuStrip3.Hide();
                 this.Text = "Mode d'édition";

                 FonctionsNatives.tuerRondelle();
                 FonctionsNatives.tuerMaillet();
                 FonctionsNatives.tuerMailletOrdi();
             }*/

            // Console.WriteLine($"Humain {estJoueurHumain}");

            estJoueurHumain = !Program.configuration.EstJoueurVirtuel;
            if (estJoueurHumain && (modeTest || Program.estPartieRapide) )
            {
                if (!enPause)
                {
                    toucheJeuEntrer = e.KeyChar;
                    if((e.KeyChar == c.ToucheHaut && e.KeyChar.Equals(c.ToucheGauche)))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.HAUTGAUCHE); }
                    else if(e.KeyChar == c.ToucheHaut && e.KeyChar.Equals(c.ToucheDroite))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.HAUTDROIT); }
                    else if ((e.KeyChar.Equals(c.ToucheBas) && e.KeyChar.Equals(c.ToucheGauche)))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.BASGAUCHE); }
                    else if (e.KeyChar.Equals(c.ToucheBas) && e.KeyChar.Equals(c.ToucheDroite))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.BASDROIT); }
                    else if (e.KeyChar == c.ToucheHaut)
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.HAUT); }
                    else if (e.KeyChar.Equals(c.ToucheBas))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.BAS); }
                    else if (e.KeyChar.Equals(c.ToucheGauche))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.GAUCHE); }
                    else if (e.KeyChar.Equals(c.ToucheDroite))
                    { FonctionsNatives.bougerMaillet((int)ToucheDirection.DROITE); }
                }
            }//else { LetsPlay(); }

        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void LetsPlay()
        ///
        /// Fonction qui est sur un thread séparer du thread principal.
        /// Ce thread est nommé : thread.
        /// Cette fonction sert à prendre en compte toutes les intéractions qui surviennent durant le jeu (Collision entre autre).
        ///
        /// @return Rien
        ///
        ////////////////////////////////////////////////////////////////////////
        private void LetsPlay()
        {
            //Console.WriteLine("Dans PLay");
            //Console.WriteLine("Est joueurVirtuel : "+Program.configuration.EstJoueurVirtuel);
            if (modeTest == true || Program.estPartieRapide || Program.estTournoi)
            {
                if (!enPause)
                {
                    int compteur = 1;
                    //nomJoueurVirtuel = c.joueurVirtuelProfil.Nom;
                    //FonctionsNatives.nomJoueurVirtuel(nomJoueurVirtuel);
                    chrono = Stopwatch.StartNew();
                    while (modeTest || Program.estPartieRapide || Program.estTournoi)
                    {
                        if (!enPause)
                        {
                            //  FonctionsNatives.deplacerMaillet(sourie.X, sourie.Y);
                            //Fonction pour que les rondelles bougents toujours meme lorsque l'utilisateur n'entre rien
                            try
                            {
                                FonctionsNatives.animationJeu();
                            }catch(System.AccessViolationException e) { Console.Error.WriteLine("animationJeu ne marche plus.\n"+e.GetBaseException());}
                            
                            chrono.Start();
                            FonctionsNatives.chrono(chrono.Elapsed.Minutes, chrono.Elapsed.Seconds);

                            if (FonctionsNatives.butCoteGauche())
                            {
                                butGauche += 1;
                                FonctionsNatives.butGauche(butGauche);
                                FonctionsNatives.nonButGauche();
                            }
                            else if (FonctionsNatives.butCoteGauche())
                            {
                                butDroit += 1;
                                FonctionsNatives.butDroit(butDroit);
                                FonctionsNatives.nonButDroit();
                            }

                            if (/*!estJoueurHumain ||*/ Program.configuration.EstJoueurVirtuel)
                            {
                                //Fonction pour le joueurVirtuel
                                //Console.WriteLine("dans zone virtuel");
                                FonctionsNatives.joueurVirtuel();
                            }
                            if (c.EstDebugLumiere)
                            {
                                //Afficher methode pour le debug de lumiere
                            }
                            if(c.EstDebugAttractionPortail)
                            {
                                //Afficher methode pour le debug de attraction portail
                            }
                            if(c.EstDebugCollision)
                            {
                                //Afficher methode pour le debug de Collision
                                string tempCollision;
                                if (FonctionsNatives.collisionBonus())
                                {
                                    tempCollision = c.afficherTemps() + " - Collision : BONUS";
                                    Console.WriteLine(tempCollision);
                                }

                                if(FonctionsNatives.collisionMailet())
                                {
                                    tempCollision = c.afficherTemps() + " - Collision : Maillet";
                                    Console.WriteLine(tempCollision);
                                }

                                if (FonctionsNatives.collisionMailetOrdi())
                                {
                                    tempCollision = c.afficherTemps() + " - Collision : Maillet";
                                    Console.WriteLine(tempCollision);
                                }

                                if (FonctionsNatives.collisionMuret())
                                {
                                    tempCollision = c.afficherTemps() + " - Collision : Muret";
                                    Console.WriteLine(tempCollision);
                                }

                                if (FonctionsNatives.collisionPortail())
                                {
                                    tempCollision = c.afficherTemps() + " - Collision : Portail";
                                    Console.WriteLine(tempCollision);
                                }

                                if (FonctionsNatives.collisionLimiteTable())
                                {
                                    tempCollision = c.afficherTemps() + " - Collision : limite table";
                                    Console.WriteLine(tempCollision);
                                }
                            }
                        }
                        else
                        {
                            chrono.Stop();
                            if (compteur == 1)
                            {
                                ++compteur;
                                //Implementation du code necessaire pour jouer
                                //Console.WriteLine("En pause.");
                            }
                        }
                    }
                }
            }
            if(thread != null)
                thread.Abort();

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void zoomLimit()
        ///
        /// Cette fonction sert à limiter le zoom qui est effectué par le nombre de fois d'affiler que l'on appuie sur le boutons '+' et '-'.
        /// Cela est fait à l'aide de 3 variables : zoomInitial, zoomMax et zoomMin.
        /// Les valeurs zoomMax et zoomMin  sont des constantes qui servent à limiter le nombre de fois que la varaible zoomInitial peut être incrémentée ou décrémentée.
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomLimit()
        {
            if (estZoomIn)
            {
                FonctionsNatives.zoomIn();
                ++zoomInitial;
            }

            if(! estZoomIn)
            {
                FonctionsNatives.zoomOut();
                --zoomInitial;
            }
               // Console.WriteLine("On ne peut pas zoomer plus! : "+ zoomInitial);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn override bool ProcessCmdKey(ref Message msg, Keys keyData)
        ///
        /// Cette fonction système de C# s'occupent elle aussi des entrées du clavié.
        /// Toutefois, on a assigné à celle-ci les touches que l'on peut entré durant un mode jeu ou teste.
        ///
        /// @param[in] msg
        /// @param[in] keyData : l'entrer au clavier.
        ///
        /// @return base.ProcessCmdKey(ref msg, keyData)
        ///
        ////////////////////////////////////////////////////////////////////////

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Up)
            {
                if (!estOrbite)
                   FonctionsNatives.deplacerXY(0.0, 0.001);
                else
                {
                    FonctionsNatives.rotaterXY(0.0, -1.5);
                    //System.Console.WriteLine("Up ok");
                }
            }
            if (keyData == Keys.Down)
            {
                if (!estOrbite)
                    FonctionsNatives.deplacerXY(0.0, -0.001);
			    else
			    {
                    FonctionsNatives.rotaterXY(0.0, 1.5);
                    //System.Console.WriteLine("Down ok");
                }
            }
            if (keyData == Keys.Left)
            {
                if (!estOrbite)
                    FonctionsNatives.deplacerXY(-0.001, 0.0);
                else
                {
                    FonctionsNatives.rotaterXY(-1.5, 0.0);
                    //System.Console.WriteLine("left ok");
                }
            }
            if (keyData == Keys.Right)
            {
                if (!estOrbite)
                    FonctionsNatives.deplacerXY(0.001, 0.0);
                else
                {
                    FonctionsNatives.rotaterXY(1.5, 0.0);
                    //System.Console.WriteLine("right ok");
                }
            }
            if (keyData == Keys.Escape)
            {
               // System.Console.WriteLine("pause mode test (Esc)");

                if (modeTest == true)
                {
                    if (!enPause) //pause
                    {
                        enPause = true;
                        this.menuStrip2.Show();
                        Program.peutAfficher = false;
                    }
                    else if (enPause) // pas en pause
                    {
                        enPause = false;
                        this.menuStrip2.Hide();
                        Program.peutAfficher = true;
                    }
                }

                if (Program.estPartieRapide)
                {
                    if (!enPause) //pause
                    {
                        enPause = true;
                        this.menuStrip3.Show();
                        Program.peutAfficher = false;
                        FonctionsNatives.dechargementSon();
                    }
                    else if (enPause) // pas en pause
                    {
                        enPause = false;
                        this.menuStrip3.Hide();
                        Program.peutAfficher = true;
                        FonctionsNatives.sonJeuF();
                    }
                }
                if (Program.estTournoi)
                {
                    if (!enPause) //pause
                    {
                        enPause = true;
                        this.menuStrip3.Show();
                        Program.peutAfficher = false;
                        FonctionsNatives.dechargementSon();
                    }
                    else if (enPause) // pas en pause
                    {
                        enPause = false;
                        this.menuStrip3.Hide();
                        Program.peutAfficher = true;
                        FonctionsNatives.sonJeuF();
                    }

                }
            }

            if(keyData == (Keys.Control | Keys.Q))
            {
                if(enPause || Program.estEdition)
                    revenirAuMenu();
                FonctionsNatives.dechargementSon();
            }

            if(Program.estPartieRapide || Program.estTournoi)
            {
                if (keyData == Keys.NumPad1 || keyData == Keys.D1)
                {
                    estOrbite = false;
                    FonctionsNatives.setOrbite(estOrbite);
                    orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
                    orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);
                }
                if (keyData == Keys.NumPad2 || keyData == Keys.D2)
                {
                    estOrbite = true;
                    FonctionsNatives.setOrbite(estOrbite);
                    orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Bold);
                    orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Regular);
                }
                if (keyData == Keys.J)
                {
                    ///Implementation pour Active / désactive la lumière ambiante.
                }
                if (keyData == Keys.K)
                {
                    ///Implementation pour Active / désactive la lumière directionnelle.
                }
                if (keyData == Keys.L)
                {
                    ///Implementation pour Active / désactive les spots.
                }
            }

            if (keyData == Keys.T && !Program.estPartieRapide && !Program.estTournoi)
            {
                if (!modeTest)
                {
                    passerEnModeTest(); /////NE MARCHE PAS CORRECTEMENT
                  modeTest = true;
                    this.Text = "Mode test";
                }
                else if(enPause)
                {
                    FonctionsNatives.pasModeTest();
                    enPause = false;
                    modeTest = false;
                    Program.estEdition = true;
                    Program.peutAfficher = true;
                    panel3.Show();
                    panel2.Hide();
                    toolStrip1.Show();
                    tableLayoutPanel1.Show();
                    tableLayoutPanel2.Show();
                    label1.Show();
                    menuStrip1.Show();
                    menuStrip2.Hide();
                    menuStrip3.Hide();
                    this.Text = "Mode d'édition";

                    FonctionsNatives.tuerRondelle();
                    FonctionsNatives.tuerMaillet();
                    FonctionsNatives.tuerMailletOrdi();
                }

            }

            if (!modeTest && !Program.estPartieRapide && !Program.estTournoi)
            {
                if(keyData == (Keys.Control | Keys.N))
                    FonctionsNatives.nouvelleScene();
                if (keyData == (Keys.Control | Keys.O))
                {
                    string name;
                    //repertoire de zone
                    if (openFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        name = openFileDialog1.FileName;
                        //System.Console.WriteLine(name);

                        if (name == "ZoneDefaut.xml")
                            enregistrerSousToolStripMenuItem.Enabled = false;

                        char[] array1 = new char[200];
                        for (int i = 0; i < (name.Length); i++)
                        {
                            array1[i] = name[i];
                        }
                        FonctionsNatives.restaurerZoneXml(name);
                        zoneCourante = name;
                    }
                }

                if (keyData == (Keys.Control | Keys.S))
                {
                    if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        string name = saveFileDialog1.FileName;
                        // System.Console.WriteLine(name);
                        //  System.Console.WriteLine("dans la fct");
                        char[] arr = new char[200];
                        for (int i = 0; i < (name.Length); i++)
                        {
                            arr[i] = name[i];
                        }
                        // System.Console.WriteLine(arr);
                        FonctionsNatives.sauvegarderZoneToXml(arr);
                        //fichierZoneCourant = String.Copy(name);
                    }
                }
                    if (keyData == Keys.Delete)
                {
                    FonctionsNatives.supprimer();
                }
                if (keyData == Keys.D)
                    etat = EtatEdition.deplacement;
                if (keyData == Keys.S)
                    etat = EtatEdition.selection;
                if (keyData == Keys.R)
                    etat = EtatEdition.rotation;
                if (keyData == Keys.E)
                    etat = EtatEdition.miseAEchelle;
                if (keyData == Keys.C)
                    etat = EtatEdition.duplication;
                if (keyData == Keys.Z)
                    etat = EtatEdition.zoom;
                if (keyData == Keys.M)
                    etat = EtatEdition.ajoutMuret;
                if (keyData == Keys.P)
                    etat = EtatEdition.ajoutPortail;
                if (keyData == Keys.B)
                    etat = EtatEdition.ajoutBonus;
                if (keyData == Keys.G)
                {
                    //etat = EtatEdition.ajoutPointsDeControle;

                    uncheckAllButton();
                    //TODO:
                    // Console.WriteLine("clique sur point de controle");
                    if (!estAfficher)
                    {
                        //Console.WriteLine("afficherPointsDeControle");
                        FonctionsNatives.afficherPointsDeControle();
                        estAfficher = true;
                    }
                    else
                    {
                        //Console.WriteLine("tuerPointsDeControle");
                        FonctionsNatives.tuerPointsDeControle();
                        estAfficher = false;
                    }
                }
                
                if (keyData == Keys.NumPad1 || keyData == Keys.D1)
                {
                    estOrbite = false;
                    FonctionsNatives.setOrbite(estOrbite);
                    orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
                    orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);
                }
                if (keyData == Keys.NumPad2 || keyData == Keys.D2)
                {
                    estOrbite = true;
                    FonctionsNatives.setOrbite(estOrbite);
                    orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Bold);
                    orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Regular);
                }

            }

            if (modeTest)
            {
                if (keyData == Keys.NumPad1 || keyData == Keys.D1)
                {
                    estOrbite = false;
                    FonctionsNatives.setOrbite(estOrbite);
                    orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
                    orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);
                }
                if (keyData == Keys.NumPad2 || keyData == Keys.D2)
                {
                    estOrbite = true;
                    FonctionsNatives.setOrbite(estOrbite);
                    orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Bold);
                    orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Regular);
                }
               /* if (keyData == Keys.T && modeTest)
                {
                    modeTest = false;
                    FonctionsNatives.pasModeTest();
                    enPause = false;

                    Program.peutAfficher = true;
                    panel3.Show();
                    panel2.Hide();
                    toolStrip1.Show();
                    tableLayoutPanel1.Show();
                    tableLayoutPanel2.Show();
                    label1.Show();
                    menuStrip1.Show();
                    menuStrip2.Hide();
                    menuStrip3.Hide();
                    this.Text = "Mode d'édition";

                    FonctionsNatives.tuerRondelle();
                    FonctionsNatives.tuerMaillet();
                    FonctionsNatives.tuerMailletOrdi();
                }*/
                if(keyData == Keys.J)
                {
                    ///Implementation pour Active / désactive la lumière ambiante.
                }
                if (keyData == Keys.K)
                {
                    ///Implementation pour Active / désactive la lumière directionnelle.
                }
                if (keyData == Keys.L)
                {
                    ///Implementation pour Active / désactive les spots.
                }
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Fonction du designer de C# qui réinitiale la scene du openGl comme elle était lors du début du teste ou du jeu,
        /// lorsque <para>nouveauToolStripMenuItem</para> est appuyé.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié au nouveauToolStripMenuItem.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //System.Console.WriteLine("Nouveau");
            FonctionsNatives.nouvelleScene();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Edition_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// Lorsqu'on appuie sur le X en haut à droite de l'interface, 
        /// cette fonction met la variable qui permet le openGl de se 
        /// renouveller à false et de fermer la fenêtre.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié au Edition_FormClosing.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Edition_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                //FonctionsNatives.libererOpenGL();
                //Program.peutAfficher = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction sert à ouvrir une fenêtre 
        /// qui permettra de visualisé les dossier XML 
        /// où les anciens environnement de jeu sauvegarder 
        /// se situent.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié au ouvrirToolStripMenuItem_Click.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        {

            string name;
            //repertoire de zone
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                name = openFileDialog1.FileName;
                //System.Console.WriteLine(name);

                if (name == "ZoneDefaut.xml")
                    enregistrerSousToolStripMenuItem.Enabled = false;

                char[] array1 = new char[200];
                for (int i = 0; i < (name.Length); i++)
                {
                    array1[i] = name[i];
                }
                FonctionsNatives.restaurerZoneXml(name);
                zoneCourante = name;
            }
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void auCliqueDeSourie(object sender, MouseEventArgs e)
        ///
        /// Methode servant a savoir si la sourie a ete 
        /// appuyer avec la gauche ou la droite et la position 
        /// du clique selon les coordonnées du Panel1.
        /// Dans le cas où la sourie est appuyée sur la droite, 
        /// le système ne fait rien.
        /// Dans le cas où la sourie est appuyée sur la gauche, 
        /// le système agit dépendament de l'état dans lequel il se situe.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a un MouseDown.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void auCliqueDeSourie(object sender, MouseEventArgs e)
        {
            
            //Console.Write("La souris a ete appuyee sur ");
            //bool estPartieRapide = Program.estPartieRapide;
            if (e.Button == MouseButtons.Left && modeTest == false)
            {
                estCliquer = true;
                if (Program.estEdition)
                {
                   // Program.peutAfficher = false;
                    clickInitial = new Point(e.X, e.Y);
                    pointAvant = this.clickInitial;
                    //FonctionsNatives.initialiserRectangle(clickInitial.X, clickInitial.Y);
                }

                switch (etat)
                {
                    case EtatEdition.initial:

                        //Console.WriteLine("etat initial");
                        break;

                    case EtatEdition.ajoutBonus:
                        //Console.WriteLine("etat ajout Bonus");
                        FonctionsNatives.ajouterNoeudBonus(e.X, e.Y);
                        break;

                    case EtatEdition.ajoutMuret:
                        //Console.WriteLine("etat ajout Muret");
                        FonctionsNatives.ajouterNoeudMuret(e.X, e.Y);
                        break;

                    case EtatEdition.ajoutPortail:
                        //Console.WriteLine("etat ajout Portail");
                        FonctionsNatives.ajouterNoeudPortail(e.X, e.Y);
                        break;

                    case EtatEdition.deplacement:
                        //Console.WriteLine("etat deplacement");
                        FonctionsNatives.initialiserDeplacement(e.X, e.Y);
                        enDeplacement = true;
                        break;

                    case EtatEdition.miseAEchelle:
                        //Console.WriteLine("etat mise a echelle");
                        valeurInitY = e.Y;
                        enEchelle = true;
                        break;

                    case EtatEdition.supprimer:
                        //Console.WriteLine("etat supprimer");
                        FonctionsNatives.supprimer();
                        break;

                    case EtatEdition.initialiserDuplication:
                        //Console.WriteLine("etat initialisation de la duplication");
                        FonctionsNatives.initialiserDuplication(e.X, e.Y);
                        etat = EtatEdition.duplication;
                        enDuplication = true;
                        break;


                    case EtatEdition.rotation:
                        //Console.WriteLine("etat rotation");
                        FonctionsNatives.initialiserRotation(e.Y);
                        enRotation = true;
                        break;

                    case EtatEdition.selection:
                        {
                            //Console.WriteLine("etat selection");
                            enSelection = true;
                            FonctionsNatives.selectionner(e.X, e.Y, enSelection);
                            try
                            {
                                if (FonctionsNatives.obtenirNombreObjetSelectionner() == 1)
                                {
                                    EntrerX1.Value = (int)FonctionsNatives.obtenirPosX();
                                    EntrerY1.Value = (int)FonctionsNatives.obtenirPosY();
                                    EntrerZ1.Value = (int)FonctionsNatives.obtenirPosZ();
                                    
                                   // EntrerMiseEchelle2.Value = (int)FonctionsNatives.obtenirEchelle();
                                   // EntrerRotation2.Value = (int)FonctionsNatives.obtenirRotation();
                                }
                                else
                                {
                                    EntrerX1.Value = 0;
                                    EntrerY1.Value = 0;
                                    EntrerZ1.Value = 0;
                                }
                            }
                            catch (System.OverflowException) { }
                            
                        }
                        break;

                    case EtatEdition.deselection:
                        {
                            //Console.WriteLine("etat deselection");
                            enSelection = false;
                            FonctionsNatives.deselectionnerTout();
                            //Console.WriteLine("enSelection");
                        }
                        break;

                    case EtatEdition.zoom:
                        //Console.WriteLine("etat zoom");
                        if (Program.peutAfficher)
                        {
                            
                            clickInitial = new Point(e.X, e.Y);
                            pointAvant = this.clickInitial;
                            enZoom = true;
                        }
                        break;
                }

            }

            //Console.WriteLine(" i : {0}, j : {1}\n", e.X, e.Y);
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void Edition_MouseMove(object sender, MouseEventArgs e)
        ///
        /// Fonction qui s'occupe de la rotation, le redimentionnement 
        /// et le déplacement des objets dans le openGL.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a un MouseMove.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Edition_MouseMove(object sender, MouseEventArgs e)
        {

            sourie.X = e.X;
            sourie.Y = e.Y;

            if (etat == EtatEdition.deplacement && enDeplacement)
            {
                FonctionsNatives.deplacement(e.X, e.Y);

                if (FonctionsNatives.obtenirNombreObjetSelectionner() == 1)
                {
                    EntrerX1.Value = (int)FonctionsNatives.obtenirPosX();
                    EntrerY1.Value = (int)FonctionsNatives.obtenirPosY();
                    EntrerZ1.Value = (int)FonctionsNatives.obtenirPosZ();
                }
            }

            if (modeTest == true || Program.estPartieRapide || Program.estTournoi)
            {
                FonctionsNatives.deplacerMaillet(e.X, e.Y);

            }

            if (e.Button == MouseButtons.Right && estOrbite)
            {

                //int dx = e.X - dernierX;
                //int dy = e.Y - dernierY;
                //angleTheta -= dx / 150.0;
                //anglePhi -= dy / 150.0; 

                int diffX = Cursor.Position.X - projetction3DRotation.X;

                if (projetction3DRotation.X > Cursor.Position.X)
                    FonctionsNatives.rotaterXY(0.99* diffX, 0.0);
                else if(projetction3DRotation.X < Cursor.Position.X)
                    FonctionsNatives.rotaterXY(0.99 * diffX, 0.0);

                int diffY = Cursor.Position.Y - projetction3DRotation.Y;

                if (projetction3DRotation.Y > Cursor.Position.Y)
                    FonctionsNatives.rotaterXY(0.0, 0.99 * diffY);
                else if (projetction3DRotation.Y < Cursor.Position.Y)
                    FonctionsNatives.rotaterXY(0.0, 0.99 * diffY);// -0.99);

                //dernierX = e.X;
                //dernierY = e.Y;
                //Console.WriteLine($" e.X : {e.X}, e.Y : {e.Y}\n");
                //Console.WriteLine($" cursor.X : {Cursor.Position.X}, cursor.Y : {Cursor.Position.Y}\n");

                
            }

            //Console.WriteLine(enSelection);
            if (etat == EtatEdition.miseAEchelle && enEchelle )
            {
                int deltaY = valeurInitY - e.Y;
                valeurInitY = e.Y;
                FonctionsNatives.miseAEchelle(deltaY);
                //Console.WriteLine("hey");
                //Console.WriteLine(deltaY);
            }

            if (etat == EtatEdition.rotation && enRotation)
            {
                // etat = EtatEdition.initial;
                FonctionsNatives.rotation(e.Y);
                //Console.WriteLine("oh");
            }

            //if (etat == EtatEdition.duplication && enDuplication)
            //{
            //    FonctionsNatives.duplication(e.X, e.Y);
            //    Console.WriteLine("hi");
            //    // etat = EtatEdition.initial;
            //}

            if (etat == EtatEdition.zoom && enZoom)
            {
                if ((e.X - this.clickInitial.X > 3 || this.clickInitial.X - e.X > 3) || (e.Y - this.clickInitial.Y > 3 || (this.clickInitial.Y - e.Y > 3))) //definition click
                    //FonctionsNatives.mettreAJourRectangle(clickInitial.X, clickInitial.Y, pointAvant.X, pointAvant.Y, e.X, e.Y, enSelection);
                //Console.WriteLine("checker");
                pointAvant = new Point(e.X, e.Y);
            }

            if (estCliquer && Program.estEdition)
                {
                    if (//clickSelection && 
                    ((e.X - this.clickInitial.X > 3 || this.clickInitial.X - e.X > 3) || (e.Y - this.clickInitial.Y > 3 || (this.clickInitial.Y - e.Y > 3)))) //definition click
                    {
                       // FonctionsNatives.mettreAJourRectangle(clickInitial.X, clickInitial.Y, pointAvant.X, pointAvant.Y, e.X, e.Y, enSelection);
                        //Console.WriteLine("\n\nmettreAJourRectangle\n\n");
                        pointAvant = new Point(e.X, e.Y);
                    }
                }

            
            projetction3DRotation.X = Cursor.Position.X;
            projetction3DRotation.Y = Cursor.Position.Y;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void auRelachementDeSourie(object sender, MouseEventArgs e)
        ///
        /// Methode servant a savoir si la sourie a 
        /// été relaché et la position du clique selon 
        /// les coordonnées du Panel1.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a un MouseUp.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void auRelachementDeSourie(object sender, MouseEventArgs e)
        {
            //if (etat == EtatEdition.initial)//****
            //{
            //    Console.Write("La sourie a relaché ");
            //    //panel1.MouseMove -= Edition_MouseMove;
            //    Console.Write(" i : {0}, j : {1}\n", e.X, e.Y);
            //    FonctionsNatives.terminerRectangle(clickInitial.X, clickInitial.Y, e.X, e.Y);
            //    Program.peutAfficher = true;
            //}

            if (etat == EtatEdition.zoom)
            {
                FonctionsNatives.terminerRectangle(clickInitial.X, clickInitial.Y, e.X, e.Y);

                Program.peutAfficher = true;
                enZoom = false;
            }
        
            if (etat == EtatEdition.selection)
            {
                clickSelection = false;
                
                //FonctionsNatives.terminerRectangle(clickInitial.X, clickInitial.Y, e.X, e.Y);
                etat = EtatEdition.selection;
            }

            if (etat == EtatEdition.selectionRectangulaire)
            {
                Program.peutAfficher = true;
                //FonctionsNatives.terminerRectangle(clickInitial.X, clickInitial.Y, e.X, e.Y);
            }

            if (estCliquer)
            {
                clickSelection = false;
               
                //FonctionsNatives.terminerRectangle(clickInitial.X, clickInitial.Y, e.X, e.Y);
                Program.peutAfficher = true;
            }

            enDeplacement = false;
            enEchelle = false;
            enRotation = false;
            enDuplication = false;
            estCliquer = false;
            Program.peutAfficher = true;
            //enSelection = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void mouse_Wheel(object sender, MouseEventArgs m)
        ///
        /// Fonction qui sert à donner une réponse au 
        /// programme lors que la roulette de la sourie est utilisée.
        /// C'est le zoom dans ce qu'à la qui est modifié.
        ///
        /// @param[in] sender
        /// @param[in] m : evenement lié a un mouse_Wheel.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mouse_Wheel(object sender, MouseEventArgs m)
        {
            if (m.Delta > 0)
            {
                estZoomIn = true;
                zoomLimit();
                // FonctionsNatives.zoomIn();
            }
            else
            {
                estZoomIn = false;
                zoomLimit();
                //FonctionsNatives.zoomOut();
            }
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void redimensionner(object sender, EventArgs e)
        ///
        /// Fonction qui fait en sort que le opengl se 
        /// redimensionne selon la nouvelle dimension de la fenêtre.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a la fenetre edition.cs.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueSélection(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode selection.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueSélection(object sender, EventArgs e)
        {
            //TODO:
            uncheckAllButton();
            etat = EtatEdition.selection;
            SelectionButton.CheckState = CheckState.Checked;
            //enSelection = true;
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueDeplacement(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode deplacement.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueDeplacement(object sender, EventArgs e)
        {
            //TODO:
            uncheckAllButton();
            etat = EtatEdition.deplacement;
            DeplacementButton.CheckState = CheckState.Checked;
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueRotation(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode rotation.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueRotation(object sender, EventArgs e)
        {
            //TODO:
            uncheckAllButton();
            etat = EtatEdition.rotation;
            RotationButton.CheckState = CheckState.Checked;
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void CliqueMiseEchelle(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode mise à 
        /// l'échelle.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CliqueMiseEchelle(object sender, EventArgs e)
        {
            //TODO:
            //etat = EtatEdition.miseAEchelle;
            uncheckAllButton();
            ScaleButton.CheckState = CheckState.Checked;
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueDuplication(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode duplication.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueDuplication(object sender, EventArgs e)
        {
            //TODO:
            uncheckAllButton();
            etat = EtatEdition.initialiserDuplication;
            DuplicationButton.CheckState = CheckState.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueZoom(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode zoom.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueZoom(object sender, EventArgs e)
        {
            //TODO:
            //FonctionsNatives.zoomIn();
            uncheckAllButton();
            etat = EtatEdition.zoom;
            toolStripButton6.CheckState = CheckState.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueAjoutAccelerateur(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode ajout bonus.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueAjoutAccelerateur(object sender, EventArgs e)
        {
            //TODO : ajouter accelerateur
            //Console.WriteLine("clique sur mur");
            //FonctionsNatives.ajouterNoeud("bonus", e.X, e.Y);
            uncheckAllButton();
            etat = EtatEdition.ajoutBonus;
            toolStripButton7.CheckState = CheckState.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueAjoutMur(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à mode ajout muret.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueAjoutMur(object sender, EventArgs e)
        {
            //TODO: Ajout Mur
            // Console.WriteLine("clique sur mur");
            uncheckAllButton();
            etat = EtatEdition.ajoutMuret;
            toolStripButton8.CheckState = CheckState.Checked;
        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueAjoutPortail(object sender, EventArgs e)
        ///
        /// Fonction qui modifie l'état du programme à ajout portail.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueAjoutPortail(object sender, EventArgs e)
        {
            //TODO:
            // Console.WriteLine("clique sur portail");
            uncheckAllButton();
            etat = EtatEdition.ajoutPortail;
            toolStripButton9.CheckState = CheckState.Checked;
        }
        

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn cliquePointControl(object sender, EventArgs e)
        ///
        /// Fonction qui sert à supprimer ou ajouter les 
        /// points de contrôle dépendament si on est en mode 
        /// teste ou non.
        ///
        /// @param[in] sender
        /// @param[in] e : evenement lié a des boutons.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliquePointControl(object sender, EventArgs e)
        {
            uncheckAllButton();
            //TODO:
            // Console.WriteLine("clique sur point de controle");
            if (!estAfficher)
            {
                //Console.WriteLine("afficherPointsDeControle");
                FonctionsNatives.afficherPointsDeControle();
                estAfficher = true;
            }
            else
            {
                //Console.WriteLine("tuerPointsDeControle");
                FonctionsNatives.tuerPointsDeControle();
                estAfficher = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void revenirAuMenu()
        ///
        /// Fonction qui sert à revenir au menu principal faite spécialement 
        /// pour le raccourcit Ctrl + Q.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void revenirAuMenu()
        {
            if(thread != null)
                thread.Abort();

            enPause = false;
            modeTest = false;
            Program.estPartieRapide = false;
            Program.estTournoi = false;
            Program.estEdition = false;
            FonctionsNatives.pasPartieRapide();

            FonctionsNatives.pasTournoi();

            if (Program.estPartieRapide == false)
            {
                FonctionsNatives.tuerMaillet();
                FonctionsNatives.tuerMailletOrdi();
                FonctionsNatives.tuerRondelle();
            }

            Program.fenetre = InterfaceGraphique.fenetre.Accueil;
            this.Hide();

            // Application.Exit();

            ////****
            modeTest = false;
            FonctionsNatives.pasModeTest();
            enPause = false;

            //Program.peutAfficher = true;
            panel3.Show();
            panel2.Hide();
            toolStrip1.Show();
            tableLayoutPanel1.Show();
            tableLayoutPanel2.Show();
            label1.Show();
            menuStrip1.Show();
            menuStrip2.Hide();
            menuStrip3.Hide();
            ////***
            Program.menu.Show();

            estOrbite = false;
            FonctionsNatives.setOrbite(estOrbite);
            orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
            orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);
        }

        /// <summary>
        /// Cette methode fait exactement la même chose que la fonction revenirAuMenu().
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void clickRevenirAuMenu(object sender, EventArgs e)
        ///
        /// Cette methode fait exactement la même chose que la fonction revenirAuMenu().
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void clickRevenirAuMenu(object sender, EventArgs e)
        {
            if(thread != null)
                thread.Abort();
            enPause = false;
            modeTest = false;
            Program.estPartieRapide = false;
            Program.estTournoi = false;
            Program.estEdition = false;
            FonctionsNatives.pasPartieRapide();
            FonctionsNatives.pasTournoi();
            FonctionsNatives.dechargementSon();

            if (Program.estPartieRapide == false)
            {
                FonctionsNatives.tuerMaillet();
                FonctionsNatives.tuerMailletOrdi();
                FonctionsNatives.tuerRondelle();
            }

            Program.fenetre = InterfaceGraphique.fenetre.Accueil;
            this.Hide();
            // Application.Exit();

            ////****
            modeTest = false;
            FonctionsNatives.pasModeTest();
            enPause = false;

            //Program.peutAfficher = true;
            panel3.Show();
            panel2.Hide();
            toolStrip1.Show();
            tableLayoutPanel1.Show();
            tableLayoutPanel2.Show();
            label1.Show();
            menuStrip1.Show();
            menuStrip2.Hide();
            menuStrip3.Hide();
            ////***
            Program.menu.Show();

            estOrbite = false;
            FonctionsNatives.setOrbite(estOrbite);
            orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
            orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert a surpprimée les objets sélectionnés
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("clique sur supprimer");
           // etat = EtatEdition.supprimer;
            FonctionsNatives.supprimer();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void miseALechelleToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert a modifier les dimensions des objets sélectionnés.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void miseALechelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etat = EtatEdition.miseAEchelle;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn double conversionStringADouble(String entrer)
        ///
        /// Cette methode sert a convertir un string en double et gérer les cas 
        /// où le string n'est pas un chiffre, mais un ensemble de charateres.
        /// 
        /// param[in] : entrer : Type : String
        /// 
        ///
        /// @return une valeur de type double si le string était un nombre.
        ///
        ////////////////////////////////////////////////////////////////////////
        private double conversionStringADouble(String entrer)
        {
            double nouvelleValeur;
            if (!double.TryParse(entrer, out nouvelleValeur))
            {
                //Console.WriteLine("Il ne s'agit pas d'un chiffre!");
                return 0.89576;
            }
            return nouvelleValeur;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueFriction(object sender, EventArgs e)
        ///
        /// Cette methode sert modifier la valeur de friction de la table et l'envoyé dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueFriction(object sender, EventArgs e)
        {
            double nouvelleFriction = conversionStringADouble(friction.Value.ToString());
            if (nouvelleFriction != 0.89576)
            {
                FonctionsNatives.modifierCoefficientFriction(nouvelleFriction);
               
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueAccelerateur(object sender, EventArgs e)
        ///
        /// Cette methode sert modifier la valeur de l'accélération 
        /// de la table et l'envoyé dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueAccelerateur(object sender, EventArgs e)
        {
            double nouvelleacceleration = conversionStringADouble(acceleration.Value.ToString());
            if (nouvelleacceleration != 0.89576)
            {
                FonctionsNatives.modifierAcceleration(nouvelleacceleration);
              
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void cliqueRebond(object sender, EventArgs e)
        ///
        /// Cette methode sert modifier la valeur de le facteur de rebond des 
        /// murets et limites de la table et l'envoyé dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cliqueRebond(object sender, EventArgs e)
        {
            double nouveauRebond = conversionStringADouble(rebond.Value.ToString());
            //if (nouveauRebond != 0.89576)
            //{
                FonctionsNatives.modifierCoefficientRebond(nouveauRebond);
               
            //}
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void entrerRotation(object sender, EventArgs e)
        ///
        /// Cette methode sert modifier la valeur de la rotation des objets 
        /// sélectionnés d'envoyés ces nouvelles valeurs dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void entrerRotation(object sender, EventArgs e)
        {
            double nouveauRotation = conversionStringADouble(EntrerRotation2.Value.ToString());
            if (nouveauRotation != 0.89576)
            {
                // FonctionsNatives.modifierCoefficientRebond(nouveauRotation);
               // labelFeedBack.Text = "Rotation : " + nouveauRotation + " °";
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void aideToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à faire apparaitre l'aide qui informe l'utilisateur 
        /// des différentes options qui lui sont possible d'Effectuer.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Aide aide = new Aide();
            aide.ShowDialog();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à enregister les modifications de la zone de 
        /// jeu qui sont faite en mode edition.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string name = saveFileDialog1.FileName;
               // System.Console.WriteLine(name);
              //  System.Console.WriteLine("dans la fct");
                char[] arr = new char[200];
                for (int i = 0; i < (name.Length); i++)
                {
                    arr[i] = name[i];
                }
               // System.Console.WriteLine(arr);
                FonctionsNatives.sauvegarderZoneToXml(arr);
                //fichierZoneCourant = String.Copy(name);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à enregister les modifications 
        /// qui sont faite en mode edition.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.sauvegarderZoneToXml(zoneCourante.ToCharArray());
        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void panel1_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à remettre le panel 1 comme étant le panel selectionner
        /// pour le jeu. Ainsi, on peut manipuler le joueur 1 même après avoir 
        /// sélectionné un textBox.
        /// 
        /// param[in] : sender
        /// param[in] : e : contient toutes les informations du clique.
        /// 
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel1_Click(object sender, EventArgs e)
        {
            this.ActiveControl = panel1;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void passerEnModeTest()
        ///
        /// Cette methode sert à passer au mode test pour tester notre zone de 
        /// jeu ainsi que les fonctionnalités qui fonctionnent ou non.
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void passerEnModeTest()
        {
            FonctionsNatives.deselectionnerTout();
            FonctionsNatives.estModeTest();
            enPause = false;
            Program.estEdition = false;
            Program.peutAfficher = true;
            panel2.Hide();
            panel3.Hide();
            toolStrip1.Hide();
            tableLayoutPanel1.Hide();
            tableLayoutPanel2.Hide();
            label1.Hide();
            menuStrip1.Hide();
            this.Text = "Mode Test";

            string sauvegarderModeTest = "sauvegarderModeTest.xml";
            sauvegarderModeTest += "\0";
            FonctionsNatives.sauvegarderZoneToXml(sauvegarderModeTest.ToCharArray());

            FonctionsNatives.genererMaillet();
            FonctionsNatives.genererMailletOrdi();
            FonctionsNatives.genererRondelle();
            FonctionsNatives.tuerPointsDeControle();


            //LetsPlay();
            thread = new Thread(new ThreadStart(LetsPlay));
            thread.Start();

            modeTest = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode qui sert à appeler la méthode passerEnModeTest() à partir d'un toolStripItem.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            passerEnModeTest();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void modeÉditionToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode qui sert à passer du mode test au mode edition.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void modeÉditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(thread != null)
                thread.Abort();
            modeTest = false;
            Program.estEdition = true;
            FonctionsNatives.pasModeTest();
            enPause = false;
         
            Program.peutAfficher = true;
            panel3.Show();
            panel2.Hide();
            toolStrip1.Show();
            tableLayoutPanel1.Show();
            tableLayoutPanel2.Show();
            label1.Show();
            menuStrip1.Show();
            menuStrip2.Hide();
            menuStrip3.Hide();
            this.Text = "Mode d'édition";

            FonctionsNatives.tuerRondelle();
            FonctionsNatives.tuerMaillet();
            FonctionsNatives.tuerMailletOrdi();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void entrerPositionX(object sender, EventArgs e)
        ///
        /// Cette methode sert à modifier la position en X d'un 
        /// seul objet sélectionné et de lui assigner cette 
        /// nouvelle position dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void entrerPositionX(object sender, EventArgs e)
        {
            double nouveauPositionX = conversionStringADouble(EntrerX1.Value.ToString());
            if (nouveauPositionX != 0.89576)
            {
                //FonctionsNatives.obtenirPosX();
                if(FonctionsNatives.obtenirNombreObjetSelectionner() == 1)
                    FonctionsNatives.assignerPosX(nouveauPositionX);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void entrerPositionY(object sender, EventArgs e)
        ///
        /// Cette methode sert à modifier la position en Y d'un 
        /// seul objet sélectionné et de lui assigner cette 
        /// nouvelle position dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void entrerPositionY(object sender, EventArgs e)
        {
            double nouveauPositionY = conversionStringADouble(EntrerY1.Value.ToString());
            if (nouveauPositionY != 0.89576)
            {
                // FonctionsNatives.modifierCoefficientRebond(nouveauRotation);
                FonctionsNatives.assignerPosY(nouveauPositionY);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void entrerPositionZ(object sender, EventArgs e)
        ///
        /// Cette methode sert à modifier la position en Z d'un 
        /// seul objet sélectionné et de lui assigner cette 
        /// nouvelle position dans le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void entrerPositionZ(object sender, EventArgs e)
        {
            double nouveauPositionZ = conversionStringADouble(EntrerZ1.Value.ToString());
            if (nouveauPositionZ != 0.89576)
            {
                // FonctionsNatives.modifierCoefficientRebond(nouveauRotation);
                FonctionsNatives.assignerPosZ(nouveauPositionZ);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void entrerEchelle(object sender, EventArgs e)
        ///
        /// Cette methode sert à modifier la valeur de la proportion de taille d'un 
        /// objet sélectionné et de lui assigner cette nouvelle position dans 
        /// le code natif.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void entrerEchelle(object sender, EventArgs e)
        {
            double nouvelleEchelle = conversionStringADouble(EntrerMiseEchelle2.Value.ToString());
            if (nouvelleEchelle != 0.89576)
            {
                // FonctionsNatives.modifierCoefficientRebond(nouveauRotation);
             
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à passer de la vue 3D à la vue 2D.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            estOrbite = false;
            FonctionsNatives.setOrbite(estOrbite);
            orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Bold);
            orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Regular);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à passer de la vue 2D à la vue 3D.
        /// 
        /// param[in] : sender
        /// param[in] : e
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            estOrbite = true;
            FonctionsNatives.setOrbite(estOrbite);
            orbiteToolStripMenuItem.Font = new Font(orbiteToolStripMenuItem.Font, FontStyle.Bold);
            orthographiqueToolStripMenuItem.Font = new Font(orthographiqueToolStripMenuItem.Font, FontStyle.Regular);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void uncheckAllButton()
        ///
        /// Cette methode sert à désactiver toutes les états dans 
        /// lequel le programme peut se situé.
        ///
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void uncheckAllButton()
        {
            SelectionButton.CheckState = CheckState.Unchecked;
            DeplacementButton.CheckState = CheckState.Unchecked;
            RotationButton.CheckState = CheckState.Unchecked;
            ScaleButton.CheckState = CheckState.Unchecked;
            DuplicationButton.CheckState = CheckState.Unchecked;
            toolStripButton6.CheckState = CheckState.Unchecked;
            toolStripButton7.CheckState = CheckState.Unchecked;
            toolStripButton8.CheckState = CheckState.Unchecked;
            toolStripButton9.CheckState = CheckState.Unchecked;
            toolStripButton10.CheckState = CheckState.Unchecked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void boutonAlterTable_Click(object sender, EventArgs e)
        ///
        /// Cette methode sert à cacher ou à montrer le menu de modification 
        /// possible au jeu et aux objets sélectionné.
        ///
        /// param[in] : sender
        /// param[in] : e
        /// 
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void boutonAlterTable_Click(object sender, EventArgs e)
        {
            hidePanel2 = ! hidePanel2;
            if (hidePanel2)
            {
                panel2.Hide();
                panel3.Show();
            }
            else
            {
                panel3.Hide();
                panel2.Show();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void modePartieRapideConfig()
        ///
        /// Cette methode sert à passer au mode de partie rapide.
        /// 
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void modePartieRapideConfig()
        {
            panel2.Hide();
            panel3.Hide();
            menuStrip1.Hide();
            toolStrip1.Hide();
            this.Text = "Partie Rapide";

            chargerConfiguration();
            zoneDeJeuEnregistrer_ = PartieRapideConfig.zoneDeJeuPartieRapide;

            if (PartieRapideConfig.defaut == true)
            {
                ZoneDefaut = System.IO.Directory.GetCurrentDirectory() + "\\zones\\zoneDefaut.xml";
                FonctionsNatives.restaurerZoneXml(ZoneDefaut);
                FonctionsNatives.afficherButs();
                FonctionsNatives.tuerMaillet();
                FonctionsNatives.tuerMailletOrdi();
                FonctionsNatives.tuerRondelle();
                FonctionsNatives.butDroit(0);
                FonctionsNatives.butGauche(0);
            }
            else
            {
                char[] arr = new char[200];
                for (int i = 0; i < (zoneDeJeuEnregistrer_.Length); i++)
                {
                    arr[i] = zoneDeJeuEnregistrer_[i];
                }
                FonctionsNatives.restaurerZoneXml(zoneDeJeuEnregistrer_);
                FonctionsNatives.afficherButs();
                FonctionsNatives.butDroit(0);
                FonctionsNatives.butGauche(0);
            }

            FonctionsNatives.genererMaillet();
            FonctionsNatives.genererMailletOrdi();
            FonctionsNatives.genererRondelle();

            thread = new Thread(new ThreadStart(LetsPlay));
            thread.Start();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void quitterModePartieConfig()
        ///
        /// Cette methode sert à passer du mode de partie rapide au menu principal.
        /// Elle est appelé dans la classe MenuPrincipal.
        /// 
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void quitterModePartieConfig()
        {
            Program.peutAfficher = true;
            panel2.Hide();
            panel3.Show();
            menuStrip1.Show();
            toolStrip1.Show();
            menuStrip3.Hide();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void modeTournoiConfig()
        ///
        /// Cette methode sert à passer du menu principal au mode tournoi.
        /// Elle est appelé dans la classe MenuPrincipal.
        /// 
        /// @return Rien.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void modeTournoiConfig()
        {
            panel2.Hide();
            panel3.Hide();
            menuStrip1.Hide();
            toolStrip1.Hide();
            this.Text = "Tournoi";

            chargerConfiguration();
            zoneDeJeuEnregistrer_ = TournoiConfig.zoneDeJeuTournoi;

            FonctionsNatives.estTournoi();

            nomJoueurVirtuel1 = t.getNomJoueur1();
            nomJoueurVirtuel2 = t.getNomJoueur2();
            nomJoueurVirtuel3 = t.getNomJoueur3();
            nomJoueurVirtuel4 = t.getNomJoueur4();
            FonctionsNatives.nomJoueurVirtuel1(nomJoueurVirtuel1);
            FonctionsNatives.nomJoueurVirtuel2(nomJoueurVirtuel2);
            FonctionsNatives.nomJoueurVirtuel3(nomJoueurVirtuel3);
            FonctionsNatives.nomJoueurVirtuel4(nomJoueurVirtuel4);

            if (TournoiConfig.defaut == true)
            {
                ZoneDefaut = System.IO.Directory.GetCurrentDirectory() + "\\zones\\zoneDefaut.xml";
                FonctionsNatives.restaurerZoneXml(ZoneDefaut);
                FonctionsNatives.afficherButs();
                FonctionsNatives.tuerMaillet();
                FonctionsNatives.tuerMailletOrdi();
                FonctionsNatives.tuerRondelle();
                FonctionsNatives.butDroit(0);
                FonctionsNatives.butGauche(0);
            }
            else
            {
                char[] arr = new char[200];
                for (int i = 0; i < (zoneDeJeuEnregistrer_.Length); i++)
                {
                    arr[i] = zoneDeJeuEnregistrer_[i];
                }
                FonctionsNatives.restaurerZoneXml(zoneDeJeuEnregistrer_);
                FonctionsNatives.afficherButs();
                FonctionsNatives.butDroit(0);
                FonctionsNatives.butGauche(0);
            }

            FonctionsNatives.genererMaillet();
            FonctionsNatives.genererMailletOrdi();
            FonctionsNatives.genererRondelle();

            thread = new Thread(new ThreadStart(LetsPlay));
            thread.Start();

        }

    }
    
    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn static partial class FonctionsNatives
    ///
    /// Classe servant à importer les méthodes du côté du code natif.
    /// 
    /// @return Rien.
    ///
    ////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserRectangle(int pX, int pY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mettreAJourRectangle(int piX, int piY, int paX, int paY, int pdX, int pdY, bool enSelection);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void terminerRectangle(int pIX, int pIY, int pFX, int pFY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int width, int height);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeudBonus(int posX, int posY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserDeplacement(double x, double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacement(double x, double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void miseAEchelle(double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimer();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeudMuret(int posX, int posY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeudPortail(int posX, int posY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void selectionner(int i, int j, bool estSelectionne);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserRotation(double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rotation(double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserDuplication(double x, double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void duplication(double x, double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerXY(double deplacementX, double deplacementY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void getFacteurEchelle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirCoefficientFriction();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modifierCoefficientFriction(double friction);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modifierAcceleration(double acceleration);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirAcceleration();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modifierCoefficientRebond(double rebond);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirCoefficientRebond();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void restaurerZoneXml([MarshalAs(UnmanagedType.LPStr)]string destination);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderZoneToXml(char[] destination);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nouvelleScene();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deselectionnerTout();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tuerMaillet();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tuerMailletOrdi();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tuerRondelle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void genererRondelle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void genererMaillet();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void genererMailletOrdi();

        //[DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void ajoutRondelleMaillet();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void bougerMaillet(int entrerUtilisateur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerMaillet(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animationJeu();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void joueurVirtuel();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ConfigurationJoueurVirtuel(int[] porfilJoueurVirtuel);

      //  [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
      //  public static extern void joueurUn(int xAvant, int yAvant, int xApres, int yApres);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reinitialiserMailletOrdi();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reinitialiserMaillet();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reinitialiserRondelle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool collisionBonus();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool collisionMailet();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool collisionMailetOrdi();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool collisionMuret();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool collisionPortail();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool collisionLimiteTable();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void afficherPointsDeControle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tuerPointsDeControle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]

        public static extern void rotaterXY(double rotationX, double rotationY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setOrbite(bool estOrbite);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void estPartieRapide();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void estTournoi();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void estEdition();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void estModeTest();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void pasPartieRapide();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void pasTournoi();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void pasEdition();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void pasModeTest();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chrono(int minutes, int secondes);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nomJoueurVirtuel1(string nomJoueurVirtuel1);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nomJoueurVirtuel2(string nomJoueurVirtuel2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nomJoueurVirtuel3(string nomJoueurVirtuel3);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nomJoueurVirtuel4(string nomJoueurVirtuel4);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void butGauche(int buts);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void butDroit(int buts);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPosX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPosY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPosZ();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreObjetSelectionner();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPosX(double x);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPosY(double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPosZ(double z);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerEchelle(double echelle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirEchelle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerRotation(double rot);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirRotation();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void afficherButs();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool butCoteGauche();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool butCoteDroit();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nonButGauche();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nonButDroit();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)] 
        public static extern void sonJeuF(); 
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)] 
        public static extern void dechargementSon();
        
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////