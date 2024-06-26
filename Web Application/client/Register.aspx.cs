using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.Net.NetworkInformation;
using System.Reflection;

namespace Web_Assignment.client
{
    public partial class Register : System.Web.UI.Page
    {
        int temp = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (IsPostBack)
            {
                SqlConnection con = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);
                con.Open();
                string checkusername = "select count(*) from [User] where username='"+usernametxt.Text+"'";
                SqlCommand com = new SqlCommand(checkusername, con);
                temp = Convert.ToInt32(com.ExecuteScalar().ToString());

                if (temp == 1)
                {
                    userexist.Text = "Username already existed.";
                }

                con.Close();
            }
        }

        protected void username_TextChanged(object sender, EventArgs e)
        {

        }

        protected void CreateUserWizard1_CreatedUser(object sender, EventArgs e)
        {

        }

        protected void passwordtxt_TextChanged(object sender, EventArgs e)
        {

        }

        protected void register_Click1(object sender, EventArgs e)
        {

            SqlConnection con = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);

            if (temp == 0)
            {
                try
                {
                    Guid newGuid = Guid.NewGuid();

                    con.Open();

                    string insertQuery = "insert into [User] (userID, username, email, password, region, roleId) values (@Uid, @Uname, @Email, @Pass, @Reg, @Rol)";
                    SqlCommand com = new SqlCommand(insertQuery, con);

                    com.Parameters.AddWithValue("@Uid", newGuid.ToString());
                    com.Parameters.AddWithValue("@Uname", usernametxt.Text);
                    com.Parameters.AddWithValue("@Email", emailtxt.Text);
                    com.Parameters.AddWithValue("@Pass", passwordtxt.Text);
                    com.Parameters.AddWithValue("@Reg", regiontxt.SelectedItem.ToString());
                    com.Parameters.AddWithValue("@Rol", 1);

                    com.ExecuteNonQuery(); 

                    Response.Write("<script>alert('" + "Account Seccesfully Registered!" + "')</script>");
                }
                catch (Exception ex)
                {
                    Response.Write("Error: " + ex.ToString());
                }
                finally
                {
                    con.Close();
                }

            }

        }

        protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}