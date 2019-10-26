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

        VreeDB db;

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

            db = VreeDB.Load(VreeDB.FindPath());
            foreach (var f in db.Functions)
            {
                var li = new ListViewItem(new string[] { "0x" + f.Offset.ToString("x").ToUpper(), f.Definition, f.Comment });
                li.Tag = f.Offset;
                funcItems.Add(li);
            }
            foreach (var v in db.Variables)
            {
                var li = new ListViewItem(new string[] { "0x" + v.Offset.ToString("x").ToUpper(), v.String, v.Comment });
                li.Tag = v.Offset;
                varItems.Add(li);
            }

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
                if (!i.SubItems[1].Text.ToLower().Contains(t) 
                 && !i.SubItems[0].Text.ToLower().Contains(t)
                 && !i.SubItems[2].Text.ToLower().Contains(t)
                 )
                    continue;
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

        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            db.Save(VreeDB.FindPath());
        }

        private void SetVariableTypeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChangeSelectedVariablesDatatype();
        }

        private void BtnChangeDatatype_Click(object sender, EventArgs e)
        {
            ChangeSelectedVariablesDatatype();
        }

        private void ChangeSelectedVariablesDatatype()
        {
            var edit = new frmEditType();
            edit.ShowDialog();
            if (edit.Selected == null)
                return;
            EditSelectedVariables((v, i) =>
            {
                if (edit.Selected.IsBasicType)
                    v.SetBasicType(edit.Selected.BasicType);
                i.SubItems[1].Text = v.String;
            });
        }

        private void EditSelectedVariables(Action<GlobalVariable, ListViewItem> action)
        {
            foreach (ListViewItem i in lstViewMain.SelectedItems)
            {
                var v = db.Variables.Find(x => x.Offset == (uint)i.Tag);
                action(v, i);
            }
            lstViewMain.Refresh();
        }

        private void EditSelectedFunctions(Action<Function, ListViewItem> action)
        {
            foreach (ListViewItem i in lstViewMain.SelectedItems)
            {
                var f = db.Functions.Find(x => x.Offset == (uint)i.Tag);
                action(f, i);
            }
            lstViewMain.Refresh();
        }

        private GlobalVariable GetSelectedVar()
        {
            return db.Variables.Find(x => x.Offset == (uint)lstViewMain.SelectedItems[0].Tag);
        }

        private Function GetSelectedFunc()
        {
            return db.Functions.Find(x => x.Offset == (uint)lstViewMain.SelectedItems[0].Tag);
        }

        private void BtnComment_Click(object sender, EventArgs e)
        {
            if (lstViewMain.SelectedItems.Count == 0)
                return;

            if(lstViewMain.SelectedItems.Count > 1)
            {
                MessageBox.Show("Only one item allowed when changing comment.");
            }

            var cmt = new frmComment();
            if (displayType == DisplayList.Variables)
            {
                var gvar = GetSelectedVar();
                cmt.ReadComment(gvar.Comment);
            }
            if(displayType == DisplayList.Functions)
            {
                var func = GetSelectedFunc();
                cmt.ReadComment(func.Comment);
            }

            cmt.ShowDialog();
            if (cmt.Comment == null)
                return;

            if (displayType == DisplayList.Variables)
            {
                EditSelectedVariables((v, i) =>
                {
                    v.Comment = cmt.Comment;
                    i.SubItems[2].Text = v.Comment;
                });
            }
            if (displayType == DisplayList.Functions)
            {
                EditSelectedFunctions((f, i) =>
                {
                    f.Comment = cmt.Comment;
                    i.SubItems[2].Text = f.Comment;
                });
            }
        }

        private void LstViewMain_DoubleClick(object sender, EventArgs e)
        {
            if(displayType == DisplayList.Functions)
            {
                var editFunc = new frmEditFunction(GetSelectedFunc());
                editFunc.ShowDialog();
                EditSelectedFunctions((f, i) =>
                {
                    f = editFunc.func;
                    i.SubItems[1].Text = f.Definition;
                });
            }
        }
    }
}
