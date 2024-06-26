<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="ClientMasterTailWind.Master" CodeBehind="OrderCartTailWind.aspx.cs" Inherits="Web_Assignment.client.OrderCartTailWind" %>
<asp:Content ContentPlaceHolderID="cart" runat="server">
        
<br />

    <!------------------------------ Tailwind ------------------------------>
    <div class="container mx-auto px-10">
        <h1 style="color:white; margin-bottom:25px" class="text-3xl font-semibold">My Cart</h1>
        <div class="grid grid-cols-12 gap-4">
            <div class="col-span-8">

                <asp:Repeater ID="Repeater1" runat="server">
                <ItemTemplate>
                <div class="flex flex-row cart-layout">
                    <div class="flex flex-row items-center">
                        <%--<a href="#"><img src="../img/product/cyberpunk.jpg" alt="cyberpunk" class="w-48 h-56 rounded-lg"/></a>--%>
                        <asp:Image ID="Image1" runat="server" ImageUrl='<%#"~/img/product/productCover/"+Eval("image")%>' 
                            CssClass="w-48 h-56 rounded-lg"/>
                    </div>
                    
                    <div class="flex flex-col flex-wrap w-full ms-8 mt-2">
                        <div class="flex flex-row w-full justify-between text-white">
                            <%--<h4 class="text-2xl font-bold mb-0">Cyberpunk 2077</h4>--%>
                            <asp:label id="lblname" runat="server" text='<%#Eval("name") %>' cssclass="mb-0" 
                                style="font-size: 1.5em; font-weight: bold;">
                            </asp:label>
                            <%--<p class="mb-0 font-bold">RM 213.99</p>--%>
                            <asp:Label ID="lblPrice" runat="server" CssClass="mb-0 font-bold" 
                                Text='<%# "RM " + Eval("price") %>'>
                            </asp:Label>
                        </div>
                        
                        <div class="flex flex-row items-center w-full mt-16">
                            <img alt="iarc 18" class="max-w-full h-auto" src="../img/product/iarc_18.jpg"/>
                            <p class="font-bold text-base leading-loose mb-0 ml-3 text-white">
                                18+ <br/> 
                                Extreme Violence, Sex, Strong Language
                            </p>
                        </div>
                        
                        <div class="flex flex-row w-full mt-16 items-end">
                            <img alt="windows OS" class="w-5 h-6" src="../img/product/windows10.png"/>
                            <img alt="mac OS" class="w-6 h-6 ms-2" src="../img/product/macOS.png"/>
                            <div class="ml-auto">
                                <asp:LinkButton ID="btnRemove" runat="server" OnClick="btnRemove_Click" style="color:#F5F5F5; opacity:0.6; text-decoration:none">
                                    <i class="fa fa-trash" aria-hidden="true"></i>
                                    &nbsp;Remove</asp:LinkButton>
                            </div>
                        </div>
                    </div>
                </div>
                </ItemTemplate>
                </asp:Repeater>
            </div>
            
            <div class="col-span-4 md:ps-3">
                <h3 class="text-white mb-7 inline-block text-3xl font-normal">
                    Game Prices Summary
                </h3>
                
                <div class="grid grid-cols-1 md:grid-cols-2 gap-2 md:ms-0 mb-8">
                    <div class="md:col-auto">
                        <label for="inputPromo" class="block text-white text-sm mb-1 pb-0">
                            ENTER PROMO CODE
                        </label>
                        <asp:TextBox ID="txtPromo" runat="server" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm 
                            rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 
                            dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 
                            dark:focus:border-blue-500" placeholder="Promo Code"></asp:TextBox>
                    </div>
                    
                    <div class="md:col-auto">
                        <asp:Button ID="btnSubmit" runat="server" Text="Submit" OnClick="btnSubmit_Click"
                            CssClass="btn bg-blue-500 hover:bg-blue-700 text-white mt-5 rounded-lg px-4 py-2"/>
                    </div>
                </div>
  
                <div class="flex justify-between text-white">
                    <p class="mb-0">Subtotal</p>
                    <asp:Label ID="lblSubtotal" runat="server" CssClass="mb-2"></asp:Label>
                    <%--<p class="mb-0">RM 213.99</p>--%>
                </div>
                
                <div class="flex justify-between text-white">
                    <p class="mb-0">Sale Discount</p>
                    <%--<p class="mb-0">-RM 0.00</p>--%>
                    <asp:Label ID="lblDiscount" runat="server" CssClass="mb-2" Text="-RM 0.00"></asp:Label>
                </div>

                <hr class="mb-4 border-0 border-b-2 border-white opacity-60">

                <div class="flex justify-between text-white mb-4">
                    <p class="mb-0">Total Price</p>
                    <%--<p class="mb-0 font-bold">RM 213.99</p>--%>
                    <asp:Label ID="lblTotal" runat="server" CssClass="mb-4 fw-bolder"></asp:Label>
                </div>
                
                <div class="grid">
                    <asp:LinkButton ID="LinkButton1" runat="server" class="btn bg-primary text-white 
                        py-3 text-lg w-full bg-indigo-600 hover:bg-indigo-700  shadow-sm text-base" 
                        OnClick="btnCheckout_Click" >Checkout</asp:LinkButton>
                </div>
                
                <div class="mt-6 flex justify-center text-center text-sm text-gray-500">
                    <span>or&nbsp&nbsp</span>         
                    <asp:LinkButton ID="LinkButton2" runat="server" class="font-medium text-indigo-600 hover:text-indigo-500" 
                        PostBackUrl="~/client/Product.aspx">Continue Shopping</asp:LinkButton>
                </div>
            </div>
        </div>
    </div>

    <br />
    <br />


</asp:Content>