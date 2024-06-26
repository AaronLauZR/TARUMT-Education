using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web_Assignment.client
{
    public partial class ClientMasterTailWind : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
             
            if (Session["UserName"] != null)
            {
                displayusername.Text = Session["UserName"].ToString();
            }
            else
            {
                Response.Redirect("Login.aspx");

            }
        }
    }
}