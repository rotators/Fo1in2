using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overseer
{
        public static class Extensions
        {
            public static void AddLine(this ListView lst, params object[] cols)
            {
                lst.Items.Add(new ListViewItem(cols.Select(x => Convert.ToString(x)).ToArray()));
            }

        }
}
