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
                tmrRefresh.Enabled = true;
            }
        }

        private void AddRow(int offset, string name, string datatype, string value)
        {
            this.dataGridView1.Rows.Add(new string[] { "0x" + offset.ToString("x"), name, datatype, value});
        }

        private void AddByte(int offset, string name)
        {
            dataGridView1.Rows.Add(offset, name, "Byte", mem.ReadByte(offset).ToString());
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
        }

        private List<PathNode> ReadPaths()
        {
            var paths = new List<PathNode>();
            var deref = mem.ReadInt(0x6B24D0);
            var pn = mem.ReadPathNode(deref);
            paths.Add(pn);
            while(pn.nextPtr != 0)
            {
                var off = mem.ReadInt(pn.nextPtr);
                pn = mem.ReadPathNode(pn.nextPtr);
                paths.Add(pn);
            }
            return paths;
        }

        private List<ScriptListInfo> ReadScriptList()
        {
            var s = new List<ScriptListInfo>();
            var offset = mem.ReadInt(0x51C7C8); // dereference pointer
            var scriptInfo = mem.ReadScriptListInfo(offset);
            while (scriptInfo != null)
            {
                s.Add(scriptInfo);
                offset += 20;
                scriptInfo = mem.ReadScriptListInfo(offset);
            }
            return s;
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
            var scripts = ReadScriptList();
        }

        private void TmrRefresh_Tick(object sender, EventArgs e)
        {
            this.ReadMemory();
        }
    }
}
