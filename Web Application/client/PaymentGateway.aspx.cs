using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;

namespace Web_Assignment.client
{
    public partial class PaymentGateway : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            //DataTable dt = new DataTable();
           // dt = (DataTable)Session["buyitems"];
            //int nrow = dt.Rows.Count;
            int i = 0;
            int orderId = 0001;
            decimal totalprice = 0;
            decimal finaltotal = 0;
            string orderNumber;

            Decimal.TryParse(Session["buyTotal"].ToString(), out totalprice);
            //while (i < nrow)
            //{
            //    totalprice = totalprice + Convert.ToDecimal(dt.Rows[i]["totalprice"].ToString());
            //    i = i + 1;
            //}
            decimal tax = totalprice * 0.06M;
            string taxFormatted = tax.ToString("0.00");
            finaltotal = totalprice + tax;
            string finalTotalFormatted = finaltotal.ToString("0.00");
            Session["finaltotal"] = finalTotalFormatted.ToString();

            /*string mycon = "Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\\Galaxy.mdf;Integrated Security=True;";
            SqlConnection scon = new SqlConnection(mycon);
            string myquery = "SELECT MAX(orderId) FROM [Order]";
            SqlCommand cmd = new SqlCommand(myquery, scon);
            scon.Open();
            object result = cmd.ExecuteScalar();
            orderId = 0;
            if (result != null && result != DBNull.Value)
            {
                orderId = Convert.ToInt32(result);
            }
            orderId++; // Increment the order ID for the next order
            scon.Close();*/

            //here we implement Paypal
            Session["orderId"] = orderId.ToString();

            Response.Write("<form action='https://www.sandbox.paypal.com/cgi-bin/webscr' method='post' name='buyCredits' id='buyCredits'>");
            Response.Write("<input type='hidden' name='cmd' value='_xclick'>");
            Response.Write("<input type='hidden' name='business' value='sb-8sw5l25586641@business.example.com'>"); // fixed value of paypalemail
            Response.Write("<input type='hidden' name='currency_code' value='MYR'>");
            Response.Write("<input type='hidden' name='item_name' value='Order ID: " + orderId + "'>");
            Response.Write("<input type='hidden' name='item_number' value='0'>");
            Response.Write("<input type='hidden' name='amount' value='" + Session["finaltotal"].ToString() + "'>");
            Response.Write("<input type='hidden' name='return' value='https://localhost:44371/client/PaymentSuccess.aspx?order=" + orderId.ToString() + "'>");
            Response.Write("</form>");

            Response.Write("<script type='text/javascript'>");
            Response.Write("document.getElementById('buyCredits').submit();");
            Response.Write("</script>");
        }

        public decimal grandtotal()
        {
            //DataTable dt = new DataTable();
            //dt = (DataTable)Session["buyitems"];
            //int nrow = dt.Rows.Count;
            int i = 0;
            decimal totalprice = 0;

           // while (i < nrow)
           // {
            //    totalprice = totalprice + Convert.ToDecimal(dt.Rows[i]["totalprice"].ToString());
            //    i = i + 1;
            //}
            return totalprice;
        }
    }
}
