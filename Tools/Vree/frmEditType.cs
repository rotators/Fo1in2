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

        private void btnUint16_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.UINT16);
        }

        private void btnInt8_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.INT8);
        }

        private void btnUint8_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.UINT8);
        }

        private void btnFloat_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.FLOAT);
        }

        private void btnInt32_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.INT32);
        }

        private void btnInt64_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.INT64);
        }

        private void btnUint64_Click(object sender, EventArgs e)
        {
            SetBasic(BasicType.UINT64);
        }
    }
}
