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
    public partial class ManageRole : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                displayRole();
            }
        }

        protected void displayRole()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                SqlCommand cmd = new SqlCommand("select * from Role", con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true)
                {
                    GridViewRole.DataSource = dr;
                    GridViewRole.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewRole.DataSource = dr;
                    GridViewRole.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }
        }


        protected void btnAddRole_Click(object sender, EventArgs e)
        {
            //Genre Input
            String roleInput = txtRole.Text;


            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                //SQL Statement

                string strAddRole = "insert into Role (roleName) values('" + roleInput + "')";

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAddRole, con);

                cmd.ExecuteNonQuery();

                con.Close();

                Response.Write("<script>alert('Successfully add new role into database') </script>");
                displayRole();

            }


        }


        protected void GridViewRole_RowEditing(object sender, GridViewEditEventArgs e)
        {
            GridViewRole.EditIndex = e.NewEditIndex;
            displayRole();
        }

        protected void GridViewRole_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {
            int id = Convert.ToInt32(GridViewRole.DataKeys[e.RowIndex].Value.ToString());
            string role = ((TextBox)GridViewRole.Rows[e.RowIndex].Cells[1].Controls[0]).Text;

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strUpdateRole = "update Role set roleName='" + role + "' where roleId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strUpdateRole, con);

                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully update role into database')</script>");
                    GridViewRole.EditIndex = -1;
                    displayRole();
                }

            }

        }

        protected void GridViewRole_RowCancelingEdit(object sender, GridViewCancelEditEventArgs e)
        {
            GridViewRole.EditIndex = -1;
            displayRole();
        }

        protected void GridViewRole_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            int id = Convert.ToInt32(GridViewRole.DataKeys[e.RowIndex].Value.ToString());

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strDeleteRole = "delete from Role where roleId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strDeleteRole, con);

                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully delete role')</script>");
                    GridViewRole.EditIndex = -1;
                    displayRole();
                }
            }

        }
    }
}