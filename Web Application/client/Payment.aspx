<%@ Page Language="C#" MasterPageFile="ClientMaster.Master" AutoEventWireup="true" CodeBehind="Payment.aspx.cs" Inherits="Web_Assignment.client.Payment" %>




<asp:Content ID="Content1" ContentPlaceHolderID="Payment" runat="Server">
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ho+j7jyWK8fNQe+A12Hb8AhRq26LrZ/JpcUGGOn+Y7RsweNrtN/tE3MoK7ZeZDyx" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-aFq/bzH65dt+w6FI2ooMVUpc+21e0SRygnTpmBvdBgSdnuTN7QbdgL+OapgHtvPp" crossorigin="anonymous">
    <html>

        <div class="container mb-5">

        <div class="row">

            <!---------- Payment Methods ---------->
            <div class="col-md-8" style="color: white; padding: 15px 15px 15px 15px">
                <h3>Payment Methods</h3>
                <hr />

                <div class="form-group">
                    <small>Please select the payment method.</small>
                    <br /><br />

                    <asp:DropDownList ID="ddlPaymentMethod" runat="server" CssClass="form-control" AutoPostBack="True" OnSelectedIndexChanged="ddlPaymentMethod_SelectedIndexChanged">
                        <asp:ListItem>Online Banking</asp:ListItem>
                        <asp:ListItem>Touch N Go</asp:ListItem>
                    </asp:DropDownList>

                </div>

                <br />

                <!----- Payment Methods - Online Banking ----->
                <div id="olineBanking" runat="server">
                    
                    <h3>Online Banking Payment</h3>
                    <hr />

                    <small>Please enter your online banking details.</small>
                    <br /><br />

                    <div class="form-group">
                        
                        <label>Bank Type</label>
                        <asp:DropDownList ID="ddlBankType" runat="server" CssClass="form-control">
                            <asp:ListItem>Maybank</asp:ListItem>
                            <asp:ListItem>Public Bank</asp:ListItem>
                            <asp:ListItem>Hong Leong</asp:ListItem>
                        </asp:DropDownList>
                    </div>

                    <br />

                    <div class="form-group">
                        <label>Account Number</label>
                        <asp:TextBox ID="txtAccountNumber" runat="server" CssClass="form-control" placeholder="Account Number"></asp:TextBox>
                    </div>

                    <br />

                    <div class="form-group">
                        <label>Account Password</label>
                        <asp:TextBox ID="txtAccountPassword" runat="server" CssClass="form-control" placeholder="Password" TextMode="Password"></asp:TextBox>
                    </div>

                </div> 
                

                <!----- Payment Methods - Touch N Go ----->
                <div id="touchNGo" class="touchNGo" runat="server" style="display: none;">

                    <h3>Touch N Go Payment</h3>
                    <hr />

                    <small>Please enter your Touch N Go payment details.</small>
                    <br /><br />

                    <div class="form-group">
                        <label>Contact Number</label>
                        <asp:TextBox ID="txtContactNumber" runat="server" CssClass="form-control" placeholder="xxx-xxxxxxx"></asp:TextBox>
                    </div>

                    <br />

                    <div class="form-group">
                        <label>PIN Number</label>
                        <asp:TextBox ID="txtPin" runat="server" CssClass="form-control" placeholder="Password" TextMode="Number"></asp:TextBox>
                    </div>

                </div>

            </div>

            <!---------- Payment Details ---------->
            <div class="col-md-4" style="padding: 15px 15px 15px 15px">

                <div class="card" style="background-color: #1A1A1A; color: white; border: 1px solid white; border-radius: 10px;">
                        
                    <div class="card-body">
                        <h3>Your Order</h3>
                        <hr style="color: white;"/>

                        <!----- Game Image ----->
                        <div style="border: 1px solid white; border-radius: 10px; padding: 5px 5px 5px 5px">
                            <div style="display: inline-block;">
                                <img src="../img/product/dead_space.jpg" alt="Alternate Text" style="width: 60px; height: 80px;" />
                            </div>
                            <div style="display: inline-block;">
                                <span>Dead Space III</span>
                                <br />
                                <span>RM 100.00</span>
                            </div>
                        </div>

                        <br />

                        <!----- Price ----->
                        <div class="row">
                            <div class="col">
                                <p class="font-weight-bold">Price: </p>
                            </div>
                            <div class="col" style="text-align: right;">
                                <p>RM 100.00</p>
                            </div>
                        </div>

                        <!----- Taxes ----->
                        <div class="row">
                            <div class="col">
                                <p class="font-weight-bold">Taxes:</p>
                            </div>
                            <div class="col" style="text-align: right;">
                                <p>Calculate at checkout</p>
                            </div>
                        </div>

                        <!----- Subtotal ----->
                        <div class="row">
                            <div class="col">
                                <h5 class="font-weight-bold">Subtotal:</h5>
                            </div>
                            <div class="col" style="text-align: right;">
                                <h5>RM 100.00</h5>
                            </div>
                        </div>

                        <br />
                        <div style="text-align: center;">
                            <asp:Button ID="btnPayNow" runat="server" Text="Pay Now" CssClass="btn btn-success btn-lg btn-block" OnClick="btnPayNow_Click" />
                        </div>
                            

                    </div>

                </div>
            </div>
        </div>
     
    </div>


    <!---------- The Modal ---------->
    <div id="receiptModal" class="modal modalShadowReceipt" runat="server">
	    <div class="modalReceipt">
            <!--
		    <span class="close">&times;</span>
            -->

            <div class="modal-body">
                <h2 class="modal-title" style="font-weight: bold;">Thank You.</h2>
                <h4>Hi Jennie!</h4>
                <p>Thanks for your purchase from Galaxy</p>

                <h3>INVOICE ID: F137996701</h3>
                    
                <hr />

                <div class="row" style="text-align: left;">
                    <div class="col-md-6">
                        <h4>Order ID: </h4>
                        <h5>12345</h5>
                    </div>
                    <div class="col-md-6">
                        <h4>Bill To: </h4>
                        <h5>Jennie123@gmail.com</h5>
                    </div>
                </div>

                <div class="row" style="text-align: left;">
                    <div class="col-md-6">
                        <h4>Order Date: </h4>
                        <h5>April 1, 2023</h5>
                    </div>
                    <div class="col-md-6">
                        <h4>Source: </h4>
                        <h5>Galaxy</h5>
                    </div>
                </div>

                <br />

                <h4 style="text-align: left;">Order</h4>

                <div class="table-responsive-xl">
                    <table class="table table-hover m-1">
                        <thead>
                        <tr style="background-color: lightgrey;">
                            <th scope="col">No</th>
                            <th scope="col">Description</th>
                            <th scope="col">Publisher:</th>
                            <th scope="col">Price:</th>
                        </tr>
                        </thead>
                        <tbody>
                        <tr>
                            <th scope="row">1</th>
                            <td>Cyberpunk</td>
                            <td>Studio</td>
                            <td>RM 170.00</td>
                        </tr>
                        <tr>
                            <th scope="row">2</th>
                            <td>Dark Soul III</td>
                            <td>Studio</td>
                            <td>RM 110.00</td>
                        </tr>
                        <tr>
                            <th scope="row">3</th>
                            <td>Left 4 Dead 2</td>
                            <td>Studio</td>
                            <td>RM 12.00</td>
                        </tr>
                        </tbody>
                    </table>
                </div>

                <div style="text-align: right;">
                    <h4>Total: <span>RM 213.99</span></h4>
                </div>

                <asp:Button ID="btnConfirmInvoice" runat="server" Text="Confirm Invoice" CssClass="btn btn-success btn-lg btn-block" OnClick="btnConfirmInvoice_Click" />

            </div>
                    
        </div>

    </div>
    <!---------- The Modal ---------->
       

    <!---------- Payment Message ---------->
    <div id="paymentMessage" class="modal modalShadowPayment" runat="server">
        <div class="modalPayment" runat="server">
                
            <asp:LinkButton ID="LinkButtonClose" runat="server" OnClick="LinkButtonClose_Click">
                <span id="close" class="close" runat="server" style="color: white;">&times;</span>
            </asp:LinkButton>
		        
                

            <div>
                <asp:Label ID="lblPaymentMessage" runat="server" Text="Payment Successfully!" style="color: white;"></asp:Label>
                <br />
                <asp:LinkButton ID="LinkButtonViewReceipt" runat="server" OnClick="LinkButtonViewReceipt_Click" style="color: white; text-decoration: underline;">View Receipt</asp:LinkButton>

            </div>

        </div>
    </div>
    
	    


    <!---------- Payment Message ---------->
    
</asp:Content>


        

