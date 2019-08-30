using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overseer
{
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


    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
            ExtGrid.grid = this.dataGridView1;
        }

        private void BtnAttach_Click(object sender, EventArgs e)
        {
            if (Engine.AttachToFallout())
                tmrRefresh.Enabled = true;
        }

        private void BtnRefresh_Click(object sender, EventArgs e)
        {
            this.ReadFromMemory();
            lstMessage.Items.Clear();
            AddMsg("SCRNAME",      Engine.ReadMessageList(0x56D754));
            AddMsg("COMBAT.MSG",   Engine.ReadMessageList(0x56D368));
            AddMsg("MAP.MSG",      Engine.ReadMessageList(0x631D48));
            AddMsg("PROTO",        Engine.ReadMessageList(0x6647FC));
            AddMsg("WORLDMAP.MSG", Engine.ReadMessageList(0x672FB0));
        }

        private void TmrRefresh_Tick(object sender, EventArgs e)
        {
            this.ReadFromMemory();
        }

        private void DATToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dat = new frmDatafiles();
            dat.Show();
        }

        private void InterfaceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var iface = new frmInterface();
            iface.Show();
        }

        private void AddMsg(string name, MessageList list)
        {
            foreach (var node in list.nodes)
                lstMessage.Items.Add(new ListViewItem(new string[] { name, node.number.ToString(), node.message, node.audio.Replace('\0', ' ') }));
        }

        private void ReadFromMemory()
        {
            this.dataGridView1.Rows.Clear();
            Globals.MouseX.ToGrid("MouseX");
            Globals.MouseY.ToGrid("MouseY");
            Globals.PlayerLevel.ToGrid("PlayerLevel");
            Globals.PlayerName.ToGrid("PlayerName");
            Globals.WorldPosX.ToGrid("WorldPosX");
            Globals.WorldPosY.ToGrid("WorldPosY");
        }
    }
}
