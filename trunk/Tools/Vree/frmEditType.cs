using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Vree.Data;

namespace Vree
{
    public partial class frmEditType : Form
    {
        public DataType Selected;

        public frmEditType()
        {
            InitializeComponent();
        }

        private void ChooseDatatype(DataType Type)
        {
            this.Selected = Type;
            this.Close();
        }

        private void SetBasic(BasicType Type)
        {
            var t = new DataType()
            {
                BasicType = Type,
                IsBasicType = true
            };
            ChooseDatatype(t);
        }

        private void BtnBool_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.BOOL);
        }

        private void BtnUint32_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.UINT32);
        }

        private void BtnCharp_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.CHARP);
        }
    }
}
