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
    public partial class frmMain : Form
    {
        Memory mem;
        MemoryReader reader;
        FalloutMemory fmem;

        public frmMain()
        {
            InitializeComponent();
        }

        private void BtnAttach_Click(object sender, EventArgs e)
        {
            var fallout2 = Process.GetProcessesByName("Fallout2");
            if (fallout2.Length > 0)
            {
                mem = new Memory(fallout2[0].Id);
                reader = new MemoryReader(mem);
                fmem = new FalloutMemory(reader);
                tmrRefresh.Enabled = true;
            }
        }

        private void AddRow(int offset, string name, string datatype, string value)
        {
            this.dataGridView1.Rows.Add(new string[] { "0x" + offset.ToString("x"), name, datatype, value});
        }

        private void AddByte(int offset, string name)
        {
            this.AddRow(offset, name, "Byte", mem.ReadByte(offset).ToString());
        }

        private void AddInt16(int offset, string name)
        {
            this.AddRow(offset, name, "Int16", mem.ReadInt16(offset).ToString());
        }

        private void AddString(int offset, string name)
        {
            this.AddRow(offset, name, "String", mem.ReadString(offset, out int _).ToString());
        }

        private void BtnRefresh_Click(object sender, EventArgs e)
        {
            this.ReadMemory();
            lstMessage.Items.Clear();
            /*foreach (var s in fmem.ReadScriptList())
            {
                lstScripts.Items.Add(new ListViewItem(new string[] { s.fileName, s.numLocalVars.ToString() }));
            }*/
            /*AddMsg("SCRNAME", fmem.ReadMessageList(0x56D754));
            AddMsg("COMBAT.MSG", fmem.ReadMessageList(0x56D368));
            AddMsg("MAP.MSG", fmem.ReadMessageList(0x631D48));
            AddMsg("PROTO", fmem.ReadMessageList(0x6647FC));
            AddMsg("WORLDMAP.MSG", fmem.ReadMessageList(0x672FB0));*/


            //var st = Encoding.ASCII.GetString(bytes);
        }

        private void AddMsg(string name, MessageList list)
        {
            foreach (var node in list.nodes)
                lstMessage.Items.Add(new ListViewItem(new string[] { name, node.number.ToString(), node.message, node.audio.Replace('\0',' ')}));
        }



        private void ReadMemory()
        {
            this.dataGridView1.Rows.Clear();
            AddByte(0x672E0C, "worldPosX");
            AddByte(0x672E10, "worldPosY");
            AddByte(0x6681B0, "playerLevel");
            AddInt16(0x6AC7A8, "mouseX");
            AddInt16(0x6AC7A4, "mouseY");
            AddString(0x56D75C, "playerName");
            //ReadPaths();
            
        }

        private void TmrRefresh_Tick(object sender, EventArgs e)
        {
            this.ReadMemory();
        }

        private void DATToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dat = new frmDatafiles(this.fmem, this.reader);
            dat.Show();
        }
    }
}
