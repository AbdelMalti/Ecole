namespace InterfaceGraphique
{
    partial class TournoiConfig
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TournoiConfig));
            this.text2 = new System.Windows.Forms.TextBox();
            this.parcourir = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.demarrerTournoi = new System.Windows.Forms.Button();
            this.humain2 = new System.Windows.Forms.RadioButton();
            this.virtuel2 = new System.Windows.Forms.RadioButton();
            this.joueur2 = new System.Windows.Forms.GroupBox();
            this.Joueur3 = new System.Windows.Forms.GroupBox();
            this.humain3 = new System.Windows.Forms.RadioButton();
            this.virtuel3 = new System.Windows.Forms.RadioButton();
            this.text3 = new System.Windows.Forms.TextBox();
            this.joueur1 = new System.Windows.Forms.GroupBox();
            this.humain1 = new System.Windows.Forms.RadioButton();
            this.virtuel1 = new System.Windows.Forms.RadioButton();
            this.text1 = new System.Windows.Forms.TextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.humain4 = new System.Windows.Forms.RadioButton();
            this.virtuel4 = new System.Windows.Forms.RadioButton();
            this.text4 = new System.Windows.Forms.TextBox();
            this.choixProfilV1 = new System.Windows.Forms.OpenFileDialog();
            this.choixProfilV2 = new System.Windows.Forms.OpenFileDialog();
            this.choixProfilV3 = new System.Windows.Forms.OpenFileDialog();
            this.choixProfilV4 = new System.Windows.Forms.OpenFileDialog();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuPrincipalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBoxJoueur = new System.Windows.Forms.GroupBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.joueur2.SuspendLayout();
            this.Joueur3.SuspendLayout();
            this.joueur1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.groupBoxJoueur.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // text2
            // 
            this.text2.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text2.Location = new System.Drawing.Point(17, 75);
            this.text2.Name = "text2";
            this.text2.Size = new System.Drawing.Size(116, 30);
            this.text2.TabIndex = 7;
            // 
            // parcourir
            // 
            this.parcourir.BackColor = System.Drawing.Color.White;
            this.parcourir.Cursor = System.Windows.Forms.Cursors.Hand;
            this.parcourir.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.parcourir.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(77)))), ((int)(((byte)(0)))), ((int)(((byte)(77)))));
            this.parcourir.Location = new System.Drawing.Point(210, 338);
            this.parcourir.Name = "parcourir";
            this.parcourir.Size = new System.Drawing.Size(207, 39);
            this.parcourir.TabIndex = 17;
            this.parcourir.Text = "Choix de la zone de jeu";
            this.parcourir.UseVisualStyleBackColor = false;
            this.parcourir.Click += new System.EventHandler(this.button1_Click);
            this.parcourir.MouseDown += new System.Windows.Forms.MouseEventHandler(this.parcourir_MouseDown);
            this.parcourir.MouseUp += new System.Windows.Forms.MouseEventHandler(this.parcourir_MouseUp);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.InitialDirectory = "zones/";
            // 
            // demarrerTournoi
            // 
            this.demarrerTournoi.BackgroundImage = global::InterfaceGraphique.Properties.Resources.play;
            this.demarrerTournoi.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.demarrerTournoi.Cursor = System.Windows.Forms.Cursors.Hand;
            this.demarrerTournoi.Dock = System.Windows.Forms.DockStyle.Fill;
            this.demarrerTournoi.Location = new System.Drawing.Point(3, 3);
            this.demarrerTournoi.Name = "demarrerTournoi";
            this.demarrerTournoi.Size = new System.Drawing.Size(122, 84);
            this.demarrerTournoi.TabIndex = 19;
            this.demarrerTournoi.Tag = "Demarrer Tournoi";
            this.toolTip1.SetToolTip(this.demarrerTournoi, "Demarrer Tournoi");
            this.demarrerTournoi.UseVisualStyleBackColor = true;
            this.demarrerTournoi.Click += new System.EventHandler(this.demarrerTournoi_Click);
            this.demarrerTournoi.MouseEnter += new System.EventHandler(this.entrerSourieSurJouer);
            this.demarrerTournoi.MouseLeave += new System.EventHandler(this.sortieSourieSurJouer);
            // 
            // humain2
            // 
            this.humain2.AutoSize = true;
            this.humain2.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.humain2.Location = new System.Drawing.Point(17, 22);
            this.humain2.Name = "humain2";
            this.humain2.Size = new System.Drawing.Size(86, 27);
            this.humain2.TabIndex = 20;
            this.humain2.TabStop = true;
            this.humain2.Text = "humain2";
            this.humain2.UseVisualStyleBackColor = true;
            this.humain2.CheckedChanged += new System.EventHandler(this.humain2_CheckedChanged);
            // 
            // virtuel2
            // 
            this.virtuel2.AutoSize = true;
            this.virtuel2.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.virtuel2.Location = new System.Drawing.Point(17, 48);
            this.virtuel2.Name = "virtuel2";
            this.virtuel2.Size = new System.Drawing.Size(87, 27);
            this.virtuel2.TabIndex = 21;
            this.virtuel2.TabStop = true;
            this.virtuel2.Text = "virtuel2";
            this.virtuel2.UseVisualStyleBackColor = true;
            this.virtuel2.Click += new System.EventHandler(this.virtuel2_Click);
            // 
            // joueur2
            // 
            this.joueur2.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.joueur2.Controls.Add(this.humain2);
            this.joueur2.Controls.Add(this.virtuel2);
            this.joueur2.Controls.Add(this.text2);
            this.joueur2.Font = new System.Drawing.Font("Comic Sans MS", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.joueur2.Location = new System.Drawing.Point(193, 34);
            this.joueur2.Name = "joueur2";
            this.joueur2.Size = new System.Drawing.Size(156, 115);
            this.joueur2.TabIndex = 22;
            this.joueur2.TabStop = false;
            this.joueur2.Text = "Joueur2";
            // 
            // Joueur3
            // 
            this.Joueur3.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Joueur3.Controls.Add(this.humain3);
            this.Joueur3.Controls.Add(this.virtuel3);
            this.Joueur3.Controls.Add(this.text3);
            this.Joueur3.Font = new System.Drawing.Font("Comic Sans MS", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Joueur3.Location = new System.Drawing.Point(26, 162);
            this.Joueur3.Name = "Joueur3";
            this.Joueur3.Size = new System.Drawing.Size(156, 115);
            this.Joueur3.TabIndex = 23;
            this.Joueur3.TabStop = false;
            this.Joueur3.Text = "Joueur3";
            // 
            // humain3
            // 
            this.humain3.AutoSize = true;
            this.humain3.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.humain3.Location = new System.Drawing.Point(17, 22);
            this.humain3.Name = "humain3";
            this.humain3.Size = new System.Drawing.Size(86, 27);
            this.humain3.TabIndex = 20;
            this.humain3.TabStop = true;
            this.humain3.Text = "humain3";
            this.humain3.UseVisualStyleBackColor = true;
            this.humain3.CheckedChanged += new System.EventHandler(this.humain3_CheckedChanged);
            // 
            // virtuel3
            // 
            this.virtuel3.AutoSize = true;
            this.virtuel3.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.virtuel3.Location = new System.Drawing.Point(17, 48);
            this.virtuel3.Name = "virtuel3";
            this.virtuel3.Size = new System.Drawing.Size(87, 27);
            this.virtuel3.TabIndex = 21;
            this.virtuel3.TabStop = true;
            this.virtuel3.Text = "virtuel3";
            this.virtuel3.UseVisualStyleBackColor = true;
            this.virtuel3.Click += new System.EventHandler(this.virtuel3_Click);
            // 
            // text3
            // 
            this.text3.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text3.Location = new System.Drawing.Point(17, 75);
            this.text3.Name = "text3";
            this.text3.Size = new System.Drawing.Size(116, 30);
            this.text3.TabIndex = 7;
            // 
            // joueur1
            // 
            this.joueur1.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.joueur1.Controls.Add(this.humain1);
            this.joueur1.Controls.Add(this.virtuel1);
            this.joueur1.Controls.Add(this.text1);
            this.joueur1.Font = new System.Drawing.Font("Comic Sans MS", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.joueur1.Location = new System.Drawing.Point(26, 34);
            this.joueur1.Name = "joueur1";
            this.joueur1.Size = new System.Drawing.Size(156, 115);
            this.joueur1.TabIndex = 24;
            this.joueur1.TabStop = false;
            this.joueur1.Text = "Joueur1";
            // 
            // humain1
            // 
            this.humain1.AutoSize = true;
            this.humain1.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.humain1.Location = new System.Drawing.Point(17, 22);
            this.humain1.Name = "humain1";
            this.humain1.Size = new System.Drawing.Size(83, 27);
            this.humain1.TabIndex = 20;
            this.humain1.TabStop = true;
            this.humain1.Text = "humain1";
            this.humain1.UseVisualStyleBackColor = true;
            this.humain1.CheckedChanged += new System.EventHandler(this.humain1_CheckedChanged);
            // 
            // virtuel1
            // 
            this.virtuel1.AutoSize = true;
            this.virtuel1.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.virtuel1.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.virtuel1.Location = new System.Drawing.Point(17, 48);
            this.virtuel1.Name = "virtuel1";
            this.virtuel1.Size = new System.Drawing.Size(84, 27);
            this.virtuel1.TabIndex = 21;
            this.virtuel1.TabStop = true;
            this.virtuel1.Text = "virtuel1";
            this.virtuel1.UseVisualStyleBackColor = true;
            this.virtuel1.Click += new System.EventHandler(this.virtuel1_Click);
            // 
            // text1
            // 
            this.text1.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text1.Location = new System.Drawing.Point(17, 75);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(116, 30);
            this.text1.TabIndex = 7;
            // 
            // groupBox4
            // 
            this.groupBox4.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.groupBox4.Controls.Add(this.humain4);
            this.groupBox4.Controls.Add(this.virtuel4);
            this.groupBox4.Controls.Add(this.text4);
            this.groupBox4.Font = new System.Drawing.Font("Comic Sans MS", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox4.Location = new System.Drawing.Point(193, 162);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(156, 115);
            this.groupBox4.TabIndex = 25;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Joueur4";
            // 
            // humain4
            // 
            this.humain4.AutoSize = true;
            this.humain4.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.humain4.Location = new System.Drawing.Point(17, 22);
            this.humain4.Name = "humain4";
            this.humain4.Size = new System.Drawing.Size(86, 27);
            this.humain4.TabIndex = 20;
            this.humain4.TabStop = true;
            this.humain4.Text = "humain4";
            this.humain4.UseVisualStyleBackColor = true;
            this.humain4.CheckedChanged += new System.EventHandler(this.humain4_CheckedChanged);
            // 
            // virtuel4
            // 
            this.virtuel4.AutoSize = true;
            this.virtuel4.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.virtuel4.Location = new System.Drawing.Point(17, 48);
            this.virtuel4.Name = "virtuel4";
            this.virtuel4.Size = new System.Drawing.Size(87, 27);
            this.virtuel4.TabIndex = 21;
            this.virtuel4.TabStop = true;
            this.virtuel4.Text = "virtuel4";
            this.virtuel4.UseVisualStyleBackColor = true;
            this.virtuel4.Click += new System.EventHandler(this.virtuel4_Click);
            // 
            // text4
            // 
            this.text4.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text4.Location = new System.Drawing.Point(17, 75);
            this.text4.Name = "text4";
            this.text4.Size = new System.Drawing.Size(116, 30);
            this.text4.TabIndex = 7;
            // 
            // choixProfilV1
            // 
            this.choixProfilV1.InitialDirectory = "./zones";
            this.choixProfilV1.RestoreDirectory = true;
            // 
            // choixProfilV2
            // 
            this.choixProfilV2.FileName = "choixProfilV2";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuPrincipalToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(7, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(630, 24);
            this.menuStrip1.TabIndex = 26;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuPrincipalToolStripMenuItem
            // 
            this.menuPrincipalToolStripMenuItem.Name = "menuPrincipalToolStripMenuItem";
            this.menuPrincipalToolStripMenuItem.Size = new System.Drawing.Size(99, 20);
            this.menuPrincipalToolStripMenuItem.Text = "Menu principal";
            this.menuPrincipalToolStripMenuItem.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBoxJoueur
            // 
            this.groupBoxJoueur.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.groupBoxJoueur.Controls.Add(this.joueur1);
            this.groupBoxJoueur.Controls.Add(this.groupBox4);
            this.groupBoxJoueur.Controls.Add(this.Joueur3);
            this.groupBoxJoueur.Controls.Add(this.joueur2);
            this.groupBoxJoueur.Font = new System.Drawing.Font("Comic Sans MS", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxJoueur.Location = new System.Drawing.Point(121, 39);
            this.groupBoxJoueur.Name = "groupBoxJoueur";
            this.groupBoxJoueur.Size = new System.Drawing.Size(375, 293);
            this.groupBoxJoueur.TabIndex = 27;
            this.groupBoxJoueur.TabStop = false;
            this.groupBoxJoueur.Text = "Choix des joueurs";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(3, 90);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 30);
            this.label1.TabIndex = 28;
            this.label1.Text = "Jouer!";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.demarrerTournoi, 0, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(244, 383);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(128, 120);
            this.tableLayoutPanel1.TabIndex = 29;
            // 
            // TournoiConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Background;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(630, 515);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.groupBoxJoueur);
            this.Controls.Add(this.parcourir);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("Comic Sans MS", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "TournoiConfig";
            this.Text = "TournoiConfig";
            this.Load += new System.EventHandler(this.TournoiConfig_Load);
            this.joueur2.ResumeLayout(false);
            this.joueur2.PerformLayout();
            this.Joueur3.ResumeLayout(false);
            this.Joueur3.PerformLayout();
            this.joueur1.ResumeLayout(false);
            this.joueur1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBoxJoueur.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox text2;
        private System.Windows.Forms.Button parcourir;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button demarrerTournoi;
        private System.Windows.Forms.RadioButton humain2;
        private System.Windows.Forms.RadioButton virtuel2;
        private System.Windows.Forms.GroupBox joueur2;
        private System.Windows.Forms.GroupBox Joueur3;
        private System.Windows.Forms.RadioButton humain3;
        private System.Windows.Forms.RadioButton virtuel3;
        private System.Windows.Forms.TextBox text3;
        private System.Windows.Forms.GroupBox joueur1;
        private System.Windows.Forms.RadioButton humain1;
        private System.Windows.Forms.RadioButton virtuel1;
        private System.Windows.Forms.TextBox text1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.RadioButton humain4;
        private System.Windows.Forms.RadioButton virtuel4;
        private System.Windows.Forms.TextBox text4;
        private System.Windows.Forms.OpenFileDialog choixProfilV1;
        private System.Windows.Forms.OpenFileDialog choixProfilV2;
        private System.Windows.Forms.OpenFileDialog choixProfilV3;
        private System.Windows.Forms.OpenFileDialog choixProfilV4;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBoxJoueur;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
    }
}