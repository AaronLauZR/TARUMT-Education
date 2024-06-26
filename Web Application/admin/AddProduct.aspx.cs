using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web_Assignment.admin
{
    public partial class AddProduct : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindReaderData_Genre();
                BindReaderData_System();

            }


        }

        private void BindReaderData_Genre()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement
                string strSelect = "Select * from [dbo].[Genre]";

                SqlCommand cmd = new SqlCommand(strSelect, con);
                con.Open();
                SqlDataReader rdr = cmd.ExecuteReader();
                while (rdr.Read())
                {
                    ListItem genreList = new ListItem(rdr["genreName"].ToString(), rdr["genreId"].ToString());
                    
                    ddlGenre.Items.Add(genreList);

                }
            }
           

        }

        private void BindReaderData_System()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement
                string strSelect = "Select * from [dbo].[System]";

                SqlCommand cmd = new SqlCommand(strSelect, con);
                con.Open();
                SqlDataReader rdr = cmd.ExecuteReader();
                while (rdr.Read())
                {
                    ListItem systemList = new ListItem(rdr["os"] + ", " + rdr["processor"] + ", " + rdr["storage"], rdr["systemId"].ToString());

                    ddlSystem.Items.Add(systemList);

                }
            }


        }

        protected void btnAddProduct_Click(object sender, EventArgs e)
        {
            
            //System Input
            String nameInput = txtProductName.Text;
            String descInput = txtDesc.InnerText;
            double priceInput = double.Parse(txtPrice.Text);
            int genreInput = int.Parse(ddlGenre.SelectedValue);
            int systemInput = int.Parse(ddlSystem.SelectedValue);
            String imageInput = null;

            if (FileUploadProductImage.HasFile)
            {

                string strname = FileUploadProductImage.FileName.ToString();
                FileUploadProductImage.PostedFile.SaveAs(Server.MapPath("~/img/product/productCover/") + strname);
                imageInput = strname;


                SqlConnection con;

                con = new SqlConnection(strCon);
                con.Open();

                //SQL Statement
                string strAddProduct = "insert into Product (image, name, description, price, genreId, systemId) values('" + imageInput + "', '" + nameInput + "', '" + descInput + "', '" + priceInput + "', '" + genreInput + "', '" + systemInput + "')";

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAddProduct, con);

                int rowAffected = cmd.ExecuteNonQuery();
                con.Close();

                if (rowAffected > 0)
                {
                    Response.Write("<script>alert('Successfully add product')</script>");
                }
                else
                {
                    Response.Write("<script>alert('Failed to add product')</script>");
                }
                Server.Transfer("ManageProduct.aspx");

            }
            else
            {
                imageInput = null;
            }

            


        }
    }
}