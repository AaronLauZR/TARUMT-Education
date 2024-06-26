using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;

namespace Web_Assignment.client
{
    public partial class GameLibraryTailWind : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                displayOwnGame();
                retrieveOrderRecord();
                // order cart lazy to check whether the user got buy the product before or not
                // here to check and display only once if there is the same product
            }
        }

        protected void displayOwnGame()
        {
            SqlConnection con = new SqlConnection(strCon);
            string strSelect = "select * from Product p where p.productId IN(select p.productId from [dbo].[Order] c where c.userId= '" + Session["UserId"] + "')";
            SqlDataAdapter sda = new SqlDataAdapter(strSelect, con);
            DataTable dt = new DataTable();
            sda.Fill(dt);
            Repeater1.DataSource = dt;
            Repeater1.DataBind();
        }

        protected void retrieveOrderRecord()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                SqlCommand cmd = new SqlCommand("select * from [dbo].[Order] o, [dbo].[User] u where o.userId = u.userId AND o.userId='" + Session["UserId"] + "'", con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true)
                {
                    GridViewOrder.DataSource = dr;
                    GridViewOrder.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewOrder.DataSource = dr;
                    GridViewOrder.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }

        }

    }
}