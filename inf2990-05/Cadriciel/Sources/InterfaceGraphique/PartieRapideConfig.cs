using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieRapideConfig : Form
    {
        private static MenuPrincipal menu = new MenuPrincipal("partie rapide configuration");
        string dossierZone = System.IO.Directory.GetCurrentDirectory() + "\\zones";
        public static string zoneDeJeuPartieRapide = "";
        public static bool defaut = false;

        public PartieRapideConfig()
        {
            InitializeComponent();
            defaut = true;
            openFileDialog1.InitialDirectory = dossierZone;
        }

        private void menuPrincipal_Click(object sender, EventArgs e)
        {
            Program.fenetre = InterfaceGraphique.fenetre.Accueil;
            this.Hide();
            menu.Show();
        }

        private void annuler_Click(object sender, EventArgs e)
        {
            Program.fenetre = InterfaceGraphique.fenetre.Accueil;
            this.Hide();
            menu.Show();
        }

        private void demarrer_Click(object sender, EventArgs e)
        {
            Program.peutAfficher = true;
            this.Hide();
            //Program.edition = new Edition(zoneDeJeu);
            FonctionsNatives.estPartieRapide();
            Program.edition.Width = Program.edition.Width + 1;
            Program.edition.Height = Program.edition.Height + 1;

            //Program.edition.ShowDialog();
            Program.edition.modePartieRapideConfig();
            Program.edition.Show();
            //Program.edition.quitterModePartieConfig();
            FonctionsNatives.sonJeuF();
        }

        private void modifConfig_Click(object sender, EventArgs e)
        {
            Configuration configuration = Program.getNosConfiguration();
            configuration.ShowDialog();
        }

        private void parcourir_Click(object sender, EventArgs e)
        {
            defaut = false;

            string name;
            //repertoire de zone
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                name = openFileDialog1.FileName;
                //System.Console.WriteLine(name);
                zoneDeJeuPartieRapide = name;
            }
        }
    }
}
