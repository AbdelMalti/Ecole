using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Xml.Serialization;
using System.IO;
using System.Xml;


namespace InterfaceGraphique
{
    public partial class Configuration : Form
    {

        private static MenuPrincipal menu = new MenuPrincipal("edition");
        string dossierZone = System.IO.Directory.GetCurrentDirectory() ;
        public struct Touches
        {
            public string haut;
            public string bas;
            public string gauche;
            public string droit;
        }
        public struct Debogage
        {
            public bool collision;
            public bool lumiere;
            public bool attractionPortail;
        }
        public struct Config
        {
            public Touches uneTouche;
            public Debogage unDebogage;
            public int but;
            public string typeJoueur;
            public string niveau;
        }
        public Config maconfig;
        public Touches controles;
        public Debogage debogage;

        NouveauJoueurVirtuel joueurVirtuel = new NouveauJoueurVirtuel();
        public const string fichierConfigs = "config.xml";
        public NouveauJoueurVirtuel joueurVirtuelProfil
        {
            get { return joueurVirtuel; }
        }



        private bool _estJoueurVirtuel;
        public bool EstJoueurVirtuel
        {
            get { return _estJoueurVirtuel; }
            set { _estJoueurVirtuel = value; }
        }
        private bool _estDebugCollision;
        public bool EstDebugCollision
        {
            get { return _estDebugCollision; }
            set { _estDebugCollision = value; }
        }
        private bool _estDebugLumiere;
        public bool EstDebugLumiere
        {
            get { return _estDebugLumiere; }
            set { _estDebugLumiere = value; }
        }
        private bool _estDebugAttractionPortail;
        public bool EstDebugAttractionPortail
        {
            get { return _estDebugAttractionPortail; }
            set { _estDebugAttractionPortail = value; }
        }
        private bool _estJoueurVirtuelPersonnaliser;
        public bool EstJoueurVirtuelPersonnaliser
        {
            get
            {
                return _estJoueurVirtuelPersonnaliser;
            }
            set
            {
                _estJoueurVirtuelPersonnaliser = value;
            }
        }
        private char _toucheHaut;
        public char ToucheHaut
        {
            get { return _toucheHaut; }
            set { _toucheHaut = value; }
        }
        private char _toucheBas;
        public char ToucheBas
        {
            get { return _toucheBas; }
            set { _toucheBas = value; }
        }
        private char _toucheGauche;
        public char ToucheGauche
        {
            get { return _toucheGauche; }
            set { _toucheGauche = value; }
        }
        private char _toucheDroite;
        public char ToucheDroite
        {
            get { return _toucheDroite; }
            set { _toucheDroite = value; }
        }
        private int _nombreButGagnant;

        public Configuration()
        {
            InitializeComponent();

            _estJoueurVirtuel = true;
            _estDebugCollision = false;
            _estDebugLumiere = false;
            _estDebugAttractionPortail = false;
            _estJoueurVirtuelPersonnaliser = false;

            _toucheHaut = 'w';
            _toucheBas = 's';
            _toucheGauche = 'a';
            _toucheDroite = 'd';

            entrerToucheHaut.Text = "w";
            entrerToucheBas.Text = "s";
            entrerToucheGauche.Text = "a";
            entrerToucheDroite.Text = "d";


            _nombreButGagnant = 2;
            bool load = chargerDerniereConfig();
            if (!load) maconfig = new Config();



            NiveauJoueurVirtuel.Show();
            //groupBox3.Hide();

            Int32 r = 102;
            Int32 g = 0;
            Int32 b = 102;
            Int32 a = 0;

            Color groupeBoxColor = new Color();

            groupeBoxColor = Color.FromArgb(a, r, g, b);

            groupBox2.BackColor = groupeBoxColor;

            labelFeedBackConfig.Text = "FeedBack";
            sauvegarderToolStripMenuItem.Enabled = true;
            menuPrincipalToolStripMenuItem.Enabled = true;
        }

