using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Configuration;
using System.Data.SqlClient;

namespace Web_Assignment.client
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void login_Click(object sender, EventArgs e)
        {
            SqlConnection con = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);
            con.Open();
            string checkusername = "select count(*) from [User] where username='" + enterusername.Text + "'";
            SqlCommand com = new SqlCommand(checkusername, con);
            int temp = Convert.ToInt32(com.ExecuteScalar().ToString());
            con.Close();
        
            if (temp == 1)
            {
                con.Open();
                string checkpassword = "select password from [User] where username='" + enterusername.Text + "'";
                SqlCommand passcom = new SqlCommand(checkpassword, con);
                string password = passcom.ExecuteScalar().ToString().Replace(" ","");

                if (password == enterpassword.Text)
                {
                    string getUserId = "select userId from [User] where username='" + enterusername.Text + "'";
                    SqlCommand uid = new SqlCommand(getUserId, con);
                    SqlDataReader rdr = uid.ExecuteReader();

                    while (rdr.Read())
                    {
                        Session["UserId"] = rdr["userId"].ToString();
                    }

                    Session["UserName"] = enterusername.Text;
                    if (enterusername.Text == "zhongren")
                    {
                        Response.Redirect("../admin/Dashboard.aspx");
                    }
                    else if (enterusername.Text == "tzenyang")
                    {
                        Response.Redirect("../admin/Dashboard.aspx");
                    }
                    else if (enterusername.Text == "hinyong")
                    {
                        Response.Redirect("../admin/Dashboard.aspx");
                    }
                    else if (enterusername.Text == "andrewhew")
                    {
                        Response.Redirect("../admin/Dashboard.aspx");
                    }
                    else
                    {
                        Response.Redirect("Home.aspx");
                    }
                }
                else
                {
                    incorrect.Text = "Username or Password is incorrect.";
                }
            }
            else
            {
                incorrect.Text = "Username or Password is incorrect.";
            }

            con.Close();
        }

            
    }
}