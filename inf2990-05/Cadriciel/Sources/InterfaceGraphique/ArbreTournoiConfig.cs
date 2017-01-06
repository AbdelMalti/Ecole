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
    public partial class ArbreTournoiConfig : Form
    {
       
        int tempsRestant;
        TournoiConfig unTournoi = Program.getNosTournoisConfiguration();
        Timer t;
        public ArbreTournoiConfig()
        {
            InitializeComponent();
            label1.Text = unTournoi.getNomJoueur1();
            label2.Text = unTournoi.getNomJoueur2();
            label3.Text = unTournoi.getNomJoueur3();
            label4.Text = unTournoi.getNomJoueur4();
            t = new Timer();
            tempsRestant = 1;
            t.Interval = 1000;
            t.Tick += new EventHandler(timer1Tick);

        }
        private void timer1Tick(object sender, EventArgs e)
        {
            tempsRestant += 1;
            if (tempsRestant == 5)
            {
                Program.arbreTournoiConfig.Hide();
                t.Stop();
            }
 
        }

    

        private void label1_Click(object sender, EventArgs e)
        {
            label1.Text = unTournoi.getNomJoueur1();
        }

        private void label2_Click(object sender, EventArgs e)
        {
            label2.Text = unTournoi.getNomJoueur2();
        }

        private void label3_Click(object sender, EventArgs e)
        {
            label3.Text = unTournoi.getNomJoueur3();
        }

        private void label4_Click(object sender, EventArgs e)
        {
            label4.Text = unTournoi.getNomJoueur4();
        }

        private void ArbreTournoiConfig_Shown(object sender, EventArgs e)
        {
            t.Start();
            
        }
    }
}
