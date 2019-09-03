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
    public partial class frmEditFunction : Form
    {
        public frmEditFunction(Function func)
        {
            InitializeComponent();
            this.func = func;
            this.txtDefinition.Text = this.func.Definition;
            this.types = BasicType.BOOL.AllBasicTypes().ToList();
        }

        public Function func;
        //List<DataType> types;
        List<BasicType> types;

        private DataType ParseDatatype(string str, bool isReturn, int argx, out bool isArray, out UInt16 arrLength, out bool isPtr)
        {
            arrLength = 1;
            isArray = false;
            isPtr = false;
            str.Reverse();
            if (str[0] == '*')
            {
                isPtr = true;
                str = str.Substring(1);
            }
            if (str[0] == ']' && str[1] == '[')
            {
                isArray = true;
                arrLength = ushort.MaxValue;
                str = str.Substring(2);
            }
            DataType type = null;
            var lw = str.ToLower();
            foreach (var ty in types)
            {
                if (lw == ty.GetBasicTypeString())
                    type = new DataType()
                    {
                        BasicType = ty,
                        IsBasicType = true
                    };
            }
            if (type == null)
            {
                if(isReturn)
                    MessageBox.Show("Unable to parse return type.");
                else
                    MessageBox.Show("Unable to parse arg " + argx + ".");
                return null;
            }

            return type;
        }

        private void BtnParse_Click(object sender, EventArgs e)
        {
            var def = txtDefinition.Text;
            if(def.IndexOf(' ') == -1)
            {
                MessageBox.Show("Unable to find return space after return type.");
                return;
            }

            var retPart = def.Substring(0, def.IndexOf(' '));
            var type = ParseDatatype(retPart, true, 0, out bool isArr, out UInt16 arrLen, out bool isPtr);
            var returnVar = new ReturnVariable()
            {
                Pointer = isPtr,
                Length = isArr ? arrLen : (UInt16)1,
                Type = type
            };

            if (returnVar.Type == null)
                return;

            var rest = def.Substring(def.IndexOf(' '));
            if (rest.IndexOf('(') == -1 || rest.IndexOf(')') == -1)
            {
                MessageBox.Show("No argument list found.");
                return;
            }
            
            var funcName = rest.Substring(0, rest.IndexOf('('));
            var sIdx = rest.IndexOf('(') + 1;
            var eIdx = rest.IndexOf(')');

            var args = rest.Substring(sIdx, eIdx - sIdx).Split(',');
            var i = 1;
            var parsedArgs = new List<Argument>();
            foreach(var a in args)
            {
                if (a == "()")
                    continue;

                var aspl = a.Split(' ');
                var name = aspl[1];
                var atype = ParseDatatype(aspl[0], false, i++, out bool aisArr, out UInt16 aarrLen, out bool aisPtr);
                parsedArgs.Add(new Argument()
                {
                    Name=name,
                    Type=atype 
                });
            }


            this.func.Name = funcName.Trim();
            this.func.ReturnType = returnVar;
            this.func.Arguments = parsedArgs;
            

            txtDefinition.Text = this.func.Definition;
        }

        private void BtnSave_Click(object sender, EventArgs e)
        {
            this.func.Comment = txtComment.Text;
            this.Close();
        }
    }
}
