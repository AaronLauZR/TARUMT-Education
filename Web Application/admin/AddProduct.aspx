<%@ Page Language="C#" MasterPageFile="AdminMaster.Master" AutoEventWireup="true" CodeBehind="AddProduct.aspx.cs" Inherits="Web_Assignment.admin.AddProduct" %>

<asp:Content ID="Content1" ContentPlaceHolderID="AddProduct" runat="Server">
    
    <div class="container mx-auto px-5">

        <h1 class="text-white text-3xl mb-3">Add Product</h1>
        <hr />

        <br />

        <!---------- Add Product Form ---------->
        <div class="text-white">

            
            <!----- Upload product image ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Image</label>
                <asp:FileUpload ID="FileUploadProductImage" runat="server"  />
                <br />
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorImageSelected" runat="server" ErrorMessage="No Image is selected" ControlToValidate="FileUploadProductImage" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>


            <!----- Product Name Input ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Name</label>
                <asp:TextBox ID="txtProductName" runat="server" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500" placeholder="Name"></asp:TextBox>
                <!--- Product Name Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorProductName" runat="server" ErrorMessage="Product Name is required" ControlToValidate="txtProductName" ForeColor="#FF3300"></asp:RequiredFieldValidator>    
            </div>

            <!----- Description Input ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Description</label>
                <textarea ID="txtDesc" runat="server" name="txtDesc" rows="4" class="block p-2.5 w-full text-sm text-gray-900 bg-gray-50 rounded-lg border border-gray-300 focus:ring-blue-500 focus:border-blue-500 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500" placeholder="Product Description"></textarea>
                <!--- Product Desc Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorProductDesc" runat="server" ErrorMessage="Product Description is required" ControlToValidate="txtDesc" ForeColor="#FF3300"></asp:RequiredFieldValidator>    
            </div>

            <!----- Price Input ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Price</label>
                <asp:TextBox ID="txtPrice" runat="server" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500" placeholder="Price"></asp:TextBox>
                
                <!--- Price Validator --->
                <div style="position: relative; margin: 0 auto; text-align: left">
                    
                    <asp:RequiredFieldValidator ID="RequiredFieldValidatorPrice" runat="server" ErrorMessage="Price is required" ControlToValidate="txtPrice" ForeColor="#FF3300"></asp:RequiredFieldValidator>
                    
                    <div style="position: absolute; top: 0; width: 100%">
                        <asp:RegularExpressionValidator ID="RegularExpressionValidatorPrice" runat="server" ErrorMessage="Please enter with price format (00.00)" ControlToValidate="txtPrice" ValidationExpression="^\d+[\.\,]\d{0,2}$" ForeColor="#FF3300"></asp:RegularExpressionValidator>
                    </div>

                </div>

            </div>

            <!----- Product Genre DropDownList ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Genre</label>         
                <asp:DropDownList ID="ddlGenre" runat="server" CssClass="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500">
                    <asp:ListItem>--- Select Genre ---</asp:ListItem>
                </asp:DropDownList>
                <!--- Genre Dropdown Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorGenre" runat="server" ErrorMessage="Genre must be chosen" InitialValue="--- Select Genre ---" ControlToValidate="ddlGenre" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>

            <!----- Product System DropDownList ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">System Requirement</label>
                <asp:DropDownList ID="ddlSystem" runat="server" CssClass="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500">
                    <asp:ListItem>--- Select System ---</asp:ListItem>
                </asp:DropDownList>
                 <!--- System Dropdown Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorSystem" runat="server" ErrorMessage="System must be chosen" InitialValue="--- Select System ---" ControlToValidate="ddlSystem" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>

            <br />

            <asp:Button ID="btnAddProduct" runat="server" Text="Add" class="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm w-full sm:w-auto px-5 py-2.5 text-center dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800" OnClick="btnAddProduct_Click" />
        </div>

    </div>

</asp:Content>
