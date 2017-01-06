using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace InterfaceGraphique
{
    public partial class NouveauJoueurVirtuel : Form
    {

        Int32 r = 102;
        Int32 g = 0;
        Int32 b = 102;
        Int32 a = 150;


        Color onClick = new Color();

        Color groupeBoxColor = new Color();

        private Color colorBackgroundInitial;
        private Color colorLabelInitial;

        public struct JouerVirt
        {
            public string nom;
            public string vitesse;
            public string passivite;

        }
        public JouerVirt lejoueur;
  
        
        private string _nom;
        public string Nom
        {
            get
            {
                return _nom;
            }
            set
            {
                _nom = value;
            }
        }
        private int _passivite;
        public int Passivite
        {
            get
            {
                return _passivite;
            }
            set
            {
                _passivite = value;
            }
        }
        private int _vitesse;
        

        public int Vitesse
        {
            get
            {
                return _vitesse;
            }
            set
            {
                _vitesse = value;
            }
        }

        public NouveauJoueurVirtuel()
        {
            InitializeComponent();

            _nom = textBoxNom.Text;
            _passivite = trackBarPassivite.Value;
            _vitesse = trackBarVitesse.Value;
            Color noColor = new Color();
            noColor = Color.FromArgb(0, 0, 0, 0);
            panel1.BackColor = noColor;
        }

        public NouveauJoueurVirtuel(string nom, string passivite, string vitesse )
        {
            InitializeComponent();

            textBoxNom.Text = nom;
            labelPassivite.Text = passivite;
            labelVitesse.Text = vitesse;
            trackBarPassivite.Value = Convert.ToInt32(passivite);
            trackBarVitesse.Value = Convert.ToInt32(vitesse);
        }

        private void Enregistrer_nouveau_profil_virtuel()
        {
            ///Hermann
            lejoueur.nom = textBoxNom.Text;
            lejoueur.passivite = labelPassivite.Text;
            lejoueur.vitesse = labelVitesse.Text;
            string chemin = "Profils/" + lejoueur.nom;
            Serialise(lejoueur,chemin);
            MessageBox.Show("Votre profil ont ete sauvegarde avec succes");

            this.Hide();
           // NouveauJoueurVirtuel.f


        }

            private void Serialise(JouerVirt unJoueur,string nomProfil)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(JouerVirt));
            using (TextWriter writer = new System.IO.StreamWriter(nomProfil))
            {
                serializer.Serialize(writer, unJoueur);
            }

        }
        private void scrollBarPassivite(object sender, EventArgs e)
        {
            labelPassivite.Text = trackBarPassivite.Value.ToString();
        }

        private void scrollBarVitesse(object sender, EventArgs e)
        {
            labelVitesse.Text = trackBarVitesse.Value.ToString();
        }

        private void Enregistrer_Click(object sender, EventArgs e)
        {
            Enregistrer_nouveau_profil_virtuel();
        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }

        /*************************************************************/
        //Bouton enregistrer
        /*************************************************************/
        private void Enregistrer_MouseDown(object sender, MouseEventArgs e)
        {
            colorBackgroundInitial = Enregistrer.BackColor;
            colorLabelInitial = Enregistrer.ForeColor;

            onClick = Color.FromArgb(a, r, g, b);
            Enregistrer.BackColor = onClick;
            Enregistrer.ForeColor = Color.White;
        }

        private void Enregistrer_MouseUp(object sender, MouseEventArgs e)
        {
            Enregistrer.BackColor = colorBackgroundInitial;
            Enregistrer.ForeColor = colorLabelInitial;
        }
    }
     

}
