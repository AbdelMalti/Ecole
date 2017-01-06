using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    public enum fenetre
    {
        Accueil,
        PartieRapideConfig,
        TournoiConfig,
        Configuration,
        Edition,
        Quitter

    }
    static class Program
    {
        private const int NB_IMAGES_PAR_SECONDE = 60;

        public static Object unLock = new Object();
        public static bool peutAfficher = true;
        public static fenetre fenetre = fenetre.Accueil;

        public static Edition edition;
        public static ArbreTournoiConfig arbreTournoiConfig;
        public static Configuration configuration;
        public static MenuPrincipal menu;
        public static PartieRapideConfig partieRapideConfig;
        public static TournoiConfig tournoiConfig;
        private static TimeSpan dernierTemps;
        private static TimeSpan tempsAccumule;
        private static Stopwatch chrono = Stopwatch.StartNew();
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE);

        public static bool estPartieRapide = false;
        public static bool estTournoi = false;
        public static bool estEdition = false;

        public static bool magie = true;

        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length != 0)
                if (args[0] == "testsC++")
                {
                    //if (FonctionsNatives.executerTests())
                    //    System.Console.WriteLine("Échec d'un ou plusieurs tests.");
                    //else
                    //    System.Console.WriteLine("Tests réussis.");
                    return;
                }
            chrono.Start();
            //Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Application.Idle += ExecuterQuandInactif;

            menu = new MenuPrincipal("accueil");
            configuration = new Configuration();
            tournoiConfig = new TournoiConfig();
            partieRapideConfig = new PartieRapideConfig();

            edition = new Edition();
            //Application.Idle += ExecuterQuandInactif;
            edition.Width = edition.Width + 1;
            edition.Height = edition.Height + 1;
            

            while (fenetre != fenetre.Quitter)
            {
                switch (fenetre)
                {
                    case fenetre.Accueil:
                        
                        menu.Show();
                        
                        break;

                    case fenetre.PartieRapideConfig:
                        //Application.Idle += ExecuterQuandInactif;
                        //partieRapideConfig.Show();
                        break;

                    case fenetre.TournoiConfig:
                        //Application.Idle += ExecuterQuandInactif;
                        //tournoiConfig.Show();
                        break;

                    case fenetre.Configuration:
                        //configuration.menuStrip1.Show();
                        //configuration.menuStrip2.Hide();
                        //configuration.Show();
                        break;

                    case fenetre.Edition:
                        
                        edition.Show();
                        //edition = new Edition(zoneDeJeu);
                        ////Application.Idle += ExecuterQuandInactif;
                        //edition.Width = edition.Width + 1;
                        //edition.Height = edition.Height + 1;
                        break;
                }
                Application.Run();
            }

            Application.Exit();
        }


        public static Configuration getNosConfiguration()
        {
            if (Program.estPartieRapide)
            {
                configuration.menuStrip1.Hide();
                configuration.menuStrip2.Show();
            }
            return configuration;
        }

        public static TournoiConfig getNosTournoisConfiguration()
        { 
            return tournoiConfig;
        }

        public static void ExecuterQuandInactif(object sender, EventArgs e)
        {
            if (magie)
            {
                //Console.WriteLine("Program.cs ExecuterQuandInactif");
                FonctionsNatives.Message message;

                while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
                {
                    TimeSpan currentTime = chrono.Elapsed;
                    TimeSpan elapsedTime = currentTime - dernierTemps;
                    dernierTemps = currentTime;

                    tempsAccumule += elapsedTime;

                    if (tempsAccumule >= tempsEcouleVoulu)
                    {
                        lock (unLock)
                        {
                            if (edition != null && peutAfficher)
                                edition.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                        }
                        tempsAccumule = TimeSpan.Zero;
                    }
                }
            }
        }
    }
    static partial class FonctionsNatives
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public uint Msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint Time;
            public System.Drawing.Point Point;
        }

        [DllImport("User32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out Message message, IntPtr hWnd, uint filterMin, uint filterMax, uint flags);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool executerTests();

    }
}
