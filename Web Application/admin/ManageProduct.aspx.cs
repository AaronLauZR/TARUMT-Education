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
    public partial class ManageProduct : System.Web.UI.Page
    {

        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                displayProduct();
            }
        }

        protected void displayProduct()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strDisplayProduct = "select * from Product p, Genre g, System s where p.genreId = g.genreId AND p.systemId = s.systemId";
                SqlCommand cmd = new SqlCommand(strDisplayProduct, con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true)
                {
                    GridViewProduct.DataSource = dr;
                    GridViewProduct.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewProduct.DataSource = dr;
                    GridViewProduct.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }
        }

        protected void GridViewProduct_RowEditing(object sender, GridViewEditEventArgs e)
        {
            GridViewRow row = GridViewProduct.Rows[e.NewEditIndex];
            int id = Convert.ToInt32(GridViewProduct.DataKeys[row.RowIndex].Value);

            Response.Redirect("UpdateProduct.aspx?id=" + id.ToString());

        }

        protected void GridViewProduct_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            int id = Convert.ToInt32(GridViewProduct.DataKeys[e.RowIndex].Value.ToString());

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                String strDeleteProduct = "delete from Product where productId='" + id + "'";
                SqlCommand cmd = new SqlCommand(strDeleteProduct, con);

                int rowAffected = cmd.ExecuteNonQuery();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully delete product')</script>");
                    GridViewProduct.EditIndex = -1;
                    displayProduct();
                }
                else
                {
                    Response.Write("<script>alert('Failed to delete product')</script>");
                    GridViewProduct.EditIndex = -1;
                    displayProduct();
                }
            }
        }


    }
}