        public bool chargerDerniereConfig()
        {
            if (!File.Exists(fichierConfigs))
                return false;

            XmlSerializer deserializer = new XmlSerializer(typeof(Config));
            TextReader reader = new StreamReader(fichierConfigs);
            object objet = deserializer.Deserialize(reader);
            maconfig = (Config)objet;
            reader.Close();

            return true;
        }

        private void revenirMenu(object sender, EventArgs e)
        {
            maconfig.uneTouche.haut = entrerToucheHaut.Text;
            maconfig.uneTouche.bas = entrerToucheBas.Text;
            maconfig.uneTouche.gauche = entrerToucheGauche.Text;
            maconfig.uneTouche.droit = entrerToucheDroite.Text;

            maconfig.unDebogage.lumiere = checkBoxLumiere.Checked;
            maconfig.unDebogage.collision = checkBoxCollision.Checked;
            maconfig.unDebogage.attractionPortail = checkBoxAttractionPortail.Checked;


            maconfig.typeJoueur = radioButton_virtuel.Checked ? radioButton_virtuel.Text : radioButton_humain.Text;
            maconfig.but = Convert.ToInt32(numericButMax.Value);
            saveDerniereConfig1(maconfig);

            if (_toucheHaut != ' ' && _toucheBas != ' ' && _toucheGauche != ' ' && _toucheDroite != ' ')
            {
                Program.fenetre = InterfaceGraphique.fenetre.Accueil;
                this.Hide();

                Program.menu.Show();
                //Application.Exit();
            }else
            {
                avertissement av = new avertissement();
                av.ShowDialog();
            }
        }

