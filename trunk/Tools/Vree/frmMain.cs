using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Vree.Data;
using Vree.Winforms;

namespace Vree
{
    public enum DisplayList
    {
        Functions,
        Variables,
        Enums,
        Datatypes
    }

    public partial class frmMain : Form
    {
        List<ColumnHeader> colFunctions = new List<ColumnHeader>();
        List<ColumnHeader> colVariables = new List<ColumnHeader>();
        List<ListViewItem> funcItems = new List<ListViewItem>();
        List<ListViewItem> varItems = new List<ListViewItem>();

        DisplayList displayType = DisplayList.Functions;
        string colText = "";
        int sortIndex = -1;
        bool sortDesc;
        const string ascArrow = " ▲";
        const string descArrow = " ▼";

        public frmMain()
        {
            InitializeComponent();

            lstViewMain.DoubleBuffering(true);
            colFunctions.Add(new ColumnHeader() { Text = "Offset", Width = 200, Name = "colOffset" });
            colFunctions.Add(new ColumnHeader() { Text = "Definition", Width = 500, Name = "colDef" });
            colFunctions.Add(new ColumnHeader() { Text = "Comment", Width = 200, Name = "colComment" });
            lstViewMain.Columns.AddRange(colFunctions.ToArray());
            colVariables.Add(new ColumnHeader() { Text = "Offset", Width = 150, Name = "colOffset" });
            colVariables.Add(new ColumnHeader() { Text = "Definition", Width = 500, Name = "colDef" });
            colVariables.Add(new ColumnHeader() { Text = "Comment", Width = 200, Name = "colComment" });

            /* List<Function> funcs = new List<Function>(); 
             foreach(var func in File.ReadLines(@"D:\Fallout\dev\Fo1Port\trunk\Reversing\FunctionOffsets_def.h"))
             {
                 var spl = func.Split(',');
                 var name = spl[0].Substring(5, spl[0].Length - 6);
                 //var offset = spl[1].Substring(0, spl[1].Length - 1);
                 var offset = spl[1].Trim();

                 var uintoff = Convert.ToUInt32(offset.Substring(2, offset.IndexOf(')') - 2), 16);

                 funcs.Add(new Function()
                 {
                     Arguments=null,
                     Calling=CallingConvention.watcom,
                     Name=name,
                     Offset=uintoff
                 });
             }

             db.Save(@"D:\Fallout\dev\Fo1Port\trunk\Reversing\fo2_vree.db");*/

            var db = VreeDB.Load(@"D:\Fallout\dev\Fo1Port\trunk\Reversing\fo2_vree.db");
            foreach (var r in File.ReadLines(@"D:\Fallout\dev\Fo1Port\trunk\Reversing\symbols.txt"))
            {
                var spl = r.Split(new string[] { ": " }, StringSplitOptions.None);
                if (spl[1][0] != '_')
                    continue;
                var offset = Convert.ToUInt32(spl[0], 16);
                db.Variables.Add(new GlobalVariable {
                    Name = spl[1].Substring(1, spl[1].Length-1),
                    Offset = offset,
                    Type = null
                });
            }

            db.Save(@"D:\Fallout\dev\Fo1Port\trunk\Reversing\fo2_vree.db");

            foreach (var f in db.Functions)
                funcItems.Add(new ListViewItem(new string[] { "0x" + f.Offset.ToString("x").ToUpper(), f.Definition, f.Comment }));
            foreach (var v in db.Variables)
                varItems.Add(new ListViewItem(new string[] { "0x" + v.Offset.ToString("x").ToUpper(), v.String, v.Comment }));

            lstViewMain.BeginUpdate();
            lstViewMain.Items.AddRange(funcItems.ToArray());
            lstViewMain.EndUpdate();
        }

        private void TxtSearch_TextChanged(object sender, EventArgs e)
        {
            UpdateListView();
        }

        public class OffsetCompare : IComparer<ListViewItem>
        {
            public int Compare(ListViewItem x, ListViewItem y) { return x.SubItems[0].Text.CompareTo(y.SubItems[0].Text); }
        }

        public class NameCompare : IComparer<ListViewItem>
        {
            public int Compare(ListViewItem x, ListViewItem y) { return x.SubItems[1].Text.CompareTo(y.SubItems[1].Text); }
        }

        private List<ListViewItem> SortAndList()
        {
            var filtered = new List<ListViewItem>();
            var t = txtSearch.Text.ToLower();
            var items = displayType == DisplayList.Functions ? funcItems : varItems;
            foreach (var i in items)
            {
                if (!i.SubItems[1].Text.ToLower().Contains(t)) continue;
                filtered.Add(i);
            }
            if (sortIndex == 0) filtered.Sort(new OffsetCompare());
            if (sortIndex == 1) filtered.Sort(new NameCompare());
            if (sortDesc)
                filtered.Reverse();
            return filtered;
        }

        private void UpdateListView()
        {
            var items = SortAndList();
            lstViewMain.Items.Clear();
            lstViewMain.BeginUpdate();
            lstViewMain.Items.AddRange(items.ToArray());
            lstViewMain.EndUpdate();
        }

        private void LstViewMain_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            var idx = e.Column;
            var col = lstViewMain.Columns[idx];
            
            if (sortIndex == e.Column)
            {
                lstViewMain.Columns[idx].Text = colText;
                sortDesc = !sortDesc;
               // col.Text = col.Text.Substring(0, col.Text.Length - 2); // Remove old arrow
            }
            else
            {
                if(colText != "")
                    lstViewMain.Columns[sortIndex].Text = colText;
                sortIndex = e.Column;
                sortDesc = false;
                colText = lstViewMain.Columns[idx].Text;
            }
            col.Text = col.Text + (sortDesc ? descArrow : ascArrow);
            UpdateListView();
        }

        private void BtnShowVariables_Click(object sender, EventArgs e)
        {
            this.displayType = DisplayList.Variables;
            this.UpdateListView();
        }

        private void BtnShowFunctions_Click(object sender, EventArgs e)
        {
            this.displayType = DisplayList.Functions;
            this.UpdateListView();
        }
    }
}
