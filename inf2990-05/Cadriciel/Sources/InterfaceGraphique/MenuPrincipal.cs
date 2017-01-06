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
    public partial class MenuPrincipal : Form
    {
        Color[] colorBackgroundInitial = new Color[5];
        Color[] colorLabelInitial = new Color[5];

        Int32 r = 102;
        Int32 g = 0;
        Int32 b = 102;
        Int32 a = 150;


        Color onClick = new Color();

        Color groupeBoxColor = new Color();

        /*********************************************/

        public MenuPrincipal(string fenetre)
        {
            InitializeComponent();
            fenetre_ = fenetre;

            groupeBoxColor = Color.FromArgb(100, 255, 255, 255);
            groupBoxBouton.BackColor = groupeBoxColor;

        }
        
        public string fenetre
        {
            get { return fenetre_; }
            set { fenetre_ = value; }
        }

        private void EditButton_Click(object sender, EventArgs e)
        {
            Program.edition.quitterModePartieConfig();

            Program.estEdition = true;
            Program.estTournoi = false;
            Program.estPartieRapide = false;
            Program.fenetre = InterfaceGraphique.fenetre.Edition;
            fenetre_ = "edition";
            this.Hide();
            Program.edition.Show();
            Program.edition.Text = "Mode d'édition";
            //Program.magie = false;
            //Application.Exit();
        }

        private void PartieRapideButton_Click(object sender, EventArgs e)
        {
            Program.estEdition = false;
            Program.estTournoi = false;
            Program.estPartieRapide = true;
            Program.fenetre = InterfaceGraphique.fenetre.PartieRapideConfig;
            fenetre_ = "partie rapide";
            this.Hide();

            Program.partieRapideConfig.Show();
        }

        private void QuitterButton_Click(object sender, EventArgs e)
        {
            Program.fenetre = InterfaceGraphique.fenetre.Quitter;
            fenetre_ = "quitter";
            Application.Exit();
        }


        //Attributs
        private static string fenetre_;

        private void ConfigButton_Click(object sender, EventArgs e)
        {
            Program.fenetre = InterfaceGraphique.fenetre.Configuration;
            fenetre_ = "configuration";
            this.Hide();
            Program.configuration.menuStrip1.Show();
            Program.configuration.menuStrip2.Hide();
            Program.configuration.Show();
        }

        

        private void TournoiButton_Click(object sender, EventArgs e)
        {
            Program.estEdition = false;
            Program.estTournoi = true;
            Program.estPartieRapide = false;
            Program.fenetre = InterfaceGraphique.fenetre.TournoiConfig;
            fenetre_ = "tournoi";
            this.Hide();
            Program.tournoiConfig.Show();
            // Application.Exit();
        }

        /************************************************************/
        //Bouton Partie Rapide
        /************************************************************/
        private void PartieRapideButton_MouseDown(object sender, MouseEventArgs e)
        {
            colorBackgroundInitial[0] = PartieRapideButton.BackColor;
            colorLabelInitial[0] = PartieRapideButton.ForeColor;
        
            onClick = Color.FromArgb(a,r,g,b);
            PartieRapideButton.BackColor = onClick;
            PartieRapideButton.ForeColor = Color.White;

            //MenuPrincipal.ActiveForm.BackgroundImage 
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.partieRapideImage;
            }
            catch { Console.WriteLine("configurationImageFond not found"); }
        }

        private void PartieRapideButton_MouseUp(object sender, MouseEventArgs e)
        {
            PartieRapideButton.BackColor = colorBackgroundInitial[0];
            PartieRapideButton.ForeColor = colorLabelInitial[0];
        }

        private void PartieRapideButton_MouseEnter(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.partieRapideImage;
            }
            catch { Console.WriteLine("configurationImageFond not found"); }
                
        }

        private void PartieRapideButton_MouseLeave(object sender, EventArgs e)
        {
            try
            {
               BackgroundImage = Properties.Resources.Background;
            }
            catch { Console.WriteLine("Background not found"); }
            
        }
        /*****************************************************************/

        /************************************************************/
        //Bouton Tournoi
        /************************************************************/
        private void TournoiButton_MouseDown(object sender, MouseEventArgs e)
        {
            colorBackgroundInitial[1] = TournoiButton.BackColor;
            colorLabelInitial[1] = TournoiButton.ForeColor;

            onClick = Color.FromArgb(a, r, g, b);
            TournoiButton.BackColor = onClick;
            TournoiButton.ForeColor = Color.White;

            //MenuPrincipal.ActiveForm.BackgroundImage 
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.stanleyCup;
            }
            catch { Console.WriteLine("stanleyCup.jpeg not found"); }
        }

        private void TournoiButton_MouseUp(object sender, MouseEventArgs e)
        {
            TournoiButton.BackColor = colorBackgroundInitial[1];
            TournoiButton.ForeColor = colorLabelInitial[1];
        }

        private void TournoiButton_MouseEnter(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.stanleyCup;
            }
            catch { Console.WriteLine("stanleyCup.jpeg not found"); }
        }

        private void TournoiButton_MouseLeave(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = Properties.Resources.Background;
            }
            catch { Console.WriteLine("Background not found"); }
        }


        /*****************************************************************/

        /************************************************************/
        //Bouton Configuration
        /************************************************************/
        private void ConfigButton_MouseDown(object sender, MouseEventArgs e)
        {
            colorBackgroundInitial[2] = ConfigButton.BackColor;
            colorLabelInitial[2] = ConfigButton.ForeColor;

            onClick = Color.FromArgb(a, r, g, b);
            ConfigButton.BackColor = onClick;
            ConfigButton.ForeColor = Color.White;

            //MenuPrincipal.ActiveForm.BackgroundImage 
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.configurationIconpre;
            }
            catch { Console.WriteLine("configurationImageFond not found"); }
        }

        private void ConfigButton_MouseUp(object sender, MouseEventArgs e)
        {
            ConfigButton.BackColor = colorBackgroundInitial[2];
            ConfigButton.ForeColor = colorLabelInitial[2];
        }

        private void ConfigButton_MouseEnter(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.configurationIconpre;
            }
            catch { Console.WriteLine("configurationImageFond not found"); }
        }

        private void ConfigButton_MouseLeave(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = Properties.Resources.Background;
            }
            catch { Console.WriteLine("Background not found"); }
        }
        
        /*****************************************************************/

        /************************************************************/
        //Bouton Edition
        /************************************************************/
        private void EditButton_MouseDown(object sender, MouseEventArgs e)
        {
            colorBackgroundInitial[3] = PartieRapideButton.BackColor;
            colorLabelInitial[3] = PartieRapideButton.ForeColor;

            onClick = Color.FromArgb(a, r, g, b);
            EditButton.BackColor = onClick;
            EditButton.ForeColor = Color.White;

            //MenuPrincipal.ActiveForm.BackgroundImage 
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.editionTactique;
            }
            catch { Console.WriteLine("configurationIconpre not found"); }
        }

        private void EditButton_MouseUp(object sender, MouseEventArgs e)
        {
            EditButton.BackColor = colorBackgroundInitial[3];
            EditButton.ForeColor = colorLabelInitial[3];
        }

        private void EditButton_MouseEnter(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.editionTactique;
            }
            catch { Console.WriteLine("configurationIconpre not found"); }
        }

        private void EditButton_MouseLeave(object sender, EventArgs e)
        {

            try
            {
               BackgroundImage = Properties.Resources.Background;
            }
            catch { Console.WriteLine("Background not found"); }
        }

        /*****************************************************************/

        /************************************************************/
        //Bouton Edition
        /************************************************************/
        private void QuitterButton_MouseDown(object sender, MouseEventArgs e)
        {
            colorBackgroundInitial[4] = QuitterButton.BackColor;
            colorLabelInitial[4] = QuitterButton.ForeColor;

            onClick = Color.FromArgb(a, r, g, b);
            QuitterButton.BackColor = onClick;
            QuitterButton.ForeColor = Color.White;

            //MenuPrincipal.ActiveForm.BackgroundImage 
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.quitterImage;
            }
            catch { Console.WriteLine("quitterImage not found"); }
        }

        private void QuitterButton_MouseUp(object sender, MouseEventArgs e)
        {
            QuitterButton.BackColor = colorBackgroundInitial[4];
            QuitterButton.ForeColor = colorLabelInitial[4];
        }

        private void QuitterButton_MouseEnter(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = InterfaceGraphique.Properties.Resources.quitterImage;
            }
            catch { Console.WriteLine("quitterImage not found"); }
        }

        private void QuitterButton_MouseLeave(object sender, EventArgs e)
        {
            try
            {
                BackgroundImage = Properties.Resources.Background;
            }
            catch { Console.WriteLine("Background not found"); }
        }
    }
}