        private void saveDerniereConfig1(Config maconfig)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Config));
            using (TextWriter writer = new System.IO.StreamWriter(fichierConfigs))
            {
                serializer.Serialize(writer, maconfig);
            }

        }


        private void checkCollision(object sender, EventArgs e)
        {
            _estDebugCollision = !_estDebugCollision;
        }

        private void checkLumiere(object sender, EventArgs e)
        {
            _estDebugLumiere = !_estDebugLumiere;
        }

        private void checkAttractionPortail(object sender, EventArgs e)
        {
            _estDebugAttractionPortail = !_estDebugAttractionPortail;
        }

        private void checkJoueurVirtuel(object sender, EventArgs e)
        {
            _estJoueurVirtuel = !_estJoueurVirtuel;
            Console.WriteLine("Dans Configuration estjoueurVirtuel : "+ _estJoueurVirtuel);
            //NiveauJoueurVirtuel.Enabled = _estJoueurVirtuel;

            //if (EstJoueurVirtuel)
            //{
            //    NiveauJoueurVirtuel.Show();
            //    groupBox3.Hide();
            //}
            //else
            //{
            //    NiveauJoueurVirtuel.Hide();
            //    groupBox3.Show();
            //}
        }
        private void checkJoueurPersonalise(object sender, EventArgs e)
        {
            _estJoueurVirtuelPersonnaliser = !_estJoueurVirtuelPersonnaliser;
            chargerbutton.Enabled = _estJoueurVirtuelPersonnaliser;
            Ajouter_nouveau_profil.Enabled = _estJoueurVirtuelPersonnaliser;
        }

        private void setButMaximal(object sender, EventArgs e)
        {
            _nombreButGagnant = (int)numericButMax.Value;
        }

        private void setToucheHaut(object sender, EventArgs e)
        {
            if (entrerToucheHaut.Text.Length == 0)
            {
                labelFeedBackConfig.Text = "Une entre est vide.";
                _toucheHaut = ' ';
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
                //entrerToucheHaut.Text = _toucheHaut.ToString();
            }

            else if (siToucheEstUneLettre(entrerToucheHaut.Text[0]))
            {
                if (verifierSiToucherEstDejaAssigner(entrerToucheHaut.Text[0]))
                {
                    _toucheHaut = entrerToucheHaut.Text[0];
                    entrerToucheHaut.BackColor = Color.White;
                    sauvegarderToolStripMenuItem.Enabled = true;
                    menuPrincipalToolStripMenuItem.Enabled = true;
                    labelFeedBackConfig.Text = $"{entrerToucheHaut.Text} a bien été assigné.";
                }
                else if (_toucheHaut == entrerToucheHaut.Text[0])
                {
                    //entrerToucheHaut.BackColor = Color.Red;
                    sauvegarderToolStripMenuItem.Enabled = false;
                    menuPrincipalToolStripMenuItem.Enabled = false;
                }
                
            }
            else
            {
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
                labelFeedBackConfig.Text = $"{entrerToucheHaut.Text} n'est pas une lettre.";
            }
        }

        private bool siToucheEstUneLettre(char lettre)
        {
            int encoding = (int)lettre;

            //Console.WriteLine($"lettre : {lettre} ; encoding {encoding}");
            if ((encoding > 64 && encoding < 91) || (encoding > 96 && encoding < 123))
                return true;
            else
            {
                //Ouvrir une boite de dialogue pour montrer l'erreur.
                return false;
            }
        }

        private void setToucheBas(object sender, EventArgs e)
        {
            if (entrerToucheBas.Text.Length == 0)
            {
                labelFeedBackConfig.Text = "Une entre est vide.";
                _toucheBas = ' ';
                //entrerToucheHaut.Text = _toucheHaut.ToString();
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
            }

            else if(siToucheEstUneLettre(entrerToucheBas.Text[0]))

            {
                if (verifierSiToucherEstDejaAssigner(entrerToucheBas.Text[0]))
                {
                    _toucheBas = entrerToucheBas.Text[0];
                    entrerToucheBas.BackColor = Color.White;
                    labelFeedBackConfig.Text = $"{entrerToucheBas.Text} a bien été assigné.";
                    sauvegarderToolStripMenuItem.Enabled = true;
                    menuPrincipalToolStripMenuItem.Enabled = true;
                }
                else if (_toucheBas != entrerToucheBas.Text[0])
                {
                    //entrerToucheBas.BackColor = Color.Red;
                    sauvegarderToolStripMenuItem.Enabled = false;
                    menuPrincipalToolStripMenuItem.Enabled = false;
                }
            }else
            {
                labelFeedBackConfig.Text = $"{entrerToucheBas.Text} n'est pas une lettre.";
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
            }
        }

        private void setToucheGauche(object sender, EventArgs e)
        {
            if (entrerToucheGauche.Text.Length == 0)
            {
                labelFeedBackConfig.Text = "Une entre est vide.";
                _toucheGauche = ' ';
                //entrerToucheHaut.Text = _toucheHaut.ToString();
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
            }

            else if (siToucheEstUneLettre(entrerToucheGauche.Text[0]))
            {
                if (verifierSiToucherEstDejaAssigner(entrerToucheGauche.Text[0]))
                {
                    _toucheGauche = entrerToucheGauche.Text[0];
                    entrerToucheGauche.BackColor = Color.White;
                    labelFeedBackConfig.Text = $"{entrerToucheGauche.Text} a bien été assigné.";
                    sauvegarderToolStripMenuItem.Enabled = true;
                    menuPrincipalToolStripMenuItem.Enabled = true;
                }
                else if (_toucheGauche != entrerToucheGauche.Text[0])
                {
                    //entrerToucheGauche.BackColor = Color.Red;
                    sauvegarderToolStripMenuItem.Enabled = false;
                    menuPrincipalToolStripMenuItem.Enabled = false;
                }
            }
            else
            {
                labelFeedBackConfig.Text = $"{entrerToucheGauche.Text} n'est pas une lettre.";
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
            }
        }

        private void setToucheDroite(object sender, EventArgs e)
        {
            if (entrerToucheDroite.Text.Length == 0)
            {
                labelFeedBackConfig.Text = "Une entre est vide.";
                _toucheDroite = ' ';
                //entrerToucheHaut.Text = _toucheHaut.ToString();
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
            }

            else if (siToucheEstUneLettre(entrerToucheDroite.Text[0]))
            {
                if (verifierSiToucherEstDejaAssigner(entrerToucheDroite.Text[0]))
                {
                    _toucheDroite = entrerToucheDroite.Text[0];
                    entrerToucheDroite.BackColor = Color.White;
                    labelFeedBackConfig.Text = $"{entrerToucheDroite.Text} a bien été assigné.";
                    sauvegarderToolStripMenuItem.Enabled = true;
                    menuPrincipalToolStripMenuItem.Enabled = true;
                }

                else if (_toucheDroite != entrerToucheDroite.Text[0])
                {
                    //entrerToucheDroite.BackColor = Color.Red;
                    sauvegarderToolStripMenuItem.Enabled = false;
                    menuPrincipalToolStripMenuItem.Enabled = false;
                }
            }
            else
            {
                labelFeedBackConfig.Text = $"{entrerToucheDroite.Text} n'est pas une lettre.";
                sauvegarderToolStripMenuItem.Enabled = false;
                menuPrincipalToolStripMenuItem.Enabled = false;
            }
        }
        /// <summary>
        /// Fonction servant à vérifier si une touche a déjà été entré plus d'une fois.
        /// </summary>
        /// <param name="nouvelleTouche"></param>
        /// <returns>boolean</returns>
        private bool verifierSiToucherEstDejaAssigner(char nouvelleTouche)
        {
            if (nouvelleTouche == _toucheHaut
                ||
              nouvelleTouche == _toucheBas
                ||
               nouvelleTouche == _toucheGauche
                ||
              nouvelleTouche == _toucheDroite)
            {
                labelFeedBackConfig.Text = $"{nouvelleTouche} est déjà assignié.";
                return false;
            }

            else
                return true;
        }
        /// <summary>
        /// Fonction qui remet tout les éléments à leur état initial sans exception.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void remettreDefault_Click(object sender, EventArgs e)
        {
            ///Variables du back-end
            _estJoueurVirtuel = true;

            _estDebugCollision = false;
            _estDebugLumiere = false;
            _estDebugAttractionPortail = false;

            _toucheHaut = 'w';
            _toucheBas = 's';
            _toucheGauche = 'a';
            _toucheDroite = 'd';

            _nombreButGagnant = 2;

            ///Variables du front-end
            NiveauJoueurVirtuel.Enabled = true;

            checkBoxCollision.CheckState = CheckState.Unchecked;
            checkBoxAttractionPortail.CheckState = CheckState.Unchecked;
            checkBoxLumiere.CheckState = CheckState.Unchecked;

            numericButMax.Value = 2;

            entrerToucheHaut.Text = "w";
            entrerToucheBas.Text = "s";
            entrerToucheGauche.Text = "a";
            entrerToucheDroite.Text = "d";

            entrerToucheHaut.BackColor = Color.White;
            entrerToucheBas.BackColor = Color.White;
            entrerToucheGauche.BackColor = Color.White;
            entrerToucheDroite.BackColor = Color.White;

            sauvegarderToolStripMenuItem.Enabled = true;
            menuPrincipalToolStripMenuItem.Enabled = true;

            radioButton_humain.Checked = false;
            radioButton_virtuel.Checked = true;
            _estJoueurVirtuel = true;

            //Console.WriteLine("Propriétés du jeu remis à leur valeur par default.");
            labelFeedBackConfig.Text = "Propriétés du jeu remis à leur valeur par default.";
        }

        /// <summary>
        /// Fonction qui renvoie l'heure a laquelle un 
        /// evenement s'est passer dans le format :
        /// HH : MM : SS.
        /// Cela est retourner sous forme de string.
        /// Il imprime a la console ce temps.
        /// </summary>
        /// <returns>temps[1]</returns>
        public string afficherTemps()
        {
            string[] temps = DateTime.Now.ToString().Split(' ');

            ///La fonction split() va nous permettre de prendre 
            ///uniquement la partie du temps qui nous interesse.
            ///
            ///temps[0] = DD/MM/AAAA
            ///temps[1] = HH:MM:SS

            //Console.WriteLine(temps[1]);
            return temps[1];
        }
        /// <summary>
        /// Fonction qui sert à sauvegarder les informations du joueur virtuel
        /// creer par l'utilisateur.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void sauvegarderJoueurVitruel(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string name = saveFileDialog1.FileName;
                enregistrementConfig(name);
                MessageBox.Show("Enregistrement effectue avec succes");
            }

        }      
        private void saveDerniereConfig(Config config)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Config));
            using (TextWriter writer = new System.IO.StreamWriter(fichierConfigs))
            {
                serializer.Serialize(writer, config);
            }

        }
        /// <summary>
        /// Fonction servant à enregistrer les modifications apporter dans
        /// l'onglet configuration.
        /// </summary>
        /// <param name="chemin"></param>
        private void enregistrementConfig(string chemin){
                maconfig.uneTouche.haut = entrerToucheHaut.Text;
                maconfig.uneTouche.bas = entrerToucheBas.Text;
                maconfig.uneTouche.gauche = entrerToucheGauche.Text;
                maconfig.uneTouche.droit = entrerToucheDroite.Text;

                maconfig.unDebogage.lumiere = checkBoxLumiere.Checked;
                maconfig.unDebogage.collision = checkBoxCollision.Checked;
                maconfig.unDebogage.attractionPortail = checkBoxAttractionPortail.Checked;


                maconfig.typeJoueur = radioButton_virtuel.Checked ? radioButton_virtuel.Text : radioButton_humain.Text;
                maconfig.but = Convert.ToInt32(numericButMax.Value);
                //maconfig.niveau = (NiveauJoueurVirtuel.Controls.OfType<RadioButton>().FirstOrDefault(r => r.Checked)).Text;
                Serialise(maconfig,chemin);
        }
            

        private void Serialise(Config maconfig,string chemin)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Config));
            using (TextWriter writer = new System.IO.StreamWriter(chemin))
            {
                serializer.Serialize(writer, maconfig);
            }

        }

        private void ajouter_nouveau_joueur(object sender, EventArgs e)
        {
            joueurVirtuel.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string profil = openFileDialog1.FileName;            
                deserialiseXml(profil);            }
        }

        public void deserialiseXml(string nomProfil)
        {
            XmlSerializer deserializer = new XmlSerializer(typeof(NouveauJoueurVirtuel.JouerVirt));
            TextReader reader = new StreamReader(nomProfil);
            object objet = deserializer.Deserialize(reader);
            NouveauJoueurVirtuel.JouerVirt joueurVirt = (NouveauJoueurVirtuel.JouerVirt)objet;
            reader.Close();
          //  Console.WriteLine(joueurVirt.nom + joueurVirt.passivite + joueurVirt.vitesse);
            NouveauJoueurVirtuel joueurVirtuel = new NouveauJoueurVirtuel(joueurVirt.nom,joueurVirt.passivite,joueurVirt.vitesse);
            joueurVirtuel.Show();
        }

        private void revenirAuConfigurationDePartieRapideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Program.fenetre = InterfaceGraphique.fenetre.PartieRapideConfig;
            this.Hide();
            Program.partieRapideConfig.Show();
        }

        private void radioButton_humain_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void remettreDefault_MouseDown(object sender, MouseEventArgs e)
        {
            remettreDefault.BackColor = Color.FromArgb(150, 102, 0, 102);
            remettreDefault.ForeColor = Color.White;
        }

        private void remettreDefault_MouseUp(object sender, MouseEventArgs e)
        {
            remettreDefault.ForeColor = Color.FromArgb(77, 0, 77);
            remettreDefault.BackColor = Color.White;
        }


        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (labelFeedBackConfig.Text != "Une entre est vide.")
            {
                if (keyData == (Keys.Control | Keys.Q))
                {
                    Program.fenetre = InterfaceGraphique.fenetre.Accueil;
                    this.Hide();
                    menu.Show();
                }

                if (keyData == (Keys.Control | Keys.S))
                {
                    if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        string name = saveFileDialog1.FileName;
                        enregistrementConfig(name);
                        MessageBox.Show("Enregistrement effectue avec succes");
                    }
                }
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }


    }

}
