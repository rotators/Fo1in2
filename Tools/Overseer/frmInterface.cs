using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overseer
{
    public partial class frmInterface : Form
    {
        public frmInterface()
        {
            InitializeComponent();
        }

        private void FrmInterface_Load(object sender, EventArgs e)
        {
            RefreshList();
        }
        
        private void RefreshList()
        {
            lstWindows.Items.Clear();
            lstButtons.Items.Clear();
            foreach (var win in Engine.GetWindows())
            {
                lstWindows.Items.Add(new ListViewItem(new string[] { win.id.ToString(),
                    win.flags.ToString(), win.left.ToString(), win.top.ToString(), win.right.ToString(),
                    win.bottom.ToString(), win.clearColor.ToString(), win.unknown.ToString(), win.unknown2.ToString(), win.unknown3.ToString(), win.unknown4.ToString() }));

                if(win.buttonPtr != 0)
                {
                    var i = Decimal.ToInt32(numericUpDown1.Value);
                    var buttons = win.GetButtons(Engine.Memory, i);
                    var ids = buttons.Select(x => x.id);

                    var listIds = lstButtons.Items.Cast<ListViewItem>().Select(x => int.Parse(x.Text));
                    foreach (var button in win.GetButtons(Engine.Memory, i).ToList())
                    {
                        lstButtons.AddLine(button.id, button.baseOffset, button.flag, win.id, button.unk, button.unk2, button.unk3, button.unk4);
                    }
                }
            }
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            RefreshList();
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            RefreshList();
        }
    }
}
