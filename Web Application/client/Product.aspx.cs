using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using static System.Net.Mime.MediaTypeNames;

namespace Web_Assignment.client
{
    public partial class Product : System.Web.UI.Page
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
                //SQL Statement

                con.Open();

                String strDisplayProduct = "select p.image, p.name, p.description, p.price, g.genreName, s.os, s.processor, s.storage from Product p, Genre g, System s where p.genreId = g.genreId AND p.systemId = s.systemId AND productId='" + Request.QueryString["id"] + "'";
                SqlCommand cmd = new SqlCommand(strDisplayProduct, con);
                SqlDataReader dr = cmd.ExecuteReader();
                

                while (dr.Read())
                {
                    string imagePath = "../img/product/productCover/" + dr.GetValue(0).ToString(); // Replace with the actual image path
                    productImage1.ImageUrl = imagePath;
                    productImage2.ImageUrl = imagePath;

                    txtProductName1.Text = dr.GetValue(1).ToString();
                    txtProductName2.Text = dr.GetValue(1).ToString();
                    txtProductDescription.Text = dr.GetValue(2).ToString();
                    txtProductPrice.Text = dr.GetValue(3).ToString();
                    txtProductGenre.Text = dr.GetValue(4).ToString();
                    txtSystem.Text = dr.GetValue(5).ToString() + ", " + dr.GetValue(6).ToString() + ", " + dr.GetValue(7).ToString();
                }

                con.Close();

            }
        }

        protected void btnAddCart_Click(object sender, EventArgs e)
        {
            String productID = Request.QueryString["id"];
            string userId = (string)Session["UserId"];

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                //SQL Statement

                string strAddCart = "insert into Cart (productId, userId) values('" + productID + "', '"+ Session["UserId"]+ "')";
                string getCartData = "SELECT * FROM Cart WHERE productId = @productId AND userId = @userId";

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAddCart, con);

                SqlCommand command = new SqlCommand(getCartData, con);
                command.Parameters.AddWithValue("@productId", productID);
                command.Parameters.AddWithValue("@userId", userId);
                SqlDataReader reader = command.ExecuteReader();

                //Validation
                if (reader.HasRows)
                {
                    Response.Write("<script>alert('Your product has added into cart!') </script>");
                }
                else
                {
                    reader.Close();
                    cmd.ExecuteNonQuery();
                    Response.Write("<script>alert('Successfully Add Product into Cart!') </script>");
                }
                con.Close();

            }
        }
    }
}