using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Services.Description;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;

namespace Web_Assignment.client
{
    public partial class UserProfile : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                retrieveData();
            }
        }

        protected void changepassword_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnection con = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);
                SqlDataAdapter sda = new SqlDataAdapter("select password from [User] where password = '" + currentpass.Text + "'", con);
                DataTable dt = new DataTable();
                sda.Fill(dt);

                if (dt.Rows.Count.ToString() == "1")
                {
                    if (newpass.Text == confirmpass.Text)
                    {
                        con.Open();
                        SqlCommand cmd = new SqlCommand("Update [User] set password = '" + confirmpass.Text + "' where password = '" + currentpass.Text + "'", con);
                        cmd.ExecuteNonQuery();
                        con.Close();

                        Response.Write("<script>alert('" + "Password has been succesfully changed!" + "')</script>");
                        errormessage.Text = "Password has been succesfully changed!";
                        errormessage.ForeColor = System.Drawing.Color.Green;
                    }
                }
                else
                {
                    errormessage.Text = "Invalid password! Please try again!";
                    errormessage.ForeColor = System.Drawing.Color.Red;
                }
            }
            catch (Exception ex)
            {
                errormessage.Text = "Error: " + ex.Message.ToString();
            }
        }

        protected void delete_Click(object sender, EventArgs e)
        {
            string delusername = Session["UserName"].ToString();

            SqlConnection con = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);
            SqlCommand cmd = new SqlCommand("delete from [User] where username = '" + delusername + "'", con);
            con.Open();
            cmd.ExecuteNonQuery();

            con.Close();

            Session["UserName"] = null;
            Response.Redirect("../client/Login.aspx");
        }

        private void retrieveData()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement

                con.Open();

                string strRetrieveProduct = "Select * from [User] where username ='" + Session["UserName"] + "'";
                SqlCommand cmd = new SqlCommand(strRetrieveProduct, con);
                SqlDataReader dr = cmd.ExecuteReader();

                while (dr.Read())
                {

                    Label1.Text = dr.GetValue(1).ToString();
                    Label2.Text = dr.GetValue(3).ToString();
                    AccountID.Text = dr.GetValue(0).ToString();
                    Label3.Text = dr.GetValue(5).ToString();
                }

            }
        }
    }
}