using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web_Assignment.admin
{
    public partial class UpdateRole : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                displayUser();
                BindReaderData_User();
                BindReaderData_Role();
            }
        }

        protected void displayUser()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strDisplayUser = "select * from [dbo].[User] u, [dbo].[Role] r where u.roleId = r.roleId";
                SqlCommand cmd = new SqlCommand(strDisplayUser, con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true)
                {
                    GridViewUser.DataSource = dr;
                    GridViewUser.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewUser.DataSource = dr;
                    GridViewUser.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }
        }


        private void BindReaderData_User()
        {
            ListItem userList = new ListItem();

            using (SqlConnection con = new SqlConnection(strCon))
            {

                //SQL Statement for retrieving User 
                string strSelectUser = "Select * from [dbo].[User]";

                SqlCommand cmd = new SqlCommand(strSelectUser, con);
                con.Open();
                SqlDataReader rdr = cmd.ExecuteReader();

                while (rdr.Read())
                {
                    userList = new ListItem(rdr["username"].ToString(), rdr["userId"].ToString());

                    ddlUser.Items.Add(userList);

                }

                con.Close();

            }


        }

        private void BindReaderData_Role()
        {

            ListItem roleList = new ListItem();

            using (SqlConnection con = new SqlConnection(strCon))
            {

                //SQL Statement for retrieving Role
                string strSelectRole = "Select * from [dbo].[Role]";

                SqlCommand cmd = new SqlCommand(strSelectRole, con);
                con.Open();
                SqlDataReader rdr = cmd.ExecuteReader();

                while (rdr.Read())
                {
                    roleList = new ListItem(rdr["roleName"].ToString(), rdr["roleId"].ToString());

                    ddlRole.Items.Add(roleList);

                }

                con.Close();

            }


        }


        protected void btnAssignRole_Click(object sender, EventArgs e)
        {

            //Assign Role to user Input
            string userId = ddlUser.SelectedValue;
            int roleId = int.Parse(ddlRole.SelectedValue);

            using (SqlConnection con = new SqlConnection(strCon))
            {

                con.Open();

                //SQL Statement (Update Image)
                string strAssignRole = "update [dbo].[User] SET roleId='" + roleId + "' where userId='" + userId + "'";

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAssignRole, con);

                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully assign role to user')</script>");
                }
                else
                {
                    Response.Write("<script>alert('Failed to assign role to user')</script>");
                }
                con.Close();


                Server.Transfer("Dashboard.aspx");
            }

        }

    }


}