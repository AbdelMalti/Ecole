using System;

using System.Windows.Forms;
using System.Xml.Serialization;
using System.Xml;
using System.IO;
using System.Drawing;
using System.Threading;

namespace InterfaceGraphique
{
    public partial class TournoiConfig : Form
    {
        private static MenuPrincipal menu = new MenuPrincipal("tournoi configuration");
        string dossierZone = System.IO.Directory.GetCurrentDirectory() + "\\Profils";
        public static string zoneDeJeuTournoi = "";
        public static bool defaut = false;
        public const string fichierConfig = "tournoiconfig.xml";
        public static string nJoueur1;
        public static string nJoueur2;
        public static string nJoueur3;
        public static string nJoueur4;
        public bool quitter = false;
    
    public struct TournoiConfigs
    {
        public string Lejoueur1;
        public string Lejoueur1Text;
        public string Lejoueur2;
        public string Lejoueur2Text;
        public string Lejoueur3;
        public string Lejoueur3Text;
        public string Lejoueur4;
        public string Lejoueur4Text;
        public string ZoneJeu;
       
    }
        TournoiConfigs maConfig;

    public ArbreTournoiConfig arbre;
        

        public TournoiConfig()
        {
            InitializeComponent();
            humain1.Checked = true;
            humain2.Checked = true;
            humain3.Checked = true;
            humain4.Checked = true;
            text1.Text = "joueur1";
            text2.Text = "joueur2";
            text3.Text = "joueur3";
            text4.Text = "joueur4";
            defaut = true;
            bool load = chargerDerniereConfig();
            if (!load) maConfig = new TournoiConfigs();
            siAucunHumain();

            groupBoxJoueur.BackColor = Color.FromArgb(0, 0, 0, 0);

            groupBoxJoueur.BackColor = Color.FromArgb(255, 185, 209, 234);
        }

       

        public string getNomJoueur1() 
            {
            return nJoueur1;//text1.Text;
            }

        public string getNomJoueur2()
        {
            return nJoueur2;//text2.Text;
        }
        public string getNomJoueur3()
        {
            return nJoueur3;//text3.Text;
        }
        public string getNomJoueur4()
        {
            return nJoueur4;//text4.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            defaut = false;

            string name;
            //repertoire de zone
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                name = openFileDialog1.FileName;
                //System.Console.WriteLine(name);
                zoneDeJeuTournoi = name;
                string[] s = name.Split('\\');
                string p = s[s.Length - 1];
                //label5.Text = name;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            FonctionsNatives.pasTournoi();
            Program.fenetre = InterfaceGraphique.fenetre.Accueil;
            this.Hide();
            menu.Show();

        }

    
        

        private void humain1_CheckedChanged(object sender, EventArgs e)
        {
            text1.Text = "";
            text1.Enabled = true;
            demarrerTournoi.Enabled = true;
        }

        private void humain2_CheckedChanged(object sender, EventArgs e)
        {
            text2.Text = "";
            text2.Enabled = true;
            demarrerTournoi.Enabled = true;
        }

        private void humain3_CheckedChanged(object sender, EventArgs e)
        {
            text3.Text = "";
            text3.Enabled = true;
            demarrerTournoi.Enabled = true;
        }

        private void humain4_CheckedChanged(object sender, EventArgs e)
        {
            text4.Text = "";
            text4.Enabled = true;
            demarrerTournoi.Enabled = true;
        }
       
       
        private void demarrerTournoi_Click(object sender, EventArgs e)
        {
            Program.peutAfficher = true;
            //appeler fonction sauvegarder            
            /*************************************************************************************/
            maConfig.Lejoueur1 = humain1.Checked == true ? humain1.Text : virtuel1.Text;
            maConfig.Lejoueur1Text = text1.Text;
            maConfig.Lejoueur2 = humain2.Checked == true ? humain2.Text : virtuel2.Text;
            maConfig.Lejoueur2Text = text2.Text;
            maConfig.Lejoueur3 = humain3.Checked == true ? humain3.Text : virtuel3.Text;
            maConfig.Lejoueur3Text = text3.Text;
            maConfig.Lejoueur4 = humain4.Checked == true ? humain4.Text : virtuel4.Text;
            maConfig.Lejoueur4Text = text4.Text;
            //maConfig.ZoneJeu = label5.Text;
            saveDerniereConfig(maConfig);

            nJoueur1 = text1.Text;
            nJoueur2 = text2.Text;
            nJoueur3 = text3.Text;
            nJoueur4 = text4.Text;
            Program.arbreTournoiConfig = new ArbreTournoiConfig();
            Program.arbreTournoiConfig.Show();
               
            this.Hide();

            Program.estTournoi = true;
            //Program.estPartieRapide = true;
            Program.edition.modeTournoiConfig();
            Program.edition.Show();
            //Program.edition = null;
            FonctionsNatives.sonJeuF();

        }

        private void siAucunHumain()
        {
            //if (humain1.Checked || humain2.Checked || humain3.Checked || humain4.Checked)
            //{ demarrerTournoi.Enabled = true; }
            //else { demarrerTournoi.Enabled = false; }

            if (virtuel1.Checked && virtuel2.Checked && virtuel3.Checked && virtuel4.Checked)
            { demarrerTournoi.Enabled = false; }
            else { demarrerTournoi.Enabled = true; }
        }
       

