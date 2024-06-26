using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;
using System.Reflection.Emit;

namespace Web_Assignment.client
{
    public partial class Home : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                SqlDataAdapter adapter = new SqlDataAdapter("Select * from Product", con);
                DataTable dt = new DataTable();
                adapter.Fill(dt);
                RepeaterDisplayProduct.DataSource = dt;
                RepeaterDisplayProduct.DataBind();
            }

            
        }

        protected void RepeaterDisplayProduct_ItemCommand(object source, RepeaterCommandEventArgs e)
        {
            if (e.CommandName == "ViewDetails")
            {
                // Get the ID of the product that was clicked
                string productId = e.CommandArgument.ToString();

                // Redirect to the product details page with the ID in the query string
                Response.Redirect("ProductDetails.aspx?ID=" + productId);
            }
        }
    }
}