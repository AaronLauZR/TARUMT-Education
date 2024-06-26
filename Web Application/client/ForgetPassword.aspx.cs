using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Reflection.Emit;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web_Assignment.client
{
    public partial class ForgetPassword : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
        protected void Page_Load(object sender, EventArgs e)
        {
           
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            SqlConnection con = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);
            SqlDataAdapter uname = new SqlDataAdapter("select username from [User] where username = '" + forgusername.Text + "'", con);
            SqlDataAdapter uemail = new SqlDataAdapter("select email from [User] where email = '" + forgemail.Text + "'", con);
            DataTable dt = new DataTable();
            DataTable dl = new DataTable();
            uname.Fill(dt);
            uemail.Fill(dl);

            if ((dt.Rows.Count.ToString() == "1") && (dl.Rows.Count.ToString() == "1"))
            {
                con.Open();

                string strRetrieveUsername = "Select * from [User] where username ='" + forgusername.Text + "'";
                SqlCommand cmd = new SqlCommand(strRetrieveUsername, con);
                SqlDataReader dr = cmd.ExecuteReader();

                while (dr.Read())
                {
                    Response.Write("<script>alert('" + "Password Founded!" + "')</script>");
                    message.Text = "Password: " + dr.GetValue(2).ToString();
                }
            }
            else
            {
                message.Text = "Invalid username or email! Please try again!";
            }
            con.Close();
        }
    }
}