        public void deserialiseXml(string nomProfil)
           {
            XmlSerializer deserializer = new XmlSerializer(typeof(NouveauJoueurVirtuel.JouerVirt));
            TextReader reader = new StreamReader(nomProfil);
            object objet = deserializer.Deserialize(reader);
            NouveauJoueurVirtuel.JouerVirt joueurVirt = (NouveauJoueurVirtuel.JouerVirt)objet;
            reader.Close();
            //  Console.WriteLine(joueurVirt.nom + joueurVirt.passivite + joueurVirt.vitesse);
            NouveauJoueurVirtuel joueurVirtuel = new NouveauJoueurVirtuel(joueurVirt.nom, joueurVirt.passivite, joueurVirt.vitesse);
           
          }

        public bool chargerDerniereConfig()
        {
            if (!File.Exists(fichierConfig))
                return false;

            XmlSerializer deserializer = new XmlSerializer(typeof(TournoiConfigs));
            TextReader reader = new StreamReader(fichierConfig);
            object objet = deserializer.Deserialize(reader);
            maConfig = (TournoiConfigs)objet;
            reader.Close();
            humain1.Checked = (humain1.Text == maConfig.Lejoueur1Text) ? true : false;
            if (humain1.Checked == false)
            {
                virtuel1.Checked = true;
          
                text1.Text = maConfig.Lejoueur1Text;
            }

            humain2.Checked = (humain2.Text == maConfig.Lejoueur2Text) ? true : false;
            if (humain2.Checked == false)
            {
                virtuel2.Checked = true;
                text2.Text = maConfig.Lejoueur2Text;
            }

            humain3.Checked = (humain3.Text == maConfig.Lejoueur3Text) ? true : false;
            if (humain3.Checked == false)
            {
                virtuel3.Checked = true;
                text3.Text = maConfig.Lejoueur3Text;
            }

            humain4.Checked = (humain4.Text == maConfig.Lejoueur4Text) ? true : false;
            if (humain4.Checked == false)
            {
                virtuel4.Checked = true;
                text4.Text = maConfig.Lejoueur4Text;
            }



            return true;
         
        }


        private void saveDerniereConfig(TournoiConfigs config)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(TournoiConfigs));
            using (TextWriter writer = new System.IO.StreamWriter(fichierConfig))
            {
                serializer.Serialize(writer, config);
            }

        }

        private void virtuel1_Click(object sender, EventArgs e)
        {
            text1.Enabled = false;
            if (humain1.Checked == false)
            {
                if (choixProfilV1.ShowDialog() == DialogResult.OK)
                {
                    string profil = choixProfilV1.FileName;
                    // System.Console.WriteLine(profil);
                    string[] s = profil.Split('\\');
                    string p = s[s.Length - 1];
                    deserialiseXml(profil);
                    text1.Text = p;
                }
            }

            siAucunHumain();
        }

        private void virtuel2_Click(object sender, EventArgs e)
        {
            text2.Enabled = false;
            if (humain2.Checked == false)
            {
                if (choixProfilV2.ShowDialog() == DialogResult.OK)
                {
                    string profil = choixProfilV2.FileName;
                    System.Console.WriteLine(profil);
                    string[] s = profil.Split('\\');
                    string p = s[s.Length - 1];
                    deserialiseXml(profil);
                    text2.Text = p;
                }
            }
            siAucunHumain();

        }

        private void virtuel3_Click(object sender, EventArgs e)
        {
            text3.Enabled = false;
            if (humain3.Checked == false)
            {
                if (choixProfilV3.ShowDialog() == DialogResult.OK)
                {
                    string profil = choixProfilV3.FileName;
                    System.Console.WriteLine(profil);
                    string[] s = profil.Split('\\');
                    string p = s[s.Length - 1];
                    deserialiseXml(profil);
                    text3.Text = p;
                }
            }
            siAucunHumain();
        }

        private void virtuel4_Click(object sender, EventArgs e)
        {

            text4.Enabled = false;
            siAucunHumain();
            if (humain4.Checked == false)
            {
                if (choixProfilV4.ShowDialog() == DialogResult.OK)
                {
                    string profil = choixProfilV4.FileName;
                    System.Console.WriteLine(profil);
                    string[] s = profil.Split('\\');
                    string p = s[s.Length - 1];
                    deserialiseXml(profil);
                    text4.Text = p;
                }
            }

            siAucunHumain();
        }

        private void TournoiConfig_Load(object sender, EventArgs e)
        {

        }

        //************************************************************************

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void parcourir_MouseDown(object sender, MouseEventArgs e)
        {
            parcourir.BackColor = Color.FromArgb(150, 102, 0, 102);
            parcourir.ForeColor = Color.White;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void parcourir_MouseUp(object sender, MouseEventArgs e)
        {
            parcourir.BackColor = Color.White; 
            parcourir.ForeColor = Color.FromArgb( 77, 0, 77);
        }

        private void entrerSourieSurJouer(object sender, EventArgs e)
        {
            Cursor = Cursors.No;

            if (demarrerTournoi.Enabled == true)
            {
                Cursor = Cursors.Hand;
                FonctionsNatives.estTournoi();
            }

            else if(demarrerTournoi.Enabled == false)
            {
                Cursor = Cursors.No;
            }
        }

        private void sortieSourieSurJouer(object sender, EventArgs e)
        {
            Cursor = Cursors.Arrow;
        }
    }
}

