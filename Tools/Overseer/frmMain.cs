using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Vree.Data;

namespace Overseer
{
   


    public partial class frmMain : Form
    {
        VreeDB db;

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
            db = VreeDB.Load(VreeDB.FindPath());
            foreach(var a in db.Variables)
            {
                if (a.Type == null)
                    continue;

                if(a.Type.IsBasicType)
                {
                    switch (a.Type.BasicType)
                    {
                        case BasicType.UINT8: Globals.Byte((int)a.Offset).ToGrid(a.Name); break;
                        case BasicType.INT8: Globals.Byte((int)a.Offset).ToGrid(a.Name); break;
                        case BasicType.UINT16: Globals.Int16((int)a.Offset).ToGrid(a.Name); break;
                        case BasicType.UINT32: Globals.Int32((int)a.Offset).ToGrid(a.Name); break;
                        case BasicType.CHARP: Globals.CString((int)a.Offset).ToGrid(a.Name); break;
                    }
                }
                
            }
        }
    }
}
