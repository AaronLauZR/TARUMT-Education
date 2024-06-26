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
    public partial class AddSystem : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                displaySystem();
            }
        }

        protected void displaySystem()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                SqlCommand cmd = new SqlCommand("select * from System", con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true)
                {
                    GridViewSystem.DataSource = dr;
                    GridViewSystem.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewSystem.DataSource = dr;
                    GridViewSystem.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }
        }

        protected void btnAddSystem_Click(object sender, EventArgs e)
        {
            //System Input
            String operatingSystemInput = txtOperatingSystem.Text;
            String processorInput = txtProcessor.Text;
            String storageInput = txtStorage.Text;


            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                //SQL Statement

                string strAddSystem = "insert into System (os, processor, storage) values('" + operatingSystemInput + "', '" + processorInput + "', '" + storageInput + "')";

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAddSystem, con);

                cmd.ExecuteNonQuery();

                con.Close();

                Response.Write("<script>alert('Successfully add new system into database') </script>");
                displaySystem();

            }

        }

        protected void GridViewSystem_RowEditing(object sender, GridViewEditEventArgs e)
        {
            GridViewSystem.EditIndex = e.NewEditIndex;
            displaySystem();
        }

        protected void GridViewSystem_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {
            int id = Convert.ToInt32(GridViewSystem.DataKeys[e.RowIndex].Value.ToString());
            string operatingSystem = ((TextBox)GridViewSystem.Rows[e.RowIndex].Cells[1].Controls[0]).Text;
            string processor = ((TextBox)GridViewSystem.Rows[e.RowIndex].Cells[2].Controls[0]).Text;
            string storage = ((TextBox)GridViewSystem.Rows[e.RowIndex].Cells[3].Controls[0]).Text;

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                string strUpdateSystem = "update System set os='" + operatingSystem + "', processor='" + processor + "', storage='" + storage + "' where systemId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strUpdateSystem, con);

                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully update system into database')</script>");
                    GridViewSystem.EditIndex = -1;
                    displaySystem();
                }


            }
        }

        protected void GridViewSystem_RowCancelingEdit(object sender, GridViewCancelEditEventArgs e)
        {
            GridViewSystem.EditIndex = -1;
            displaySystem();
        }

        protected void GridViewSystem_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            int id = Convert.ToInt32(GridViewSystem.DataKeys[e.RowIndex].Value.ToString());

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strDeleteSystem = "delete from System where systemId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strDeleteSystem, con);

                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully delete genre')</script>");
                    GridViewSystem.EditIndex = -1;
                    displaySystem();
                }
            }
        }

        
    }
}