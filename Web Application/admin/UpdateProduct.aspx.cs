using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Web_Assignment.client;

namespace Web_Assignment.admin
{
    public partial class UpdateProduct : System.Web.UI.Page
    {

        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;


        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                retrieveData();
                BindReaderData_Genre();
                BindReaderData_System();

            }
        }

        private void retrieveData()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement
                
                con.Open();

                string strRetrieveProduct = "Select * from [dbo].[Product] where productId ='" + Request.QueryString["id"] + "'";
                SqlCommand cmd = new SqlCommand(strRetrieveProduct, con);
                SqlDataReader dr = cmd.ExecuteReader();

                while (dr.Read())
                {

                    if (string.IsNullOrEmpty(dr.GetValue(1).ToString()))
                    {
                        labelImageExisting.Text = "Currently no product image";
                    }
                    else
                    {
                        labelImageExisting.Text = "Product image: " + dr.GetValue(1).ToString();

                    }

                    txtProductName.Text = dr.GetValue(2).ToString();
                    txtDesc.InnerText= dr.GetValue(3).ToString();
                    txtPrice.Text = dr.GetValue(4).ToString();
                    
                }
               
            }

        }

        private void BindReaderData_Genre()
        {
            ListItem genreList = new ListItem();

            using (SqlConnection con = new SqlConnection(strCon))
            {

                
                //SQL Statement for retrieving Genre to edit
                string strRetrieveGenre = "Select * from Product p, Genre g where p.genreId = g.genreId AND p.productId='" + Request.QueryString["id"] + "'";

                SqlCommand cmd_retrieveGenre = new SqlCommand(strRetrieveGenre, con);
                con.Open();
                SqlDataReader rdr_retrieveGenre = cmd_retrieveGenre.ExecuteReader();

                while (rdr_retrieveGenre.Read())
                {
                    genreList = new ListItem(rdr_retrieveGenre["genreName"].ToString(), rdr_retrieveGenre["genreId"].ToString());

                    ddlGenre.Items.Add(genreList);
                }

                con.Close();
                

                //SQL Statement for retrieving other Genre 
                string strSelectGenre = "Select * from Genre g where g.genreId NOT IN(select p.genreId from Product p where p.productId='" + Request.QueryString["id"] + "')";

                SqlCommand cmd = new SqlCommand(strSelectGenre, con);
                con.Open();
                SqlDataReader rdr = cmd.ExecuteReader();

                while (rdr.Read())
                {
                    genreList = new ListItem(rdr["genreName"].ToString(), rdr["genreId"].ToString());

                    ddlGenre.Items.Add(genreList);

                }

                con.Close();
                
            }


        }

        private void BindReaderData_System()
        {

            ListItem systemList= new ListItem();

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement for retrieving System to edit
                string strRetrieveSystem = "Select * from Product p, System s where p.systemId = s.systemId AND p.productId='" + Request.QueryString["id"] + "'";

                SqlCommand cmd_retrieveSystem = new SqlCommand(strRetrieveSystem, con);
                con.Open();
                SqlDataReader rdr_retrieveSystem = cmd_retrieveSystem.ExecuteReader();
                while (rdr_retrieveSystem.Read())
                {
                    systemList = new ListItem(rdr_retrieveSystem["os"] + ", " + rdr_retrieveSystem["processor"] + ", " + rdr_retrieveSystem["storage"], rdr_retrieveSystem["systemId"].ToString());

                    ddlSystem.Items.Add(systemList);

                }

                con.Close();

                //SQL Statement
                string strSelectSystem = "Select * from System s where s.systemId NOT IN(select p.systemId from Product p where p.productId='" + Request.QueryString["id"] + "')";

                SqlCommand cmd = new SqlCommand(strSelectSystem, con);
                con.Open();
                SqlDataReader rdr = cmd.ExecuteReader();
                while (rdr.Read())
                {
                    systemList = new ListItem(rdr["os"] + ", " + rdr["processor"] + ", " + rdr["storage"], rdr["systemId"].ToString());

                    ddlSystem.Items.Add(systemList);

                }

                con.Close();
            }


        }

        protected void btnUpdateProduct_Click(object sender, EventArgs e)
        {
            //System Input
            String nameInput = txtProductName.Text;
            String descInput = txtDesc.InnerText;
            double priceInput = double.Parse(txtPrice.Text);
            int genreInput = int.Parse(ddlGenre.SelectedValue);
            int systemInput = int.Parse(ddlSystem.SelectedValue);
            String imageInput = null;

            using (SqlConnection con = new SqlConnection(strCon))
            {
                if (FileUploadProductImage.HasFile)
                {
                    string strname = FileUploadProductImage.FileName.ToString();
                    FileUploadProductImage.PostedFile.SaveAs(Server.MapPath("~/img/product/productCover/") + strname);
                    imageInput = strname;
                    labelImageExisting.Text = null;

                    con.Open();

                    //SQL Statement (Update Image)
                    string strUpdateProduct = "update Product SET image='" + imageInput + "', name='" + nameInput + "', description='" + descInput + "', price='" + priceInput + "', genreId='" + genreInput + "', systemId='" + systemInput + "' where productId='" + Request.QueryString["id"] + "'";

                    //Need sqlcommand to execute sql query
                    SqlCommand cmd = new SqlCommand(strUpdateProduct, con);

                    int rowAffected = cmd.ExecuteNonQuery();

                    if (rowAffected > 0)
                    {
                        Response.Write("<script>alert('Successfully update product')</script>");
                    }
                    else
                    {
                        Response.Write("<script>alert('Failed to update product')</script>");
                    }
                    con.Close();

                }
                else
                {
                    con.Open();

                    //SQL Statement (No Update Image)
                    string strUpdateProduct = "update Product SET name='" + nameInput + "', description='" + descInput + "', price='" + priceInput + "', genreId='" + genreInput + "', systemId='" + systemInput + "' where productId='" + Request.QueryString["id"] + "'";

                    //Need sqlcommand to execute sql query
                    SqlCommand cmd = new SqlCommand(strUpdateProduct, con);

                    int rowAffected = cmd.ExecuteNonQuery();
                    
                    if (rowAffected > 0)
                    {
                        Response.Write("<script>alert('Successfully update product')</script>");
                    }
                    else
                    {
                        Response.Write("<script>alert('Failed to update product')</script>");
                    }
                    con.Close();
                }
                
                Server.Transfer("ManageProduct.aspx");


            }




        }
    }
}