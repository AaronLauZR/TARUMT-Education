using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;

namespace Web_Assignment.admin
{
    public partial class AddGenre : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;


        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                displayGenre();
                
            }
            
        }

        protected void displayGenre()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                SqlCommand cmd = new SqlCommand("select * from genre", con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true) 
                { 
                    GridViewGenre.DataSource= dr;
                    GridViewGenre.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewGenre.DataSource = dr;
                    GridViewGenre.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }
        }


        protected void btnAddGenre_Click(object sender, EventArgs e)
        {

            //Genre Input
            String genreInput = txtGenre.Text;


            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                //SQL Statement

                string strAddGenre = "insert into Genre (genreName) values('" + genreInput + "')";

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAddGenre, con);

                cmd.ExecuteNonQuery();

                con.Close();

                Response.Write("<script>alert('Successfully add new genre into database') </script>");
                displayGenre();   

            }
            

        }


        protected void GridViewGenre_RowEditing(object sender, GridViewEditEventArgs e)
        {
            GridViewGenre.EditIndex = e.NewEditIndex;
            displayGenre();
        }

        protected void GridViewGenre_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {

            int id = Convert.ToInt32(GridViewGenre.DataKeys[e.RowIndex].Value.ToString());
            string genre = ((TextBox)GridViewGenre.Rows[e.RowIndex].Cells[1].Controls[0]).Text;

            using(SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strUpdateGenre = "update genre set genreName='" + genre + "' where genreId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strUpdateGenre, con);
                
                int rowAffected = cmd.ExecuteNonQuery();
                
                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully update genre into database')</script>");
                    GridViewGenre.EditIndex = -1;
                    displayGenre();
                }

            }

        }

        protected void GridViewGenre_RowCancelingEdit(object sender, GridViewCancelEditEventArgs e)
        {
            GridViewGenre.EditIndex = -1;
            displayGenre();
        }

        protected void GridViewGenre_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            int id = Convert.ToInt32(GridViewGenre.DataKeys[e.RowIndex].Value.ToString());

            using(SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strDeleteGenre = "delete from genre where genreId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strDeleteGenre, con);
                
                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully delete genre')</script>");
                    GridViewGenre.EditIndex = -1;
                    displayGenre();
                }
            }

        }
    }
}