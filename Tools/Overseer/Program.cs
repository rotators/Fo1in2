using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overseer
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frmMain());
        }
    }

    public static class ExtGrid
    {
        public static DataGridView grid;
        public static void ToGrid<T>(this Global<T> global, string name)
        {
            string s = "";
            var v = global.value.GetType();
            s = Convert.ToString(global.value);

            grid.Rows.Add((new string[] { global.HexOffset, name, v.Name, s }));
        }
    }
}
